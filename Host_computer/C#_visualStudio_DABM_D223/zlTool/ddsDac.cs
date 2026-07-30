using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static zlTool.msgStruct;
using static zlTool.zlTool;

namespace zlTool
{
    public delegate void ddsDac_SendData(byte[] str);

    public partial class ddsDac : Form
    {

        public event ddsDac_SendData _ddsDacSendData;

        zlTool _mainForm = null;

        public ddsDac(zlTool zlMain)
        {
            InitializeComponent();
            _mainForm = zlMain;
        }


        private void usbDdsDac_Load(object sender, EventArgs e)
        {
            this._mainForm._deviceRxMsg += new deviceRxMsg(rxMsgProcess);
            clearSelectMode(1);
            clearSelectMode(2);
            clearSelectMode(3);
            clearSelectMode(4);
        }



        private void usbSendCmdNoParam(byte cmd, byte ch)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];
            //struct_noParam _pTx = new struct_noParam();

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgNoParam _pTx = (msgNoParam)Marshal.PtrToStructure(ptrStruct, typeof(msgNoParam));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(cmd);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = ch;

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _ddsDacSendData(txbuf);
        }



        private void usbSendCmdUByteParam(byte cmd, byte ch, byte data)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgUbyte _pTx = (msgUbyte)Marshal.PtrToStructure(ptrStruct, typeof(msgUbyte));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(cmd);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = ch;
            _pTx.data = data;

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _ddsDacSendData(txbuf);
        }

        private void usbSendCmdUWordParam(byte cmd, byte ch, UInt16 data)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgUWord _pTx = (msgUWord)Marshal.PtrToStructure(ptrStruct, typeof(msgUWord));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(cmd);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = ch;
            _pTx.data = SWAP16(data);

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _ddsDacSendData(txbuf);
        }


        List<UInt32> xAxisIndex = new List<UInt32>();

        List<double> adcRecord1 = new List<double>();
        List<double> adcRecord2 = new List<double>();
        List<double> adcRecord3 = new List<double>();
        List<double> adcRecord4 = new List<double>();
        List<double> adcRecord5 = new List<double>();
        List<double> adcRecord6 = new List<double>();
        List<double> adcRecord7 = new List<double>();
        List<double> adcRecord8 = new List<double>();

        UInt32 listAxisIndex = 0;
        const UInt16 ADC_ONCE_LEN = 4000;

        byte flash_year, flash_month, flash_day, flash_hour, flash_minute, flash_second, adc_ch_Enable;
        UInt16 flashRecordIntervalTime;

        public void rxMsgProcess(byte[] rxBuf)
        {
            BeginInvoke(new MethodInvoker(delegate
            {
                try
                {
                    msgHead _pRxHead = new msgHead();
                    _pRxHead = (msgHead)msgStruct.BytesToDataStruct(rxBuf, typeof(msgHead));

                    if (_pRxHead.cmdId == (byte)_CmdId._cmdId_ddsDacGetParam)
                    {
                        msgDdsDacParam _prxData = new msgDdsDacParam();
                        _prxData = (msgDdsDacParam)msgStruct.BytesToDataStruct(rxBuf, typeof(msgDdsDacParam));

                        if (_prxData.ch == 1)
                        {
                            double dacVolt = (double)(SWAP16(_prxData.volt) / 1000.0);
                            double dacBias = (double)(SWAP16(_prxData.bias) / 1000.0);
                            dacRate.Text = Convert.ToString(SWAP16(_prxData.dacRate));
                            dacFreq1.Text = Convert.ToString(SWAP16(_prxData.freq));
                            dacVolt1.Text = dacVolt.ToString("0.000");
                            dacDuty1.Text = Convert.ToString(SWAP16(_prxData.duty));
                            dacBias1.Text = dacBias.ToString("0.000");
                            ddsPhase1.Text = Convert.ToString(SWAP16(_prxData.phase));
                        }
                        else if (_prxData.ch == 2)
                        {
                            double dacVolt = (double)(SWAP16(_prxData.volt) / 1000.0);
                            double dacBias = (double)(SWAP16(_prxData.bias) / 1000.0);
                            dacRate.Text = Convert.ToString(SWAP16(_prxData.dacRate));
                            dacFreq2.Text = Convert.ToString(SWAP16(_prxData.freq));
                            dacVolt2.Text = dacVolt.ToString("0.000");
                            dacDuty2.Text = Convert.ToString(SWAP16(_prxData.duty));
                            dacBias2.Text = dacBias.ToString("0.000");
                            ddsPhase2.Text = Convert.ToString(SWAP16(_prxData.phase));
                        }
                        else if (_prxData.ch == 3)
                        {
                            double dacVolt = (double)(SWAP16(_prxData.volt) / 1000.0);
                            double dacBias = (double)(SWAP16(_prxData.bias) / 1000.0);
                            dacRate.Text = Convert.ToString(SWAP16(_prxData.dacRate));
                            dacFreq3.Text = Convert.ToString(SWAP16(_prxData.freq));
                            dacVolt3.Text = dacVolt.ToString("0.000");
                            dacDuty3.Text = Convert.ToString(SWAP16(_prxData.duty));
                            dacBias3.Text = dacBias.ToString("0.000");
                            ddsPhase3.Text = Convert.ToString(SWAP16(_prxData.phase));
                        }
                        else if (_prxData.ch == 4)
                        {
                            double dacVolt = (double)(SWAP16(_prxData.volt) / 1000.0);
                            double dacBias = (double)(SWAP16(_prxData.bias) / 1000.0);
                            dacRate.Text = Convert.ToString(SWAP16(_prxData.dacRate));
                            dacFreq4.Text = Convert.ToString(SWAP16(_prxData.freq));
                            dacVolt4.Text = dacVolt.ToString("0.000");
                            dacDuty4.Text = Convert.ToString(SWAP16(_prxData.duty));
                            dacBias4.Text = dacBias.ToString("0.000");
                            ddsPhase4.Text = Convert.ToString(SWAP16(_prxData.phase));
                        }
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_ddsDacGetCalibParam)
                    {
                        msgGetDacCalibParam _prxData = new msgGetDacCalibParam();
                        _prxData = (msgGetDacCalibParam)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetDacCalibParam));

                        ckb_enA1.Checked = _prxData._dacCalibDatasPointA[0].calibEnable == 1;
                        ckb_enA2.Checked = _prxData._dacCalibDatasPointA[1].calibEnable == 1;
                        ckb_enA3.Checked = _prxData._dacCalibDatasPointA[2].calibEnable == 1;
                        ckb_enA4.Checked = _prxData._dacCalibDatasPointA[3].calibEnable == 1;

                        ckb_enB1.Checked = _prxData._dacCalibDatasPointB[0].calibEnable == 1;
                        ckb_enB2.Checked = _prxData._dacCalibDatasPointB[1].calibEnable == 1;
                        ckb_enB3.Checked = _prxData._dacCalibDatasPointB[2].calibEnable == 1;
                        ckb_enB4.Checked = _prxData._dacCalibDatasPointB[3].calibEnable == 1;

                        calibDigitalA1.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointA[0].calibDigital));
                        calibDigitalA2.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointA[1].calibDigital));
                        calibDigitalA3.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointA[2].calibDigital));
                        calibDigitalA4.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointA[3].calibDigital));
                        calibDigitalB1.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointB[0].calibDigital));
                        calibDigitalB2.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointB[1].calibDigital));
                        calibDigitalB3.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointB[2].calibDigital));
                        calibDigitalB4.Text = Convert.ToString(SWAPS32(_prxData._dacCalibDatasPointB[3].calibDigital));

                        calibAnaloigA1.Text = (SWAPS32(_prxData._dacCalibDatasPointA[0].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigA2.Text = (SWAPS32(_prxData._dacCalibDatasPointA[1].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigA3.Text = (SWAPS32(_prxData._dacCalibDatasPointA[2].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigA4.Text = (SWAPS32(_prxData._dacCalibDatasPointA[3].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigB1.Text = (SWAPS32(_prxData._dacCalibDatasPointB[0].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigB2.Text = (SWAPS32(_prxData._dacCalibDatasPointB[1].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigB3.Text = (SWAPS32(_prxData._dacCalibDatasPointB[2].calibAnalog) * 0.001).ToString("0.000");
                        calibAnaloigB4.Text = (SWAPS32(_prxData._dacCalibDatasPointB[3].calibAnalog) * 0.001).ToString("0.000");

                    }
                }
                catch { }

            }));
        }


        private void dacParamSet1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(dacFreq1.Text)) return;
            if (string.IsNullOrEmpty(dacVolt1.Text)) return;
            if (string.IsNullOrEmpty(dacDuty1.Text)) return;
            if (string.IsNullOrEmpty(dacBias1.Text)) return;
            if (string.IsNullOrEmpty(ddsPhase1.Text)) return;

            UInt16 dacFreq = Convert.ToUInt16(dacFreq1.Text);
            double t1 = Convert.ToDouble(dacVolt1.Text);
            UInt16 dacDuty = Convert.ToUInt16(dacDuty1.Text);
            double t2 = Convert.ToDouble(dacBias1.Text);

            UInt16 dacphase = Convert.ToUInt16(ddsPhase1.Text);

            UInt16 dacVolt = (UInt16)(t1 * 1000);
            UInt16 dacBias = (UInt16)(t2 * 1000);

            func_setDdsDacParams(_CmdId._cmdId_setDdsDacParam, 1, dacFreq, dacVolt, dacDuty, dacBias, dacphase);
        }

        private void dacParamSet2_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(dacFreq2.Text)) return;
            if (string.IsNullOrEmpty(dacVolt2.Text)) return;
            if (string.IsNullOrEmpty(dacDuty2.Text)) return;
            if (string.IsNullOrEmpty(dacBias2.Text)) return;
            if (string.IsNullOrEmpty(ddsPhase2.Text)) return;
            UInt16 dacFreq = Convert.ToUInt16(dacFreq2.Text);
            double t1 = Convert.ToDouble(dacVolt2.Text);
            UInt16 dacDuty = Convert.ToUInt16(dacDuty2.Text);
            double t2 = Convert.ToDouble(dacBias2.Text);
            UInt16 dacphase = Convert.ToUInt16(ddsPhase2.Text);

            UInt16 dacVolt = (UInt16)(t1 * 1000);
            UInt16 dacBias = (UInt16)(t2 * 1000);
            func_setDdsDacParams(_CmdId._cmdId_setDdsDacParam, 2, dacFreq, dacVolt, dacDuty, dacBias, dacphase);
        }

        private void dacParamSet3_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(dacFreq3.Text)) return;
            if (string.IsNullOrEmpty(dacVolt3.Text)) return;
            if (string.IsNullOrEmpty(dacDuty3.Text)) return;
            if (string.IsNullOrEmpty(dacBias3.Text)) return;
            if (string.IsNullOrEmpty(ddsPhase3.Text)) return;
            UInt16 dacFreq = Convert.ToUInt16(dacFreq3.Text);
            double t1 = Convert.ToDouble(dacVolt3.Text);
            UInt16 dacDuty = Convert.ToUInt16(dacDuty3.Text);
            double t2 = Convert.ToDouble(dacBias3.Text);
            UInt16 dacphase = Convert.ToUInt16(ddsPhase3.Text);

            UInt16 dacVolt = (UInt16)(t1 * 1000);
            UInt16 dacBias = (UInt16)(t2 * 1000);
            func_setDdsDacParams(_CmdId._cmdId_setDdsDacParam, 3, dacFreq, dacVolt, dacDuty, dacBias, dacphase);
        }

        private void dacParamSet4_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(dacFreq4.Text)) return;
            if (string.IsNullOrEmpty(dacVolt4.Text)) return;
            if (string.IsNullOrEmpty(dacDuty4.Text)) return;
            if (string.IsNullOrEmpty(dacBias4.Text)) return;
            if (string.IsNullOrEmpty(ddsPhase4.Text)) return;
            UInt16 dacFreq = Convert.ToUInt16(dacFreq4.Text);
            double t1 = Convert.ToDouble(dacVolt4.Text);
            UInt16 dacDuty = Convert.ToUInt16(dacDuty4.Text);
            double t2 = Convert.ToDouble(dacBias4.Text);
            UInt16 dacphase = Convert.ToUInt16(ddsPhase4.Text);

            UInt16 dacVolt = (UInt16)(t1 * 1000);
            UInt16 dacBias = (UInt16)(t2 * 1000);
            func_setDdsDacParams(_CmdId._cmdId_setDdsDacParam, 4, dacFreq, dacVolt, dacDuty, dacBias, dacphase);
        }

        private void func_setDdsDacParams(_CmdId cmd, byte ch, UInt16 freq, UInt16 volt, UInt16 duty, UInt16 bias, UInt16 phase)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgDdsDacParam _pTx = (msgDdsDacParam)Marshal.PtrToStructure(ptrStruct, typeof(msgDdsDacParam));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(cmd);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = Convert.ToByte(ch);
            _pTx.dacRate = SWAP16(Convert.ToUInt16(dacRate.Text));
            _pTx.freq = SWAP16(freq);
            _pTx.volt = SWAP16(volt);
            _pTx.duty = SWAP16(duty);
            _pTx.bias = SWAP16(bias);
            _pTx.phase = SWAP16(phase);

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _ddsDacSendData(txbuf);
        }

        private void clearSelectMode(byte ch)
        {
            if (ch == 1)
            {
                ckb_stop1.Checked = false;
                ckb_dc1.Checked = false;
                ckb_sin1.Checked = false;
                ckb_triangle1.Checked = false;
                ckb_square1.Checked = false;
                ckb_dds1.Checked = false;
                ckb_calib1.Checked = false;
                calibAnaloigA1.Enabled = false;
                calibAnaloigB1.Enabled = false;
                calibClear1.Enabled = false;
            }
            else if (ch == 2)
            {
                ckb_stop2.Checked = false;
                ckb_dc2.Checked = false;
                ckb_sin2.Checked = false;
                ckb_triangle2.Checked = false;
                ckb_square2.Checked = false;
                ckb_dds2.Checked = false;
                ckb_calib2.Checked = false;
                calibAnaloigA2.Enabled = false;
                calibAnaloigB2.Enabled = false;
                calibClear2.Enabled = false;
            }
            else if (ch == 3)
            {
                ckb_stop3.Checked = false;
                ckb_dc3.Checked = false;
                ckb_sin3.Checked = false;
                ckb_triangle3.Checked = false;
                ckb_square3.Checked = false;
                ckb_dds3.Checked = false;
                ckb_calib3.Checked = false;
                calibAnaloigA3.Enabled = false;
                calibAnaloigB3.Enabled = false;
                calibClear3.Enabled = false;
            }
            else if (ch == 4)
            {
                ckb_stop4.Checked = false;
                ckb_dc4.Checked = false;
                ckb_sin4.Checked = false;
                ckb_triangle4.Checked = false;
                ckb_square4.Checked = false;
                ckb_dds4.Checked = false;
                ckb_calib4.Checked = false;
                calibAnaloigA4.Enabled = false;
                calibAnaloigB4.Enabled = false;
                calibClear4.Enabled = false;
            }
        }


        private void ckb_stop1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            ckb_stop1.Checked = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Stop));
        }


        private void ckb_stop2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            ckb_stop2.Checked = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Stop));
        }

        private void ckb_stop3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            ckb_stop3.Checked = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Stop));
        }

        private void ckb_stop4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            ckb_stop4.Checked = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Stop));
        }

        private void ckb_dc1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            ckb_dc1.Checked = true;

            dacVolt1.Enabled = true;
            dacFreq1.Enabled = false;
            dacBias1.Enabled = false;
            dacDuty1.Enabled = false;
            ddsPhase1.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dc));
        }

        private void ckb_dc2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            ckb_dc2.Checked = true;

            dacVolt2.Enabled = true;
            dacFreq2.Enabled = false;
            dacBias2.Enabled = false;
            dacDuty2.Enabled = false;
            ddsPhase2.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dc));
        }

        private void ckb_dc3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            ckb_dc3.Checked = true;

            dacVolt3.Enabled = true;
            dacFreq3.Enabled = false;
            dacBias3.Enabled = false;
            dacDuty3.Enabled = false;
            ddsPhase3.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dc));
        }

        private void ckb_dc4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            ckb_dc4.Checked = true;

            dacVolt4.Enabled = true;
            dacFreq4.Enabled = false;
            dacBias4.Enabled = false;
            dacDuty4.Enabled = false;
            ddsPhase4.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dc));
        }

        private void ckb_sin1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            ckb_sin1.Checked = true;

            dacVolt1.Enabled = true;
            dacFreq1.Enabled = true;
            dacBias1.Enabled = true;
            dacDuty1.Enabled = false;
            ddsPhase1.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Sin));
        }

        private void ckb_sin2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            ckb_sin2.Checked = true;

            dacVolt2.Enabled = true;
            dacFreq2.Enabled = true;
            dacBias2.Enabled = true;
            dacDuty2.Enabled = false;
            ddsPhase2.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Sin));
        }

        private void ckb_sin3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            ckb_sin3.Checked = true;

            dacVolt3.Enabled = true;
            dacFreq3.Enabled = true;
            dacBias3.Enabled = true;
            dacDuty3.Enabled = false;
            ddsPhase3.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Sin));
        }

        private void ckb_sin4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            ckb_sin4.Checked = true;

            dacVolt4.Enabled = true;
            dacFreq4.Enabled = true;
            dacBias4.Enabled = true;
            dacDuty4.Enabled = false;
            ddsPhase4.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Sin));
        }

        private void ckb_triangle1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            ckb_triangle1.Checked = true;

            dacVolt1.Enabled = true;
            dacFreq1.Enabled = true;
            dacBias1.Enabled = true;
            dacDuty1.Enabled = false;
            ddsPhase1.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Triangle));
        }

        private void ckb_triangle2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            ckb_triangle2.Checked = true;

            dacVolt2.Enabled = true;
            dacFreq2.Enabled = true;
            dacBias2.Enabled = true;
            dacDuty2.Enabled = false;
            ddsPhase2.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Triangle));
        }

        private void ckb_triangle3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            ckb_triangle3.Checked = true;

            dacVolt3.Enabled = true;
            dacFreq3.Enabled = true;
            dacBias3.Enabled = true;
            dacDuty3.Enabled = false;
            ddsPhase3.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Triangle));
        }

        private void ckb_triangle4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            ckb_triangle4.Checked = true;

            dacVolt4.Enabled = true;
            dacFreq4.Enabled = true;
            dacBias4.Enabled = true;
            dacDuty4.Enabled = false;
            ddsPhase4.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Triangle));
        }

        private void ckb_square1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            ckb_square1.Checked = true;

            dacVolt1.Enabled = true;
            dacFreq1.Enabled = true;
            dacBias1.Enabled = true;
            dacDuty1.Enabled = true;
            ddsPhase1.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Square));
        }


        private void ckb_square2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            ckb_square2.Checked = true;

            dacVolt2.Enabled = true;
            dacFreq2.Enabled = true;
            dacBias2.Enabled = true;
            dacDuty2.Enabled = true;
            ddsPhase2.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Square));
        }

        private void ckb_square3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            ckb_square3.Checked = true;

            dacVolt3.Enabled = true;
            dacFreq3.Enabled = true;
            dacBias3.Enabled = true;
            dacDuty3.Enabled = true;
            ddsPhase3.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Square));
        }

        private void ckb_square4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            ckb_square4.Checked = true;

            dacVolt4.Enabled = true;
            dacFreq4.Enabled = true;
            dacBias4.Enabled = true;
            dacDuty4.Enabled = true;
            ddsPhase4.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Square));
        }

        private void ckb_dds1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            ckb_dds1.Checked = true;

            dacVolt1.Enabled = false;
            dacFreq1.Enabled = false;
            dacBias1.Enabled = true;
            dacDuty1.Enabled = false;
            ddsPhase1.Enabled = false;


            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dds));
        }

        private void ckb_dds2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            ckb_dds2.Checked = true;

            dacVolt2.Enabled = false;
            dacFreq2.Enabled = false;
            dacBias2.Enabled = true;
            dacDuty2.Enabled = false;
            ddsPhase2.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dds));
        }

        private void ckb_dds3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            ckb_dds3.Checked = true;

            dacVolt3.Enabled = false;
            dacFreq3.Enabled = false;
            dacBias3.Enabled = true;
            dacDuty3.Enabled = false;
            ddsPhase3.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dds));
        }

        private void ckb_dds4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            ckb_dds4.Checked = true;

            dacVolt4.Enabled = false;
            dacFreq4.Enabled = false;
            dacBias4.Enabled = true;
            dacDuty4.Enabled = false;
            ddsPhase4.Enabled = true;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Dds));
        }

        private void ckb_calib1_Click(object sender, EventArgs e)
        {
            clearSelectMode(1);
            calibAnaloigA1.Enabled = true;
            calibAnaloigB1.Enabled = true;
            calibClear1.Enabled = true;

            ckb_calib1.Checked = true;

            dacVolt1.Enabled = true;
            dacFreq1.Enabled = false;
            dacBias1.Enabled = false;
            dacDuty1.Enabled = false;
            ddsPhase1.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 1,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Calib));
        }

        private void ckb_calib2_Click(object sender, EventArgs e)
        {
            clearSelectMode(2);
            calibAnaloigA2.Enabled = true;
            calibAnaloigB2.Enabled = true;
            ckb_calib2.Checked = true;
            calibClear2.Enabled = true;

            dacVolt2.Enabled = true;
            dacFreq2.Enabled = false;
            dacBias2.Enabled = false;
            dacDuty2.Enabled = false;
            ddsPhase2.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 2,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Calib));
        }

        private void ckb_calib3_Click(object sender, EventArgs e)
        {
            clearSelectMode(3);
            calibAnaloigA3.Enabled = true;
            calibAnaloigB3.Enabled = true;
            ckb_calib3.Checked = true;
            calibClear3.Enabled = true;

            dacVolt3.Enabled = true;
            dacFreq3.Enabled = false;
            dacBias3.Enabled = false;
            dacDuty3.Enabled = false;
            ddsPhase3.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 3,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Calib));
        }

        private void ckb_calib4_Click(object sender, EventArgs e)
        {
            clearSelectMode(4);
            calibAnaloigA4.Enabled = true;
            calibAnaloigB4.Enabled = true;
            ckb_calib4.Checked = true;
            calibClear4.Enabled = true;

            dacVolt4.Enabled = true;
            dacFreq4.Enabled = false;
            dacBias4.Enabled = false;
            dacDuty4.Enabled = false;
            ddsPhase4.Enabled = false;

            usbSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setDdsDacWorkMode), 4,
                Convert.ToByte(_ddsDacWorkMode._ddsDacWorkMode_Calib));
        }

        private void button13_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(dacRate.Text)) return;
            UInt32 freq = Convert.ToUInt16(dacRate.Text);
            usbSendCmdUWordParam(Convert.ToByte(_CmdId._cmdId_setAdc_samplingRate), 0, (UInt16)freq);

        }

        private void button6_Click(object sender, EventArgs e)
        {
            string[] loadText = new string[200000];
            UInt16 maxLen = 0;

            try
            {
                //string s_con = string.Empty;
                // 创建一个 StreamReader 的实例来读取文件 
                // using 语句也能关闭 StreamReader
                var f = new OpenFileDialog();
                f.Multiselect = false; //多选
                string path = "";
                if (f.ShowDialog() == DialogResult.OK)
                {
                    String filepath = f.FileName;//G:\新建文件夹\新建文本文档.txt
                    //String filename = f.SafeFileName;//新建文本文档.txt
                    path = filepath;
                }
                else
                {
                    return;
                }

                //string s_con = string.Empty;
                // 创建一个 StreamReader 的实例来读取文件 
                // using 语句也能关闭 StreamReader
                using (StreamReader sr = new StreamReader(path))
                {
                    string line;
                    // 从文件读取并显示行，直到文件的末尾 
                    //只读取1000行, 超过1000行的部分忽略, 不足的话按照实际长度读取
                    for (Int32 i = 0; i < 1000; i++)
                    {
                        if ((line = sr.ReadLine()) != null)
                        {
                            loadText[maxLen] = line;
                            maxLen++;
                        }
                    }
                }
            }
            catch (Exception ex) { }


            //消息数组转结构体//

            msgSetDacDatas _pTx = new msgSetDacDatas();

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(30000);//分配非托管内存空间
            _pTx = (msgSetDacDatas)Marshal.PtrToStructure(ptrStruct, typeof(msgSetDacDatas));
            Marshal.FreeHGlobal(ptrStruct);//释放内存

            _pTx.head = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(_CmdId._cmdId_setDdsDacDatas);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.dataLen = SWAP16(maxLen);
            xDdsWaveIndex.Clear();
            ddsWave.Clear();

            try
            {
                //填充结构体正文
                for (UInt16 i = 0; i < maxLen; i++)
                {
                    string[] AryBuf = new string[10];
                    if (loadText[i].Contains(',') == false)
                    {
                        continue;
                    }

                    AryBuf = loadText[i].Split(',');

                    if (string.IsNullOrEmpty(AryBuf[0])) return;
                    _pTx.ddsDatas[i] = SWAP16((Convert.ToUInt16(AryBuf[0])));
                    xDdsWaveIndex.Add(i);
                    ddsWave.Add(_pTx.ddsDatas[i] * 5.0 / 1000);

                }
            }
            catch { }
            waveform.Plot.Clear();
            waveform.Plot.Add.ScatterLine(xDdsWaveIndex, ddsWave, ScottPlot.Colors.Red);
            waveform.Plot.Axes.SetLimits(0, maxLen, -10, ddsWave.Max() + 10);
            waveform.Show();
            waveform.Refresh();

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _ddsDacSendData(txbuf);
        }

        List<UInt16> xDdsWaveIndex = new List<UInt16>();
        List<double> ddsWave = new List<double>();

        private void button5_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA1.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA1.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint1), 1, volt);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA2.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA2.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint1), 2, volt);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA3.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA3.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint1), 3, volt);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA4.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA4.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint1), 4, volt);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB1.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB1.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint2), 1, volt);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB2.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB2.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint2), 2, volt);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB3.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB3.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint2), 3, volt);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB4.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB4.Text);
            if (voltF > 65.535) { voltF = 65.535; }
            UInt16 volt = (UInt16)(voltF * 1000);
            usbSendCmdUWordParam((Byte)(_CmdId._cmdId_ddsDacCalibPoint2), 4, volt);
        }

        private void button14_Click(object sender, EventArgs e)
        {
            usbSendCmdNoParam((Byte)(_CmdId._cmdId_ddsDacClearCalib), 1);
        }

        private void button13_Click_1(object sender, EventArgs e)
        {
            usbSendCmdNoParam((Byte)(_CmdId._cmdId_ddsDacClearCalib), 2);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            usbSendCmdNoParam((Byte)(_CmdId._cmdId_ddsDacClearCalib), 3);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            usbSendCmdNoParam((Byte)(_CmdId._cmdId_ddsDacClearCalib), 4);
        }

        private void setAdcSamplingRate_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
