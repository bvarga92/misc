namespace ProcMemChanger
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
            this.btnFind = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.lbApps = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbSearchValue = new System.Windows.Forms.TextBox();
            this.rbDecimal = new System.Windows.Forms.RadioButton();
            this.rbHex = new System.Windows.Forms.RadioButton();
            this.tbMax = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnSearch = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnModify = new System.Windows.Forms.Button();
            this.tbResValue = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.lbAddr = new System.Windows.Forms.ListBox();
            this.backgroundWorker = new System.ComponentModel.BackgroundWorker();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnFind
            // 
            this.btnFind.Location = new System.Drawing.Point(6, 224);
            this.btnFind.Name = "btnFind";
            this.btnFind.Size = new System.Drawing.Size(95, 23);
            this.btnFind.TabIndex = 1;
            this.btnFind.Text = "Find Windows";
            this.btnFind.UseVisualStyleBackColor = true;
            this.btnFind.Click += new System.EventHandler(this.btnFind_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnHelp);
            this.groupBox1.Controls.Add(this.lbApps);
            this.groupBox1.Controls.Add(this.btnFind);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(475, 255);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Running Applications";
            // 
            // btnHelp
            // 
            this.btnHelp.Location = new System.Drawing.Point(374, 224);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(95, 23);
            this.btnHelp.TabIndex = 2;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // lbApps
            // 
            this.lbApps.FormattingEnabled = true;
            this.lbApps.Location = new System.Drawing.Point(6, 19);
            this.lbApps.Name = "lbApps";
            this.lbApps.Size = new System.Drawing.Size(463, 199);
            this.lbApps.TabIndex = 0;
            this.lbApps.DoubleClick += new System.EventHandler(this.lbApps_DoubleClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "Value:";
            // 
            // tbSearchValue
            // 
            this.tbSearchValue.Location = new System.Drawing.Point(56, 20);
            this.tbSearchValue.Name = "tbSearchValue";
            this.tbSearchValue.Size = new System.Drawing.Size(119, 20);
            this.tbSearchValue.TabIndex = 1;
            this.tbSearchValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbSearchValue_KeyPress);
            // 
            // rbDecimal
            // 
            this.rbDecimal.AutoSize = true;
            this.rbDecimal.Checked = true;
            this.rbDecimal.Location = new System.Drawing.Point(193, 22);
            this.rbDecimal.Name = "rbDecimal";
            this.rbDecimal.Size = new System.Drawing.Size(63, 17);
            this.rbDecimal.TabIndex = 2;
            this.rbDecimal.TabStop = true;
            this.rbDecimal.Text = "Decimal";
            this.rbDecimal.UseVisualStyleBackColor = true;
            this.rbDecimal.CheckedChanged += new System.EventHandler(this.rbDecimal_CheckedChanged);
            // 
            // rbHex
            // 
            this.rbHex.AutoSize = true;
            this.rbHex.Location = new System.Drawing.Point(263, 22);
            this.rbHex.Name = "rbHex";
            this.rbHex.Size = new System.Drawing.Size(86, 17);
            this.rbHex.TabIndex = 3;
            this.rbHex.Text = "Hexadecimal";
            this.rbHex.UseVisualStyleBackColor = true;
            // 
            // tbMax
            // 
            this.tbMax.Location = new System.Drawing.Point(123, 52);
            this.tbMax.Name = "tbMax";
            this.tbMax.Size = new System.Drawing.Size(52, 20);
            this.tbMax.TabIndex = 5;
            this.tbMax.Text = "50";
            this.tbMax.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbMax_KeyPress);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.progressBar);
            this.groupBox2.Controls.Add(this.btnClear);
            this.groupBox2.Controls.Add(this.btnSearch);
            this.groupBox2.Controls.Add(this.tbMax);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.rbHex);
            this.groupBox2.Controls.Add(this.rbDecimal);
            this.groupBox2.Controls.Add(this.tbSearchValue);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(12, 273);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(469, 117);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Search Value";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(6, 83);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(457, 23);
            this.progressBar.TabIndex = 8;
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(274, 52);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 7;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnSearch
            // 
            this.btnSearch.Location = new System.Drawing.Point(193, 52);
            this.btnSearch.Name = "btnSearch";
            this.btnSearch.Size = new System.Drawing.Size(75, 23);
            this.btnSearch.TabIndex = 6;
            this.btnSearch.Text = "Search";
            this.btnSearch.UseVisualStyleBackColor = true;
            this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label2.Location = new System.Drawing.Point(6, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(111, 16);
            this.label2.TabIndex = 4;
            this.label2.Text = "Max results to list:";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnModify);
            this.groupBox3.Controls.Add(this.tbResValue);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.lbAddr);
            this.groupBox3.Location = new System.Drawing.Point(493, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(175, 378);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Search Results: 0";
            // 
            // btnModify
            // 
            this.btnModify.Location = new System.Drawing.Point(6, 344);
            this.btnModify.Name = "btnModify";
            this.btnModify.Size = new System.Drawing.Size(159, 23);
            this.btnModify.TabIndex = 2;
            this.btnModify.Text = "Modify Value";
            this.btnModify.UseVisualStyleBackColor = true;
            this.btnModify.Click += new System.EventHandler(this.btnModify_Click);
            // 
            // tbResValue
            // 
            this.tbResValue.Location = new System.Drawing.Point(58, 312);
            this.tbResValue.Name = "tbResValue";
            this.tbResValue.Size = new System.Drawing.Size(107, 20);
            this.tbResValue.TabIndex = 3;
            this.tbResValue.Enter += new System.EventHandler(this.tbResValue_Enter);
            this.tbResValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbResValue_KeyPress);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label3.Location = new System.Drawing.Point(8, 313);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 16);
            this.label3.TabIndex = 2;
            this.label3.Text = "Value:";
            // 
            // lbAddr
            // 
            this.lbAddr.FormattingEnabled = true;
            this.lbAddr.Location = new System.Drawing.Point(6, 19);
            this.lbAddr.Name = "lbAddr";
            this.lbAddr.Size = new System.Drawing.Size(159, 277);
            this.lbAddr.TabIndex = 0;
            // 
            // backgroundWorker
            // 
            this.backgroundWorker.WorkerReportsProgress = true;
            this.backgroundWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker_DoWork);
            this.backgroundWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker_ProgressChanged);
            this.backgroundWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker_RunWorkerCompleted);
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
            this.ClientSize = new System.Drawing.Size(680, 397);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Process Memory Changer";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnFind;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ListBox lbApps;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbSearchValue;
        private System.Windows.Forms.RadioButton rbDecimal;
        private System.Windows.Forms.RadioButton rbHex;
        private System.Windows.Forms.TextBox tbMax;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox tbResValue;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListBox lbAddr;
        private System.Windows.Forms.Button btnModify;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnSearch;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.ComponentModel.BackgroundWorker backgroundWorker;
        private System.Windows.Forms.Timer timer;
    }
}

