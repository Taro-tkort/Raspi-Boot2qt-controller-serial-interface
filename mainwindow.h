#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSocketNotifier>
#include <QtSerialPort/QSerialPort>
#include "joypoller.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    joypoller controller0;
    const char *cntpath;
    int fd;
    struct input_event ev;
    struct input_event trsl;
    int dir;

public slots:
    void handleInputEvent();
private slots:
    void sendSerial(QByteArray s);
private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
};
#endif // MAINWINDOW_H
