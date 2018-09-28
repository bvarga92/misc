using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ProcMemChanger
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowText(IntPtr hWnd, StringBuilder lpText, int nMaxCount);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool IsWindowVisible(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr GetWindow(IntPtr hWnd, uint uCmd);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr GetWindowThreadProcessId(IntPtr hWnd, out uint dwProcessId);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool EnumWindows(EnumWindowsProc enumProc, IntPtr lParam);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, uint dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool CloseHandle(IntPtr hProcess);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint dwSize, out int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint dwSize, out int lpNumberOfBytesRead);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern int VirtualQueryEx(IntPtr hProcess, IntPtr lpAddress, out MEMORY_BASIC_INFORMATION32 lpBuffer, int dwLength);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern void GetSystemInfo(out SYSTEM_INFO Info);

        private delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION32
        {
            public IntPtr BaseAddress;
            public IntPtr AllocationBase;
            public uint AllocationProtect;
            public IntPtr RegionSize;
            public uint State;
            public uint Protect;
            public uint Type;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION64
        {
            public ulong BaseAddress;
            public ulong AllocationBase;
            public int AllocationProtect;
            public int __alignment1;
            public ulong RegionSize;
            public int State;
            public int Protect;
            public int Type;
            public int __alignment2;
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct SYSTEM_INFO
        {
            public ushort processorArchitecture;
            ushort __reserved;
            public uint PageSize;
            public IntPtr MinimumApplicationAddress;
            public IntPtr MaximumApplicationAddress;
            public IntPtr ActiveProcessorMask;
            public uint NumberOfProcessors;
            public uint ProcessorType;
            public uint AllocationGranularity;
            public ushort ProcessorLevel;
            public ushort ProcessorRevision;
        }

        private const int PROCESS_ALL_ACCESS = 0x001F0FFF;
        private const int PAGE_EXECUTE_READ = 0x00000020;
        private const int PAGE_NOACCESS = 0x00000001;
        private const int PAGE_READONLY = 0x00000002;
        private const int PAGE_GUARD = 0x00000100;
        private const int MEM_COMMIT = 0x00001000;

        private StringBuilder str = new StringBuilder(1024);
        private IntPtr hProc = IntPtr.Zero;
        private List<long> addrList = new List<long>();
        private byte[] byteBuffer = new byte[1024];

        private void listWindows()
        {
            EnumWindows(delegate(IntPtr hWnd, IntPtr lParam)
            {
                if (IsWindowVisible(hWnd) && hWnd != this.Handle && GetWindowText(hWnd, str, str.Capacity) != 0 && !str.ToString().Equals(""))
                {
                    lbApps.Items.Add(str.ToString());
                }
                return true;
            }, IntPtr.Zero);
        }

        private int pos(byte[] arr, byte[] pattern, int offset, int len)
        {
            for (int i = offset; i <= len - pattern.Length; i++)
            {
                int k = 0;
                for (int j = 0; j < pattern.Length; j++) if (arr[i + j] == pattern[j]) k++;
                if (k == pattern.Length) return i;
            }
            return -1;
        }

        private void searchValue(ulong value, bool newSearch)
        {
            byte[] pattern = new byte[4];
            pattern[0] = (byte)(value & 0x000000FF);
            pattern[1] = (byte)((value & 0x0000FF00) >> 8);
            pattern[2] = (byte)((value & 0x00FF0000) >> 16);
            pattern[3] = (byte)((value & 0xFF000000) >> 24);
            MEMORY_BASIC_INFORMATION32 mbi = new MEMORY_BASIC_INFORMATION32();
            int mbiSize = Marshal.SizeOf(typeof(MEMORY_BASIC_INFORMATION32));
            SYSTEM_INFO si = new SYSTEM_INFO();
            GetSystemInfo(out si);
            if (newSearch)
            {
                IntPtr currentAddress = si.MinimumApplicationAddress;
                while ((long)currentAddress < (long)si.MaximumApplicationAddress)
                {
                    if (VirtualQueryEx(hProc, currentAddress, out mbi, mbiSize) == mbiSize)
                    {
                        if (mbi.State == MEM_COMMIT && mbi.Protect != PAGE_READONLY && mbi.Protect != PAGE_EXECUTE_READ && mbi.Protect != PAGE_GUARD && mbi.Protect != PAGE_NOACCESS && (long)mbi.RegionSize > 0)
                        {
                            if (byteBuffer.Length < (long)mbi.RegionSize)
                                byteBuffer = new byte[(long)mbi.RegionSize];
                            int bytesRead;
                            ReadProcessMemory(hProc, mbi.BaseAddress, byteBuffer, (uint)mbi.RegionSize, out bytesRead);
                            int offset = 0;
                            while (offset < (long)mbi.RegionSize)
                            {
                                int p = pos(byteBuffer, pattern, offset, (int)mbi.RegionSize);
                                if (p < 0)
                                    break;
                                else
                                {
                                    addrList.Add((long)mbi.BaseAddress + p);
                                    offset = p + 1;
                                }
                            }
                        }
                    }
                    currentAddress = (IntPtr)((long)mbi.BaseAddress + (long)mbi.RegionSize);
                    backgroundWorker.ReportProgress((int)(((long)currentAddress * 100) / (long)(si.MaximumApplicationAddress)));
                }
            }
            else
            {
                int k = addrList.Count;
                for (int i = addrList.Count - 1; i >= 0; i--)
                {
                    int bytesRead;
                    ReadProcessMemory(hProc, (IntPtr)addrList[i], byteBuffer, 4, out bytesRead);
                    if (pos(byteBuffer, pattern, 0, 4) < 0) addrList.RemoveAt(i);
                    backgroundWorker.ReportProgress((100 * (k - i)) / k);
                }
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            listWindows();
        }

        private void btnFind_Click(object sender, EventArgs e)
        {
            lbApps.Items.Clear();
            hProc = IntPtr.Zero;
            listWindows();
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Always run this program with administrator privileges!\n\nSelect an application from the list by double clicking it. You can update the list by clicking the Find Windows button.\n\nYou can list memory addresses containing the specified value by clicking the Search button. A subsequent search will only look for the value at the addresses found by the previous search, this way you can find changing values such as timers. You can start a new search by clicking the Clear button.\n\nBy clicking the Modify Value button, you can write a new value to the address selected from the list.", "Usage");
        }

        private void rbDecimal_CheckedChanged(object sender, EventArgs e)
        {
            tbSearchValue.Text = "";
        }

        private void tbSearchValue_KeyPress(object sender, KeyPressEventArgs e)
        {
            int radix = rbDecimal.Checked ? 10 : 16;
            if (e.KeyChar == (char)13)
            {
                btnSearch_Click(sender, e);
            }
            else
            {
                if (radix == 10)
                {
                    if ((e.KeyChar < '0' || e.KeyChar > '9') && e.KeyChar != '\b') e.KeyChar = '\0';
                }
                else
                {
                    if ((e.KeyChar < '0' || e.KeyChar > '9') && (e.KeyChar < 'A' || e.KeyChar > 'F') && (e.KeyChar < 'a' || e.KeyChar > 'f') && e.KeyChar != '\b') e.KeyChar = '\0';
                }
            }
        }

        private void tbMax_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < '0' || e.KeyChar > '9') && e.KeyChar != '\b') e.KeyChar = '\0';
        }

        private void lbApps_DoubleClick(object sender, EventArgs e)
        {
            if (lbApps.SelectedIndex < 0) return;
            IntPtr hWnd = FindWindow(null, lbApps.SelectedItem.ToString());
            if (!hWnd.Equals(IntPtr.Zero))
            {
                uint procID;
                GetWindowThreadProcessId(hWnd, out procID);
                hProc = OpenProcess(PROCESS_ALL_ACCESS, false, procID);
                if (hProc.Equals(IntPtr.Zero))
                {
                    MessageBox.Show("Failed to open process.", "Error");
                    this.Text = "Process Memory Changer";
                }
                else
                {
                    this.Text = "Process Memory Changer - [process #" + procID.ToString() + " selected]";
                }
            }
            else
            {
                MessageBox.Show("Cannot select the process. (Maybe it has been closed?) Please update the list.", "Error");
                this.Text = "Process Memory Changer";
            }
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            if (tbSearchValue.Text.Equals(""))
                MessageBox.Show("Please specify a value to look for.", "Error");
            else if (hProc.Equals(IntPtr.Zero))
                MessageBox.Show("Please select a process from the list.", "Error");
            else
            {
                btnSearch.Enabled = false;
                btnClear.Enabled = false;
                tbSearchValue.Enabled = false;
                ulong value = Convert.ToUInt64(tbSearchValue.Text, rbDecimal.Checked ? 10 : 16);
                bool newSearch = (addrList.Count == 0);
                backgroundWorker.RunWorkerAsync(argument: new Tuple<ulong, bool>(value, newSearch));
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            addrList.Clear();
            lbAddr.Items.Clear();
            groupBox3.Text = "Search Results: 0";
            timer.Enabled = false;
        }

        private void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            btnSearch.Enabled = false;
            btnClear.Enabled = false;
            tbSearchValue.Enabled = false;
            ulong value = ((Tuple<ulong, bool>)e.Argument).Item1;
            bool newSearch = ((Tuple<ulong, bool>)e.Argument).Item2;
            searchValue(value, newSearch);
        }

        private void backgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBar.Value = e.ProgressPercentage;
        }

        private void backgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            progressBar.Value = 0;
            groupBox3.Text = "Search Results: " + addrList.Count.ToString();
            if (addrList.Count <= Convert.ToInt64(tbMax.Text))
            {
                lbAddr.Items.Clear();
                for (int i = 0; i < addrList.Count; i++) lbAddr.Items.Add("0x" + addrList[i].ToString("X8"));
            }
            btnSearch.Enabled = true;
            btnClear.Enabled = true;
            tbSearchValue.Enabled = true;
            timer.Enabled = true;
        }

        private void btnModify_Click(object sender, EventArgs e)
        {
            if (lbAddr.SelectedIndex < 0)
                MessageBox.Show("Please select an address from the list.", "Error");
            else if (tbResValue.Text.Equals(""))
                MessageBox.Show("Please type in a value.", "Error");
            else if (timer.Enabled == false)
            {
                ulong value = Convert.ToUInt64(tbResValue.Text);
                byteBuffer[0] = (byte)(value & 0x000000FF);
                byteBuffer[1] = (byte)((value & 0x0000FF00) >> 8);
                byteBuffer[2] = (byte)((value & 0x00FF0000) >> 16);
                byteBuffer[3] = (byte)((value & 0xFF000000) >> 24);
                int bytesWritten;
                WriteProcessMemory(hProc, (IntPtr)Convert.ToUInt64(lbAddr.SelectedItem.ToString(), 16), byteBuffer, 4, out bytesWritten);
                timer.Enabled = true;
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if (lbAddr.SelectedIndex >= 0)
            {
                int bytesRead;
                ReadProcessMemory(hProc, (IntPtr)Convert.ToUInt64(lbAddr.SelectedItem.ToString(), 16), byteBuffer, 4, out bytesRead);
                ulong value = (ulong)(byteBuffer[0] + (byteBuffer[1] << 8) + (byteBuffer[2] << 16) + (byteBuffer[3] << 24));
                tbResValue.Text = value.ToString();
            }
        }

        private void tbResValue_Enter(object sender, EventArgs e)
        {
            timer.Enabled = false;
        }

        private void tbResValue_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)13)
                btnModify_Click(sender, e);
            else if ((e.KeyChar < '0' || e.KeyChar > '9') && e.KeyChar != '\b')
                e.KeyChar = '\0';
        }
    }
}
