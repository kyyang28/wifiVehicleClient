#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "control.h"
#include "setupdialog.h"
#include "displayvideo.h"
#include "aboutdialog.h"
#include "grapdialog.h"
#include "ctrlmodedialog.h"

namespace Ui {
    class MainWindow;
}

class ctrlModeDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

private slots:
    /* Wifi vehicle control operations */
    void on_frontButton_pressed();
    void on_frontButton_released();
    void on_leftButton_pressed();
    void on_leftButton_released();
    void on_rightButton_pressed();
    void on_rightButton_released();
    void on_backButton_pressed();
    void on_backButton_released();
    void on_connectButton_clicked();

    /* Temperature related */
    void on_readTempButton_clicked();

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

    void on_actionPicture_directory_setup_triggered();

    /* Camera on/off/capture operations */
    void on_startCamButton_clicked();
    void on_stopCamButton_clicked();
    void on_capFrameButton_clicked();

    /* Camera control operations */
    void on_camUpButton_pressed();
    void on_camDownButton_pressed();
    void on_camLeftButton_pressed();
    void on_camRightButton_pressed();
    void on_camUpButton_released();
    void on_camDownButton_released();
    void on_camLeftButton_released();
    void on_camRightButton_released();

    /* Miscellaneous */
    void on_back2ModeButton_clicked();

private:
    Ui::MainWindow *ui;

    ctrlModeDialog *ctrlMode;
    SetupDialog *setup;
    grapDialog *grap;
    AboutDialog *about;
    control *carControl;        //定义 control 类
    bool isConnected;             //判断是否按了连接按钮
    bool isConnecting;
    bool openvideo;             //判断视频是否开启
    void newConnect();
    void disconnect();
    void savePicture();
};

#endif // MAINWINDOW_H
