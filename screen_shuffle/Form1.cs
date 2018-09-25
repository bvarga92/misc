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

namespace ScreenShuffle
{
    public partial class Form1 : Form
    {
        private const int N = 4;

        private void shuffle(int[] arr)
        {
            Random rnd = new Random();
            for (int i = arr.Length; i > 0; i--)
            {
                int r = rnd.Next(i);
                int temp = arr[r];
                arr[r] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Bitmap bmScreen = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height);
            Graphics gScreen = Graphics.FromImage(bmScreen);
            gScreen.CopyFromScreen(new Point(), new Point(), bmScreen.Size);
            Bitmap bmShuffled = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height);
            Graphics gShuffled = Graphics.FromImage(bmShuffled);
            int[] dst = new int[N * N];
            for (int i = 0; i < N * N; i++) dst[i] = i;
            shuffle(dst);
            int segmW = Screen.PrimaryScreen.Bounds.Width / N;
            int segmH = Screen.PrimaryScreen.Bounds.Height / N;
            for (int row = 0; row < N; row++)
            {
                for (int col = 0; col < N; col++)
                {
                    int dstX = dst[row * N + col] % N;
                    int dstY = dst[row * N + col] / N;
                    Rectangle rectSrc = new Rectangle(col * segmW, row * segmH, segmW, segmH);
                    Rectangle rectDst = new Rectangle(dstX * segmW, dstY * segmH, segmW, segmH);
                    gShuffled.DrawImage(bmScreen, rectDst, rectSrc, GraphicsUnit.Pixel);
                }
            }

            pictureBox.Image = bmShuffled;
            this.Opacity = 100;
        }
    }
}
