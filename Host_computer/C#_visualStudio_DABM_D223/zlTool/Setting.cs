using ScottPlot.Colormaps;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.DirectoryServices.ActiveDirectory;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static OpenTK.Graphics.OpenGL.GL;
using static System.Runtime.InteropServices.JavaScript.JSType;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Rebar;
using static zlTool.msgStruct;
using static zlTool.zlTool;

namespace zlTool
{
    public delegate void settingSendData(byte[] str);

    public partial class Setting : Form
    {
        public event settingSendData _settingSendData;

        zlTool _mainForm = null;

        public Setting(zlTool zlMain)
        {
            InitializeComponent();
            _mainForm = zlMain;

        }

        private void Setting_Load(object sender, EventArgs e)
        {
            this._mainForm._deviceRxMsg += new deviceRxMsg(rxMsgProcess);
            sensorUnit1.Items.Clear();
            sensorUnit2.Items.Clear();
            sensorUnit3.Items.Clear();
            sensorUnit4.Items.Clear();
            sensorUnit5.Items.Clear();
            sensorUnit6.Items.Clear();
            sensorUnit7.Items.Clear();
            sensorUnit8.Items.Clear();
            sensorUnit1.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit2.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit3.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit4.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit5.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit6.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit7.Items.AddRange(adcCalibParams.sensorUnitList);
            sensorUnit8.Items.AddRange(adcCalibParams.sensorUnitList);

        }

