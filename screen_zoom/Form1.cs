using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace zoom
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
        }

        private void trackBarMag_Scroll(object sender, EventArgs e)
        {
            labelMag.Text = "Magnification: " + trackBarMag.Value.ToString();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            Point cur = Control.MousePosition;
            if (cur.X >= this.Location.X && cur.X <= this.Location.X + this.Width && cur.Y >= this.Location.Y && cur.Y <= this.Location.Y + this.Height)
            {
                pictureBox.Visible = false;
                return;
            }
            pictureBox.Visible = true;
            Size sizeSrc = new Size(pictureBox.ClientRectangle.Width / trackBarMag.Value, pictureBox.ClientRectangle.Height / trackBarMag.Value);
            Size sizeDst = new Size(pictureBox.ClientRectangle.Width, pictureBox.ClientRectangle.Height);
            Point topleft = new Point(cur.X - sizeSrc.Width / 2, cur.Y - sizeSrc.Height / 2);
            if (topleft.X < 0) topleft.X = 0;
            if (topleft.X > Screen.PrimaryScreen.Bounds.Width - sizeSrc.Width) topleft.X = Screen.PrimaryScreen.Bounds.Width - sizeSrc.Width;
            if (topleft.Y < 0) topleft.Y = 0;
            if (topleft.Y > Screen.PrimaryScreen.Bounds.Height - sizeSrc.Height) topleft.Y = Screen.PrimaryScreen.Bounds.Height - sizeSrc.Height;
            Bitmap bmSrc = new Bitmap(sizeSrc.Width, sizeSrc.Height);
            using (Graphics gSrc = Graphics.FromImage(bmSrc))
            {
                gSrc.CopyFromScreen(topleft, new Point(0, 0), bmSrc.Size);
            }
            Bitmap bmDst = new Bitmap(sizeDst.Width, sizeDst.Height);
            using (Graphics gDst = Graphics.FromImage(bmDst))
            {
                gDst.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
                gDst.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                gDst.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.None;
                gDst.DrawImage(bmSrc, 0, 0, bmDst.Size.Width, bmDst.Size.Height);
                if (checkBoxColor.Checked)
                {
                    Color c = bmDst.GetPixel(sizeDst.Width / 2, sizeDst.Height / 2);
                    gDst.DrawLine(Pens.Red, new Point(sizeDst.Width / 2 - 20, sizeDst.Height / 2), new Point(sizeDst.Width / 2 + 20, sizeDst.Height / 2));
                    gDst.DrawLine(Pens.Red, new Point(sizeDst.Width / 2, sizeDst.Height / 2 - 20), new Point(sizeDst.Width / 2, sizeDst.Height / 2 + 20));
                    panelColor.BackColor = c;
                    labelColor.Text = "R: " + c.R.ToString() + " G: " + c.G.ToString() + " B: " + c.B.ToString();
                    labelColor.ForeColor = Color.FromArgb(255 - c.R, 255 - c.G, 255 - c.B);
                    panelColor.Visible = true;
                }
                else
                {
                    panelColor.Visible = false;
                }
            }
            pictureBox.Image = bmDst;
            bmSrc.Dispose();
        }

    }
}
