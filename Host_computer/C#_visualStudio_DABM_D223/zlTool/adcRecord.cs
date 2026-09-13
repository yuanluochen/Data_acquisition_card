using Microsoft.VisualBasic.Logging;
using OpenTK.Audio.OpenAL;
using ScottPlot.Colormaps;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Runtime.InteropServices.JavaScript.JSType;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static zlTool.msgStruct;
using static zlTool.zlTool;

namespace zlTool
{
    public delegate void adcRecord_SendData(byte[] str);

    public partial class autoscaling : Form
    {
        public event adcRecord_SendData _adcRecordSendData;

        zlTool _mainForm = null;

        public autoscaling(zlTool zlMain)
        {
            InitializeComponent();
            _mainForm = zlMain;
        }


        private void adcRecord_Load(object sender, EventArgs e)
        {
            this._mainForm._deviceRxMsg += new deviceRxMsg(rxMsgProcess);
        }


        private void adcRecordSendCmdNoParam(byte cmd, byte ch)
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
            _adcRecordSendData(txbuf);
        }



        private void adcRecordSendCmdUByteParam(byte cmd, byte data, byte ch)
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
            _pTx.data = data;
            _pTx.ch = ch;
            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _adcRecordSendData(txbuf);
        }

        private void adcRecordSendCmdUWordParam(byte cmd, UInt16 data, byte ch)
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
            _pTx.data = SWAP16(data);

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _adcRecordSendData(txbuf);
        }

        private double wave_GetLimitsMax()
        {
            double range = -99999;
            if (ckb_autoscaling.Checked)
            {
                // 只有对象不为 null 才计算，为 null 则跳过该通道
                if (adcCheck1.Checked && adcRecord1 != null) { range = Math.Max(range, adcRecord1.Max()); }
                if (adcCheck2.Checked && adcRecord2 != null) { range = Math.Max(range, adcRecord2.Max()); }
                if (adcCheck3.Checked && adcRecord3 != null) { range = Math.Max(range, adcRecord3.Max()); }
                if (adcCheck4.Checked && adcRecord4 != null) { range = Math.Max(range, adcRecord4.Max()); }
                if (adcCheck5.Checked && adcRecord5 != null) { range = Math.Max(range, adcRecord5.Max()); }
                if (adcCheck6.Checked && adcRecord6 != null) { range = Math.Max(range, adcRecord6.Max()); }
                if (adcCheck7.Checked && adcRecord7 != null) { range = Math.Max(range, adcRecord7.Max()); }
                if (adcCheck8.Checked && adcRecord8 != null) { range = Math.Max(range, adcRecord8.Max()); }
            }
            else
            {
                if (adcRange.Checked)
                {
                    range = adcSignalType.Checked ? 40.1 : 10.1;
                }
                else
                {
                    range = adcSignalType.Checked ? 20.1 : 5.1;
                }
            }
            return range;
        }
        private double wave_GetLimitsMin()
        {
            double range = 99999;
            if (ckb_autoscaling.Checked)
            {
                // 只有对象不为 null 才计算，为 null 则跳过该通道
                if (adcCheck1.Checked && adcRecord1 != null) { range = Math.Min(range, adcRecord1.Min()); }
                if (adcCheck2.Checked && adcRecord2 != null) { range = Math.Min(range, adcRecord2.Min()); }
                if (adcCheck3.Checked && adcRecord3 != null) { range = Math.Min(range, adcRecord3.Min()); }
                if (adcCheck4.Checked && adcRecord4 != null) { range = Math.Min(range, adcRecord4.Min()); }
                if (adcCheck5.Checked && adcRecord5 != null) { range = Math.Min(range, adcRecord5.Min()); }
                if (adcCheck6.Checked && adcRecord6 != null) { range = Math.Min(range, adcRecord6.Min()); }
                if (adcCheck7.Checked && adcRecord7 != null) { range = Math.Min(range, adcRecord7.Min()); }
                if (adcCheck8.Checked && adcRecord8 != null) { range = Math.Min(range, adcRecord8.Min()); }
            }
            else
            {
                if (adcRange.Checked)
                {
                    range = adcSignalType.Checked ? -40.1 : -10.1;
                }
                else
                {
                    range = adcSignalType.Checked ? -20.1 : -5.1;
                }
            }
            return range;
        }

        private double getCalibAdcDatas(byte widthByte, byte ch, Int32 data)
        {
            ch -= 1;

            // ========== 1. 先处理原始数据符号扩展（核心修复）==========
            double rawVal;
            long digitalMult = 1;
            double fullScale;
            switch (widthByte)
            {
                case 1:
                    digitalMult = 65536;
                    // 16位补码
                    ushort u16_1 = (ushort)data;
                    rawVal = (short)u16_1;
                    fullScale = 32768.0;
                    break;
                case 2:
                    digitalMult = 256;
                    // 16位补码
                    ushort u16_2 = (ushort)data;
                    rawVal = (short)u16_2;
                    fullScale = 32768.0;
                    break;
                case 3:
                    digitalMult = 1;
                    // 24位补码
                    int u24 = data & 0xFFFFFF;
                    rawVal = u24;
                    if ((u24 & 0x800000) != 0)
                        rawVal -= 0x1000000;
                    fullScale = 8388608.0;
                    break;
                default:
                    rawVal = data;
                    digitalMult = 1;
                    fullScale = 1;
                    break;
            }

            double adcFloat = 0;
            bool useCalib = adcCalibParams.calib_adcCalib_enableA[ch] == 1
                         && adcCalibParams.calib_adcCalib_enableB[ch] == 1
                         && calibEnable.Checked;

            if (useCalib)
            {
                double calibInput = rawVal * digitalMult;
                adcFloat = calc_adcCalibData(
                    calibInput,
                    adcCalibParams.calib_adcCalib_digitalA[ch],
                    adcCalibParams.calib_adcCalib_analogA[ch],
                    adcCalibParams.calib_adcCalib_digitalB[ch],
                    adcCalibParams.calib_adcCalib_analogB[ch]
                ) * 0.00001;
            }
            else
            {
                double voltMax = adcRange.Checked ? 10.0 : 5.0;
                adcFloat = rawVal * voltMax / fullScale;
            }

            // 电流信号转换
            if (adcSignalType.Checked)
            {
                adcFloat = adcFloat / 240.0 * 1000;
            }

            // 整体修正系数+零点
            if (calibEnable.Checked)
            {
                double factor = adcCalibParams.correctFactor[ch] * 0.00001;
                double zeroOff = adcCalibParams.calibZero[ch] * 0.00001;
                adcFloat = adcFloat * factor + zeroOff;
            }

            return adcFloat;
        }

        List<double> adcRecord1 = new List<double>();
        List<double> adcRecord2 = new List<double>();
        List<double> adcRecord3 = new List<double>();
        List<double> adcRecord4 = new List<double>();
        List<double> adcRecord5 = new List<double>();
        List<double> adcRecord6 = new List<double>();
        List<double> adcRecord7 = new List<double>();
        List<double> adcRecord8 = new List<double>();

        List<double> xAxisIndex = new List<double>();
        List<double> xDinAxisIndex = new List<double>();

        double[] showAdcRecord1 = new double[10000];
        double[] showAdcRecord2 = new double[10000];
        double[] showAdcRecord3 = new double[10000];
        double[] showAdcRecord4 = new double[10000];
        double[] showAdcRecord5 = new double[10000];
        double[] showAdcRecord6 = new double[10000];
        double[] showAdcRecord7 = new double[10000];
        double[] showAdcRecord8 = new double[10000];
        UInt16[] showAdcRecordIndex = new UInt16[8];



        UInt32 listAxisIndex = 0;
        const UInt16 ADC_ONCE_LEN = 10000;

        byte adc_ch_Enable;
        UInt16 flashRecordIntervalTime;
        UInt64 flash_DateTimeOffset_H;
        UInt64 flash_DateTimeOffset_L;
        UInt32 recordMaxDataLen = 0;
        UInt32 recordDatasNowLen = 0;
        UInt32 recordTick = 0;
        bool sramRecordFlag = false;
        bool flashRecordFlag = false;
        UInt32 RecentRecord_globalTick = 0;

        UInt16[] adcEnableChState = new UInt16[8];
        UInt16 adcEnableChNum = 0;


        public void rxMsgProcess(byte[] rxBuf)
        {
            BeginInvoke(new MethodInvoker(delegate
            {
                try
                {
                    string[] sensorUnit = new string[8];
                    if (calibEnable.Checked)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            sensorUnit[i] = adcCalibParams.sensorUnitList[adcCalibParams.sensorUnit[i]];
                        }
                    }
                    else if (adcSignalType.Checked)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            sensorUnit[i] = "mA";
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            sensorUnit[i] = "V";
                        }
                    }


                    msgHead _pRxHead = new msgHead();
                    _pRxHead = (msgHead)msgStruct.BytesToDataStruct(rxBuf, typeof(msgHead));


                    if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getDeviceParam)
                    {
                        msgAdcWaveState _prxData = new msgAdcWaveState();
                        _prxData = (msgAdcWaveState)msgStruct.BytesToDataStruct(rxBuf, typeof(msgAdcWaveState));

                        UInt16 localChEnable = SWAP16(_prxData.adc_ch_Enable);
                        adcCheck1.Checked = ((localChEnable >> 0) & 0x01) == 1;
                        adcCheck2.Checked = ((localChEnable >> 1) & 0x01) == 1;
                        adcCheck3.Checked = ((localChEnable >> 2) & 0x01) == 1;
                        adcCheck4.Checked = ((localChEnable >> 3) & 0x01) == 1;
                        adcCheck5.Checked = ((localChEnable >> 4) & 0x01) == 1;
                        adcCheck6.Checked = ((localChEnable >> 5) & 0x01) == 1;
                        adcCheck7.Checked = ((localChEnable >> 6) & 0x01) == 1;
                        adcCheck8.Checked = ((localChEnable >> 7) & 0x01) == 1;

                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;


                        adcSignalType.Checked = _prxData.adcSignalType == 1;
                        adcRange.Checked = _prxData.adcRange == 1;

                        setAdcSamplingRate.Text = Convert.ToString(SWAP32(_prxData.adcSamplingRate));
                        setSramSamplingTime.Text = Convert.ToString(SWAP32(_prxData.adcSramRecordMaxTime));

                        ckb_sramTrigEnable.Checked = (_prxData.sramAdutoTrigEnable & 0x01) == 1;
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getAdcValue)
                    {
                        if (autoReadCheck.Checked == false) return;
                        msgGetAdcValue _prxData = new msgGetAdcValue();
                        _prxData = (msgGetAdcValue)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetAdcValue));

                        // 处理数据并添加到显示缓冲区和完整数据存储
                        UInt16 localChEnable = SWAP16(_prxData.adc_ch_Enable);
                        adcCheck1.Checked = ((localChEnable >> 0) & 0x01) == 1;
                        adcCheck2.Checked = ((localChEnable >> 1) & 0x01) == 1;
                        adcCheck3.Checked = ((localChEnable >> 2) & 0x01) == 1;
                        adcCheck4.Checked = ((localChEnable >> 3) & 0x01) == 1;
                        adcCheck5.Checked = ((localChEnable >> 4) & 0x01) == 1;
                        adcCheck6.Checked = ((localChEnable >> 5) & 0x01) == 1;
                        adcCheck7.Checked = ((localChEnable >> 6) & 0x01) == 1;
                        adcCheck8.Checked = ((localChEnable >> 7) & 0x01) == 1;

                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;
                        adcSignalType.Checked = _prxData.adcSignalType == 1;
                        adcRange.Checked = _prxData.adcRange == 1;

                        dinCheck1.Checked = ((_prxData.din >> 0) & 0x01) == 1;
                        dinCheck2.Checked = ((_prxData.din >> 1) & 0x01) == 1;
                        dinCheck3.Checked = ((_prxData.din >> 2) & 0x01) == 1;
                        dinCheck4.Checked = ((_prxData.din >> 3) & 0x01) == 1;
                        dinCheck5.Checked = ((_prxData.din >> 4) & 0x01) == 1;
                        dinCheck6.Checked = ((_prxData.din >> 5) & 0x01) == 1;
                        dinCheck7.Checked = ((_prxData.din >> 6) & 0x01) == 1;
                        dinCheck8.Checked = ((_prxData.din >> 7) & 0x01) == 1;

                        double adc1 = getCalibAdcDatas(3, 1, SWAPS32(_prxData.adcValue[0]));
                        double adc2 = getCalibAdcDatas(3, 2, SWAPS32(_prxData.adcValue[1]));
                        double adc3 = getCalibAdcDatas(3, 3, SWAPS32(_prxData.adcValue[2]));
                        double adc4 = getCalibAdcDatas(3, 4, SWAPS32(_prxData.adcValue[3]));
                        double adc5 = getCalibAdcDatas(3, 5, SWAPS32(_prxData.adcValue[4]));
                        double adc6 = getCalibAdcDatas(3, 6, SWAPS32(_prxData.adcValue[5]));
                        double adc7 = getCalibAdcDatas(3, 7, SWAPS32(_prxData.adcValue[6]));
                        double adc8 = getCalibAdcDatas(3, 8, SWAPS32(_prxData.adcValue[7]));


                        adcValue1.Text = adc1.ToString("0.#####") + " " + sensorUnit[0];
                        adcValue2.Text = adc2.ToString("0.#####") + " " + sensorUnit[1];
                        adcValue3.Text = adc3.ToString("0.#####") + " " + sensorUnit[2];
                        adcValue4.Text = adc4.ToString("0.#####") + " " + sensorUnit[3];
                        adcValue5.Text = adc5.ToString("0.#####") + " " + sensorUnit[4];
                        adcValue6.Text = adc6.ToString("0.#####") + " " + sensorUnit[5];
                        adcValue7.Text = adc7.ToString("0.#####") + " " + sensorUnit[6];
                        adcValue8.Text = adc8.ToString("0.#####") + " " + sensorUnit[7];

                        if (xAxisIndex.Count < 2000)
                        {
                            xAxisIndex.Add(Convert.ToDouble(xAxisIndex.Count) * Convert.ToDouble(autoReadTime.Text));
                        }
                        else
                        {
                            adcRecord1.RemoveAt(0);
                            adcRecord2.RemoveAt(0);
                            adcRecord3.RemoveAt(0);
                            adcRecord4.RemoveAt(0);
                            adcRecord5.RemoveAt(0);
                            adcRecord6.RemoveAt(0);
                            adcRecord7.RemoveAt(0);
                            adcRecord8.RemoveAt(0);
                        }

                        adcRecord1.Add(getCalibAdcDatas(3, 1, SWAPS32(_prxData.adcValue[0])));
                        adcRecord2.Add(getCalibAdcDatas(3, 2, SWAPS32(_prxData.adcValue[1])));
                        adcRecord3.Add(getCalibAdcDatas(3, 3, SWAPS32(_prxData.adcValue[2])));
                        adcRecord4.Add(getCalibAdcDatas(3, 4, SWAPS32(_prxData.adcValue[3])));
                        adcRecord5.Add(getCalibAdcDatas(3, 5, SWAPS32(_prxData.adcValue[4])));
                        adcRecord6.Add(getCalibAdcDatas(3, 6, SWAPS32(_prxData.adcValue[5])));
                        adcRecord7.Add(getCalibAdcDatas(3, 7, SWAPS32(_prxData.adcValue[6])));
                        adcRecord8.Add(getCalibAdcDatas(3, 8, SWAPS32(_prxData.adcValue[7])));

                        waveform.Plot.Clear();

                        if (adcCheck1.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord1, ScottPlot.Colors.Brown); }
                        if (adcCheck2.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord2, ScottPlot.Colors.Red); }
                        if (adcCheck3.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord3, ScottPlot.Colors.Magenta); }
                        if (adcCheck4.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord4, ScottPlot.Colors.Orange); }
                        if (adcCheck5.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord5, ScottPlot.Colors.Green); }
                        if (adcCheck6.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord6, ScottPlot.Colors.DarkCyan); }
                        if (adcCheck7.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord7, ScottPlot.Colors.Blue); }
                        if (adcCheck8.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord8, ScottPlot.Colors.Purple); }

                        waveform.Plot.Axes.SetLimits(0, xAxisIndex.ToArray()[xAxisIndex.Count() - 1], wave_GetLimitsMin(), wave_GetLimitsMax());
                        waveform.Show();
                        waveform.Refresh();

                        if (autoSave.Checked == true && filePath.Text != "N/A" && filePath.Text != "")
                        {
                            string str = "";
                            str += System.DateTime.Now.ToString("yy-MM-dd-HH-mm-ss.fff") + "->";

                            str += adcValue1.Text + ",";
                            str += adcValue2.Text + ",";
                            str += adcValue3.Text + ",";
                            str += adcValue4.Text + ",";
                            str += adcValue5.Text + ",";
                            str += adcValue6.Text + ",";
                            str += adcValue7.Text + ",";
                            str += adcValue8.Text + ",";
                            str += ("\r\n");
                            File.AppendAllText(@filePath.Text, str);
                        }
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_readRecentConsecutiveDatasInit)
                    {
                        msgULong _prxData = new msgULong();
                        _prxData = (msgULong)msgStruct.BytesToDataStruct(rxBuf, typeof(msgULong));

                        RecentRecord_globalTick = SWAP32(_prxData.data);
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_readRecentConsecutiveDatas)
                    {
                        if (chk_recent1000.Checked == false) return;
                        msgGetRecentConsecutiveDatas _prxData = new msgGetRecentConsecutiveDatas();
                        _prxData = (msgGetRecentConsecutiveDatas)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetRecentConsecutiveDatas));


                        // 处理数据并添加到显示缓冲区和完整数据存储
                        UInt16 localChEnable = SWAP16(_prxData.adc_ch_Enable);
                        adcCheck1.Checked = ((localChEnable >> 0) & 0x01) == 1;
                        adcCheck2.Checked = ((localChEnable >> 1) & 0x01) == 1;
                        adcCheck3.Checked = ((localChEnable >> 2) & 0x01) == 1;
                        adcCheck4.Checked = ((localChEnable >> 3) & 0x01) == 1;
                        adcCheck5.Checked = ((localChEnable >> 4) & 0x01) == 1;
                        adcCheck6.Checked = ((localChEnable >> 5) & 0x01) == 1;
                        adcCheck7.Checked = ((localChEnable >> 6) & 0x01) == 1;
                        adcCheck8.Checked = ((localChEnable >> 7) & 0x01) == 1;


                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;

                        adcSignalType.Checked = _prxData.adcSignalType == 1;
                        adcRange.Checked = _prxData.adcRange == 1;
                        setAdcSamplingRate.Text = Convert.ToString(SWAP32(_prxData.adcSamplingRate));

                        dinCheck1.Checked = ((_prxData.din >> 0) & 0x01) == 1;
                        dinCheck2.Checked = ((_prxData.din >> 1) & 0x01) == 1;
                        dinCheck3.Checked = ((_prxData.din >> 2) & 0x01) == 1;
                        dinCheck4.Checked = ((_prxData.din >> 3) & 0x01) == 1;
                        dinCheck5.Checked = ((_prxData.din >> 4) & 0x01) == 1;
                        dinCheck6.Checked = ((_prxData.din >> 5) & 0x01) == 1;
                        dinCheck7.Checked = ((_prxData.din >> 6) & 0x01) == 1;
                        dinCheck8.Checked = ((_prxData.din >> 7) & 0x01) == 1;
                        if (RecentRecord_globalTick == 0) { RecentRecord_globalTick = SWAP32(_prxData.globalTick); }
                        UInt32 dataNum = (UInt32)((SWAP32(_prxData.globalTick) - RecentRecord_globalTick));
                        if (dataNum > 1000) { dataNum = 1000; RecentRecord_globalTick = SWAP32(_prxData.globalTick) - 1000; }
                        string str = "";

                        for (UInt32 i = (1000 - dataNum); i < 1000; i++)
                        {
                            double adc1 = getCalibAdcDatas(2, 1, SWAP16(_prxData.adcData1[i]));
                            double adc2 = getCalibAdcDatas(2, 2, SWAP16(_prxData.adcData2[i]));
                            double adc3 = getCalibAdcDatas(2, 3, SWAP16(_prxData.adcData3[i]));
                            double adc4 = getCalibAdcDatas(2, 4, SWAP16(_prxData.adcData4[i]));
                            double adc5 = getCalibAdcDatas(2, 5, SWAP16(_prxData.adcData5[i]));
                            double adc6 = getCalibAdcDatas(2, 6, SWAP16(_prxData.adcData6[i]));
                            double adc7 = getCalibAdcDatas(2, 7, SWAP16(_prxData.adcData7[i]));
                            double adc8 = getCalibAdcDatas(2, 8, SWAP16(_prxData.adcData8[i]));

                            adcRecord1.Add(adc1);
                            adcRecord2.Add(adc2);
                            adcRecord3.Add(adc3);
                            adcRecord4.Add(adc4);
                            adcRecord5.Add(adc5);
                            adcRecord6.Add(adc6);
                            adcRecord7.Add(adc7);
                            adcRecord8.Add(adc8);

                            if (autoSave.Checked == true && filePath.Text != "N/A" && filePath.Text != "")
                            {
                                str += (RecentRecord_globalTick + i).ToString() + "->";
                                str += (adc1.ToString("0.####")) + ",";
                                str += (adc2.ToString("0.####")) + ",";
                                str += (adc3.ToString("0.####")) + ",";
                                str += (adc4.ToString("0.####")) + ",";
                                str += (adc5.ToString("0.####")) + ",";
                                str += (adc6.ToString("0.####")) + ",";
                                str += (adc7.ToString("0.####")) + ",";
                                str += (adc8.ToString("0.####")) + ",";

                                str += ("\r\n");

                            }

                            if (xAxisIndex.Count < 10000)
                            {
                                xAxisIndex.Add(Convert.ToDouble(xAxisIndex.Count) / (Convert.ToDouble(SWAP32(_prxData.adcSamplingRate)) / 1000));
                            }
                            else
                            {
                                adcRecord1.RemoveAt(0);
                                adcRecord2.RemoveAt(0);
                                adcRecord3.RemoveAt(0);
                                adcRecord4.RemoveAt(0);
                                adcRecord5.RemoveAt(0);
                                adcRecord6.RemoveAt(0);
                                adcRecord7.RemoveAt(0);
                                adcRecord8.RemoveAt(0);
                            }
                        }

                        adcValue1.Text = getCalibAdcDatas(2, 1, SWAP16(_prxData.adcData1[999])).ToString("0.####") + " " + sensorUnit[0];
                        adcValue2.Text = getCalibAdcDatas(2, 2, SWAP16(_prxData.adcData2[999])).ToString("0.####") + " " + sensorUnit[1];
                        adcValue3.Text = getCalibAdcDatas(2, 3, SWAP16(_prxData.adcData3[999])).ToString("0.####") + " " + sensorUnit[2];
                        adcValue4.Text = getCalibAdcDatas(2, 4, SWAP16(_prxData.adcData4[999])).ToString("0.####") + " " + sensorUnit[3];
                        adcValue5.Text = getCalibAdcDatas(2, 5, SWAP16(_prxData.adcData5[999])).ToString("0.####") + " " + sensorUnit[4];
                        adcValue6.Text = getCalibAdcDatas(2, 6, SWAP16(_prxData.adcData6[999])).ToString("0.####") + " " + sensorUnit[5];
                        adcValue7.Text = getCalibAdcDatas(2, 7, SWAP16(_prxData.adcData7[999])).ToString("0.####") + " " + sensorUnit[6];
                        adcValue8.Text = getCalibAdcDatas(2, 8, SWAP16(_prxData.adcData8[999])).ToString("0.####") + " " + sensorUnit[7];

                        if (autoSave.Checked == true && filePath.Text != "N/A" && filePath.Text != "")
                        {
                            File.AppendAllText(@filePath.Text, str);
                        }
                        RecentRecord_globalTick = SWAP32(_prxData.globalTick);

                        waveform.Plot.Clear();

                        if (adcCheck1.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord1, ScottPlot.Colors.Brown); }
                        if (adcCheck2.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord2, ScottPlot.Colors.Red); }
                        if (adcCheck3.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord3, ScottPlot.Colors.Magenta); }
                        if (adcCheck4.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord4, ScottPlot.Colors.Orange); }
                        if (adcCheck5.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord5, ScottPlot.Colors.Green); }
                        if (adcCheck6.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord6, ScottPlot.Colors.DarkCyan); }
                        if (adcCheck7.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord7, ScottPlot.Colors.Blue); }
                        if (adcCheck8.Checked) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord8, ScottPlot.Colors.Purple); }
                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;
                        waveform.Plot.Axes.SetLimits(0, xAxisIndex.ToArray()[xAxisIndex.Count() - 1], wave_GetLimitsMin(), wave_GetLimitsMax());
                        waveform.Show();
                        waveform.Refresh();

                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_recordUploadStart)
                    {
                        msgULong _prxData = new msgULong();
                        _prxData = (msgULong)msgStruct.BytesToDataStruct(rxBuf, typeof(msgULong));
                        progressBar.Value = 0;
                        recordDatasNowLen = 0;
                        recordMaxDataLen = SWAP32(_prxData.data);
                        clearAllWaves();
                        ///sramRecordFlag = false;
                        //flashRecordFlag = true;
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_recordUploadEnd)
                    {
                        try
                        {
                            msgULong _prxData = new msgULong();
                            _prxData = (msgULong)msgStruct.BytesToDataStruct(rxBuf, typeof(msgULong));

                            waveform.Plot.Clear();
                            sramRecordFlag = false;
                            waveform.Plot.Clear();

                            //清除过长的数据
                            if (adcRecord1.Count() > xAxisIndex.Count()) { adcRecord1.RemoveRange(xAxisIndex.Count(), adcRecord1.Count() - xAxisIndex.Count()); }
                            if (adcRecord2.Count() > xAxisIndex.Count()) { adcRecord2.RemoveRange(xAxisIndex.Count(), adcRecord2.Count() - xAxisIndex.Count()); }
                            if (adcRecord3.Count() > xAxisIndex.Count()) { adcRecord3.RemoveRange(xAxisIndex.Count(), adcRecord3.Count() - xAxisIndex.Count()); }
                            if (adcRecord4.Count() > xAxisIndex.Count()) { adcRecord4.RemoveRange(xAxisIndex.Count(), adcRecord4.Count() - xAxisIndex.Count()); }
                            if (adcRecord5.Count() > xAxisIndex.Count()) { adcRecord5.RemoveRange(xAxisIndex.Count(), adcRecord5.Count() - xAxisIndex.Count()); }
                            if (adcRecord6.Count() > xAxisIndex.Count()) { adcRecord6.RemoveRange(xAxisIndex.Count(), adcRecord6.Count() - xAxisIndex.Count()); }
                            if (adcRecord7.Count() > xAxisIndex.Count()) { adcRecord7.RemoveRange(xAxisIndex.Count(), adcRecord7.Count() - xAxisIndex.Count()); }
                            if (adcRecord8.Count() > xAxisIndex.Count()) { adcRecord8.RemoveRange(xAxisIndex.Count(), adcRecord8.Count() - xAxisIndex.Count()); }
                            try
                            {
                                if (adcCheck1.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord1.ToArray(), ScottPlot.Colors.Brown); }
                                if (adcCheck2.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord2.ToArray(), ScottPlot.Colors.Red); }
                                if (adcCheck3.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord3.ToArray(), ScottPlot.Colors.Magenta); }
                                if (adcCheck4.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord4.ToArray(), ScottPlot.Colors.Orange); }
                                if (adcCheck5.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord5.ToArray(), ScottPlot.Colors.Green); }
                                if (adcCheck6.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord6.ToArray(), ScottPlot.Colors.DarkCyan); }
                                if (adcCheck7.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord7.ToArray(), ScottPlot.Colors.Blue); }
                                if (adcCheck8.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord8.ToArray(), ScottPlot.Colors.Purple); }
                            }
                            catch { }
                            waveform.Plot.Axes.SetLimits(0, xAxisIndex.ToArray()[xAxisIndex.Count() - 1], wave_GetLimitsMin(), wave_GetLimitsMax());

                            waveform.Show();
                            waveform.Refresh();
                        }
                        catch { }
                        progressBar.Value = 0;
                        recordDatasNowLen = 0;
                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getSramRecordDatas)
                    {
                        msgGetAdcDatas _prxData = new msgGetAdcDatas();
                        _prxData = (msgGetAdcDatas)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetAdcDatas));

                        // 处理数据并添加到显示缓冲区和完整数据存储
                        UInt16 localChEnable = SWAP16(_prxData.adc_ch_Enable);
                        adcCheck1.Checked = ((localChEnable >> 0) & 0x01) == 1;
                        adcCheck2.Checked = ((localChEnable >> 1) & 0x01) == 1;
                        adcCheck3.Checked = ((localChEnable >> 2) & 0x01) == 1;
                        adcCheck4.Checked = ((localChEnable >> 3) & 0x01) == 1;
                        adcCheck5.Checked = ((localChEnable >> 4) & 0x01) == 1;
                        adcCheck6.Checked = ((localChEnable >> 5) & 0x01) == 1;
                        adcCheck7.Checked = ((localChEnable >> 6) & 0x01) == 1;
                        adcCheck8.Checked = ((localChEnable >> 7) & 0x01) == 1;

                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;
                        adcSignalType.Checked = _prxData.adcSignalType == 1;
                        adcRange.Checked = _prxData.adcRange == 1;
                        setAdcSamplingRate.Text = Convert.ToString(SWAP32(_prxData.adcSamplingRate));

                        adcEnableChNum = 0;
                        for (UInt16 i = 0; i < 8; i++)
                        {
                            if (((localChEnable >> i) & 0x01) == 1)
                            {
                                adcEnableChState[adcEnableChNum++] = i;
                            }
                        }
                        /*
                        if (((localChEnable >> 8) & 0x01) == 1)
                        {
                            adcEnableChState[adcEnableChNum++] = 8;
                            adcEnableChState[adcEnableChNum++] = 9;
                        }
                        */
                        for (UInt16 i = 0; i < SWAP16(_prxData.dataLen); i++)
                        {
                            if (adcEnableChState[(i) % adcEnableChNum] == 0) { adcRecord1.Add(getCalibAdcDatas(2, 1, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 1) { adcRecord2.Add(getCalibAdcDatas(2, 2, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 2) { adcRecord3.Add(getCalibAdcDatas(2, 3, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 3) { adcRecord4.Add(getCalibAdcDatas(2, 4, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 4) { adcRecord5.Add(getCalibAdcDatas(2, 5, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 5) { adcRecord6.Add(getCalibAdcDatas(2, 6, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 6) { adcRecord7.Add(getCalibAdcDatas(2, 7, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 7) { adcRecord8.Add(getCalibAdcDatas(2, 8, SWAPS16(_prxData.adcData[i]))); }

                        }
                        //生成X轴数组
                        for (UInt16 i = 0; i < (SWAP16(_prxData.dataLen) / adcEnableChNum); i++)
                        {
                            xAxisIndex.Add(Convert.ToDouble(xAxisIndex.Count) / (Convert.ToDouble(SWAP32(_prxData.adcSamplingRate)) / 1000));
                        }

                        recordDatasNowLen += SWAP16(_prxData.dataLen);
                        sramRecordFlag = true;
                        flashRecordFlag = false;
                        double barPercent = recordDatasNowLen * 200.0 / recordMaxDataLen;
                        progressBar.Value = Convert.ToUInt16(barPercent);

                    }
                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_sramRecordAutoUploadDatas)
                    {
                        msgAutoUploadDatas _prxData = new msgAutoUploadDatas();
                        _prxData = (msgAutoUploadDatas)msgStruct.BytesToDataStruct(rxBuf, typeof(msgAutoUploadDatas));

                        sramSecond.Text = _prxData.second.ToString();
                        sramMinute.Text = _prxData.minute.ToString();
                        sramHour.Text = _prxData.hour.ToString();
                        // 处理数据并添加到显示缓冲区和完整数据存储
                        UInt16 localChEnable = SWAP16(_prxData.adc_ch_Enable);
                        adcCheck1.Checked = ((localChEnable >> 0) & 0x01) == 1;
                        adcCheck2.Checked = ((localChEnable >> 1) & 0x01) == 1;
                        adcCheck3.Checked = ((localChEnable >> 2) & 0x01) == 1;
                        adcCheck4.Checked = ((localChEnable >> 3) & 0x01) == 1;
                        adcCheck5.Checked = ((localChEnable >> 4) & 0x01) == 1;
                        adcCheck6.Checked = ((localChEnable >> 5) & 0x01) == 1;
                        adcCheck7.Checked = ((localChEnable >> 6) & 0x01) == 1;
                        adcCheck8.Checked = ((localChEnable >> 7) & 0x01) == 1;


                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;
                        adcSignalType.Checked = _prxData.adcSignalType == 1;
                        adcRange.Checked = _prxData.adcRange == 1;
                    }

                    else if (_pRxHead.cmdId == (byte)_CmdId._cmdId_readOnlineRecordDatas)
                    {
                        msgGetAdcDatas _prxData = new msgGetAdcDatas();
                        _prxData = (msgGetAdcDatas)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetAdcDatas));

                        // 添加数据到图表
                        //waveform.AddScatter(data);
                        //根据回读信息更新adc通道选项, 并建立bool数组用来处理循环依据
                        UInt16 localChEnable = SWAP16(_prxData.adc_ch_Enable);
                        adcCheck1.Checked = ((localChEnable >> 0) & 0x01) == 1;
                        adcCheck2.Checked = ((localChEnable >> 1) & 0x01) == 1;
                        adcCheck3.Checked = ((localChEnable >> 2) & 0x01) == 1;
                        adcCheck4.Checked = ((localChEnable >> 3) & 0x01) == 1;
                        adcCheck5.Checked = ((localChEnable >> 4) & 0x01) == 1;
                        adcCheck6.Checked = ((localChEnable >> 5) & 0x01) == 1;
                        adcCheck7.Checked = ((localChEnable >> 6) & 0x01) == 1;
                        adcCheck8.Checked = ((localChEnable >> 7) & 0x01) == 1;

                        diffCheck1.Checked = ((_prxData.adc_diff_Enable >> 0) & 0x01) == 1;
                        diffCheck2.Checked = ((_prxData.adc_diff_Enable >> 1) & 0x01) == 1;
                        diffCheck3.Checked = ((_prxData.adc_diff_Enable >> 2) & 0x01) == 1;
                        diffCheck4.Checked = ((_prxData.adc_diff_Enable >> 3) & 0x01) == 1;
                        adcSignalType.Checked = _prxData.adcSignalType == 1;
                        adcRange.Checked = _prxData.adcRange == 1;

                        setAdcSamplingRate.Text = Convert.ToString(SWAP32(_prxData.adcSamplingRate));

                        adcRecord1.Clear();
                        adcRecord2.Clear();
                        adcRecord3.Clear();
                        adcRecord4.Clear();
                        adcRecord5.Clear();
                        adcRecord6.Clear();
                        adcRecord7.Clear();
                        adcRecord8.Clear();

                        adcEnableChNum = 0;
                        for (UInt16 i = 0; i < 8; i++)
                        {
                            if (((localChEnable >> i) & 0x01) == 1)
                            {
                                adcEnableChState[adcEnableChNum++] = i;
                            }
                            showAdcRecordIndex[i] = 0;
                        }
            
                        //生成X轴数组
                        onlineRecordMaxLen = (UInt16)(SWAP16(_prxData.dataLen) / adcEnableChNum);
                        for (UInt16 i = 0; i < SWAP16(_prxData.dataLen); i++)
                        {
                            //最后叠加的数字为偏置
                            if (adcEnableChState[(i ) % adcEnableChNum] == 0) { adcRecord1.Add(getCalibAdcDatas(2, 1, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 1) { adcRecord2.Add(getCalibAdcDatas(2, 2, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 2) { adcRecord3.Add(getCalibAdcDatas(2, 3, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 3) { adcRecord4.Add(getCalibAdcDatas(2, 4, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 4) { adcRecord5.Add(getCalibAdcDatas(2, 5, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 5) { adcRecord6.Add(getCalibAdcDatas(2, 6, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 6) { adcRecord7.Add(getCalibAdcDatas(2, 7, SWAPS16(_prxData.adcData[i]))); }
                            else if (adcEnableChState[(i) % adcEnableChNum] == 7) { adcRecord8.Add(getCalibAdcDatas(2, 8, SWAPS16(_prxData.adcData[i]))); }
                        }

                        //生成X轴数组
                        for (UInt16 i = 0; i < onlineRecordMaxLen; i++) { xAxisIndex.Add(i / (Convert.ToDouble(setAdcSamplingRate.Text) / 1000)); }
                        if (progressBar.Value > 0)
                        {
                            progressBar.Value = 0;
                        }
                        else
                        {
                            progressBar.Value = 100;
                        }

                        onlineRecordRefreshFlag = true;
                        
                        if (autoSave.Checked == true && filePath.Text != "N/A" && filePath.Text != "")
                        {
                            StringBuilder str = new StringBuilder();
                            for (int i = 0; i < onlineRecordMaxLen; i++)
                            {
                                if (adcRecord1.Count > i) { str.Append(adcRecord1[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord2.Count > i) { str.Append(adcRecord2[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord3.Count > i) { str.Append(adcRecord3[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord4.Count > i) { str.Append(adcRecord4[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord5.Count > i) { str.Append(adcRecord5[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord6.Count > i) { str.Append(adcRecord6[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord7.Count > i) { str.Append(adcRecord7[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                if (adcRecord8.Count > i) { str.Append(adcRecord8[i].ToString("0.0000") + ","); } else { str.Append(","); }
                                str.Append("\r\n");
                            }

                            FileStream fs = new FileStream(@filePath.Text, FileMode.Append);
                            StreamWriter wr = new StreamWriter(fs);
                            wr.Write(str);
                            wr.Close();

                        }

                    }

                }
                catch { }

            }));
        }

        UInt16 onlineRecordMaxLen = 0;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (ckb_RefreshWave.Checked && onlineRecordRefreshFlag)
            {

                waveform.Plot.Clear();
                //将曲线分别加入到相应的list 
                for (UInt16 i = 0; i < adcEnableChNum; i++)
                {
                    if ((adcEnableChState[i % adcEnableChNum]) == 0) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord1, ScottPlot.Colors.Brown); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 1) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord2, ScottPlot.Colors.Red); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 2) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord3, ScottPlot.Colors.Magenta); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 3) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord4, ScottPlot.Colors.Orange); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 4) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord5, ScottPlot.Colors.Green); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 5) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord6, ScottPlot.Colors.DarkCyan); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 6) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord7, ScottPlot.Colors.Blue); }
                    else if ((adcEnableChState[i % adcEnableChNum]) == 7) { waveform.Plot.Add.ScatterLine(xAxisIndex, adcRecord8, ScottPlot.Colors.Purple); }
                }

                waveform.Plot.Axes.SetLimits(0, Convert.ToDouble(onlineRecordMaxLen) / (Convert.ToDouble(setAdcSamplingRate.Text) / 1000), wave_GetLimitsMin(), wave_GetLimitsMax());
                waveform.Show();
                waveform.Refresh();
                
            }

            onlineRecordRefreshFlag = false;
            if (string.IsNullOrEmpty(setAdcSamplingRate.Text)) return;
            if (adcCalibParams.calibMode == true)
            {
                chk_recent1000.Checked = false;
                autoReadCheck.Checked = false;
            }
            try
            {
                Int32 getTime = 1000 / Convert.ToInt32(setAdcSamplingRate.Text);
                if (getTime > 10) { getTime = 10; }
                if (getTime == 0) { getTime = 1; }
                autoRecent.Interval = getTime * 100;
                if (chk_recent1000.Checked)
                {
                    adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_readRecentConsecutiveDatas), 0);
                }
            }
            catch { }
        }

        private void autoRead_Tick(object sender, EventArgs e)
        {
            if (autoReadCheck.Checked)
            {
                adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getAdcValue), 0);
            }
        }

        private void serialPort_Click(object sender, EventArgs e)
        {
        }


        private void button4_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getAdcValue), 0);
        }

        private void button15_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getDeviceParam), 0);
        }

        private UInt16 fun_getAdcChStateEnable()
        {
            UInt16 adc1ChState = Convert.ToByte((Convert.ToByte(adcCheck1.Checked) << 0));
            UInt16 adc2ChState = Convert.ToByte((Convert.ToByte(adcCheck2.Checked) << 1));
            UInt16 adc3ChState = Convert.ToByte((Convert.ToByte(adcCheck3.Checked) << 2));
            UInt16 adc4ChState = Convert.ToByte((Convert.ToByte(adcCheck4.Checked) << 3));
            UInt16 adc5ChState = Convert.ToByte((Convert.ToByte(adcCheck5.Checked) << 4));
            UInt16 adc6ChState = Convert.ToByte((Convert.ToByte(adcCheck6.Checked) << 5));
            UInt16 adc7ChState = Convert.ToByte((Convert.ToByte(adcCheck7.Checked) << 6));
            UInt16 adc8ChState = Convert.ToByte((Convert.ToByte(adcCheck8.Checked) << 7));

            UInt16 adcChState = Convert.ToUInt16(adc1ChState + adc2ChState + adc3ChState + adc4ChState + adc5ChState + adc6ChState + adc7ChState + adc8ChState);

            return adcChState;
        }
        private byte fun_getAdcChDiffState()
        {
            byte adcDiffState1 = Convert.ToByte((Convert.ToByte(diffCheck1.Checked) << 0));
            byte adcDiffState2 = Convert.ToByte((Convert.ToByte(diffCheck2.Checked) << 1));
            byte adcDiffState3 = Convert.ToByte((Convert.ToByte(diffCheck3.Checked) << 2));
            byte adcDiffState4 = Convert.ToByte((Convert.ToByte(diffCheck4.Checked) << 3));

            byte adcDiffState = Convert.ToByte(adcDiffState1 + adcDiffState2 + adcDiffState3 + adcDiffState4);

            return adcDiffState;
        }

        private void fun_setAdcState()
        {
            clearAllWaves();
            waveform.Plot.Clear();
            // 更新图形化显示
            if (adcCheck1.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord1.ToArray(), ScottPlot.Colors.Brown); }
            if (adcCheck2.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord2.ToArray(), ScottPlot.Colors.Red); }
            if (adcCheck3.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord3.ToArray(), ScottPlot.Colors.Magenta); }
            if (adcCheck4.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord4.ToArray(), ScottPlot.Colors.Orange); }
            if (adcCheck5.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord5.ToArray(), ScottPlot.Colors.Green); }
            if (adcCheck6.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord6.ToArray(), ScottPlot.Colors.DarkCyan); }
            if (adcCheck7.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord7.ToArray(), ScottPlot.Colors.Blue); }
            if (adcCheck8.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord8.ToArray(), ScottPlot.Colors.Purple); }
            waveform.Refresh();
            adcRecordSendCmdUWordParam(Convert.ToByte(_CmdId._cmdId_setAdc_chEnable), fun_getAdcChStateEnable(), 0);
        }


        private void adcCheck1_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck2_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck3_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck4_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck5_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck6_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck7_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }

        private void adcCheck8_Click(object sender, EventArgs e)
        {
            fun_setAdcState();
        }


        private void button14_Click(object sender, EventArgs e)
        {
            clearAllWaves();
        }

        private void clearAllWaves()
        {
            xAxisIndex.Clear();
            listAxisIndex = 0;
            adcRecord1.Clear();
            adcRecord2.Clear();
            adcRecord3.Clear();
            adcRecord4.Clear();
            adcRecord5.Clear();
            adcRecord6.Clear();
            adcRecord7.Clear();
            adcRecord8.Clear();
            waveform.Plot.Clear();
            waveform.Refresh();
            RecentRecord_globalTick = 0;
        }



        private void button1_Click(object sender, EventArgs e)
        {
            clearAllWaves();
            /************消息数组转结构体************/
            if (string.IsNullOrEmpty(setAdcSamplingRate.Text)) { return; }
            if (string.IsNullOrEmpty(setSramSamplingTime.Text)) { return; }

            byte[] buf1 = new byte[256];
            msgAdcStartSramRecord _pTx = new msgAdcStartSramRecord();

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            _pTx = (msgAdcStartSramRecord)Marshal.PtrToStructure(ptrStruct, typeof(msgAdcStartSramRecord));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(_CmdId._cmdId_startSramRecord);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));

            _pTx.adc_ch_Enable = SWAP16(fun_getAdcChStateEnable());
            _pTx.adc_diff_Enable = fun_getAdcChDiffState();
            _pTx.adcSignalType = Convert.ToByte(adcSignalType.Checked);
            _pTx.adcRange = Convert.ToByte(adcRange.Checked);
            _pTx.adcSamplingRate = SWAP32(Convert.ToUInt32(setAdcSamplingRate.Text));
            _pTx.sramSamplingTime = SWAP32(Convert.ToUInt32(setSramSamplingTime.Text));

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _adcRecordSendData(txbuf);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_stopSramRecord), 0);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            autoReadCheck.Checked = false;
            Thread.Sleep(100);
            clearAllWaves();
            Thread.Sleep(100);
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getSramRecordDatas), 0);

        }

        private void button13_Click(object sender, EventArgs e)
        {

        }



        private void button7_Click(object sender, EventArgs e)
        {
            string path = string.Empty;
            System.Windows.Forms.FolderBrowserDialog fbd = new System.Windows.Forms.FolderBrowserDialog();
            if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                path = fbd.SelectedPath;
            }
            else
            {
                return;
            }
            path += "\\test " + System.DateTime.Now.ToString("yy-MM-dd HH-mm-ss") + ".txt";

            FileStream fs = new FileStream(path, FileMode.Append);
            StreamWriter wr = new StreamWriter(fs);
            //string str = "";
            StringBuilder str = new StringBuilder();

            str.Append("SRAM RECORD, TOTAL LINE: " + xAxisIndex.Count.ToString() + "\r\n");
            str.Append("\r\n");
            for (int i = 0; i < xAxisIndex.Count; i++)
            {
                if (adcRecord1.Count > i) { str.Append(adcRecord1[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord2.Count > i) { str.Append(adcRecord2[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord3.Count > i) { str.Append(adcRecord3[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord4.Count > i) { str.Append(adcRecord4[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord5.Count > i) { str.Append(adcRecord5[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord6.Count > i) { str.Append(adcRecord6[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord7.Count > i) { str.Append(adcRecord7[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord8.Count > i) { str.Append(adcRecord8[i].ToString("0.####") + ","); } else { str.Append(","); }

                str.Append("\r\n");
            }
            wr.Write(str);
            wr.Close();
        }



        private void button8_Click(object sender, EventArgs e)
        {
            string path = string.Empty;
            System.Windows.Forms.FolderBrowserDialog fbd = new System.Windows.Forms.FolderBrowserDialog();
            if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                path = fbd.SelectedPath;
            }
            else
            {
                return;
            }
            path += "\\test " + System.DateTime.Now.ToString("yy-MM-dd HH-mm-ss") + ".txt";

            FileStream fs = new FileStream(path, FileMode.Append);
            StreamWriter wr = new StreamWriter(fs);
            StringBuilder str = new StringBuilder();
            str.Append("FLASH RECORD, TOTAL LINE: " + xAxisIndex.Count.ToString() + "\r\n");
            str.Append("\r\n");
            UInt16 flash_sector, flash_inner;
            UInt64 flash_DateTimeOffset = (flash_DateTimeOffset_H << 32) + flash_DateTimeOffset_L;
            for (int i = 0; i < xAxisIndex.Count; i++)
            {
                flash_DateTimeOffset += (flashRecordIntervalTime);

                str.Append(flash_DateTimeOffset.ToString() + "->");
                if (adcRecord1.Count > i) { str.Append(adcRecord1[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord2.Count > i) { str.Append(adcRecord2[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord3.Count > i) { str.Append(adcRecord3[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord4.Count > i) { str.Append(adcRecord4[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord5.Count > i) { str.Append(adcRecord5[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord6.Count > i) { str.Append(adcRecord6[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord7.Count > i) { str.Append(adcRecord7[i].ToString("0.####") + ","); } else { str.Append(","); }
                if (adcRecord8.Count > i) { str.Append(adcRecord8[i].ToString("0.####") + ","); } else { str.Append(","); }
                str.Append("\r\n");
            }

            wr.Write(str);
            wr.Close();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string[] loadText = new string[10000000];
            UInt32 maxLen = 0;
            clearAllWaves();

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
                    string filepath = f.FileName;//G:\新建文件夹\新建文本文档.txt
                    //String filename = f.SafeFileName;//新建文本文档.txt
                    path = filepath;
                }
                else
                {
                    return;
                }

                using (StreamReader sr = new StreamReader(@path))
                {
                    string line;
                    // 从文件读取并显示行，直到文件的末尾 
                    //只读取20000行, 超过20000行的部分忽略, 不足的话按照实际长度读取
                    for (Int32 i = 0; i < 10000000; i++)
                    {
                        if ((line = sr.ReadLine()) != null)
                        {
                            loadText[maxLen] = line;
                            maxLen++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            catch { }

            try
            {
                //填充结构体正文
                for (UInt32 i = 0; i < maxLen; i++)
                {
                    if (loadText[i].Contains(',') == false)
                    {
                        continue;
                    }

                    string[] recordBuf = new string[10];
                    recordBuf = loadText[i].Split(',');

                    if (recordBuf.Length < 9)
                    {
                        continue;
                    }

                    if (recordBuf[0] != "") { adcRecord1.Add(Convert.ToDouble(recordBuf[0])); }
                    if (recordBuf[1] != "") { adcRecord2.Add(Convert.ToDouble(recordBuf[1])); }
                    if (recordBuf[2] != "") { adcRecord3.Add(Convert.ToDouble(recordBuf[2])); }
                    if (recordBuf[3] != "") { adcRecord4.Add(Convert.ToDouble(recordBuf[3])); }
                    if (recordBuf[4] != "") { adcRecord5.Add(Convert.ToDouble(recordBuf[4])); }
                    if (recordBuf[5] != "") { adcRecord6.Add(Convert.ToDouble(recordBuf[5])); }
                    if (recordBuf[6] != "") { adcRecord7.Add(Convert.ToDouble(recordBuf[6])); }
                    if (recordBuf[7] != "") { adcRecord8.Add(Convert.ToDouble(recordBuf[7])); }

                    xAxisIndex.Add(i);
                }

                if (adcRecord1.Count != 0) { adcCheck1.Checked = true; } else { adcCheck1.Checked = false; }
                if (adcRecord2.Count != 0) { adcCheck2.Checked = true; } else { adcCheck2.Checked = false; }
                if (adcRecord3.Count != 0) { adcCheck3.Checked = true; } else { adcCheck3.Checked = false; }
                if (adcRecord4.Count != 0) { adcCheck4.Checked = true; } else { adcCheck4.Checked = false; }
                if (adcRecord5.Count != 0) { adcCheck5.Checked = true; } else { adcCheck5.Checked = false; }
                if (adcRecord6.Count != 0) { adcCheck6.Checked = true; } else { adcCheck6.Checked = false; }
                if (adcRecord7.Count != 0) { adcCheck7.Checked = true; } else { adcCheck7.Checked = false; }
                if (adcRecord8.Count != 0) { adcCheck8.Checked = true; } else { adcCheck8.Checked = false; }

                if (adcCheck1.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord1.ToArray(), ScottPlot.Colors.Brown); }
                if (adcCheck2.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord2.ToArray(), ScottPlot.Colors.Red); }
                if (adcCheck3.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord3.ToArray(), ScottPlot.Colors.Magenta); }
                if (adcCheck4.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord4.ToArray(), ScottPlot.Colors.Orange); }
                if (adcCheck5.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord5.ToArray(), ScottPlot.Colors.Green); }
                if (adcCheck6.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord6.ToArray(), ScottPlot.Colors.DarkCyan); }
                if (adcCheck7.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord7.ToArray(), ScottPlot.Colors.Blue); }
                if (adcCheck8.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord8.ToArray(), ScottPlot.Colors.Purple); }


                waveform.Plot.Axes.SetLimits(0, xAxisIndex.Count(), -5, 5);

                waveform.Show();
                waveform.Refresh();
            }
            catch (Exception ex) { }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            string[] loadText = new string[10000000];
            UInt32 maxLen = 0;
            clearAllWaves();

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
                    string filepath = f.FileName;//G:\新建文件夹\新建文本文档.txt
                    //String filename = f.SafeFileName;//新建文本文档.txt
                    path = filepath;
                }
                else
                {
                    return;
                }

                using (StreamReader sr = new StreamReader(@path))
                {
                    string line;
                    // 从文件读取并显示行，直到文件的末尾 
                    //只读取20000行, 超过20000行的部分忽略, 不足的话按照实际长度读取
                    for (Int32 i = 0; i < 10000000; i++)
                    {
                        if ((line = sr.ReadLine()) != null)
                        {
                            loadText[maxLen] = line;
                            maxLen++;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            catch { }

            try
            {
                //填充结构体正文
                for (UInt32 i = 0; i < maxLen; i++)
                {
                    string[] ArrayBuf = new string[10];
                    if (loadText[i].Contains('>') == false)
                    {
                        continue;
                    }

                    if (loadText[i].Contains(',') == false)
                    {
                        continue;
                    }
                    ArrayBuf = loadText[i].Split('>');

                    string[] recordBuf = new string[10];
                    recordBuf = ArrayBuf[1].Split(',');

                    if (recordBuf.Length < 9)
                    {
                        continue;
                    }

                    if (recordBuf[0] != "") { adcRecord1.Add(Convert.ToDouble(recordBuf[0])); }
                    if (recordBuf[1] != "") { adcRecord2.Add(Convert.ToDouble(recordBuf[1])); }
                    if (recordBuf[2] != "") { adcRecord3.Add(Convert.ToDouble(recordBuf[2])); }
                    if (recordBuf[3] != "") { adcRecord4.Add(Convert.ToDouble(recordBuf[3])); }
                    if (recordBuf[4] != "") { adcRecord5.Add(Convert.ToDouble(recordBuf[4])); }
                    if (recordBuf[5] != "") { adcRecord6.Add(Convert.ToDouble(recordBuf[5])); }
                    if (recordBuf[6] != "") { adcRecord7.Add(Convert.ToDouble(recordBuf[6])); }
                    if (recordBuf[7] != "") { adcRecord8.Add(Convert.ToDouble(recordBuf[7])); }

                    xAxisIndex.Add(i);
                }

                if (adcRecord1.Count != 0) { adcCheck1.Checked = true; } else { adcCheck1.Checked = false; }
                if (adcRecord2.Count != 0) { adcCheck2.Checked = true; } else { adcCheck2.Checked = false; }
                if (adcRecord3.Count != 0) { adcCheck3.Checked = true; } else { adcCheck3.Checked = false; }
                if (adcRecord4.Count != 0) { adcCheck4.Checked = true; } else { adcCheck4.Checked = false; }
                if (adcRecord5.Count != 0) { adcCheck5.Checked = true; } else { adcCheck5.Checked = false; }
                if (adcRecord6.Count != 0) { adcCheck6.Checked = true; } else { adcCheck6.Checked = false; }
                if (adcRecord7.Count != 0) { adcCheck7.Checked = true; } else { adcCheck7.Checked = false; }
                if (adcRecord8.Count != 0) { adcCheck8.Checked = true; } else { adcCheck8.Checked = false; }

                if (adcCheck1.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord1.ToArray(), ScottPlot.Colors.Brown); }
                if (adcCheck2.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord2.ToArray(), ScottPlot.Colors.Red); }
                if (adcCheck3.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord3.ToArray(), ScottPlot.Colors.Magenta); }
                if (adcCheck4.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord4.ToArray(), ScottPlot.Colors.Orange); }
                if (adcCheck5.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord5.ToArray(), ScottPlot.Colors.Green); }
                if (adcCheck6.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord6.ToArray(), ScottPlot.Colors.DarkCyan); }
                if (adcCheck7.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord7.ToArray(), ScottPlot.Colors.Blue); }
                if (adcCheck8.Checked == true) { waveform.Plot.Add.ScatterLine(xAxisIndex.ToArray(), adcRecord8.ToArray(), ScottPlot.Colors.Purple); }


                waveform.Plot.Axes.SetLimits(0, xAxisIndex.Count(), -5, 5);

                waveform.Show();
                waveform.Refresh();
            }
            catch { }
        }

        private void button13_Click_1(object sender, EventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog fbd = new System.Windows.Forms.FolderBrowserDialog();
            if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                filePath.Text = fbd.SelectedPath;
            }
            else
            {
                return;
            }
            filePath.Text += "\\test " + System.DateTime.Now.ToString("yy-MM-dd HH-mm-ss") + ".txt";


            FileStream fs = new FileStream(filePath.Text, FileMode.Append);
            StreamWriter wr = new StreamWriter(fs);
            //string str = "";
            StringBuilder str = new StringBuilder();
            //str.Append(System.DateTime.Now.ToString("yy-MM-dd HH-mm-ss") + "\r\n");
            //str.Append("\r\n");
            wr.Write(str);
            wr.Close();
        }

        private void button16_Click(object sender, EventArgs e)
        {
            /************消息数组转结构体************/
            if (string.IsNullOrEmpty(setAdcSamplingRate.Text)) { return; }

            byte[] buf1 = new byte[256];
            msgAdcStartOnlineRecord _pTx = new msgAdcStartOnlineRecord();

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            _pTx = (msgAdcStartOnlineRecord)Marshal.PtrToStructure(ptrStruct, typeof(msgAdcStartOnlineRecord));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(_CmdId._cmdId_startOnlineRecord);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));

            _pTx.adc_ch_Enable = SWAP16(fun_getAdcChStateEnable());
            _pTx.adc_diff_Enable = fun_getAdcChDiffState();
            _pTx.adcSignalType = Convert.ToByte(adcSignalType.Checked);
            _pTx.adcRange = Convert.ToByte(adcRange.Checked);
            _pTx.adcSamplingRate = SWAP32(Convert.ToUInt32(setAdcSamplingRate.Text));
            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _adcRecordSendData(txbuf);
        }

        private void button17_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_stopOnlineRecord), 0);
        }

        private void button15_Click_1(object sender, EventArgs e)
        {
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_readRecentConsecutiveDatas), 0);
        }



        private void button19_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getSettingParam), 0);
        }

        private void waveform_DragDrop(object sender, DragEventArgs e)
        {

        }

        private void waveform_Paint(object sender, PaintEventArgs e)
        {

        }

        private void adcRange_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdcRange), Convert.ToByte(adcRange.Checked), 0);
        }

        private void testCurrent_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdcSignalType), Convert.ToByte(adcSignalType.Checked), 0);
        }

        private void adcRange_CheckedChanged(object sender, EventArgs e)
        {
            if (adcRange.Checked == true)
            {
                adcRange.Text = "ADC量程10V";
            }
            else
            {
                adcRange.Text = "ADC量程5V";
            }
        }

        private void adcSignalType_CheckedChanged(object sender, EventArgs e)
        {
            if (adcSignalType.Checked == true)
            {
                adcSignalType.Text = "电流型";
            }
            else
            {
                adcSignalType.Text = "电压型";
            }
        }

        private void checkBox2_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_sramAdutoTrigEnable), Convert.ToByte(ckb_sramTrigEnable.Checked), 0);
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void groupBox5_Enter(object sender, EventArgs e)
        {

        }

        private void label22_Click(object sender, EventArgs e)
        {

        }

        private void autoReadTime_TextChanged(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void chk_recent200_CheckedChanged(object sender, EventArgs e)
        {

        }
        private void autoRead_Tick_1(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(autoReadTime.Text)) return;
            if (adcCalibParams.calibMode == true)
            {
                chk_recent1000.Checked = false;
                autoReadCheck.Checked = false;
            }
            try
            {
                autoRead.Interval = Convert.ToInt32(autoReadTime.Text) + 10;

                if (autoReadCheck.Checked)
                {
                    adcRecordSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getAdcValue), 0);
                }

            }
            catch { }


            //全部接收完成后再刷新波形
        }
        bool onlineRecordRefreshFlag;



        private void adcRecordSendCmdULongParam(byte cmd, byte ch, UInt32 data)
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
            _adcRecordSendData(txbuf);
        }


        private void button4_Click_1(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(setAdcSamplingRate.Text)) return;
            UInt32 freq = Convert.ToUInt32(setAdcSamplingRate.Text);
            adcRecordSendCmdULongParam(Convert.ToByte(_CmdId._cmdId_setAdc_samplingRate), 0, (UInt32)freq);
        }

        private void chk_recent200_Click(object sender, EventArgs e)
        {
            autoReadCheck.Checked = false;
            Task.Delay(300);
            if (chk_recent1000.Checked)
            {
                clearAllWaves();
            }

        }
        private void autoReadCheck_Click(object sender, EventArgs e)
        {
            chk_recent1000.Checked = false;

            Task.Delay(300);
            if (autoReadCheck.Checked)
            {
                clearAllWaves();
            }
        }

        private void diffCheck1_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck2_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck3_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck4_Click(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck1_Click_1(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck2_Click_1(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck3_Click_1(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck4_Click_1(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck1_Click_2(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck2_Click_2(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck3_Click_2(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }

        private void diffCheck4_Click_2(object sender, EventArgs e)
        {
            adcRecordSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setAdc_diffEnable), fun_getAdcChDiffState(), 0);
        }
    }
}
