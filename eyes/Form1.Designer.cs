namespace EyesOnYou
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
            this.pbLW = new System.Windows.Forms.PictureBox();
            this.pbRW = new System.Windows.Forms.PictureBox();
            this.pbLB = new System.Windows.Forms.PictureBox();
            this.pbRB = new System.Windows.Forms.PictureBox();
            this.timer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pbLW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbRW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbLB)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbRB)).BeginInit();
            this.SuspendLayout();
            // 
            // pbLW
            // 
            this.pbLW.Location = new System.Drawing.Point(5, 5);
            this.pbLW.Name = "pbLW";
            this.pbLW.Size = new System.Drawing.Size(100, 100);
            this.pbLW.TabIndex = 0;
            this.pbLW.TabStop = false;
            this.pbLW.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbLW_MouseDown);
            this.pbLW.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbLW_MouseMove);
            this.pbLW.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbLW_MouseUp);
            // 
            // pbRW
            // 
            this.pbRW.Location = new System.Drawing.Point(110, 5);
            this.pbRW.Name = "pbRW";
            this.pbRW.Size = new System.Drawing.Size(100, 100);
            this.pbRW.TabIndex = 1;
            this.pbRW.TabStop = false;
            this.pbRW.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbRW_MouseDown);
            this.pbRW.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbRW_MouseMove);
            this.pbRW.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbRW_MouseUp);
            // 
            // pbLB
            // 
            this.pbLB.Location = new System.Drawing.Point(72, 48);
            this.pbLB.Name = "pbLB";
            this.pbLB.Size = new System.Drawing.Size(20, 20);
            this.pbLB.TabIndex = 2;
            this.pbLB.TabStop = false;
            this.pbLB.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbLB_MouseDown);
            this.pbLB.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbLB_MouseMove);
            this.pbLB.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbLB_MouseUp);
            // 
            // pbRB
            // 
            this.pbRB.Location = new System.Drawing.Point(120, 48);
            this.pbRB.Name = "pbRB";
            this.pbRB.Size = new System.Drawing.Size(20, 20);
            this.pbRB.TabIndex = 3;
            this.pbRB.TabStop = false;
            this.pbRB.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pbRB_MouseDown);
            this.pbRB.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pbRB_MouseMove);
            this.pbRB.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pbRB_MouseUp);
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(225, 122);
            this.Controls.Add(this.pbRB);
            this.Controls.Add(this.pbLB);
            this.Controls.Add(this.pbRW);
            this.Controls.Add(this.pbLW);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Eyes On You";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbLW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbRW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbLB)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbRB)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pbLW;
        private System.Windows.Forms.PictureBox pbRW;
        private System.Windows.Forms.PictureBox pbLB;
        private System.Windows.Forms.PictureBox pbRB;
        private System.Windows.Forms.Timer timer;
    }
}

