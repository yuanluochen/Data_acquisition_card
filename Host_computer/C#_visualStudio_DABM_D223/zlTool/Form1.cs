using ScottPlot;
using ScottPlot.AxisPanels;
using ScottPlot.Colormaps;
using ScottPlot.Palettes;
using ScottPlot.Statistics;
using SkiaSharp;
using System;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Net;
using System.Net.Sockets;
using System.Reflection.Metadata;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.InteropServices;
using System.Xml.Linq;
using static System.Runtime.InteropServices.JavaScript.JSType;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Rebar;
using static zlTool.msgStruct;
using System.Threading;

namespace zlTool
{
    public partial class zlTool : Form
    {
        public delegate void deviceRxMsg(byte[] data);

        public event deviceRxMsg _deviceRxMsg;

        public zlTool()
        {
            InitializeComponent();

        }

        //实例化
        autoscaling _adc_record_page = null;
        ddsDac _ddsDac_page = null;
        DIO _DIO_page = null;
        Setting _Setting_page = null;

        public static SerialPort comPort = new SerialPort();


        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;

            comPort.DataReceived += new SerialDataReceivedEventHandler(Com_DataReceived);  //绑定其他页面串口发送任务

            fun_findSerialPort();


            _adc_record_page = new autoscaling(this);
            _ddsDac_page = new ddsDac(this);
            _DIO_page = new DIO(this);
            _Setting_page = new Setting(this);

            _adc_record_page._adcRecordSendData += new adcRecord_SendData(usbSend);

            _ddsDac_page._ddsDacSendData += new ddsDac_SendData(usbSend);

            _DIO_page._dioSendData += new dioSendData(usbSend);

            _Setting_page._settingSendData += new settingSendData(usbSend);

            _adc_record_page.TopLevel = false;                         //设置窗体为不显示顶级窗口
            _adc_record_page.FormBorderStyle = FormBorderStyle.None;   //设置子窗体样式,取消标题栏
            _adc_record_page.Dock = DockStyle.Fill;                    //填充显示

            _Setting_page.TopLevel = false;                         //设置窗体为不显示顶级窗口
            _Setting_page.FormBorderStyle = FormBorderStyle.None;   //设置子窗体样式,取消标题栏
            _Setting_page.Dock = DockStyle.Fill;

            _Setting_page.Show();

            this.childWindow.Controls.Clear();              //清空窗体控件
            this.childWindow.Controls.Add(_adc_record_page);
            _adc_record_page.Show();
            //参数初始化
            for (int i = 0; i < 8; i++)
            {
                adcCalibParams.calib_adcCalib_enableA[i] = 0;
                adcCalibParams.calib_adcCalib_enableB[i] = 0;
                adcCalibParams.correctFactor[i] = 100000;
                adcCalibParams.calibZero[i] = 0;
            }
        }


