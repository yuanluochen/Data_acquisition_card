namespace zlTool
{
    partial class zlTool
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            label5 = new Label();
            label6 = new Label();
            childWindow = new Panel();
            button4 = new Button();
            button7 = new Button();
            serialPort = new ComboBox();
            serialOpen = new Button();
            rxUsbTim = new System.Windows.Forms.Timer(components);
            button2 = new Button();
            button3 = new Button();
            SuspendLayout();
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("黑体", 12F, FontStyle.Bold);
            label5.Location = new Point(1084, 8);
            label5.Name = "label5";
            label5.Size = new Size(408, 16);
            label5.TabIndex = 188;
            label5.Text = "鼠标左键拖动 右键拖动缩放 滚轮缩放 滚轮按下复位";
            label5.Click += label5_Click;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("黑体", 12F, FontStyle.Bold);
            label6.Location = new Point(1124, 28);
            label6.Name = "label6";
            label6.Size = new Size(355, 16);
            label6.TabIndex = 189;
            label6.Text = "Shift+Ctrl+滚轮单轴缩放 Alt+左键选中放大";
            // 
            // childWindow
            // 
            childWindow.BorderStyle = BorderStyle.FixedSingle;
            childWindow.Location = new Point(122, 47);
            childWindow.Name = "childWindow";
            childWindow.Size = new Size(1400, 800);
            childWindow.TabIndex = 254;
            childWindow.Paint += childWindow_Paint;
            // 
            // button4
            // 
            button4.BackColor = SystemColors.InactiveBorder;
            button4.Font = new Font("黑体", 14F, FontStyle.Bold);
            button4.ForeColor = Color.FromArgb(42, 42, 42);
            button4.Location = new Point(12, 78);
            button4.Name = "button4";
            button4.Size = new Size(101, 70);
            button4.TabIndex = 255;
            button4.Text = "记录仪";
            button4.UseVisualStyleBackColor = false;
            button4.Click += button4_Click;
            // 
            // button7
            // 
            button7.BackColor = SystemColors.InactiveBorder;
            button7.Font = new Font("黑体", 14F, FontStyle.Bold);
            button7.ForeColor = Color.FromArgb(42, 42, 42);
            button7.Location = new Point(12, 164);
            button7.Name = "button7";
            button7.Size = new Size(101, 70);
            button7.TabIndex = 255;
            button7.Text = "信号源";
            button7.UseVisualStyleBackColor = false;
            button7.Click += button7_Click;
            // 
            // serialPort
            // 
            serialPort.Font = new Font("黑体", 12F, FontStyle.Bold);
            serialPort.FormattingEnabled = true;
            serialPort.Location = new Point(12, 6);
            serialPort.Name = "serialPort";
            serialPort.Size = new Size(101, 24);
            serialPort.TabIndex = 288;
            serialPort.Click += serialPort_Click;
            // 
            // serialOpen
            // 
            serialOpen.Font = new Font("黑体", 12F, FontStyle.Bold);
            serialOpen.Location = new Point(119, 1);
            serialOpen.Name = "serialOpen";
            serialOpen.Size = new Size(101, 31);
            serialOpen.TabIndex = 287;
            serialOpen.Text = "打开串口";
            serialOpen.UseVisualStyleBackColor = true;
            serialOpen.Click += serialOpen_Click;
            // 
            // rxUsbTim
            // 
            rxUsbTim.Enabled = true;
            rxUsbTim.Interval = 20;
            rxUsbTim.Tick += rxTim_Tick;
            // 
            // button2
            // 
            button2.BackColor = SystemColors.InactiveBorder;
            button2.Font = new Font("黑体", 14F, FontStyle.Bold);
            button2.ForeColor = Color.FromArgb(42, 42, 42);
            button2.Location = new Point(12, 250);
            button2.Name = "button2";
            button2.Size = new Size(101, 70);
            button2.TabIndex = 255;
            button2.Text = "通用IO";
            button2.UseVisualStyleBackColor = false;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.BackColor = SystemColors.InactiveBorder;
            button3.Font = new Font("黑体", 14F, FontStyle.Bold);
            button3.ForeColor = Color.FromArgb(42, 42, 42);
            button3.Location = new Point(12, 336);
            button3.Name = "button3";
            button3.Size = new Size(101, 70);
            button3.TabIndex = 255;
            button3.Text = "参数设置";
            button3.UseVisualStyleBackColor = false;
            button3.Click += button3_Click;
            // 
            // zlTool
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSize = true;
            BackColor = SystemColors.GradientInactiveCaption;
            ClientSize = new Size(1526, 851);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(serialPort);
            Controls.Add(serialOpen);
            Controls.Add(button7);
            Controls.Add(button4);
            Controls.Add(childWindow);
            Controls.Add(label6);
            Controls.Add(label5);
            Name = "zlTool";
            Text = "DABM-D223上位机专用";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private ScottPlot.WinForms.FormsPlot waveVolt;
        private Label label5;
        private Label label6;
        private ScottPlot.WinForms.FormsPlot waveCurt;
        private Label getCurrent;
        private Label chargeVolt;
        private Label inputVolt;
        private Label pwmDuty;
        private Label label11;
        private Panel childWindow;
        private Button button4;
        private Button button7;
        private ComboBox serialPort;
        private Button serialOpen;
        private System.Windows.Forms.Timer rxUsbTim;
        private Button button2;
        private Button button3;
    }
}
