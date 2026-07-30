using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using static SkiaSharp.SKImageFilter;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace zlTool
{
    internal class msgStruct
    {

        public enum _CmdId
        {
            //示波器指令
            _cmdId_setAdc_chEnable = 0x01,
            _cmdId_getDeviceParam = 0x02,
            _cmdId_getAdc_waveData = 0x03,
            _cmdId_setAdc_waveEnable_flag = 0x04,
            _cmdId_setAdc_trigCh = 0x05,
            _cmdId_setAdc_samplingRate = 0x06,
            _cmdId_setAdc_trigValue = 0x07,
            _cmdId_getAdcValue = 0x08,

		    _cmdId_setCommunicatiaonPort = 0x0f,

            _cmdId_startSramRecord = 0x10,
            _cmdId_stopSramRecord = 0x11,
            _cmdId_getSramRecordDatas = 0x12,
            _cmdId_sramRecordAutoUploadDatas = 0x13,
            _cmdId_recordUploadStart = 0x14,
            _cmdId_recordUploadEnd = 0x15,
            _cmdId_startOnlineRecord = 0x16,
            _cmdId_stopOnlineRecord = 0x17,
            _cmdId_readOnlineRecordDatas = 0x18,
            _cmdId_readRecentConsecutiveDatas = 0x19,
            _cmdId_setAdc_diffEnable = 0x1a,
            _cmdId_readRecentConsecutiveDatasInit = 0x1b,
           

            _cmdId_ddsDacGetParamTotal = 0x20,
            _cmdId_ddsDacGetParam = 0x21,
            _cmdId_setDdsDacParam = 0x22,
            _cmdId_setDdsDacWorkMode = 0x23,
            _cmdId_setDdsDacDatas = 0x24,
            _cmdId_ddsDacCalibPoint1 = 0x25,
            _cmdId_ddsDacCalibPoint2 = 0x26,
            _cmdId_ddsDacClearCalib = 0x27,
            _cmdId_ddsDacGetCalibParam = 0x28,

            _cmdId_getIoAll = 0x30,
            _cmdId_getInputIO = 0x31,
            _cmdId_setOutputIO = 0x32,

            _cmdId_setPwmEnable = 0x33,
            _cmdId_setPwmParam = 0x34,

            _cmdId_setAdcRange = 0x40,
            _cmdId_setAdcSignalType = 0x41,
            _cmdId_sramAdutoTrigEnable = 0x42,

            _cmdId_getSettingParam = 0x50,
            _cmdId_settingAdcCalibPoint1 = 0x51,
            _cmdId_settingAdcCalibPoint2 = 0x52,
            _cmdId_settingClearAdcCalibDatas = 0x53,
            _cmdId_settingSetAdcCalibMode = 0x54,
            _cmdId_getAdcCalibParam = 0x55,
            _cmdId_setIpAndPort = 0x56,
            _cmdId_getIpAndPort = 0x57,
            _cmdId_setDeviceAddr = 0x58,
            _cmdId_setDeviceBauds = 0x59,

            _cmdId_setCorrectFactor = 0x5b,
            _cmdId_setCalibZero = 0x5c,
            _cmdId_getCalibVolt = 0x5d,
            _cmdId_setRecordDelay = 0x5e,
            _cmdId_setSensorUnit = 0x5f,

            _cmdId_getSoftVersion = 0xf0,

        };


        public static class adcCalibParams
        {
            public static Int32[] calib_adcCalib_digitalA = new Int32[8];
            public static Int32[] calib_adcCalib_analogA = new Int32[8];
            public static byte[] calib_adcCalib_enableA = new byte[8];
            public static Int32[] calib_adcCalib_digitalB = new Int32[8];
            public static Int32[] calib_adcCalib_analogB = new Int32[8];
            public static byte[] calib_adcCalib_enableB = new byte[8];
            public static Int32[] calibZero = new Int32[8];
            public static Int32[] correctFactor = new Int32[8];
            public static bool calibMode;
            public static byte[] sensorUnit = new byte[8];
            public static string[] sensorUnitList = {
                        "V",
                        "mV",
                        "A",
                        "mA",
                        "℃",
                        "m℃",
                        "N",
                        "kg",
                        "g",
                        "G",
                        "K",
                        "mK",
                        "MPa",
                        "kPa",
                        "hPa",
                        "Pa",
                        "℉"
                        };
        }

        public static double calc_adcCalibData(double data, double d1, double a1, double d2, double a2)
        {
            double result = (((data - d1) * (a2 - a1)  / (d2 - d1))  + a1);
            return result;
        }

        public enum _ddsDacWorkMode
        {
            //示波器指令
            _ddsDacWorkMode_Stop = 0x00,
            _ddsDacWorkMode_Dc = 0x01,
            _ddsDacWorkMode_Sin = 0x02,
            _ddsDacWorkMode_Triangle = 0x03,
            _ddsDacWorkMode_Square = 0x04,
            _ddsDacWorkMode_Dds = 0x05,
            _ddsDacWorkMode_Calib = 0xff,

        };

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgHead
        {
            public UInt16 head;
            public byte cmdId;
            public UInt16 frameLen;
        }


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgSetDacDatas
        {
            public UInt16 head;
            public byte cmdId;
            public UInt16 frameLen;
            public UInt16 dataLen;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] ddsDatas;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetDacCalibParam
        {
            public UInt16 head;
            public byte cmdId;
            public UInt16 frameLen;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public calibDatas[] _dacCalibDatasPointA;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public calibDatas[] _dacCalibDatasPointB;
            public UInt16 crc;
        }
        
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgDdsDacParam
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public byte ch;

            public UInt16 dacRate;

            public UInt16 freq;
            public UInt16 volt;
            public UInt16 duty;
            public UInt16 bias;
            public UInt16 phase;

            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgAdcWaveState
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            
            public byte adcSignalType;
            public byte adcRange;
            public byte trigCh;
            public UInt32 adcSamplingRate;
            public UInt16 adcTrigValue;

            public UInt32 adcSramRecordMaxTime;
            public byte sramAdutoTrigEnable;

            public UInt16 crc;
        }


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgAdcStartSramRecord
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;

            public byte adcSignalType;
            public byte adcRange;

            public UInt32 adcSamplingRate;
            public UInt32 sramSamplingTime;

            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgAdcStartOnlineRecord
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            public byte adcSignalType;
            public byte adcRange;
            public UInt32 adcSamplingRate;

            public UInt16 crc;
        }


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgNoParam
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public byte ch;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgUbyte
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public byte ch;
            public byte data;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgUWord
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public byte ch;
            public UInt16 data;
            public UInt16 crc;
        }


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgULong
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public byte ch;
            public UInt32 data;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgSLong
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public byte ch;
            public Int32 data;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetAdcValue
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            public byte adcSignalType;
            public byte adcRange;
            public byte din;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public Int32[] adcValue;

            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetCalibVolt
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            public byte adcRange;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public Int32[] adcValue;

            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetRecentConsecutiveDatas
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public UInt32 globalTick;
            public UInt32 adcSamplingRate;
            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            public byte adcSignalType;
            public byte adcRange;
            public byte din;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData1;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData2;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData3;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData4;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData5;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData6;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData7;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1000)]
            public UInt16[] adcData8;
            public UInt16 crc;  
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgAutoUploadDatas
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            public byte adcSignalType;
            public byte adcRange;

            public byte hour;
            public byte minute;
            public byte second;

            public UInt16 crc;
        }


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetDioAll
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public byte din;

            public byte dout;

            public byte pwmEnable;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
            public UInt16[] pwmFreq;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
            public UInt16[] pwmDuty;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
            public UInt16[] pwmPulseNum;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
            public UInt16[] pwmAccUnit;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetAdcDatas
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;
            public UInt16 dataLen;

            public UInt16 adc_ch_Enable;
            public byte adc_diff_Enable;
            public byte adcSignalType;
            public byte adcRange;
            public byte trigCh;
            public UInt32 adcSamplingRate;
            public UInt16 adcTrigValue;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10000)]
            public Int16[] adcData;

            public UInt16 crc;
        }


        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct calibDatas
        {
            public byte calibEnable;
            public Int32 calibDigital;
            public Int32 calibAnalog;
        }
            
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgGetSettingParam
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public byte deviceWorkMode;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public calibDatas[] _adcCalibDatasPointA;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public calibDatas[] _adcCalibDatasPointB;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public Int32[] correctFactor;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public Int32[] calibZero;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
            public byte[] sensorUnit;
            
            public byte RecordDelay;

            public UInt32 softVersion;
            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgPwmParam
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public byte ch;

            public UInt16 freq;
            public UInt16 duty;
            public UInt16 pulseNum;
            public UInt16 accUnit;

            public UInt16 crc;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct msgSetIpAndPort
        {
            public UInt16 msgHead;
            public byte cmdId;
            public UInt16 frameLen;

            public byte ch;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
            public byte[] serverIp;

            public UInt16 serverPort;

            public UInt16 crc;
        }

        public static UInt16 SWAP16(UInt16 data)
        {
            UInt16 low, high;
            low = (UInt16)((data >> 8) & 0xff);
            high = (UInt16)((data & 0xff) << 8);

            return (UInt16)(high | low);
        }

        public static UInt32 SWAP32(UInt32 data)
        {
            UInt32 b1, b2, b3, b4;
            b1 = (UInt32)(((data >> 0) & 0xff) << 24);
            b2 = (UInt32)(((data >> 8) & 0xff) << 16);
            b3 = (UInt32)(((data >> 16) & 0xff) << 8);
            b4 = (UInt32)(((data >> 24) & 0xff) << 0);

            return (UInt32)(b1 | b2 | b3 | b4);
        }
        public static Int16 SWAPS16(Int16 data)
        {
            Int16 low, high;
            low = (Int16)((data >> 8) & 0xff);
            high = (Int16)((data & 0xff) << 8);

            return (Int16)(high | low);
        }

        public static Int32 SWAPS32(Int32 data)
        {
            Int32 b1, b2, b3, b4;
            b1 = (Int32)(((data >> 0) & 0xff) << 24);
            b2 = (Int32)(((data >> 8) & 0xff) << 16);
            b3 = (Int32)(((data >> 16) & 0xff) << 8);
            b4 = (Int32)(((data >> 24) & 0xff) << 0);

            return (Int32)(b1 | b2 | b3 | b4);
        }

        public static void BytesArrayCopy(byte[] sorce, byte[] destination, int index, int len)
        {
            for (int i = 0; i < len; i++)
            {
                destination[i + index] = sorce[i];
            }
        }


        public static void listArrayCopy(byte[] sorce, List<byte> destination, int len)
        {
            for (int i = 0; i < len; i++)
            {
                destination.Add(sorce[i]);
            }
        }

        public static object BytesToDataStruct(byte[] bytes, Type type)
        {
            //DataStruct data = new DataStruct();

            int size = Marshal.SizeOf(type);

            if (size > bytes.Length)
            {
                return null;
            }

            IntPtr structPtr = Marshal.AllocHGlobal(size);
            Marshal.Copy(bytes, 0, structPtr, size);
            object obj = Marshal.PtrToStructure(structPtr, type);
            Marshal.FreeHGlobal(structPtr);
            return obj;
        }

        public static byte[] StructToBytes(object anyStruct)
        {
            int size = Marshal.SizeOf(anyStruct);
            IntPtr bytesPtr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(anyStruct, bytesPtr, false);
            byte[] bytes = new byte[size];
            Marshal.Copy(bytesPtr, bytes, 0, size);
            Marshal.FreeHGlobal(bytesPtr);

            return bytes;
        }
    }
}
