using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EyesOnYou
{
    public partial class Form1 : Form
    {

        private Bitmap bmWhite, bmBlack;
        private Point p;
        private bool moving = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.DimGray;
            this.TransparencyKey = Color.DimGray;
            this.Location = new Point(Screen.PrimaryScreen.Bounds.Width - this.Size.Width, 10);
            float cX = pbLW.ClientRectangle.Width / 2;
            float cY = pbLW.ClientRectangle.Height / 2;
            float r = Math.Min(cX, cY) - 1;
            bmWhite = new Bitmap(pbLW.ClientRectangle.Width, pbLW.ClientRectangle.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
            Graphics gW = Graphics.FromImage(bmWhite);
            gW.Clear(Color.DimGray);
            gW.FillEllipse(Brushes.White, cX - r, cY - r, r + r, r + r);
            gW.DrawEllipse(Pens.Black, cX - r, cY - r, r + r, r + r);
            pbLW.Image = pbRW.Image = bmWhite;
            cX = pbLB.ClientRectangle.Width / 2;
            cY = pbLB.ClientRectangle.Height / 2;
            r = Math.Min(cX, cY);
            bmBlack = new Bitmap(pbLB.ClientRectangle.Width, pbLB.ClientRectangle.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
            Graphics gB = Graphics.FromImage(bmBlack);
            gB.Clear(Color.White);
            gB.FillEllipse(Brushes.Black, cX - r, cY - r, r + r, r + r);
            pbLB.Image = pbRB.Image = bmBlack;
        }

        private void pbLW_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                p = Control.MousePosition;
                timer.Enabled = false;
                moving = true;
            }
        }

        private void pbLW_MouseMove(object sender, MouseEventArgs e)
        {
            if (moving)
            {
                Point m = Control.MousePosition;
                this.Location = new Point(this.Location.X - p.X + m.X, this.Location.Y - p.Y + m.Y);
                p = m;
            }
        }

        private void pbLW_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left) moving = false;
            timer.Enabled = true;
        }

        private void pbRW_MouseDown(object sender, MouseEventArgs e)
        {
            pbLW_MouseDown(sender, e);
        }

        private void pbRW_MouseMove(object sender, MouseEventArgs e)
        {
            pbLW_MouseMove(sender, e);
        }

        private void pbRW_MouseUp(object sender, MouseEventArgs e)
        {
            pbLW_MouseUp(sender, e);
        }

        private void pbLB_MouseDown(object sender, MouseEventArgs e)
        {
            pbLW_MouseDown(sender, e);
        }

        private void pbLB_MouseMove(object sender, MouseEventArgs e)
        {
            pbLW_MouseMove(sender, e);
        }

        private void pbLB_MouseUp(object sender, MouseEventArgs e)
        {
            pbLW_MouseUp(sender, e);
        }

        private void pbRB_MouseDown(object sender, MouseEventArgs e)
        {
            pbLW_MouseDown(sender, e);
        }

        private void pbRB_MouseMove(object sender, MouseEventArgs e)
        {
            pbLW_MouseMove(sender, e);
        }

        private void pbRB_MouseUp(object sender, MouseEventArgs e)
        {
            pbLW_MouseUp(sender, e);
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            Point m = Control.MousePosition;
            Point cL = new Point(this.Location.X + pbLW.Left + pbLW.ClientRectangle.Width / 2, this.Location.Y + pbLW.Top + pbLW.ClientRectangle.Height / 2);
            Point cR = new Point(this.Location.X + pbRW.Left + pbRW.ClientRectangle.Width / 2, this.Location.Y + pbRW.Top + pbRW.ClientRectangle.Height / 2);
            int r = 24;
            int rL = m.X - cL.X;
            int rR = m.X - cR.X;
            if (rL > r)
                rL = r;
            else if (rL < -r)
                rL = -r;
            if (rR > r)
                rR = r;
            else if (rR < -r)
                rR = -r;
            pbLB.Left = cL.X - this.Location.X + rL - 10;
            pbRB.Left = cR.X - this.Location.X + rR - 10;
            pbLB.Top = (int)Math.Round(Math.Sin(Math.Atan2(m.Y - cL.Y, Math.Abs(m.X - cL.X))) * r) + cL.Y - this.Location.Y - 10;
            pbRB.Top = (int)Math.Round(Math.Sin(Math.Atan2(m.Y - cL.Y, Math.Abs(m.X - cL.X))) * r) + cR.Y - this.Location.Y - 10;
        }
    }
}
