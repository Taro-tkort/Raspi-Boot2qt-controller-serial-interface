#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fcntl.h>
#include <unistd.h>
#include <qdebug.h>
#include <QMessageBox>
#include <QSocketNotifier>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //joypoller controller0;
    cntpath = "/dev/input/event0";
    fd = open(cntpath, O_RDONLY);
    if (fd == -1) {
        qDebug() << "Error opening device";
    }
    //struct input_event ev;
    //struct input_event trsl;

    QSocketNotifier *notifier = NULL;

    notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    connect(notifier, &QSocketNotifier::activated, this, &MainWindow::handleInputEvent);

    //serial transmits
    //QSerialPort *serialPort = NULL;
    serialPort = new QSerialPort("/dev/ttyACM0");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Port open success!!";
    } else {
        qDebug() << "Port open failed!! + usb->errorString()";
    }

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:"
                 << (portInfo.hasVendorIdentifier()
                         ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                         : QByteArray()) << "\n"
                 << "Product Identifier:"
                 << (portInfo.hasProductIdentifier()
                         ? QByteArray::number(portInfo.productIdentifier(), 16)
                         : QByteArray());
    }
    if(serialPort->isWritable()){
        qint64 bytesWritten = serialPort->write("700\n");
    } else {
        qDebug() << "shi failed not writable\n";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInputEvent(){
    ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
    if (bytesRead == sizeof(struct input_event) && ev.code !=0) { //joypoller may need to be rewritten for the directions...
        trsl = controller0.eventInterpreter(&ev);
        qDebug() << trsl.code;
        if(trsl.code == 18){
            sendSerial("D\n");
        } else if(trsl.code == 17){
            sendSerial("U\n");
        } else if(trsl.code == 14){
            sendSerial("T\n");
        }
    }
}

void MainWindow::sendSerial(QByteArray s){
    // Send data to the Arduino
    //QByteArray dataToSend ="B";
    //std::string sendata = std::to_string(s) + "\n";
    //qDebug(sendata);
    //QByteArray poop = "250\n";
    qint64 bytesWritten = serialPort->write(s);
}

