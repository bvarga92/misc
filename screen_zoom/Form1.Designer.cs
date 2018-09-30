namespace zoom
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
            this.components = new System.ComponentModel.Container();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.checkBoxColor = new System.Windows.Forms.CheckBox();
            this.labelMag = new System.Windows.Forms.Label();
            this.trackBarMag = new System.Windows.Forms.TrackBar();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.panelColor = new System.Windows.Forms.Panel();
            this.labelColor = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMag)).BeginInit();
            this.panelColor.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox
            // 
            this.pictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox.Location = new System.Drawing.Point(0, 0);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(362, 275);
            this.pictureBox.TabIndex = 0;
            this.pictureBox.TabStop = false;
            // 
            // checkBoxColor
            // 
            this.checkBoxColor.AutoSize = true;
            this.checkBoxColor.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.checkBoxColor.Location = new System.Drawing.Point(12, 131);
            this.checkBoxColor.Name = "checkBoxColor";
            this.checkBoxColor.Size = new System.Drawing.Size(113, 20);
            this.checkBoxColor.TabIndex = 1;
            this.checkBoxColor.Text = "Color Analysis";
            this.checkBoxColor.UseVisualStyleBackColor = true;
            // 
            // labelMag
            // 
            this.labelMag.AutoSize = true;
            this.labelMag.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelMag.Location = new System.Drawing.Point(12, 52);
            this.labelMag.Name = "labelMag";
            this.labelMag.Size = new System.Drawing.Size(100, 16);
            this.labelMag.TabIndex = 2;
            this.labelMag.Text = "Magnification: 2";
            // 
            // trackBarMag
            // 
            this.trackBarMag.Location = new System.Drawing.Point(12, 76);
            this.trackBarMag.Maximum = 12;
            this.trackBarMag.Minimum = 1;
            this.trackBarMag.Name = "trackBarMag";
            this.trackBarMag.Size = new System.Drawing.Size(149, 45);
            this.trackBarMag.TabIndex = 3;
            this.trackBarMag.Value = 2;
            this.trackBarMag.Scroll += new System.EventHandler(this.trackBarMag_Scroll);
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 20;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // panelColor
            // 
            this.panelColor.Controls.Add(this.labelColor);
            this.panelColor.Location = new System.Drawing.Point(0, 0);
            this.panelColor.Name = "panelColor";
            this.panelColor.Size = new System.Drawing.Size(135, 35);
            this.panelColor.TabIndex = 4;
            this.panelColor.Visible = false;
            // 
            // labelColor
            // 
            this.labelColor.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelColor.Location = new System.Drawing.Point(0, 9);
            this.labelColor.Name = "labelColor";
            this.labelColor.Size = new System.Drawing.Size(135, 16);
            this.labelColor.TabIndex = 0;
            this.labelColor.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(362, 275);
            this.Controls.Add(this.panelColor);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.trackBarMag);
            this.Controls.Add(this.labelMag);
            this.Controls.Add(this.checkBoxColor);
            this.Name = "Form1";
            this.Text = "Screen Magnifier";
            this.TopMost = true;
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMag)).EndInit();
            this.panelColor.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.CheckBox checkBoxColor;
        private System.Windows.Forms.Label labelMag;
        private System.Windows.Forms.TrackBar trackBarMag;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Panel panelColor;
        private System.Windows.Forms.Label labelColor;
    }
}

