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

namespace WinObjectGrabber
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll")]
        private static extern IntPtr WindowFromPoint(Point point);
        [DllImport("user32.dll")]
        private static extern bool ScreenToClient(IntPtr hWnd, ref Point lpPoint);
        [DllImport("user32.dll")]
        static extern IntPtr ChildWindowFromPoint(IntPtr hWndParent, Point point);
        [DllImport("user32.dll")]
        private static extern int GetClassName(IntPtr hWnd, StringBuilder lpClassName, int nMaxCount);
        [DllImport("user32.dll")]
        private static extern int GetWindowText(IntPtr hWnd, StringBuilder lpText, int nMaxCount);
        [DllImport("user32.dll")]
        private static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
        [DllImport("user32.dll")]
        private static extern bool IsWindow(IntPtr hWnd);
        [DllImport("User32.dll")]
        private static extern IntPtr GetParent(IntPtr hWnd);
        [DllImport("user32.dll")]
        private static extern bool IsWindowEnabled(IntPtr hWnd);
        [DllImport("user32.dll")]
        private static extern bool IsWindowVisible(IntPtr hWnd);
        [DllImport("user32.dll")]
        private static extern IntPtr SendMessage(IntPtr hWnd, uint uMsg, IntPtr wParam, string lParam);
        [DllImport("user32.dll")]
        private static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        [DllImport("user32.dll")]
        private static extern bool EnableWindow(IntPtr hWnd, bool bEnable);
        [DllImport("user32.dll")]
        private static extern bool MoveWindow(IntPtr hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint);

        [StructLayout(LayoutKind.Sequential)]
        private struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        private Bitmap bmGreen, bmRed;
        private IntPtr hWnd;
        private StringBuilder str = new StringBuilder(512);

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            float cX = pictureBox.ClientRectangle.Width / 2;
            float cY = pictureBox.ClientRectangle.Height / 2;
            float r = Math.Min(pictureBox.ClientRectangle.Width / 2, pictureBox.ClientRectangle.Height / 2);
            bmGreen = new Bitmap(pictureBox.ClientRectangle.Width, pictureBox.ClientRectangle.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
            Graphics g = Graphics.FromImage(bmGreen);
            g.Clear(SystemColors.Control);
            g.FillEllipse(Brushes.ForestGreen, cX - r, cY - r, r + r, r + r);
            bmRed = new Bitmap(pictureBox.ClientRectangle.Width, pictureBox.ClientRectangle.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
            g = Graphics.FromImage(bmRed);
            g.Clear(SystemColors.Control);
            g.FillEllipse(Brushes.Red, cX - r, cY - r, r + r, r + r);
            pictureBox.Image = bmGreen;
        }

        private void pictureBox_MouseEnter(object sender, EventArgs e)
        {
            Cursor = Cursors.Cross;
        }

        private void pictureBox_MouseLeave(object sender, EventArgs e)
        {
            Cursor = Cursors.Arrow;
        }

        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            pictureBox.Image = bmRed;
            timer.Enabled = true;
        }

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            pictureBox.Image = bmGreen;
            timer.Enabled = false;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            Point cur = Control.MousePosition;
            IntPtr temp = WindowFromPoint(cur);
            do
            {
                hWnd = temp;
                if (ScreenToClient(temp, ref cur)) temp = ChildWindowFromPoint(temp, cur);
            } while (!temp.Equals(IntPtr.Zero) && hWnd != temp);
            tbHandle.Text = hWnd.ToString();
            if (GetClassName(hWnd, str, str.Capacity) != 0)
                tbClass.Text = str.ToString();
            else
                tbClass.Text = "";
            if (GetWindowText(hWnd, str, str.Capacity) != 0)
                tbText.Text = str.ToString();
            else
                tbText.Text = "";
            RECT rect;
            if (GetWindowRect(hWnd, out rect))
            {
                if (IsWindow(hWnd))
                {
                    Point p = new Point(rect.Left, rect.Top);
                    ScreenToClient(GetParent(hWnd), ref p);
                    tbLeft.Text = p.X.ToString();
                    tbTop.Text = p.Y.ToString();
                    Console.WriteLine("hehe");
                }
                else
                {
                    tbLeft.Text = rect.Left.ToString();
                    tbTop.Text = rect.Top.ToString();
                }
                tbHeight.Text = (rect.Bottom - rect.Top).ToString();
                tbWidth.Text = (rect.Right - rect.Left).ToString();
            }
            else
            {
                tbLeft.Text = tbTop.Text = tbHeight.Text = tbWidth.Text = "";
            }
            if (IsWindowEnabled(hWnd))
                cbEnabled.Checked = true;
            else
                cbEnabled.Checked = false;
            if (IsWindowVisible(hWnd))
                cbVisible.Checked = true;
            else
                cbVisible.Checked = false;
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            if (!hWnd.Equals(IntPtr.Zero))
            {
                SendMessage(hWnd, 0x000C, IntPtr.Zero, tbText.Text); //WM_SETTEXT
                SendMessage(hWnd, 0x00B9, new IntPtr(1), null); //EM_SETMODIFY
                if (cbVisible.Checked)
                    ShowWindow(hWnd, 1);
                else
                    ShowWindow(hWnd, 0);
                EnableWindow(hWnd, cbEnabled.Checked);
                MoveWindow(hWnd, Int32.Parse(tbLeft.Text), Int32.Parse(tbTop.Text), Int32.Parse(tbWidth.Text), Int32.Parse(tbHeight.Text), true);
            }
        }
    }
}
