using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace FileDateChanger
{
    public partial class Form1 : Form
    {
        private string fileName;
        private bool fileSelected = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dtpCurrent.Value = dtpNew.Value = DateTime.Now;            
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                fileSelected = true;
                fileName = openFileDialog1.FileName;
                tbFileName.Text = fileName;
                dtpCurrent.Value = File.GetLastWriteTime(fileName);
            }
            else
            {
                fileSelected = false;
                tbFileName.Text = "";
            }
        }

        private void btnSet_Click(object sender, EventArgs e)
        {
            if (fileSelected)
            {
                File.SetLastWriteTime(fileName, dtpNew.Value);
                File.SetLastAccessTime(fileName, dtpNew.Value);
                File.SetCreationTime(fileName, dtpNew.Value);
                dtpCurrent.Value = File.GetLastWriteTime(fileName);
            }
            else
            {
                MessageBox.Show("No file is selected.","Error");
            }
        }
    }
}
