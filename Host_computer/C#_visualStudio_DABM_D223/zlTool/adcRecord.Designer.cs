namespace zlTool
{
    partial class autoscaling
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
            components = new System.ComponentModel.Container();
            waveform = new ScottPlot.WinForms.FormsPlot();
            autoReadCheck = new CheckBox();
            button2 = new Button();
            adcCheck8 = new CheckBox();
            adcCheck7 = new CheckBox();
            adcCheck6 = new CheckBox();
            adcCheck5 = new CheckBox();
            adcCheck4 = new CheckBox();
            adcCheck3 = new CheckBox();
            adcCheck2 = new CheckBox();
            adcCheck1 = new CheckBox();
            adcValue1 = new Label();
            adcValue2 = new Label();
            adcValue3 = new Label();
            adcValue4 = new Label();
            adcValue8 = new Label();
            adcValue7 = new Label();
            adcValue6 = new Label();
            adcValue5 = new Label();
            label5 = new Label();
            sramHour = new Label();
            label7 = new Label();
            label8 = new Label();
            sramMinute = new Label();
            label10 = new Label();
            sramSecond = new Label();
            button1 = new Button();
            button3 = new Button();
            button5 = new Button();
            button6 = new Button();
            button7 = new Button();
            setAdcSamplingRate = new TextBox();
            button14 = new Button();
            label16 = new Label();
            setSramSamplingTime = new TextBox();
            autoRead = new System.Windows.Forms.Timer(components);
            progressBar = new ProgressBar();
            filePath = new Label();
            button13 = new Button();
            autoSave = new CheckBox();
            button16 = new Button();
            button17 = new Button();
            chk_recent1000 = new CheckBox();
            calibEnable = new CheckBox();
            button19 = new Button();
            ckb_RefreshWave = new CheckBox();
            autoReadTime = new TextBox();
            label11 = new Label();
            adcRange = new CheckBox();
            adcSignalType = new CheckBox();
            dinCheck6 = new CheckBox();
            dinCheck5 = new CheckBox();
            dinCheck4 = new CheckBox();
            dinCheck3 = new CheckBox();
            dinCheck2 = new CheckBox();
            dinCheck1 = new CheckBox();
            groupBox1 = new GroupBox();
            groupBox2 = new GroupBox();
            groupBox3 = new GroupBox();
            ckb_sramTrigEnable = new CheckBox();
            groupBox5 = new GroupBox();
            label2 = new Label();
            label1 = new Label();
            groupBox7 = new GroupBox();
            groupBox6 = new GroupBox();
            dinCheck8 = new CheckBox();
            dinCheck7 = new CheckBox();
            groupBox8 = new GroupBox();
            button4 = new Button();
            autoRecent = new System.Windows.Forms.Timer(components);
            ckb_autoscaling = new CheckBox();
            groupBox9 = new GroupBox();
            diffCheck4 = new CheckBox();
            diffCheck3 = new CheckBox();
            diffCheck2 = new CheckBox();
            diffCheck1 = new CheckBox();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            groupBox5.SuspendLayout();
            groupBox7.SuspendLayout();
            groupBox6.SuspendLayout();
            groupBox8.SuspendLayout();
            groupBox9.SuspendLayout();
            SuspendLayout();
            // 
            // waveform
            // 
            waveform.BackColor = Color.FromArgb(242, 247, 250);
            waveform.DisplayScale = 1F;
            waveform.Location = new Point(195, 237);
            waveform.Name = "waveform";
            waveform.Size = new Size(1193, 561);
            waveform.TabIndex = 287;
            waveform.DragDrop += waveform_DragDrop;
            waveform.Paint += waveform_Paint;
            // 
            // autoReadCheck
            // 
            autoReadCheck.AutoSize = true;
            autoReadCheck.Font = new Font("黑体", 12F, FontStyle.Bold);
            autoReadCheck.Location = new Point(8, 59);
            autoReadCheck.Name = "autoReadCheck";
            autoReadCheck.Size = new Size(147, 20);
            autoReadCheck.TabIndex = 320;
            autoReadCheck.Text = "自动读取(24位)";
            autoReadCheck.UseVisualStyleBackColor = true;
            autoReadCheck.Click += autoReadCheck_Click;
            // 
            // button2
            // 
            button2.Font = new Font("黑体", 12F);
            button2.Location = new Point(12, 821);
            button2.Name = "button2";
            button2.Size = new Size(108, 31);
            button2.TabIndex = 334;
            button2.Text = "清空";
            button2.UseVisualStyleBackColor = true;
            // 
            // adcCheck8
            // 
            adcCheck8.AutoSize = true;
            adcCheck8.Checked = true;
            adcCheck8.CheckState = CheckState.Checked;
            adcCheck8.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck8.ForeColor = Color.Purple;
            adcCheck8.Location = new Point(15, 236);
            adcCheck8.Name = "adcCheck8";
            adcCheck8.Size = new Size(71, 20);
            adcCheck8.TabIndex = 342;
            adcCheck8.Text = "ADC_8";
            adcCheck8.UseVisualStyleBackColor = true;
            adcCheck8.Click += adcCheck8_Click;
            // 
            // adcCheck7
            // 
            adcCheck7.AutoSize = true;
            adcCheck7.Checked = true;
            adcCheck7.CheckState = CheckState.Checked;
            adcCheck7.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck7.ForeColor = Color.Blue;
            adcCheck7.Location = new Point(15, 207);
            adcCheck7.Name = "adcCheck7";
            adcCheck7.Size = new Size(71, 20);
            adcCheck7.TabIndex = 341;
            adcCheck7.Text = "ADC_7";
            adcCheck7.UseVisualStyleBackColor = true;
            adcCheck7.Click += adcCheck7_Click;
            // 
            // adcCheck6
            // 
            adcCheck6.AutoSize = true;
            adcCheck6.Checked = true;
            adcCheck6.CheckState = CheckState.Checked;
            adcCheck6.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck6.ForeColor = Color.DarkCyan;
            adcCheck6.Location = new Point(15, 178);
            adcCheck6.Name = "adcCheck6";
            adcCheck6.Size = new Size(71, 20);
            adcCheck6.TabIndex = 340;
            adcCheck6.Text = "ADC_6";
            adcCheck6.UseVisualStyleBackColor = true;
            adcCheck6.Click += adcCheck6_Click;
            // 
            // adcCheck5
            // 
            adcCheck5.AutoSize = true;
            adcCheck5.Checked = true;
            adcCheck5.CheckState = CheckState.Checked;
            adcCheck5.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck5.ForeColor = Color.Green;
            adcCheck5.Location = new Point(15, 149);
            adcCheck5.Name = "adcCheck5";
            adcCheck5.Size = new Size(71, 20);
            adcCheck5.TabIndex = 339;
            adcCheck5.Text = "ADC_5";
            adcCheck5.UseVisualStyleBackColor = true;
            adcCheck5.Click += adcCheck5_Click;
            // 
            // adcCheck4
            // 
            adcCheck4.AutoSize = true;
            adcCheck4.Checked = true;
            adcCheck4.CheckState = CheckState.Checked;
            adcCheck4.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck4.ForeColor = Color.Orange;
            adcCheck4.Location = new Point(15, 120);
            adcCheck4.Name = "adcCheck4";
            adcCheck4.Size = new Size(71, 20);
            adcCheck4.TabIndex = 338;
            adcCheck4.Text = "ADC_4";
            adcCheck4.UseVisualStyleBackColor = true;
            adcCheck4.Click += adcCheck4_Click;
            // 
            // adcCheck3
            // 
            adcCheck3.AutoSize = true;
            adcCheck3.Checked = true;
            adcCheck3.CheckState = CheckState.Checked;
            adcCheck3.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck3.ForeColor = Color.Magenta;
            adcCheck3.Location = new Point(15, 91);
            adcCheck3.Name = "adcCheck3";
            adcCheck3.Size = new Size(71, 20);
            adcCheck3.TabIndex = 337;
            adcCheck3.Text = "ADC_3";
            adcCheck3.UseVisualStyleBackColor = true;
            adcCheck3.Click += adcCheck3_Click;
            // 
            // adcCheck2
            // 
            adcCheck2.AutoSize = true;
            adcCheck2.Checked = true;
            adcCheck2.CheckState = CheckState.Checked;
            adcCheck2.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck2.ForeColor = Color.Red;
            adcCheck2.Location = new Point(15, 62);
            adcCheck2.Name = "adcCheck2";
            adcCheck2.Size = new Size(71, 20);
            adcCheck2.TabIndex = 336;
            adcCheck2.Text = "ADC_2";
            adcCheck2.UseVisualStyleBackColor = true;
            adcCheck2.Click += adcCheck2_Click;
            // 
            // adcCheck1
            // 
            adcCheck1.AutoSize = true;
            adcCheck1.Checked = true;
            adcCheck1.CheckState = CheckState.Checked;
            adcCheck1.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcCheck1.ForeColor = Color.Brown;
            adcCheck1.Location = new Point(15, 33);
            adcCheck1.Name = "adcCheck1";
            adcCheck1.Size = new Size(71, 20);
            adcCheck1.TabIndex = 335;
            adcCheck1.Text = "ADC_1";
            adcCheck1.UseVisualStyleBackColor = true;
            adcCheck1.Click += adcCheck1_Click;
            // 
            // adcValue1
            // 
            adcValue1.AutoSize = true;
            adcValue1.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue1.ForeColor = Color.Brown;
            adcValue1.Location = new Point(93, 34);
            adcValue1.Name = "adcValue1";
            adcValue1.Size = new Size(34, 16);
            adcValue1.TabIndex = 363;
            adcValue1.Text = "N/A";
            // 
            // adcValue2
            // 
            adcValue2.AutoSize = true;
            adcValue2.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue2.ForeColor = Color.Red;
            adcValue2.Location = new Point(93, 63);
            adcValue2.Name = "adcValue2";
            adcValue2.Size = new Size(34, 16);
            adcValue2.TabIndex = 364;
            adcValue2.Text = "N/A";
            // 
            // adcValue3
            // 
            adcValue3.AutoSize = true;
            adcValue3.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue3.ForeColor = Color.Magenta;
            adcValue3.Location = new Point(93, 92);
            adcValue3.Name = "adcValue3";
            adcValue3.Size = new Size(34, 16);
            adcValue3.TabIndex = 365;
            adcValue3.Text = "N/A";
            // 
            // adcValue4
            // 
            adcValue4.AutoSize = true;
            adcValue4.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue4.ForeColor = Color.Orange;
            adcValue4.Location = new Point(93, 121);
            adcValue4.Name = "adcValue4";
            adcValue4.Size = new Size(34, 16);
            adcValue4.TabIndex = 366;
            adcValue4.Text = "N/A";
            // 
            // adcValue8
            // 
            adcValue8.AutoSize = true;
            adcValue8.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue8.ForeColor = Color.Purple;
            adcValue8.Location = new Point(93, 237);
            adcValue8.Name = "adcValue8";
            adcValue8.Size = new Size(34, 16);
            adcValue8.TabIndex = 370;
            adcValue8.Text = "N/A";
            // 
            // adcValue7
            // 
            adcValue7.AutoSize = true;
            adcValue7.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue7.ForeColor = Color.Blue;
            adcValue7.Location = new Point(93, 208);
            adcValue7.Name = "adcValue7";
            adcValue7.Size = new Size(34, 16);
            adcValue7.TabIndex = 369;
            adcValue7.Text = "N/A";
            // 
            // adcValue6
            // 
            adcValue6.AutoSize = true;
            adcValue6.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue6.ForeColor = Color.DarkCyan;
            adcValue6.Location = new Point(93, 179);
            adcValue6.Name = "adcValue6";
            adcValue6.Size = new Size(34, 16);
            adcValue6.TabIndex = 368;
            adcValue6.Text = "N/A";
            // 
            // adcValue5
            // 
            adcValue5.AutoSize = true;
            adcValue5.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcValue5.ForeColor = Color.Green;
            adcValue5.Location = new Point(93, 150);
            adcValue5.Name = "adcValue5";
            adcValue5.Size = new Size(34, 16);
            adcValue5.TabIndex = 367;
            adcValue5.Text = "N/A";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("黑体", 12F, FontStyle.Bold);
            label5.ForeColor = Color.FromArgb(42, 42, 42);
            label5.Location = new Point(10, 175);
            label5.Name = "label5";
            label5.Size = new Size(67, 16);
            label5.TabIndex = 293;
            label5.Text = "已采集:";
            // 
            // sramHour
            // 
            sramHour.AutoSize = true;
            sramHour.Font = new Font("黑体", 12F, FontStyle.Bold);
            sramHour.ForeColor = Color.FromArgb(42, 42, 42);
            sramHour.Location = new Point(76, 175);
            sramHour.Name = "sramHour";
            sramHour.Size = new Size(34, 16);
            sramHour.TabIndex = 293;
            sramHour.Text = "N/A";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("黑体", 12F, FontStyle.Bold);
            label7.ForeColor = Color.FromArgb(42, 42, 42);
            label7.Location = new Point(113, 175);
            label7.Name = "label7";
            label7.Size = new Size(24, 16);
            label7.TabIndex = 293;
            label7.Text = "时";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("黑体", 12F, FontStyle.Bold);
            label8.ForeColor = Color.FromArgb(42, 42, 42);
            label8.Location = new Point(192, 175);
            label8.Name = "label8";
            label8.Size = new Size(24, 16);
            label8.TabIndex = 371;
            label8.Text = "分";
            // 
            // sramMinute
            // 
            sramMinute.AutoSize = true;
            sramMinute.Font = new Font("黑体", 12F, FontStyle.Bold);
            sramMinute.ForeColor = Color.FromArgb(42, 42, 42);
            sramMinute.Location = new Point(155, 175);
            sramMinute.Name = "sramMinute";
            sramMinute.Size = new Size(34, 16);
            sramMinute.TabIndex = 372;
            sramMinute.Text = "N/A";
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Font = new Font("黑体", 12F, FontStyle.Bold);
            label10.ForeColor = Color.FromArgb(42, 42, 42);
            label10.Location = new Point(273, 175);
            label10.Name = "label10";
            label10.Size = new Size(24, 16);
            label10.TabIndex = 373;
            label10.Text = "秒";
            // 
            // sramSecond
            // 
            sramSecond.AutoSize = true;
            sramSecond.Font = new Font("黑体", 12F, FontStyle.Bold);
            sramSecond.ForeColor = Color.FromArgb(42, 42, 42);
            sramSecond.Location = new Point(236, 175);
            sramSecond.Name = "sramSecond";
            sramSecond.Size = new Size(34, 16);
            sramSecond.TabIndex = 374;
            sramSecond.Text = "N/A";
            // 
            // button1
            // 
            button1.BackColor = Color.FromArgb(20, 131, 197);
            button1.Font = new Font("黑体", 12F, FontStyle.Bold);
            button1.ForeColor = Color.White;
            button1.Location = new Point(213, 18);
            button1.Name = "button1";
            button1.Size = new Size(83, 62);
            button1.TabIndex = 288;
            button1.Text = "开始采集";
            button1.UseVisualStyleBackColor = false;
            button1.Click += button1_Click;
            // 
            // button3
            // 
            button3.BackColor = Color.FromArgb(20, 131, 197);
            button3.Font = new Font("黑体", 12F, FontStyle.Bold);
            button3.ForeColor = Color.White;
            button3.Location = new Point(16, 89);
            button3.Name = "button3";
            button3.Size = new Size(83, 59);
            button3.TabIndex = 288;
            button3.Text = "停止采集";
            button3.UseVisualStyleBackColor = false;
            button3.Click += button3_Click;
            // 
            // button5
            // 
            button5.BackColor = SystemColors.GradientInactiveCaption;
            button5.Font = new Font("黑体", 12F, FontStyle.Bold);
            button5.ForeColor = Color.FromArgb(42, 42, 42);
            button5.Location = new Point(113, 89);
            button5.Name = "button5";
            button5.Size = new Size(83, 59);
            button5.TabIndex = 288;
            button5.Text = "读取波形";
            button5.UseVisualStyleBackColor = false;
            button5.Click += button5_Click;
            // 
            // button6
            // 
            button6.BackColor = SystemColors.GradientInactiveCaption;
            button6.Font = new Font("黑体", 12F, FontStyle.Bold);
            button6.ForeColor = Color.FromArgb(42, 42, 42);
            button6.Location = new Point(213, 89);
            button6.Name = "button6";
            button6.Size = new Size(83, 29);
            button6.TabIndex = 288;
            button6.Text = "打开波形";
            button6.UseVisualStyleBackColor = false;
            button6.Click += button6_Click;
            // 
            // button7
            // 
            button7.BackColor = SystemColors.GradientInactiveCaption;
            button7.Font = new Font("黑体", 12F, FontStyle.Bold);
            button7.ForeColor = Color.FromArgb(42, 42, 42);
            button7.Location = new Point(213, 115);
            button7.Name = "button7";
            button7.Size = new Size(83, 33);
            button7.TabIndex = 288;
            button7.Text = "保存波形";
            button7.UseVisualStyleBackColor = false;
            button7.Click += button7_Click;
            // 
            // setAdcSamplingRate
            // 
            setAdcSamplingRate.BackColor = SystemColors.InactiveBorder;
            setAdcSamplingRate.Font = new Font("黑体", 12F, FontStyle.Bold);
            setAdcSamplingRate.ForeColor = Color.Black;
            setAdcSamplingRate.Location = new Point(4, 27);
            setAdcSamplingRate.Name = "setAdcSamplingRate";
            setAdcSamplingRate.Size = new Size(114, 26);
            setAdcSamplingRate.TabIndex = 391;
            setAdcSamplingRate.Text = "500000";
            setAdcSamplingRate.TextAlign = HorizontalAlignment.Center;
            // 
            // button14
            // 
            button14.BackColor = Color.FromArgb(20, 131, 197);
            button14.Font = new Font("黑体", 12F, FontStyle.Bold);
            button14.ForeColor = Color.White;
            button14.Location = new Point(1173, 12);
            button14.Name = "button14";
            button14.Size = new Size(169, 39);
            button14.TabIndex = 401;
            button14.Text = "清除波形";
            button14.UseVisualStyleBackColor = false;
            button14.Click += button14_Click;
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Font = new Font("黑体", 12F, FontStyle.Bold);
            label16.Location = new Point(9, 40);
            label16.Name = "label16";
            label16.Size = new Size(111, 16);
            label16.TabIndex = 403;
            label16.Text = "采集时间(ms)";
            // 
            // setSramSamplingTime
            // 
            setSramSamplingTime.BackColor = SystemColors.InactiveBorder;
            setSramSamplingTime.Font = new Font("黑体", 12F, FontStyle.Bold);
            setSramSamplingTime.Location = new Point(114, 32);
            setSramSamplingTime.Name = "setSramSamplingTime";
            setSramSamplingTime.Size = new Size(80, 26);
            setSramSamplingTime.TabIndex = 402;
            setSramSamplingTime.Text = "300";
            setSramSamplingTime.TextAlign = HorizontalAlignment.Center;
            // 
            // autoRead
            // 
            autoRead.Enabled = true;
            autoRead.Tick += autoRead_Tick_1;
            // 
            // progressBar
            // 
            progressBar.Location = new Point(12, 118);
            progressBar.Name = "progressBar";
            progressBar.Size = new Size(167, 28);
            progressBar.TabIndex = 404;
            // 
            // filePath
            // 
            filePath.AutoSize = true;
            filePath.Font = new Font("黑体", 12F, FontStyle.Bold);
            filePath.Location = new Point(229, 11);
            filePath.Name = "filePath";
            filePath.Size = new Size(34, 16);
            filePath.TabIndex = 407;
            filePath.Text = "N/A";
            // 
            // button13
            // 
            button13.Font = new Font("黑体", 12F, FontStyle.Bold);
            button13.Location = new Point(12, 2);
            button13.Name = "button13";
            button13.Size = new Size(86, 36);
            button13.TabIndex = 408;
            button13.Text = "选择路径";
            button13.UseVisualStyleBackColor = true;
            button13.Click += button13_Click_1;
            // 
            // autoSave
            // 
            autoSave.AutoSize = true;
            autoSave.Font = new Font("黑体", 12F, FontStyle.Bold);
            autoSave.Location = new Point(104, 9);
            autoSave.Name = "autoSave";
            autoSave.Size = new Size(128, 20);
            autoSave.TabIndex = 409;
            autoSave.Text = "自动保存文件";
            autoSave.UseVisualStyleBackColor = true;
            // 
            // button16
            // 
            button16.BackColor = Color.FromArgb(20, 131, 197);
            button16.Font = new Font("黑体", 12F, FontStyle.Bold);
            button16.ForeColor = Color.White;
            button16.Location = new Point(36, 53);
            button16.Name = "button16";
            button16.Size = new Size(83, 57);
            button16.TabIndex = 412;
            button16.Text = "开始采集";
            button16.UseVisualStyleBackColor = false;
            button16.Click += button16_Click;
            // 
            // button17
            // 
            button17.BackColor = Color.FromArgb(20, 131, 197);
            button17.Font = new Font("黑体", 12F, FontStyle.Bold);
            button17.ForeColor = Color.White;
            button17.Location = new Point(36, 112);
            button17.Name = "button17";
            button17.Size = new Size(83, 59);
            button17.TabIndex = 413;
            button17.Text = "停止采集";
            button17.UseVisualStyleBackColor = false;
            button17.Click += button17_Click;
            // 
            // chk_recent1000
            // 
            chk_recent1000.AutoSize = true;
            chk_recent1000.Font = new Font("黑体", 12F, FontStyle.Bold);
            chk_recent1000.Location = new Point(8, 35);
            chk_recent1000.Name = "chk_recent1000";
            chk_recent1000.Size = new Size(199, 20);
            chk_recent1000.TabIndex = 416;
            chk_recent1000.Text = "自动读取(最近1000次)";
            chk_recent1000.UseVisualStyleBackColor = true;
            chk_recent1000.Click += chk_recent200_Click;
            // 
            // calibEnable
            // 
            calibEnable.AutoSize = true;
            calibEnable.Font = new Font("黑体", 12F, FontStyle.Bold);
            calibEnable.ForeColor = Color.OrangeRed;
            calibEnable.Location = new Point(1173, 103);
            calibEnable.Name = "calibEnable";
            calibEnable.Size = new Size(94, 20);
            calibEnable.TabIndex = 420;
            calibEnable.Text = "启用标定";
            calibEnable.UseVisualStyleBackColor = true;
            // 
            // button19
            // 
            button19.BackColor = Color.FromArgb(255, 224, 192);
            button19.Font = new Font("黑体", 12F, FontStyle.Bold);
            button19.Location = new Point(1173, 57);
            button19.Name = "button19";
            button19.Size = new Size(169, 40);
            button19.TabIndex = 421;
            button19.Text = "读取标定参数";
            button19.UseVisualStyleBackColor = false;
            button19.Click += button19_Click;
            // 
            // ckb_RefreshWave
            // 
            ckb_RefreshWave.AutoSize = true;
            ckb_RefreshWave.Checked = true;
            ckb_RefreshWave.CheckState = CheckState.Checked;
            ckb_RefreshWave.Font = new Font("黑体", 12F, FontStyle.Bold);
            ckb_RefreshWave.Location = new Point(63, 172);
            ckb_RefreshWave.Name = "ckb_RefreshWave";
            ckb_RefreshWave.Size = new Size(94, 20);
            ckb_RefreshWave.TabIndex = 425;
            ckb_RefreshWave.Text = "刷新波形";
            ckb_RefreshWave.UseVisualStyleBackColor = true;
            // 
            // autoReadTime
            // 
            autoReadTime.BackColor = SystemColors.InactiveBorder;
            autoReadTime.Font = new Font("黑体", 12F, FontStyle.Bold);
            autoReadTime.Location = new Point(114, 27);
            autoReadTime.Name = "autoReadTime";
            autoReadTime.Size = new Size(72, 26);
            autoReadTime.TabIndex = 417;
            autoReadTime.Text = "100";
            autoReadTime.TextAlign = HorizontalAlignment.Center;
            autoReadTime.TextChanged += autoReadTime_TextChanged;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Font = new Font("黑体", 12F, FontStyle.Bold);
            label11.Location = new Point(6, 35);
            label11.Name = "label11";
            label11.Size = new Size(111, 16);
            label11.TabIndex = 418;
            label11.Text = "读取间隔(ms)";
            // 
            // adcRange
            // 
            adcRange.AutoSize = true;
            adcRange.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcRange.ForeColor = Color.FromArgb(20, 131, 197);
            adcRange.Location = new Point(1173, 163);
            adcRange.Name = "adcRange";
            adcRange.Size = new Size(105, 20);
            adcRange.TabIndex = 529;
            adcRange.Text = "ADC量程5V";
            adcRange.UseVisualStyleBackColor = true;
            adcRange.CheckedChanged += adcRange_CheckedChanged;
            adcRange.Click += adcRange_Click;
            // 
            // adcSignalType
            // 
            adcSignalType.AutoSize = true;
            adcSignalType.Font = new Font("黑体", 12F, FontStyle.Bold);
            adcSignalType.ForeColor = Color.FromArgb(20, 131, 197);
            adcSignalType.Location = new Point(1173, 133);
            adcSignalType.Name = "adcSignalType";
            adcSignalType.Size = new Size(77, 20);
            adcSignalType.TabIndex = 529;
            adcSignalType.Text = "电压型";
            adcSignalType.UseVisualStyleBackColor = true;
            adcSignalType.CheckedChanged += adcSignalType_CheckedChanged;
            adcSignalType.Click += testCurrent_Click;
            // 
            // dinCheck6
            // 
            dinCheck6.AutoSize = true;
            dinCheck6.Enabled = false;
            dinCheck6.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck6.ForeColor = Color.DarkCyan;
            dinCheck6.Location = new Point(78, 64);
            dinCheck6.Name = "dinCheck6";
            dinCheck6.Size = new Size(62, 20);
            dinCheck6.TabIndex = 535;
            dinCheck6.Text = "DIN6";
            dinCheck6.UseVisualStyleBackColor = true;
            // 
            // dinCheck5
            // 
            dinCheck5.AutoSize = true;
            dinCheck5.Enabled = false;
            dinCheck5.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck5.ForeColor = Color.Green;
            dinCheck5.Location = new Point(78, 35);
            dinCheck5.Name = "dinCheck5";
            dinCheck5.Size = new Size(62, 20);
            dinCheck5.TabIndex = 534;
            dinCheck5.Text = "DIN5";
            dinCheck5.UseVisualStyleBackColor = true;
            // 
            // dinCheck4
            // 
            dinCheck4.AutoSize = true;
            dinCheck4.Enabled = false;
            dinCheck4.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck4.ForeColor = Color.Orange;
            dinCheck4.Location = new Point(11, 120);
            dinCheck4.Name = "dinCheck4";
            dinCheck4.Size = new Size(62, 20);
            dinCheck4.TabIndex = 533;
            dinCheck4.Text = "DIN4";
            dinCheck4.UseVisualStyleBackColor = true;
            // 
            // dinCheck3
            // 
            dinCheck3.AutoSize = true;
            dinCheck3.Enabled = false;
            dinCheck3.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck3.ForeColor = Color.Magenta;
            dinCheck3.Location = new Point(11, 91);
            dinCheck3.Name = "dinCheck3";
            dinCheck3.Size = new Size(62, 20);
            dinCheck3.TabIndex = 532;
            dinCheck3.Text = "DIN3";
            dinCheck3.UseVisualStyleBackColor = true;
            // 
            // dinCheck2
            // 
            dinCheck2.AutoSize = true;
            dinCheck2.Enabled = false;
            dinCheck2.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck2.ForeColor = Color.Red;
            dinCheck2.Location = new Point(11, 62);
            dinCheck2.Name = "dinCheck2";
            dinCheck2.Size = new Size(62, 20);
            dinCheck2.TabIndex = 531;
            dinCheck2.Text = "DIN2";
            dinCheck2.UseVisualStyleBackColor = true;
            // 
            // dinCheck1
            // 
            dinCheck1.AutoSize = true;
            dinCheck1.Enabled = false;
            dinCheck1.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck1.ForeColor = Color.Brown;
            dinCheck1.Location = new Point(11, 33);
            dinCheck1.Name = "dinCheck1";
            dinCheck1.Size = new Size(62, 20);
            dinCheck1.TabIndex = 530;
            dinCheck1.Text = "DIN1";
            dinCheck1.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            groupBox1.BackColor = Color.White;
            groupBox1.Controls.Add(label11);
            groupBox1.Controls.Add(autoReadTime);
            groupBox1.Controls.Add(autoReadCheck);
            groupBox1.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox1.Location = new Point(707, 134);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(273, 103);
            groupBox1.TabIndex = 538;
            groupBox1.TabStop = false;
            groupBox1.Text = "单点记录仪(抓取电脑时间存储)";
            groupBox1.Enter += groupBox1_Enter;
            // 
            // groupBox2
            // 
            groupBox2.BackColor = Color.White;
            groupBox2.Controls.Add(chk_recent1000);
            groupBox2.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox2.Location = new Point(707, 40);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(273, 68);
            groupBox2.TabIndex = 539;
            groupBox2.TabStop = false;
            groupBox2.Text = "多点记录仪(最大5K采样率)";
            // 
            // groupBox3
            // 
            groupBox3.BackColor = Color.White;
            groupBox3.Controls.Add(ckb_sramTrigEnable);
            groupBox3.Controls.Add(label16);
            groupBox3.Controls.Add(setSramSamplingTime);
            groupBox3.Controls.Add(label10);
            groupBox3.Controls.Add(sramSecond);
            groupBox3.Controls.Add(label8);
            groupBox3.Controls.Add(sramMinute);
            groupBox3.Controls.Add(label7);
            groupBox3.Controls.Add(sramHour);
            groupBox3.Controls.Add(label5);
            groupBox3.Controls.Add(button7);
            groupBox3.Controls.Add(button6);
            groupBox3.Controls.Add(button5);
            groupBox3.Controls.Add(button3);
            groupBox3.Controls.Add(button1);
            groupBox3.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox3.Location = new Point(392, 37);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(309, 200);
            groupBox3.TabIndex = 540;
            groupBox3.TabStop = false;
            groupBox3.Text = "SRAM记录仪";
            // 
            // ckb_sramTrigEnable
            // 
            ckb_sramTrigEnable.AutoSize = true;
            ckb_sramTrigEnable.Font = new Font("黑体", 12F, FontStyle.Bold);
            ckb_sramTrigEnable.ForeColor = Color.SteelBlue;
            ckb_sramTrigEnable.Location = new Point(16, 150);
            ckb_sramTrigEnable.Name = "ckb_sramTrigEnable";
            ckb_sramTrigEnable.Size = new Size(183, 20);
            ckb_sramTrigEnable.TabIndex = 559;
            ckb_sramTrigEnable.Text = "DIN8触发SRAM记录仪";
            ckb_sramTrigEnable.UseVisualStyleBackColor = true;
            ckb_sramTrigEnable.Click += checkBox2_Click;
            // 
            // groupBox5
            // 
            groupBox5.BackColor = Color.White;
            groupBox5.Controls.Add(label2);
            groupBox5.Controls.Add(label1);
            groupBox5.Controls.Add(button17);
            groupBox5.Controls.Add(button16);
            groupBox5.Controls.Add(ckb_RefreshWave);
            groupBox5.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox5.ForeColor = Color.Black;
            groupBox5.Location = new Point(229, 40);
            groupBox5.Name = "groupBox5";
            groupBox5.Size = new Size(166, 197);
            groupBox5.TabIndex = 542;
            groupBox5.TabStop = false;
            groupBox5.Text = "在线记录仪";
            groupBox5.Enter += groupBox5_Enter;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("黑体", 10F, FontStyle.Bold);
            label2.Location = new Point(35, 35);
            label2.Name = "label2";
            label2.Size = new Size(99, 14);
            label2.TabIndex = 561;
            label2.Text = "(1K速率预览)";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("黑体", 10F, FontStyle.Bold);
            label1.Location = new Point(22, 18);
            label1.Name = "label1";
            label1.Size = new Size(128, 14);
            label1.TabIndex = 560;
            label1.Text = "(高性能电脑适用)";
            // 
            // groupBox7
            // 
            groupBox7.BackColor = Color.White;
            groupBox7.Controls.Add(adcValue8);
            groupBox7.Controls.Add(adcValue7);
            groupBox7.Controls.Add(adcValue6);
            groupBox7.Controls.Add(adcValue5);
            groupBox7.Controls.Add(adcValue4);
            groupBox7.Controls.Add(adcValue3);
            groupBox7.Controls.Add(adcValue2);
            groupBox7.Controls.Add(adcValue1);
            groupBox7.Controls.Add(adcCheck8);
            groupBox7.Controls.Add(adcCheck7);
            groupBox7.Controls.Add(adcCheck6);
            groupBox7.Controls.Add(adcCheck5);
            groupBox7.Controls.Add(adcCheck4);
            groupBox7.Controls.Add(adcCheck3);
            groupBox7.Controls.Add(adcCheck2);
            groupBox7.Controls.Add(adcCheck1);
            groupBox7.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox7.Location = new Point(1, 355);
            groupBox7.Name = "groupBox7";
            groupBox7.Size = new Size(188, 272);
            groupBox7.TabIndex = 544;
            groupBox7.TabStop = false;
            groupBox7.Text = "模拟输入";
            // 
            // groupBox6
            // 
            groupBox6.BackColor = Color.White;
            groupBox6.Controls.Add(dinCheck8);
            groupBox6.Controls.Add(dinCheck7);
            groupBox6.Controls.Add(dinCheck6);
            groupBox6.Controls.Add(dinCheck5);
            groupBox6.Controls.Add(dinCheck4);
            groupBox6.Controls.Add(dinCheck3);
            groupBox6.Controls.Add(dinCheck2);
            groupBox6.Controls.Add(dinCheck1);
            groupBox6.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox6.Location = new Point(1, 640);
            groupBox6.Name = "groupBox6";
            groupBox6.Size = new Size(188, 158);
            groupBox6.TabIndex = 545;
            groupBox6.TabStop = false;
            groupBox6.Text = "数字输入";
            // 
            // dinCheck8
            // 
            dinCheck8.AutoSize = true;
            dinCheck8.Enabled = false;
            dinCheck8.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck8.ForeColor = Color.Purple;
            dinCheck8.Location = new Point(78, 122);
            dinCheck8.Name = "dinCheck8";
            dinCheck8.Size = new Size(62, 20);
            dinCheck8.TabIndex = 537;
            dinCheck8.Text = "DIN8";
            dinCheck8.UseVisualStyleBackColor = true;
            // 
            // dinCheck7
            // 
            dinCheck7.AutoSize = true;
            dinCheck7.Enabled = false;
            dinCheck7.Font = new Font("黑体", 12F, FontStyle.Bold);
            dinCheck7.ForeColor = Color.Blue;
            dinCheck7.Location = new Point(78, 93);
            dinCheck7.Name = "dinCheck7";
            dinCheck7.Size = new Size(62, 20);
            dinCheck7.TabIndex = 536;
            dinCheck7.Text = "DIN7";
            dinCheck7.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            groupBox8.BackColor = Color.White;
            groupBox8.Controls.Add(button4);
            groupBox8.Controls.Add(setAdcSamplingRate);
            groupBox8.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox8.Location = new Point(12, 40);
            groupBox8.Name = "groupBox8";
            groupBox8.Size = new Size(167, 72);
            groupBox8.TabIndex = 546;
            groupBox8.TabStop = false;
            groupBox8.Text = "采样率设置";
            // 
            // button4
            // 
            button4.BackColor = Color.FromArgb(20, 131, 197);
            button4.Font = new Font("黑体", 12F, FontStyle.Bold);
            button4.ForeColor = Color.White;
            button4.Location = new Point(113, 27);
            button4.Name = "button4";
            button4.Size = new Size(54, 29);
            button4.TabIndex = 563;
            button4.Text = "写入";
            button4.UseVisualStyleBackColor = false;
            button4.Click += button4_Click;
            // 
            // autoRecent
            // 
            autoRecent.Enabled = true;
            autoRecent.Interval = 150;
            autoRecent.Tick += timer1_Tick;
            // 
            // ckb_autoscaling
            // 
            ckb_autoscaling.AutoSize = true;
            ckb_autoscaling.Font = new Font("黑体", 12F, FontStyle.Bold);
            ckb_autoscaling.ForeColor = Color.SteelBlue;
            ckb_autoscaling.Location = new Point(1291, 219);
            ckb_autoscaling.Name = "ckb_autoscaling";
            ckb_autoscaling.Size = new Size(94, 20);
            ckb_autoscaling.TabIndex = 560;
            ckb_autoscaling.Text = "自动缩放";
            ckb_autoscaling.UseVisualStyleBackColor = true;
            // 
            // groupBox9
            // 
            groupBox9.BackColor = Color.White;
            groupBox9.Controls.Add(diffCheck4);
            groupBox9.Controls.Add(diffCheck3);
            groupBox9.Controls.Add(diffCheck2);
            groupBox9.Controls.Add(diffCheck1);
            groupBox9.Font = new Font("黑体", 12F, FontStyle.Bold);
            groupBox9.Location = new Point(1, 169);
            groupBox9.Name = "groupBox9";
            groupBox9.Size = new Size(188, 142);
            groupBox9.TabIndex = 561;
            groupBox9.TabStop = false;
            groupBox9.Text = "差分设置";
            // 
            // diffCheck4
            // 
            diffCheck4.AutoSize = true;
            diffCheck4.Font = new Font("黑体", 12F, FontStyle.Bold);
            diffCheck4.ForeColor = Color.Blue;
            diffCheck4.Location = new Point(6, 108);
            diffCheck4.Name = "diffCheck4";
            diffCheck4.Size = new Size(87, 20);
            diffCheck4.TabIndex = 341;
            diffCheck4.Text = "差分7-8";
            diffCheck4.UseVisualStyleBackColor = true;
            diffCheck4.Click += diffCheck4_Click_2;
            // 
            // diffCheck3
            // 
            diffCheck3.AutoSize = true;
            diffCheck3.Font = new Font("黑体", 12F, FontStyle.Bold);
            diffCheck3.ForeColor = Color.Green;
            diffCheck3.Location = new Point(6, 83);
            diffCheck3.Name = "diffCheck3";
            diffCheck3.Size = new Size(87, 20);
            diffCheck3.TabIndex = 339;
            diffCheck3.Text = "差分5-6";
            diffCheck3.UseVisualStyleBackColor = true;
            diffCheck3.Click += diffCheck3_Click_2;
            // 
            // diffCheck2
            // 
            diffCheck2.AutoSize = true;
            diffCheck2.Font = new Font("黑体", 12F, FontStyle.Bold);
            diffCheck2.ForeColor = Color.Magenta;
            diffCheck2.Location = new Point(6, 58);
            diffCheck2.Name = "diffCheck2";
            diffCheck2.Size = new Size(87, 20);
            diffCheck2.TabIndex = 337;
            diffCheck2.Text = "差分3-4";
            diffCheck2.UseVisualStyleBackColor = true;
            diffCheck2.Click += diffCheck2_Click_2;
            // 
            // diffCheck1
            // 
            diffCheck1.AutoSize = true;
            diffCheck1.Font = new Font("黑体", 12F, FontStyle.Bold);
            diffCheck1.ForeColor = Color.Brown;
            diffCheck1.Location = new Point(6, 33);
            diffCheck1.Name = "diffCheck1";
            diffCheck1.Size = new Size(87, 20);
            diffCheck1.TabIndex = 335;
            diffCheck1.Text = "差分1-2";
            diffCheck1.UseVisualStyleBackColor = true;
            diffCheck1.Click += diffCheck1_Click_2;
            // 
            // autoscaling
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.FromArgb(242, 247, 250);
            ClientSize = new Size(1400, 800);
            Controls.Add(groupBox9);
            Controls.Add(ckb_autoscaling);
            Controls.Add(groupBox8);
            Controls.Add(button14);
            Controls.Add(groupBox6);
            Controls.Add(groupBox7);
            Controls.Add(groupBox5);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Controls.Add(adcSignalType);
            Controls.Add(adcRange);
            Controls.Add(button19);
            Controls.Add(calibEnable);
            Controls.Add(autoSave);
            Controls.Add(button13);
            Controls.Add(filePath);
            Controls.Add(progressBar);
            Controls.Add(button2);
            Controls.Add(waveform);
            FormBorderStyle = FormBorderStyle.None;
            Name = "autoscaling";
            Text = "adcRecord";
            Load += adcRecord_Load;
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            groupBox5.ResumeLayout(false);
            groupBox5.PerformLayout();
            groupBox7.ResumeLayout(false);
            groupBox7.PerformLayout();
            groupBox6.ResumeLayout(false);
            groupBox6.PerformLayout();
            groupBox8.ResumeLayout(false);
            groupBox8.PerformLayout();
            groupBox9.ResumeLayout(false);
            groupBox9.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private ScottPlot.WinForms.FormsPlot waveform;
        private CheckBox autoReadCheck;
        private Button button2;
        private CheckBox adcCheck8;
        private CheckBox adcCheck7;
        private CheckBox adcCheck6;
        private CheckBox adcCheck5;
        private CheckBox adcCheck4;
        private CheckBox adcCheck3;
        private CheckBox adcCheck2;
        private CheckBox adcCheck1;
        private Label adcValue1;
        private Label adcValue2;
        private Label adcValue3;
        private Label adcValue4;
        private Label adcValue8;
        private Label adcValue7;
        private Label adcValue6;
        private Label adcValue5;
        private Label label5;
        private Label sramHour;
        private Label label7;
        private Label label8;
        private Label sramMinute;
        private Label label10;
        private Label sramSecond;
        private Button button1;
        private Button button3;
        private Button button5;
        private Button button6;
        private Button button7;
        private TextBox setAdcSamplingRate;
        private Button button14;
        private Label label16;
        private TextBox setSramSamplingTime;
        private System.Windows.Forms.Timer autoRead;
        private ProgressBar progressBar;
        private Label filePath;
        private Button button13;
        private CheckBox autoSave;
        private Button button16;
        private Button button17;
        private CheckBox chk_recent1000;
        private CheckBox calibEnable;
        private Button button19;
        private TextBox adcUnit;
        private CheckBox ckb_RefreshWave;
        private TextBox autoReadTime;
        private Label label11;
        private CheckBox adcRange;
        private CheckBox adcSignalType;
        private CheckBox dinCheck6;
        private CheckBox dinCheck5;
        private CheckBox dinCheck4;
        private CheckBox dinCheck3;
        private CheckBox dinCheck2;
        private CheckBox dinCheck1;
        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private GroupBox groupBox5;
        private CheckBox ckb_sramTrigEnable;
        private GroupBox groupBox7;
        private GroupBox groupBox6;
        private GroupBox groupBox8;
        private Button button4;
        private System.Windows.Forms.Timer autoRecent;
        private CheckBox dinCheck8;
        private CheckBox dinCheck7;
        private CheckBox ckb_autoscaling;
        private GroupBox groupBox9;
        private CheckBox diffCheck4;
        private CheckBox diffCheck3;
        private CheckBox diffCheck2;
        private CheckBox diffCheck1;
        private Label label1;
        private Label label2;
    }
}