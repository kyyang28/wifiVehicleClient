#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "control.h"
#include "setupdialog.h"
#include "displayvideo.h"
#include "aboutdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

private slots:
    /* Control related */
    void on_frontButton_pressed();
    void on_frontButton_released();
    void on_leftButton_pressed();
    void on_leftButton_released();
    void on_rightButton_pressed();
    void on_rightButton_released();
    void on_backButton_pressed();
    void on_backButton_released();
    void on_connectButton_clicked();

    /* Camera related */
    void on_startCamButton_clicked();
    void on_stopCamButton_clicked();
    void on_capFrameButton_clicked();

    /* Temperature related */
    void on_readTempButton_clicked();

    /* Buzzer related */
    void on_buzzerButton_clicked();

    void on_exitButton_clicked();

    void on_actionIP_Setup_IP_triggered();

    /* TcpSocket related */
    void socketSucceed();
    void socketFailed();

    void on_pwmMotorSlider_valueChanged(int value);

    void on_disconnectButton_clicked();
    void on_actionAbout_triggered();

    void on_actionExit_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

private:
    Ui::MainWindow *ui;

    SetupDialog *setup;
    AboutDialog *about;
    control *carControl;        //定义 control 类
    bool isConnected;             //判断是否按了连接按钮
    bool isConnecting;
    bool openvideo;             //判断视频是否开启 。
    void newConnect();
    void disconnect();
};

#endif // MAINWINDOW_H
