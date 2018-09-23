namespace FileDateChanger
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnBrowse = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.dtpCurrent = new System.Windows.Forms.DateTimePicker();
            this.dtpNew = new System.Windows.Forms.DateTimePicker();
            this.lbCurrent = new System.Windows.Forms.Label();
            this.lbNew = new System.Windows.Forms.Label();
            this.btnSet = new System.Windows.Forms.Button();
            this.tbFileName = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(12, 12);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(75, 23);
            this.btnBrowse.TabIndex = 0;
            this.btnBrowse.Text = "Browse";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // dtpCurrent
            // 
            this.dtpCurrent.CustomFormat = "MM/dd/yyyy hh:mm:ss";
            this.dtpCurrent.Enabled = false;
            this.dtpCurrent.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtpCurrent.Location = new System.Drawing.Point(94, 45);
            this.dtpCurrent.Name = "dtpCurrent";
            this.dtpCurrent.Size = new System.Drawing.Size(150, 20);
            this.dtpCurrent.TabIndex = 1;
            // 
            // dtpNew
            // 
            this.dtpNew.CustomFormat = "MM/dd/yyyy hh:mm:ss";
            this.dtpNew.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtpNew.Location = new System.Drawing.Point(94, 71);
            this.dtpNew.Name = "dtpNew";
            this.dtpNew.Size = new System.Drawing.Size(150, 20);
            this.dtpNew.TabIndex = 2;
            // 
            // lbCurrent
            // 
            this.lbCurrent.AutoSize = true;
            this.lbCurrent.Location = new System.Drawing.Point(12, 48);
            this.lbCurrent.Name = "lbCurrent";
            this.lbCurrent.Size = new System.Drawing.Size(70, 13);
            this.lbCurrent.TabIndex = 3;
            this.lbCurrent.Text = "Current Time:";
            // 
            // lbNew
            // 
            this.lbNew.AutoSize = true;
            this.lbNew.Location = new System.Drawing.Point(11, 74);
            this.lbNew.Name = "lbNew";
            this.lbNew.Size = new System.Drawing.Size(58, 13);
            this.lbNew.TabIndex = 4;
            this.lbNew.Text = "New Time:";
            // 
            // btnSet
            // 
            this.btnSet.Location = new System.Drawing.Point(251, 44);
            this.btnSet.Name = "btnSet";
            this.btnSet.Size = new System.Drawing.Size(61, 47);
            this.btnSet.TabIndex = 5;
            this.btnSet.Text = "Set New";
            this.btnSet.UseVisualStyleBackColor = true;
            this.btnSet.Click += new System.EventHandler(this.btnSet_Click);
            // 
            // tbFileName
            // 
            this.tbFileName.Location = new System.Drawing.Point(94, 13);
            this.tbFileName.Name = "tbFileName";
            this.tbFileName.ReadOnly = true;
            this.tbFileName.Size = new System.Drawing.Size(218, 20);
            this.tbFileName.TabIndex = 6;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 103);
            this.Controls.Add(this.tbFileName);
            this.Controls.Add(this.btnSet);
            this.Controls.Add(this.lbNew);
            this.Controls.Add(this.lbCurrent);
            this.Controls.Add(this.dtpNew);
            this.Controls.Add(this.dtpCurrent);
            this.Controls.Add(this.btnBrowse);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "File Date Changer";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.DateTimePicker dtpCurrent;
        private System.Windows.Forms.DateTimePicker dtpNew;
        private System.Windows.Forms.Label lbCurrent;
        private System.Windows.Forms.Label lbNew;
        private System.Windows.Forms.Button btnSet;
        private System.Windows.Forms.TextBox tbFileName;
    }
}

