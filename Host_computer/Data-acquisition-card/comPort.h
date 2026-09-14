#ifndef COMPORT_H
#define COMPORT_H
#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
class comPort
{
public:
    comPort(QString name) : _name(name){
        //实例化串口对象
        this->_serialport = new QSerialPort();
    }
    //析构函数
    ~comPort(){
        //关闭串口
        if (this->isopen()){
            //已经打开，关闭
            this->_serialport->clear();
            this->_serialport->close();
        }
        //释放内存
        delete this->_serialport;
        qDebug() << "comPort  has been released";
    }
    //判断串口是否开启
    bool isopen(){
        return this->_serialport->isOpen();
    }
    //开启串口
    bool open();
public:
    //串口对象
    QSerialPort *_serialport;
private:
    //串口名
    QString _name;

};

#endif // COMPORT_H
