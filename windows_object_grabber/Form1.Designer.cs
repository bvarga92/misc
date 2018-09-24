namespace WinObjectGrabber
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
            this.btnApply = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.lbHandle = new System.Windows.Forms.Label();
            this.tbHandle = new System.Windows.Forms.TextBox();
            this.tbClass = new System.Windows.Forms.TextBox();
            this.lbClass = new System.Windows.Forms.Label();
            this.tbText = new System.Windows.Forms.TextBox();
            this.lbText = new System.Windows.Forms.Label();
            this.tbHeight = new System.Windows.Forms.TextBox();
            this.lbHeight = new System.Windows.Forms.Label();
            this.tbWidth = new System.Windows.Forms.TextBox();
            this.lbWidth = new System.Windows.Forms.Label();
            this.tbLeft = new System.Windows.Forms.TextBox();
            this.lbLeft = new System.Windows.Forms.Label();
            this.tbTop = new System.Windows.Forms.TextBox();
            this.lbTop = new System.Windows.Forms.Label();
            this.cbVisible = new System.Windows.Forms.CheckBox();
            this.cbEnabled = new System.Windows.Forms.CheckBox();
            this.lbAccess = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // btnApply
            // 
            this.btnApply.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnApply.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.btnApply.Location = new System.Drawing.Point(12, 222);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(131, 34);
            this.btnApply.TabIndex = 0;
            this.btnApply.Text = "Apply Changes";
            this.btnApply.UseVisualStyleBackColor = true;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // timer
            // 
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // pictureBox
            // 
            this.pictureBox.Location = new System.Drawing.Point(363, 222);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(51, 34);
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            this.pictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseDown);
            this.pictureBox.MouseEnter += new System.EventHandler(this.pictureBox_MouseEnter);
            this.pictureBox.MouseLeave += new System.EventHandler(this.pictureBox_MouseLeave);
            this.pictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox_MouseUp);
            // 
            // lbHandle
            // 
            this.lbHandle.AutoSize = true;
            this.lbHandle.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbHandle.Location = new System.Drawing.Point(13, 14);
            this.lbHandle.Name = "lbHandle";
            this.lbHandle.Size = new System.Drawing.Size(55, 16);
            this.lbHandle.TabIndex = 2;
            this.lbHandle.Text = "Handle:";
            // 
            // tbHandle
            // 
            this.tbHandle.Location = new System.Drawing.Point(75, 12);
            this.tbHandle.Name = "tbHandle";
            this.tbHandle.ReadOnly = true;
            this.tbHandle.Size = new System.Drawing.Size(339, 20);
            this.tbHandle.TabIndex = 3;
            // 
            // tbClass
            // 
            this.tbClass.Location = new System.Drawing.Point(75, 38);
            this.tbClass.Name = "tbClass";
            this.tbClass.ReadOnly = true;
            this.tbClass.Size = new System.Drawing.Size(339, 20);
            this.tbClass.TabIndex = 5;
            // 
            // lbClass
            // 
            this.lbClass.AutoSize = true;
            this.lbClass.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbClass.Location = new System.Drawing.Point(13, 40);
            this.lbClass.Name = "lbClass";
            this.lbClass.Size = new System.Drawing.Size(45, 16);
            this.lbClass.TabIndex = 4;
            this.lbClass.Text = "Class:";
            // 
            // tbText
            // 
            this.tbText.Location = new System.Drawing.Point(75, 64);
            this.tbText.Name = "tbText";
            this.tbText.Size = new System.Drawing.Size(339, 20);
            this.tbText.TabIndex = 7;
            // 
            // lbText
            // 
            this.lbText.AutoSize = true;
            this.lbText.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbText.Location = new System.Drawing.Point(13, 66);
            this.lbText.Name = "lbText";
            this.lbText.Size = new System.Drawing.Size(37, 16);
            this.lbText.TabIndex = 6;
            this.lbText.Text = "Text:";
            // 
            // tbHeight
            // 
            this.tbHeight.Location = new System.Drawing.Point(75, 90);
            this.tbHeight.Name = "tbHeight";
            this.tbHeight.Size = new System.Drawing.Size(339, 20);
            this.tbHeight.TabIndex = 9;
            // 
            // lbHeight
            // 
            this.lbHeight.AutoSize = true;
            this.lbHeight.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbHeight.Location = new System.Drawing.Point(13, 92);
            this.lbHeight.Name = "lbHeight";
            this.lbHeight.Size = new System.Drawing.Size(50, 16);
            this.lbHeight.TabIndex = 8;
            this.lbHeight.Text = "Height:";
            // 
            // tbWidth
            // 
            this.tbWidth.Location = new System.Drawing.Point(75, 116);
            this.tbWidth.Name = "tbWidth";
            this.tbWidth.Size = new System.Drawing.Size(339, 20);
            this.tbWidth.TabIndex = 11;
            // 
            // lbWidth
            // 
            this.lbWidth.AutoSize = true;
            this.lbWidth.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbWidth.Location = new System.Drawing.Point(13, 118);
            this.lbWidth.Name = "lbWidth";
            this.lbWidth.Size = new System.Drawing.Size(45, 16);
            this.lbWidth.TabIndex = 10;
            this.lbWidth.Text = "Width:";
            // 
            // tbLeft
            // 
            this.tbLeft.Location = new System.Drawing.Point(75, 142);
            this.tbLeft.Name = "tbLeft";
            this.tbLeft.Size = new System.Drawing.Size(339, 20);
            this.tbLeft.TabIndex = 13;
            // 
            // lbLeft
            // 
            this.lbLeft.AutoSize = true;
            this.lbLeft.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbLeft.Location = new System.Drawing.Point(13, 144);
            this.lbLeft.Name = "lbLeft";
            this.lbLeft.Size = new System.Drawing.Size(32, 16);
            this.lbLeft.TabIndex = 12;
            this.lbLeft.Text = "Left:";
            // 
            // tbTop
            // 
            this.tbTop.Location = new System.Drawing.Point(75, 168);
            this.tbTop.Name = "tbTop";
            this.tbTop.Size = new System.Drawing.Size(339, 20);
            this.tbTop.TabIndex = 15;
            // 
            // lbTop
            // 
            this.lbTop.AutoSize = true;
            this.lbTop.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbTop.Location = new System.Drawing.Point(13, 170);
            this.lbTop.Name = "lbTop";
            this.lbTop.Size = new System.Drawing.Size(36, 16);
            this.lbTop.TabIndex = 14;
            this.lbTop.Text = "Top:";
            // 
            // cbVisible
            // 
            this.cbVisible.AutoSize = true;
            this.cbVisible.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.cbVisible.Location = new System.Drawing.Point(75, 196);
            this.cbVisible.Name = "cbVisible";
            this.cbVisible.Size = new System.Drawing.Size(68, 20);
            this.cbVisible.TabIndex = 18;
            this.cbVisible.Text = "Visible";
            this.cbVisible.UseVisualStyleBackColor = true;
            // 
            // cbEnabled
            // 
            this.cbEnabled.AutoSize = true;
            this.cbEnabled.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.cbEnabled.Location = new System.Drawing.Point(149, 196);
            this.cbEnabled.Name = "cbEnabled";
            this.cbEnabled.Size = new System.Drawing.Size(78, 20);
            this.cbEnabled.TabIndex = 19;
            this.cbEnabled.Text = "Enabled";
            this.cbEnabled.UseVisualStyleBackColor = true;
            // 
            // lbAccess
            // 
            this.lbAccess.AutoSize = true;
            this.lbAccess.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lbAccess.Location = new System.Drawing.Point(14, 196);
            this.lbAccess.Name = "lbAccess";
            this.lbAccess.Size = new System.Drawing.Size(56, 16);
            this.lbAccess.TabIndex = 20;
            this.lbAccess.Text = "Access:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(428, 267);
            this.Controls.Add(this.lbAccess);
            this.Controls.Add(this.cbEnabled);
            this.Controls.Add(this.cbVisible);
            this.Controls.Add(this.tbTop);
            this.Controls.Add(this.lbTop);
            this.Controls.Add(this.tbLeft);
            this.Controls.Add(this.lbLeft);
            this.Controls.Add(this.tbWidth);
            this.Controls.Add(this.lbWidth);
            this.Controls.Add(this.tbHeight);
            this.Controls.Add(this.lbHeight);
            this.Controls.Add(this.tbText);
            this.Controls.Add(this.lbText);
            this.Controls.Add(this.tbClass);
            this.Controls.Add(this.lbClass);
            this.Controls.Add(this.tbHandle);
            this.Controls.Add(this.lbHandle);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.btnApply);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Windows Object Grabber";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Label lbHandle;
        private System.Windows.Forms.TextBox tbHandle;
        private System.Windows.Forms.TextBox tbClass;
        private System.Windows.Forms.Label lbClass;
        private System.Windows.Forms.TextBox tbText;
        private System.Windows.Forms.Label lbText;
        private System.Windows.Forms.TextBox tbHeight;
        private System.Windows.Forms.Label lbHeight;
        private System.Windows.Forms.TextBox tbWidth;
        private System.Windows.Forms.Label lbWidth;
        private System.Windows.Forms.TextBox tbLeft;
        private System.Windows.Forms.Label lbLeft;
        private System.Windows.Forms.TextBox tbTop;
        private System.Windows.Forms.Label lbTop;
        private System.Windows.Forms.CheckBox cbVisible;
        private System.Windows.Forms.CheckBox cbEnabled;
        private System.Windows.Forms.Label lbAccess;
    }
}

