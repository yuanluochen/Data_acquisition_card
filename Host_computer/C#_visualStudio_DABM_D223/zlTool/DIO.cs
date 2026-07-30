using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.DirectoryServices.ActiveDirectory;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static zlTool.msgStruct;
using static zlTool.zlTool;

namespace zlTool
{
    public delegate void dioSendData(byte[] str);
    public partial class DIO : Form
    {
        public event dioSendData _dioSendData;

        zlTool _mainForm = null;
        public DIO(zlTool zlMain)
        {
            InitializeComponent();
            _mainForm = zlMain;
        }

        private void DIO_Load(object sender, EventArgs e)
        {
            this._mainForm._deviceRxMsg += new deviceRxMsg(rxMsgProcess);
        }



        public void rxMsgProcess(byte[] rxBuf)
        {
            BeginInvoke(new MethodInvoker(delegate
            {
                try
                {
                    msgHead _pRxHead = new msgHead();
                    _pRxHead = (msgHead)msgStruct.BytesToDataStruct(rxBuf, typeof(msgHead));

                    if (_pRxHead.cmdId == (byte)_CmdId._cmdId_getIoAll)
                    {
                        msgGetDioAll _prxData = new msgGetDioAll();
                        _prxData = (msgGetDioAll)msgStruct.BytesToDataStruct(rxBuf, typeof(msgGetDioAll));

                        dinCheck1.Checked = ((_prxData.din >>0) & 1) == 1;
                        dinCheck2.Checked = ((_prxData.din >>1) & 1) == 1;
                        dinCheck3.Checked = ((_prxData.din >>2) & 1) == 1;
                        dinCheck4.Checked = ((_prxData.din >>3) & 1) == 1;
                        dinCheck5.Checked = ((_prxData.din >>4) & 1) == 1;
                        dinCheck6.Checked = ((_prxData.din >>5) & 1) == 1;
                        dinCheck7.Checked = ((_prxData.din >>6) & 1) == 1;
                        dinCheck8.Checked = ((_prxData.din >>7) & 1) == 1;

                        doutCheck1.Checked = ((_prxData.dout >> 0) & 1) == 1;
                        doutCheck2.Checked = ((_prxData.dout >> 1) & 1) == 1;

                        pwmCheck1.Checked = ((_prxData.pwmEnable >> 0) & 1) == 1;
                        pwmCheck2.Checked = ((_prxData.pwmEnable >> 1) & 1) == 1;
                        pwmCheck3.Checked = ((_prxData.pwmEnable >> 2) & 1) == 1;
                        pwmCheck4.Checked = ((_prxData.pwmEnable >> 3) & 1) == 1;
                        pwmCheck5.Checked = ((_prxData.pwmEnable >> 4) & 1) == 1;
                        pwmCheck6.Checked = ((_prxData.pwmEnable >> 5) & 1) == 1;

                        pwmFreq1.Text = SWAP16(_prxData.pwmFreq[0]).ToString();
                        pwmFreq2.Text = SWAP16(_prxData.pwmFreq[1]).ToString();
                        pwmFreq3.Text = SWAP16(_prxData.pwmFreq[2]).ToString();
                        pwmFreq4.Text = SWAP16(_prxData.pwmFreq[3]).ToString();
                        pwmFreq5.Text = SWAP16(_prxData.pwmFreq[4]).ToString();
                        pwmFreq6.Text = SWAP16(_prxData.pwmFreq[5]).ToString();

                        pwmDuty1.Text = (Convert.ToDouble(SWAP16(_prxData.pwmDuty[0])) / 10).ToString("0.0");
                        pwmDuty2.Text = (Convert.ToDouble(SWAP16(_prxData.pwmDuty[1])) / 10).ToString("0.0");
                        pwmDuty3.Text = (Convert.ToDouble(SWAP16(_prxData.pwmDuty[2])) / 10).ToString("0.0");
                        pwmDuty4.Text = (Convert.ToDouble(SWAP16(_prxData.pwmDuty[3])) / 10).ToString("0.0");
                        pwmDuty5.Text = (Convert.ToDouble(SWAP16(_prxData.pwmDuty[4])) / 10).ToString("0.0");
                        pwmDuty6.Text = (Convert.ToDouble(SWAP16(_prxData.pwmDuty[5])) / 10).ToString("0.0");

                        pwmPulseNum1.Text = SWAP16(_prxData.pwmPulseNum[0]).ToString();
                        pwmPulseNum2.Text = SWAP16(_prxData.pwmPulseNum[1]).ToString();
                        pwmPulseNum3.Text = SWAP16(_prxData.pwmPulseNum[2]).ToString();
                        pwmPulseNum4.Text = SWAP16(_prxData.pwmPulseNum[3]).ToString();
                        pwmPulseNum5.Text = SWAP16(_prxData.pwmPulseNum[4]).ToString();
                        pwmPulseNum6.Text = SWAP16(_prxData.pwmPulseNum[5]).ToString();

                        pwmAccUnit1.Text = SWAP16(_prxData.pwmAccUnit[0]).ToString();
                        pwmAccUnit2.Text = SWAP16(_prxData.pwmAccUnit[1]).ToString();
                        pwmAccUnit3.Text = SWAP16(_prxData.pwmAccUnit[2]).ToString();
                        pwmAccUnit4.Text = SWAP16(_prxData.pwmAccUnit[3]).ToString();
                        pwmAccUnit5.Text = SWAP16(_prxData.pwmAccUnit[4]).ToString();
                        pwmAccUnit6.Text = SWAP16(_prxData.pwmAccUnit[5]).ToString();

                    }
                }

                catch { }
                ;
            }));
        }
        private void dioSendCmdNoParam(byte cmd, byte ch)
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
            _dioSendData(txbuf);
        }


