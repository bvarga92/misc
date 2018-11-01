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
using System.Security.Cryptography;

namespace ScreenChangeAlarm
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool EnumWindows(EnumWindowsProc enumProc, IntPtr lParam);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowText(IntPtr hWnd, StringBuilder lpText, int nMaxCount);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool IsWindowVisible(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr GetWindowRect(IntPtr hWnd, out RECT rect);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr GetWindowThreadProcessId(IntPtr hWnd, out uint dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, uint dwProcessId);

        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool PrintWindow(IntPtr hWnd, IntPtr hdcBlt, int nFlags);

        [StructLayout(LayoutKind.Sequential)]
        private struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        private delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

        private byte[] hashPrev = null;
        private IntPtr hWnd;

        private void listWindows()
        {
            StringBuilder str = new StringBuilder(1024);
            EnumWindows(delegate(IntPtr hWnd, IntPtr lParam)
            {
                if (IsWindowVisible(hWnd) && hWnd != this.Handle && GetWindowText(hWnd, str, str.Capacity) != 0 && !str.ToString().Equals(""))
                {
                    lbApps.Items.Add(str.ToString());
                }
                return true;
            }, IntPtr.Zero);
        }

        private void lbApps_DoubleClick(object sender, EventArgs e)
        {
            if (lbApps.SelectedIndex < 0) return;
            hWnd = FindWindow(null, lbApps.SelectedItem.ToString());
            if (!hWnd.Equals(IntPtr.Zero))
            {
                MessageBox.Show("Starting watch for window " + hWnd.ToString() + ".", "Success");
                timer1.Enabled = true;
                btnStop.Enabled = true;
                lbApps.Enabled = false;
            }
            else
            {
                MessageBox.Show("Cannot select the process. (Maybe it has been closed?) Please update the list.", "Error");
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
            listWindows();
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            btnStop.Enabled = false;
            lbApps.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (hWnd == IntPtr.Zero) return;
            /* uj screenshot */
            RECT rc;
            GetWindowRect(hWnd, out rc);
            Bitmap bmp = new Bitmap(rc.Right - rc.Left, rc.Bottom - rc.Top, System.Drawing.Imaging.PixelFormat.Format32bppRgb);
            Graphics g = Graphics.FromImage(bmp);
            IntPtr hdcBitmap = g.GetHdc();
            PrintWindow(hWnd, hdcBitmap, 0);
            g.ReleaseHdc(hdcBitmap);
            g.Dispose();
            /* hash szamitasa */
            System.Drawing.ImageConverter ic = new System.Drawing.ImageConverter();
            byte[] bytes = (byte[])ic.ConvertTo(bmp, typeof(byte[]));
            SHA256Managed sha = new SHA256Managed();
            byte[] hash = sha.ComputeHash(bytes);
            /* osszehasonlitas */
            if (hashPrev != null)
            {
                for (int i = 0; i < hash.Length; i++)
                {
                    if (hash[i] != hashPrev[i])
                    {
                        System.Media.SystemSounds.Asterisk.Play();
                        break;
                    }
                }
            }
            /* frissites a kovetkezo utemre */
            hashPrev = hash;
        }

    }
}