        public void rxMsgProcess(byte[] rxBuf)
        {
            BeginInvoke(new MethodInvoker(delegate
            {
                try
                {
                    msgHead _pRxHead = new msgHead();
                    _pRxHead = (msgHead)msgStruct.BytesToDataStruct(rxBuf, typeof(msgHead));

                    if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getSoftVersion)
                    {
                        msgULong _prxData = new msgULong();
                        _prxData = (msgULong)msgStruct.BytesToDataStruct(rxBuf, typeof(msgULong));

                        softVersion.Text = SWAP32(_prxData.data).ToString("X08");
                        if (upperVersion.Text == softVersion.Text)
                        {
                            checkResult.Text = "成功";
                        }
                        else
                        {
                            checkResult.Text = "失败";
                            MessageBox.Show("版本校验失败,请在网盘重新下载采集卡固件并烧录!");
                        }
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getSettingParam)
                    {
                        msgGetSettingParam _prxData = new msgGetSettingParam();
                        _prxData = (msgGetSettingParam)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetSettingParam));


                        ckb_enAdcCalib.Checked = _prxData.deviceWorkMode == 1;
                        ckb_enA1.Checked = _prxData._adcCalibDatasPointA[0].calibEnable == 1;
                        ckb_enA2.Checked = _prxData._adcCalibDatasPointA[1].calibEnable == 1;
                        ckb_enA3.Checked = _prxData._adcCalibDatasPointA[2].calibEnable == 1;
                        ckb_enA4.Checked = _prxData._adcCalibDatasPointA[3].calibEnable == 1;
                        ckb_enA5.Checked = _prxData._adcCalibDatasPointA[4].calibEnable == 1;
                        ckb_enA6.Checked = _prxData._adcCalibDatasPointA[5].calibEnable == 1;
                        ckb_enA7.Checked = _prxData._adcCalibDatasPointA[6].calibEnable == 1;
                        ckb_enA8.Checked = _prxData._adcCalibDatasPointA[7].calibEnable == 1;

                        ckb_enB1.Checked = _prxData._adcCalibDatasPointB[0].calibEnable == 1;
                        ckb_enB2.Checked = _prxData._adcCalibDatasPointB[1].calibEnable == 1;
                        ckb_enB3.Checked = _prxData._adcCalibDatasPointB[2].calibEnable == 1;
                        ckb_enB4.Checked = _prxData._adcCalibDatasPointB[3].calibEnable == 1;
                        ckb_enB5.Checked = _prxData._adcCalibDatasPointB[4].calibEnable == 1;
                        ckb_enB6.Checked = _prxData._adcCalibDatasPointB[5].calibEnable == 1;
                        ckb_enB7.Checked = _prxData._adcCalibDatasPointB[6].calibEnable == 1;
                        ckb_enB8.Checked = _prxData._adcCalibDatasPointB[7].calibEnable == 1;

                        recordDelay.Text = Convert.ToString(_prxData.RecordDelay);


                        calibDigitalA1.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[0].calibDigital));
                        calibDigitalA2.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[1].calibDigital));
                        calibDigitalA3.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[2].calibDigital));
                        calibDigitalA4.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[3].calibDigital));
                        calibDigitalA5.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[4].calibDigital));
                        calibDigitalA6.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[5].calibDigital));
                        calibDigitalA7.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[6].calibDigital));
                        calibDigitalA8.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointA[7].calibDigital));


                        calibDigitalB1.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[0].calibDigital));
                        calibDigitalB2.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[1].calibDigital));
                        calibDigitalB3.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[2].calibDigital));
                        calibDigitalB4.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[3].calibDigital));
                        calibDigitalB5.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[4].calibDigital));
                        calibDigitalB6.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[5].calibDigital));
                        calibDigitalB7.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[6].calibDigital));
                        calibDigitalB8.Text = Convert.ToString(SWAPS32(_prxData._adcCalibDatasPointB[7].calibDigital));

                        calibAnaloigA1.Text = (SWAPS32(_prxData._adcCalibDatasPointA[0].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA2.Text = (SWAPS32(_prxData._adcCalibDatasPointA[1].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA3.Text = (SWAPS32(_prxData._adcCalibDatasPointA[2].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA4.Text = (SWAPS32(_prxData._adcCalibDatasPointA[3].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA5.Text = (SWAPS32(_prxData._adcCalibDatasPointA[4].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA6.Text = (SWAPS32(_prxData._adcCalibDatasPointA[5].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA7.Text = (SWAPS32(_prxData._adcCalibDatasPointA[6].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigA8.Text = (SWAPS32(_prxData._adcCalibDatasPointA[7].calibAnalog) * 0.00001).ToString("0.00000");

                        calibAnaloigB1.Text = (SWAPS32(_prxData._adcCalibDatasPointB[0].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB2.Text = (SWAPS32(_prxData._adcCalibDatasPointB[1].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB3.Text = (SWAPS32(_prxData._adcCalibDatasPointB[2].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB4.Text = (SWAPS32(_prxData._adcCalibDatasPointB[3].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB5.Text = (SWAPS32(_prxData._adcCalibDatasPointB[4].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB6.Text = (SWAPS32(_prxData._adcCalibDatasPointB[5].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB7.Text = (SWAPS32(_prxData._adcCalibDatasPointB[6].calibAnalog) * 0.00001).ToString("0.00000");
                        calibAnaloigB8.Text = (SWAPS32(_prxData._adcCalibDatasPointB[7].calibAnalog) * 0.00001).ToString("0.00000");

                        correctFactor1.Text = (SWAPS32(_prxData.correctFactor[0]) * 0.00001).ToString("0.00000");
                        correctFactor2.Text = (SWAPS32(_prxData.correctFactor[1]) * 0.00001).ToString("0.00000");
                        correctFactor3.Text = (SWAPS32(_prxData.correctFactor[2]) * 0.00001).ToString("0.00000");
                        correctFactor4.Text = (SWAPS32(_prxData.correctFactor[3]) * 0.00001).ToString("0.00000");
                        correctFactor5.Text = (SWAPS32(_prxData.correctFactor[4]) * 0.00001).ToString("0.00000");
                        correctFactor6.Text = (SWAPS32(_prxData.correctFactor[5]) * 0.00001).ToString("0.00000");
                        correctFactor7.Text = (SWAPS32(_prxData.correctFactor[6]) * 0.00001).ToString("0.00000");
                        correctFactor8.Text = (SWAPS32(_prxData.correctFactor[7]) * 0.00001).ToString("0.00000");

                        calibZero1.Text = (SWAPS32(_prxData.calibZero[0]) * 0.00001).ToString("0.00000");
                        calibZero2.Text = (SWAPS32(_prxData.calibZero[1]) * 0.00001).ToString("0.00000");
                        calibZero3.Text = (SWAPS32(_prxData.calibZero[2]) * 0.00001).ToString("0.00000");
                        calibZero4.Text = (SWAPS32(_prxData.calibZero[3]) * 0.00001).ToString("0.00000");
                        calibZero5.Text = (SWAPS32(_prxData.calibZero[4]) * 0.00001).ToString("0.00000");
                        calibZero6.Text = (SWAPS32(_prxData.calibZero[5]) * 0.00001).ToString("0.00000");
                        calibZero7.Text = (SWAPS32(_prxData.calibZero[6]) * 0.00001).ToString("0.00000");
                        calibZero8.Text = (SWAPS32(_prxData.calibZero[7]) * 0.00001).ToString("0.00000");

                        for (int i = 0; i < 8; i++)
                        {
                            adcCalibParams.calib_adcCalib_digitalA[i] = SWAPS32(_prxData._adcCalibDatasPointA[i].calibDigital);
                            adcCalibParams.calib_adcCalib_analogA[i] = SWAPS32(_prxData._adcCalibDatasPointA[i].calibAnalog);
                            adcCalibParams.calib_adcCalib_enableA[i] = _prxData._adcCalibDatasPointA[i].calibEnable;
                            adcCalibParams.calib_adcCalib_digitalB[i] = SWAPS32(_prxData._adcCalibDatasPointB[i].calibDigital);
                            adcCalibParams.calib_adcCalib_analogB[i] = SWAPS32(_prxData._adcCalibDatasPointB[i].calibAnalog);
                            adcCalibParams.calib_adcCalib_enableB[i] = _prxData._adcCalibDatasPointB[i].calibEnable;

                            adcCalibParams.correctFactor[i] = SWAPS32(_prxData.correctFactor[i]);
                            adcCalibParams.calibZero[i] = SWAPS32(_prxData.calibZero[i]);
                            adcCalibParams.sensorUnit[i] = _prxData.sensorUnit[i];

                        }
                        try
                        {
                            sensorUnit1.SelectedIndex = _prxData.sensorUnit[0];
                            sensorUnit2.SelectedIndex = _prxData.sensorUnit[1];
                            sensorUnit3.SelectedIndex = _prxData.sensorUnit[2];
                            sensorUnit4.SelectedIndex = _prxData.sensorUnit[3];
                            sensorUnit5.SelectedIndex = _prxData.sensorUnit[4];
                            sensorUnit6.SelectedIndex = _prxData.sensorUnit[5];
                            sensorUnit7.SelectedIndex = _prxData.sensorUnit[6];
                            sensorUnit8.SelectedIndex = _prxData.sensorUnit[7];
                        }
                        catch (Exception ex) { }


                        softVersion.Text =  SWAP32(_prxData.softVersion).ToString("X08");
                        if (upperVersion.Text == softVersion.Text)
                        {
                            checkResult.Text = "成功";
                        }
                        else
                        {
                            checkResult.Text = "失败";
                            MessageBox.Show("版本校验失败,请在网盘重新下载采集卡固件并烧录!");
                        }
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getCalibVolt)
                    {
                        msgGetCalibVolt _prxData = new msgGetCalibVolt();
                        _prxData = (msgGetCalibVolt)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetCalibVolt));

                        // 处理数据并添加到显示缓冲区和完整数据存储
                        double value1;
                        double value2;
                        double value3;
                        double value4;
                        double value5;
                        double value6;
                        double value7;
                        double value8;


                        if (_prxData.adcRange == 1)
                        {
                            value1 = Convert.ToDouble(SWAPS32(_prxData.adcValue[0])) * 10.0 / 0x800000;
                            value2 = Convert.ToDouble(SWAPS32(_prxData.adcValue[1])) * 10.0 / 0x800000;
                            value3 = Convert.ToDouble(SWAPS32(_prxData.adcValue[2])) * 10.0 / 0x800000;
                            value4 = Convert.ToDouble(SWAPS32(_prxData.adcValue[3])) * 10.0 / 0x800000;
                            value5 = Convert.ToDouble(SWAPS32(_prxData.adcValue[4])) * 10.0 / 0x800000;
                            value6 = Convert.ToDouble(SWAPS32(_prxData.adcValue[5])) * 10.0 / 0x800000;
                            value7 = Convert.ToDouble(SWAPS32(_prxData.adcValue[6])) * 10.0 / 0x800000;
                            value8 = Convert.ToDouble(SWAPS32(_prxData.adcValue[7])) * 10.0 / 0x800000;
                        }
                        else
                        {
                            value1 = Convert.ToDouble(SWAPS32(_prxData.adcValue[0])) * 5.0 / 0x800000;
                            value2 = Convert.ToDouble(SWAPS32(_prxData.adcValue[1])) * 5.0 / 0x800000;
                            value3 = Convert.ToDouble(SWAPS32(_prxData.adcValue[2])) * 5.0 / 0x800000;
                            value4 = Convert.ToDouble(SWAPS32(_prxData.adcValue[3])) * 5.0 / 0x800000;
                            value5 = Convert.ToDouble(SWAPS32(_prxData.adcValue[4])) * 5.0 / 0x800000;
                            value6 = Convert.ToDouble(SWAPS32(_prxData.adcValue[5])) * 5.0 / 0x800000;
                            value7 = Convert.ToDouble(SWAPS32(_prxData.adcValue[6])) * 5.0 / 0x800000;
                            value8 = Convert.ToDouble(SWAPS32(_prxData.adcValue[7])) * 5.0 / 0x800000;
                        }

                        if (((_prxData.adc_ch_Enable >> 0) & 0x01) == 1) { adcValue1.Text = value1.ToString("0.00000"); } else { adcValue1.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 1) & 0x01) == 1) { adcValue2.Text = value2.ToString("0.00000"); } else { adcValue2.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 2) & 0x01) == 1) { adcValue3.Text = value3.ToString("0.00000"); } else { adcValue3.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 3) & 0x01) == 1) { adcValue4.Text = value4.ToString("0.00000"); } else { adcValue4.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 4) & 0x01) == 1) { adcValue5.Text = value5.ToString("0.00000"); } else { adcValue5.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 5) & 0x01) == 1) { adcValue6.Text = value6.ToString("0.00000"); } else { adcValue6.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 6) & 0x01) == 1) { adcValue7.Text = value7.ToString("0.00000"); } else { adcValue7.Text = "DISABLE"; }
                        if (((_prxData.adc_ch_Enable >> 7) & 0x01) == 1) { adcValue8.Text = value8.ToString("0.00000"); } else { adcValue8.Text = "DISABLE"; }

                    }

                }
                catch { }


            }));
        }


        private void settingSendCmdNoParam(byte cmd, byte ch)
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
            _settingSendData(txbuf);
        }
        private void settingSendCmdUByteParam(byte cmd, byte ch, byte data)
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
            _settingSendData(txbuf);
        }

        private void settingSendCmdUWordParam(byte cmd, byte ch, UInt16 data)
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
            _settingSendData(txbuf);
        }
        private void settingSendCmdULongParam(byte cmd, byte ch, UInt32 data)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgULong _pTx = (msgULong)Marshal.PtrToStructure(ptrStruct, typeof(msgULong));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(cmd);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = ch;
            _pTx.data = SWAP32(data);

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _settingSendData(txbuf);
        }

        private void settingSendCmdSLongParam(byte cmd, byte ch, Int32 data)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgSLong _pTx = (msgSLong)Marshal.PtrToStructure(ptrStruct, typeof(msgSLong));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(cmd);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = ch;
            _pTx.data = SWAPS32(data);

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _settingSendData(txbuf);
        }

        private void button24_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 1);
        }

        private void button23_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 2);
        }

        private void button22_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 3);
        }

        private void button21_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 4);
        }

        private void button20_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 5);
        }

        private void button19_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 6);
        }

        private void button18_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 7);
        }

        private void button17_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_settingClearAdcCalibDatas), 8);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA1.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA1.Text);

            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 1, volt);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA2.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA2.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 2, volt);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA3.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA3.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 3, volt);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA4.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA4.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 4, volt);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA5.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA5.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 5, volt);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA6.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA6.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 6, volt);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA7.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA7.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 7, volt);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (calibAnaloigA8.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigA8.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint1), 8, volt);
        }

        private void button16_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB1.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB1.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 1, volt);

        }

        private void button15_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB2.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB2.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 2, volt);
        }

        private void button14_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB3.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB3.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 3, volt);
        }

        private void button13_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB4.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB4.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 4, volt);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB5.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB5.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 5, volt);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB6.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB6.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 6, volt);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB7.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB7.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 7, volt);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (calibAnaloigB8.Text == "") return;
            double voltF = Convert.ToDouble(calibAnaloigB8.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_settingAdcCalibPoint2), 8, volt);
        }

        private void ckb_calib1_Click(object sender, EventArgs e)
        {
            settingSendCmdUByteParam((Byte)(_CmdId._cmdId_settingSetAdcCalibMode), 0, Convert.ToByte(ckb_enAdcCalib.Checked));
        }

        private void button25_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getCalibVolt), 0);
        }

        private void button26_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getSettingParam), 0);
        }


        private void button27_Click(object sender, EventArgs e)
        {
            settingSendCmdNoParam((Byte)(_CmdId._cmdId_getIpAndPort), 1);
        }


        private void button29_Click(object sender, EventArgs e)
        {
            if (calibZero1.Text == "") return;
            double voltF = Convert.ToDouble(calibZero1.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 1, volt);
        }

        private void button30_Click(object sender, EventArgs e)
        {
            if (calibZero2.Text == "") return;
            double voltF = Convert.ToDouble(calibZero2.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 2, volt);
        }

        private void button31_Click(object sender, EventArgs e)
        {
            if (calibZero3.Text == "") return;
            double voltF = Convert.ToDouble(calibZero3.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 3, volt);
        }

        private void button32_Click(object sender, EventArgs e)
        {
            if (calibZero4.Text == "") return;
            double voltF = Convert.ToDouble(calibZero4.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 4, volt);
        }

        private void button33_Click(object sender, EventArgs e)
        {
            if (calibZero5.Text == "") return;
            double voltF = Convert.ToDouble(calibZero5.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 5, volt);
        }

        private void button34_Click(object sender, EventArgs e)
        {
            if (calibZero6.Text == "") return;
            double voltF = Convert.ToDouble(calibZero6.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 6, volt);
        }

        private void button35_Click(object sender, EventArgs e)
        {
            if (calibZero7.Text == "") return;
            double voltF = Convert.ToDouble(calibZero7.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 7, volt);
        }

        private void button36_Click(object sender, EventArgs e)
        {
            if (calibZero8.Text == "") return;
            double voltF = Convert.ToDouble(calibZero8.Text);
            Int32 volt = (Int32)(voltF * 100000);
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCalibZero), 8, volt);
        }

        private void button44_Click(object sender, EventArgs e)
        {
            if (correctFactor1.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor1.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 1, data);
        }

        private void button43_Click(object sender, EventArgs e)
        {
            if (correctFactor2.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor2.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 2, data);

        }

        private void button42_Click(object sender, EventArgs e)
        {
            if (correctFactor3.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor3.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 3, data);

        }

        private void button41_Click(object sender, EventArgs e)
        {
            if (correctFactor4.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor4.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 4, data);
        }

        private void button40_Click(object sender, EventArgs e)
        {
            if (correctFactor5.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor5.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 5, data);
        }

        private void button39_Click(object sender, EventArgs e)
        {
            if (correctFactor6.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor6.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 6, data);
        }

        private void button38_Click(object sender, EventArgs e)
        {
            if (correctFactor7.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor7.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 7, data);
        }

        private void button37_Click(object sender, EventArgs e)
        {
            if (correctFactor8.Text == "") return;
            double dataF = Convert.ToDouble(correctFactor8.Text);
            Int32 data = (Int32)(dataF * 100000);
            if (data == 0) return;
            settingSendCmdSLongParam((Byte)(_CmdId._cmdId_setCorrectFactor), 8, data);
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void ckb_enAdcCalib_CheckedChanged(object sender, EventArgs e)
        {
            if (ckb_enAdcCalib.Checked)
            {
                groupBoxA.Enabled = true;
                groupBoxB.Enabled = true;
                groupBoxZ.Enabled = true;
                adcCalibParams.calibMode = true;
                bt_clearCalib1.Enabled = true;
                bt_clearCalib2.Enabled = true;
                bt_clearCalib3.Enabled = true;
                bt_clearCalib4.Enabled = true;
                bt_clearCalib5.Enabled = true;
                bt_clearCalib6.Enabled = true;
                bt_clearCalib7.Enabled = true;
                bt_clearCalib8.Enabled = true;
            }
            else
            {
                groupBoxA.Enabled = false;
                groupBoxB.Enabled = false;
                groupBoxZ.Enabled = false;
                adcCalibParams.calibMode = false;
                bt_clearCalib1.Enabled = false;
                bt_clearCalib2.Enabled = false;
                bt_clearCalib3.Enabled = false;
                bt_clearCalib4.Enabled = false;
                bt_clearCalib5.Enabled = false;
                bt_clearCalib6.Enabled = false;
                bt_clearCalib7.Enabled = false;
                bt_clearCalib8.Enabled = false;
            }
        }

        private void label26_Click(object sender, EventArgs e)
        {

        }

        private void button46_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(recordDelay.Text)) return;
            UInt32 delayTime = Convert.ToByte(recordDelay.Text);
            if (delayTime > 255) { delayTime = 255; }
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setRecordDelay), 0, (byte)delayTime);

        }

        private void sensorUnit1_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 1, (byte)sensorUnit1.SelectedIndex);
        }

        private void sensorUnit2_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 2, (byte)sensorUnit2.SelectedIndex);
        }

        private void sensorUnit3_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 3, (byte)sensorUnit3.SelectedIndex);
        }

        private void sensorUnit4_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 4, (byte)sensorUnit4.SelectedIndex);
        }

        private void sensorUnit5_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 5, (byte)sensorUnit5.SelectedIndex);
        }

        private void sensorUnit6_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 6, (byte)sensorUnit6.SelectedIndex);
        }

        private void sensorUnit7_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 7, (byte)sensorUnit7.SelectedIndex);
        }

        private void sensorUnit8_SelectionChangeCommitted(object sender, EventArgs e)
        {
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setSensorUnit), 8, (byte)sensorUnit8.SelectedIndex);
        }

        private void button47_Click(object sender, EventArgs e)
        {
            checkResult.Text = "等待校验";
            settingSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getSoftVersion), 0);
        }

        private void button46_Click_1(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(recordDelay.Text)) return;
            UInt32 delayTime = Convert.ToByte(recordDelay.Text);
            if (delayTime > 255) { delayTime = 255; }
            settingSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setRecordDelay), 0, (byte)delayTime);
        }
    }
}