        private void dioSendCmdUByteParam(byte cmd, byte ch, byte data)
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
            _dioSendData(txbuf);
        }


        private void button1_Click(object sender, EventArgs e)
        {
            dioSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getIoAll), 0);
        }
        private void doutCheck1_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 1, Convert.ToByte(doutCheck1.Checked));
        }

        private void doutCheck2_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 2, Convert.ToByte(doutCheck2.Checked));
        }

        private void doutCheck5_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 3, Convert.ToByte(pwmCheck1.Checked));
        }

        private void doutCheck6_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 4, Convert.ToByte(pwmCheck2.Checked));
        }

        private void doutCheck7_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 5, Convert.ToByte(pwmCheck3.Checked));
        }

        private void doutCheck8_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 6, Convert.ToByte(pwmCheck4.Checked));
        }

        private void pwmCheck5_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 7, Convert.ToByte(pwmCheck5.Checked));
        }

        private void pwmCheck6_Click(object sender, EventArgs e)
        {
            dioSendCmdUByteParam(Convert.ToByte(_CmdId._cmdId_setOutputIO), 8, Convert.ToByte(pwmCheck6.Checked));
        }

        private void func_setPwmParams(byte ch, UInt16 freq, UInt16 duty, UInt16 pulseNum, UInt16 accUnit)
        {
            /************消息数组转结构体************/
            byte[] buf1 = new byte[256];

            //数组转结构体，字节对齐
            IntPtr ptrStruct = Marshal.AllocHGlobal(256);//分配非托管内存空间
            Marshal.Copy(buf1, 0, ptrStruct, buf1.Length);//将数组数组拷贝到非托管内存指针
            msgPwmParam _pTx = (msgPwmParam)Marshal.PtrToStructure(ptrStruct, typeof(msgPwmParam));
            Marshal.FreeHGlobal(ptrStruct);//释放内存
            /************************/

            _pTx.msgHead = SWAP16(0x55aa);
            _pTx.cmdId = Convert.ToByte(_CmdId._cmdId_setPwmParam);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));
            _pTx.ch = Convert.ToByte(ch);
            _pTx.freq = SWAP16(freq);
            _pTx.duty = SWAP16(duty);
            _pTx.pulseNum = SWAP16(pulseNum);
            _pTx.accUnit = SWAP16(accUnit);

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            _dioSendData(txbuf);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(pwmFreq1.Text)) return;
            if (string.IsNullOrEmpty(pwmDuty1.Text)) return;
            if (string.IsNullOrEmpty(pwmPulseNum1.Text)) return;
            if (string.IsNullOrEmpty(pwmAccUnit1.Text)) return;

            UInt16 pwmFreq = Convert.ToUInt16(pwmFreq1.Text);
            double duty = Convert.ToDouble(pwmDuty1.Text) * 10;
            UInt16 pwmDuty = (UInt16)duty;
            UInt16 pwmPulseNum = Convert.ToUInt16(pwmPulseNum1.Text);
            UInt16 pwmAccUnit = Convert.ToUInt16(pwmAccUnit1.Text);

            func_setPwmParams(1, pwmFreq, pwmDuty, pwmPulseNum, pwmAccUnit);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(pwmFreq2.Text)) return;
            if (string.IsNullOrEmpty(pwmDuty2.Text)) return;
            if (string.IsNullOrEmpty(pwmPulseNum2.Text)) return;
            if (string.IsNullOrEmpty(pwmAccUnit2.Text)) return;

            UInt16 pwmFreq = Convert.ToUInt16(pwmFreq2.Text);
            double duty = Convert.ToDouble(pwmDuty2.Text) * 10;
            UInt16 pwmDuty = (UInt16)duty;
            UInt16 pwmPulseNum = Convert.ToUInt16(pwmPulseNum2.Text);
            UInt16 pwmAccUnit = Convert.ToUInt16(pwmAccUnit2.Text);

            func_setPwmParams(2, pwmFreq, pwmDuty, pwmPulseNum, pwmAccUnit);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(pwmFreq3.Text)) return;
            if (string.IsNullOrEmpty(pwmDuty3.Text)) return;
            if (string.IsNullOrEmpty(pwmPulseNum3.Text)) return;
            if (string.IsNullOrEmpty(pwmAccUnit3.Text)) return;

            UInt16 pwmFreq = Convert.ToUInt16(pwmFreq3.Text);
            double duty = Convert.ToDouble(pwmDuty3.Text) * 10;
            UInt16 pwmDuty = (UInt16)duty;
            UInt16 pwmPulseNum = Convert.ToUInt16(pwmPulseNum3.Text);
            UInt16 pwmAccUnit = Convert.ToUInt16(pwmAccUnit3.Text);

            func_setPwmParams(3, pwmFreq, pwmDuty, pwmPulseNum, pwmAccUnit);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(pwmFreq4.Text)) return;
            if (string.IsNullOrEmpty(pwmDuty4.Text)) return;
            if (string.IsNullOrEmpty(pwmPulseNum4.Text)) return;
            if (string.IsNullOrEmpty(pwmAccUnit4.Text)) return;

            UInt16 pwmFreq = Convert.ToUInt16(pwmFreq4.Text);
            double duty = Convert.ToDouble(pwmDuty4.Text) * 10;
            UInt16 pwmDuty = (UInt16)duty;
            UInt16 pwmPulseNum = Convert.ToUInt16(pwmPulseNum4.Text);
            UInt16 pwmAccUnit = Convert.ToUInt16(pwmAccUnit4.Text);

            func_setPwmParams(4, pwmFreq, pwmDuty, pwmPulseNum, pwmAccUnit);
        }

        private void autoRead_Tick(object sender, EventArgs e)
        {
            if (ckb_atrd.Checked)
            {
                dioSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getIoAll), 0);
            }
        }

        private void doutCheck4_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void ckb_atrd_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void doutCheck2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void doutCheck3_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(pwmFreq5.Text)) return;
            if (string.IsNullOrEmpty(pwmDuty5.Text)) return;
            if (string.IsNullOrEmpty(pwmPulseNum5.Text)) return;
            if (string.IsNullOrEmpty(pwmAccUnit5.Text)) return;

            UInt16 pwmFreq = Convert.ToUInt16(pwmFreq5.Text);
            double duty = Convert.ToDouble(pwmDuty5.Text) * 10;
            UInt16 pwmDuty = (UInt16)duty;
            UInt16 pwmPulseNum = Convert.ToUInt16(pwmPulseNum5.Text);
            UInt16 pwmAccUnit = Convert.ToUInt16(pwmAccUnit5.Text);

            func_setPwmParams(5, pwmFreq, pwmDuty, pwmPulseNum, pwmAccUnit);

        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(pwmFreq6.Text)) return;
            if (string.IsNullOrEmpty(pwmDuty6.Text)) return;
            if (string.IsNullOrEmpty(pwmPulseNum6.Text)) return;
            if (string.IsNullOrEmpty(pwmAccUnit6.Text)) return;

            UInt16 pwmFreq = Convert.ToUInt16(pwmFreq6.Text);
            double duty = Convert.ToDouble(pwmDuty6.Text) * 10;
            UInt16 pwmDuty = (UInt16)duty;
            UInt16 pwmPulseNum = Convert.ToUInt16(pwmPulseNum6.Text);
            UInt16 pwmAccUnit = Convert.ToUInt16(pwmAccUnit6.Text);

            func_setPwmParams(6, pwmFreq, pwmDuty, pwmPulseNum, pwmAccUnit);

        }

    }
}