        private void button4_Click(object sender, EventArgs e)
        {
            _adc_record_page.TopLevel = false;                         //设置窗体为不显示顶级窗口
            _adc_record_page.FormBorderStyle = FormBorderStyle.None;   //设置子窗体样式,取消标题栏
            _adc_record_page.Dock = DockStyle.Fill;                    //填充显示
            this.childWindow.Controls.Clear();              //清空窗体控件
            this.childWindow.Controls.Add(_adc_record_page);
            _adc_record_page.Show();

            msgSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getDeviceParam));
        }

        private void button7_Click(object sender, EventArgs e)
        {
            _ddsDac_page.TopLevel = false;                         //设置窗体为不显示顶级窗口
            _ddsDac_page.FormBorderStyle = FormBorderStyle.None;   //设置子窗体样式,取消标题栏
            _ddsDac_page.Dock = DockStyle.Fill;                    //填充显示
            this.childWindow.Controls.Clear();              //清空窗体控件
            this.childWindow.Controls.Add(_ddsDac_page);
            _ddsDac_page.Show();

            msgSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_ddsDacGetParamTotal));
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _DIO_page.TopLevel = false;                         //设置窗体为不显示顶级窗口
            _DIO_page.FormBorderStyle = FormBorderStyle.None;   //设置子窗体样式,取消标题栏
            _DIO_page.Dock = DockStyle.Fill;                    //填充显示
            this.childWindow.Controls.Clear();              //清空窗体控件
            this.childWindow.Controls.Add(_DIO_page);
            _DIO_page.Show();

            msgSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getIoAll));
        }


        private void button3_Click(object sender, EventArgs e)
        {
            _Setting_page.TopLevel = false;                         //设置窗体为不显示顶级窗口
            _Setting_page.FormBorderStyle = FormBorderStyle.None;   //设置子窗体样式,取消标题栏
            _Setting_page.Dock = DockStyle.Fill;                    //填充显示
            this.childWindow.Controls.Clear();              //清空窗体控件
            this.childWindow.Controls.Add(_Setting_page);
            _Setting_page.Show();

            msgSendCmdNoParam(Convert.ToByte(_CmdId._cmdId_getSettingParam));
        }


        private void fun_findSerialPort()
        {
            serialPort.Text = "";
            serialPort.Items.Clear();
            serialPort.Items.AddRange(SerialPort.GetPortNames());

            //查询主机上存在的串口
            if (serialPort.Items.Count > 0)
            {
                serialPort.SelectedIndex = 0;
            }
            else
            {
                serialPort.Text = "NO PORT";
            }
        }

        private void serialPort_Click(object sender, EventArgs e)
        {
            fun_findSerialPort();
        }

        public void usbSend(byte[] txbuf)
        {
            if (comPort.IsOpen)
            {
                try
                {
                    comPort.Write(txbuf, 0, txbuf.Length);//发送数据
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

        }




        private void msgSendCmdNoParam(byte cmd)
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

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            usbSend(txbuf);
        }




        private void serialOpen_Click(object sender, EventArgs e)
        {
            if (comPort.IsOpen == false)
            {
                comPort.PortName = serialPort.SelectedItem.ToString();
                comPort.BaudRate = Convert.ToInt32(115200);
                comPort.Parity = Parity.None;
                comPort.DataBits = 8;
                comPort.StopBits = StopBits.One;
                try
                {
                    comPort.Open();
                }
                catch (Exception ex)
                {
                    serialOpen.Text = "打开串口";
                    serialPort.Enabled = true;
                    return;
                }
                serialOpen.Text = "关闭串口";
                serialPort.Enabled = false;
            }
            else
            {
                try
                {
                    comPort.Close();

                }
                catch (Exception ex)
                {

                }
                serialOpen.Text = "打开串口";
                serialPort.Enabled = true;
            }

        }

        /// <summary>
        /// 接收服务端
        /// </summary>
        List<byte> usbRxMsgBuf = new List<byte>();
        UInt16 uart_overtime_tick;
        private void Com_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            byte[] rdData = new byte[comPort.BytesToRead];
            comPort.Read(rdData, 0, rdData.Length);//读取数据1

            //将新收到的数据放进缓存区, 并标记开始接收
            //listArrayCopy(rdData, usbRxMsgBuf, rdData.Length);
            usbRxMsgBuf.AddRange(rdData);
            // uart_overtime_tick = 0;
        }

        private void rxTim_Tick(object sender, EventArgs e)
        {
            //检索收到的数据开头是否为0x55aa, 如果不是则继续轮循下一步
            while (usbRxMsgBuf.Count > 5)
            {
                //找0x55作为包头
                bool findNewHead = false;
                byte[] usbRxBuf = usbRxMsgBuf.ToArray();

                for (UInt16 i = 0; i < usbRxBuf.Length; i++)
                {
                    if (usbRxBuf[i] == 0x55 && i != (usbRxBuf.Length - 1))
                    {
                        if (usbRxBuf[i + 1] == 0xaa)
                        {
                            if (i > 0 && usbRxMsgBuf.Count >= i)
                            {
                                //清除源文件数据
                                usbRxMsgBuf.RemoveRange(0, i);
                                break;
                            }

                            //检索到报文开头,判断是否完成一帧
                            findNewHead = true;
                            msgHead _pRxHead = new msgHead();
                            _pRxHead = (msgHead)msgStruct.BytesToDataStruct(usbRxBuf, typeof(msgHead));

                            if ((usbRxBuf.Length - i) >= SWAP16(_pRxHead.frameLen))
                            {
                                string crcResult = crcCheck.checkCrc16WithTail(usbRxBuf, SWAP16(_pRxHead.frameLen));

                                if (crcResult != "OK")
                                {
                                    //校验失败, 说明0x55aa不是包头 或者数据被污染, 重新找包头
                                    usbRxMsgBuf.RemoveRange(0, 2);
                                    break;
                                }
                                _deviceRxMsg(usbRxMsgBuf.ToArray());
                                usbRxMsgBuf.RemoveRange(0, SWAP16(_pRxHead.frameLen));
                                break;
                            }
                            else
                            {
                                //长度不够, 退出中断继续接收
                                return;
                            }
                        }
                    }
                }

                //未找到 newHead, 则清空缓存区
                if (!findNewHead)
                {
                    usbRxMsgBuf.Clear();
                }
            }
        }



        private void ckb_net_Click(object sender, EventArgs e)
        {
            // rxNetTim.Enabled = true;
            // rxUsbTim.Enabled = false;

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
            _pTx.cmdId = Convert.ToByte(_CmdId._cmdId_setCommunicatiaonPort);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
        }

        private void ckb_usb_Click(object sender, EventArgs e)
        {
            //rxNetTim.Enabled = false;
            //rxUsbTim.Enabled = true;
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
            _pTx.cmdId = Convert.ToByte(_CmdId._cmdId_setCommunicatiaonPort);
            _pTx.frameLen = SWAP16((UInt16)Marshal.SizeOf(_pTx));

            //结构体转数组
            byte[] txbuf1 = StructToBytes(_pTx);
            ushort crctx = crcCheck.getCrc16WithTail(txbuf1, SWAP16(_pTx.frameLen));
            _pTx.crc = SWAP16(crctx);
            byte[] txbuf = StructToBytes(_pTx);
            usbSend(txbuf);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void childWindow_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }
}
