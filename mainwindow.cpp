#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Wifi Vehicle Client"));
    setObjectName("MainWindow");
    setStyleSheet("#MainWindow{border-image:url(:/wifiVehicleImages/image/background.png);}");
    ui->readTempButton->setObjectName("readTempButton");
    ui->readTempButton->setStyleSheet("#readTempButton{border-image:url(:/wifiVehicleImages/image/readTemperature.png);}");
    ui->exitButton->setObjectName("exitButton");
    ui->exitButton->setStyleSheet("#exitButton{border-image:url(:/wifiVehicleImages/image/exit.png);}");
    ui->back2ModeButton->setObjectName("back2ModeButton");
    ui->back2ModeButton->setStyleSheet("#back2ModeButton{border-image:url(:/wifiVehicleImages/image/back2Mode.png);}");

    //ctrlMode        = new ctrlModeDialog;     // WARNING: The program cannot be running, still need to figure it out
    setup           = new SetupDialog(this);
    grap            = new grapDialog(this);
    about           = new AboutDialog(this);
    carControl      = new control;
    isConnected     = false;
    isConnecting    = false;
    openvideo       = false;

    /* if client connected the server, the socketSucceed will be invoked */
    connect(carControl->tcpSocket, SIGNAL(connected()), this, SLOT(socketSucceed()));

    /* if client failed to connect the server, the socketFailed will be invoked */
    connect(carControl->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketFailed()));

    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->frontButton->setEnabled(false);
    ui->backButton->setEnabled(false);
    ui->leftButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->startCamButton->setEnabled(false);
    ui->stopCamButton->setEnabled(false);
    ui->capFrameButton->setEnabled(false);
    ui->readTempButton->setEnabled(false);
    ui->pwmMotorSlider->setEnabled(false);
    ui->camUpButton->setEnabled(false);
    ui->camDownButton->setEnabled(false);
    ui->camLeftButton->setEnabled(false);
    ui->camRightButton->setEnabled(false);
    ui->back2ModeButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    carControl->tcpSocket->abort();
    delete ui;
    delete carControl->tcpSocket;
    delete carControl;
    delete setup;
    delete about;
    delete grap;
}

void MainWindow::newConnect()
{
    carControl->tcpSocket->abort(); //取消已有的连接
    ui->netState->setText(tr("Connecting..."));
    //qDebug() << "ipAddr = " << setup->ipAddr;
    //qDebug("controlPort = %d\n", setup->controlPort.toInt());

    carControl->tcpSocket->connectToHost(setup->ipAddr, setup->controlPort.toInt());
    //carControl->tcpSocket->connectToHost("192.168.10.1", 8888);
}

void MainWindow::disconnect()
{
    carControl->tcpSocket->disconnectFromHost();
    ui->videoWidget->videotcpSocket->disconnect();
    ui->videoWidget->image.load(":/wifiVehicleImages/image/video_background.png");
}

void MainWindow::socketSucceed()
{
    ui->netState->setText(tr("Connected"));
    isConnected = true;

    ui->frontButton->setEnabled(true);
    ui->backButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->startCamButton->setEnabled(true);
    ui->stopCamButton->setEnabled(true);
    ui->capFrameButton->setEnabled(true);
    ui->readTempButton->setEnabled(true);
    ui->pwmMotorSlider->setEnabled(true);
    ui->back2ModeButton->setEnabled(false);
}

void MainWindow::socketFailed()
{
    ui->netState->setText(tr("Connection failure"));
    ui->connectButton->setEnabled(true);
    ui->actionConnect->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->actionDisconnect->setEnabled(false);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
#if 0
    /*  Since we disabled the control buttons at the beginning,
     *  so we dont need to determine whether the client is connected the server or not
     */
    if (!isConnected) {
        QMessageBox::warning(this, tr("Key press warning"),
                             tr("Please connect to the server before pressing the direction keys"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
#endif
        ui->controlState->setText(tr("Keyboard"));
        /* Wifi vehicle movements */
        if ( (keyEvent->key() == Qt::Key_W) && (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Foreward"));
            carControl->vehicleMoveForward();
            ui->frontButton->setEnabled(false);
            keyEvent->ignore();
        }

        if ( (keyEvent->key() == Qt::Key_S) && (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Backward"));
            carControl->vehicleMoveBackward();
            ui->backButton->setEnabled(false);
            keyEvent->ignore();
        }

        if ( (keyEvent->key() == Qt::Key_A) && (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Left turn"));
            carControl->vehicleTurnLeft();
            ui->leftButton->setEnabled(false);
            keyEvent->ignore();
        }

        if ( (keyEvent->key() == Qt::Key_D) && (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Right turn"));
            carControl->vehicleTurnRight();
            ui->rightButton->setEnabled(false);
            keyEvent->ignore();
        }

        if (openvideo) {
            /* Camera control related */
            if ( (keyEvent->key() == Qt::Key_I) && (keyEvent->isAutoRepeat() == false) ) {
                ui->camState->setText(tr("Cam Up"));
                carControl->camServoMoveUp();
                ui->camUpButton->setEnabled(false);
                keyEvent->ignore();
            }

            if ( (keyEvent->key() == Qt::Key_K) && (keyEvent->isAutoRepeat() == false) ) {
                ui->camState->setText(tr("Cam Down"));
                carControl->camServoMoveDown();
                ui->camDownButton->setEnabled(false);
                keyEvent->ignore();
            }

            if ( (keyEvent->key() == Qt::Key_J) && (keyEvent->isAutoRepeat() == false) ) {
                ui->camState->setText(tr("Cam Left"));
                carControl->camServoMoveLeft();
                ui->camLeftButton->setEnabled(false);
                keyEvent->ignore();
            }

            if ( (keyEvent->key() == Qt::Key_L) && (keyEvent->isAutoRepeat() == false) ) {
                ui->camState->setText(tr("Cam Right"));
                carControl->camServoMoveRight();
                ui->camRightButton->setEnabled(false);
                keyEvent->ignore();
            }
        }
    //}
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (isConnected) {
        ui->controlState->setText(tr("Unknown"));
        /* Wifi vehicle control keys release */
        if ( (keyEvent->key() == Qt::Key_W || keyEvent->key() == Qt::Key_S ||
              keyEvent->key() == Qt::Key_A || keyEvent->key() == Qt::Key_D) &&
             (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Stopped"));
            carControl->vehicleStop();
            ui->frontButton->setEnabled(true);
            ui->backButton->setEnabled(true);
            ui->leftButton->setEnabled(true);
            ui->rightButton->setEnabled(true);
        }

        if (openvideo) {
            /* Camera control keys release */
            if ( (keyEvent->key() == Qt::Key_I || keyEvent->key() == Qt::Key_K ||
                  keyEvent->key() == Qt::Key_J || keyEvent->key() == Qt::Key_L) &&
                 (keyEvent->isAutoRepeat() == false) ) {
                ui->camState->setText(tr("Unknown"));
                ui->camUpButton->setEnabled(true);
                ui->camDownButton->setEnabled(true);
                ui->camLeftButton->setEnabled(true);
                ui->camRightButton->setEnabled(true);
            }
        }
    }
}

void MainWindow::on_frontButton_pressed()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Front button warning"),
                             tr("Please connect to the server before pressing the front button"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->moveState->setText(tr("Foreward"));
        carControl->vehicleMoveForward();
    }
}

void MainWindow::on_frontButton_released()
{
    if (isConnected) {
        ui->controlState->setText(tr("Unknown"));
        ui->moveState->setText(tr("Stopped"));
        carControl->vehicleStop();
    }
}

void MainWindow::on_leftButton_pressed()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Left button warning"),
                             tr("Please connect to the server before pressing the left button"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->moveState->setText(tr("Left turn"));
        carControl->vehicleTurnLeft();
    }
}

void MainWindow::on_leftButton_released()
{
    if (isConnected) {
        ui->controlState->setText(tr("Unknown"));
        ui->moveState->setText(tr("Stopped"));
        carControl->vehicleStop();
    }
}

void MainWindow::on_rightButton_pressed()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Right button warning"),
                             tr("Please connect to the server before pressing the right button"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->moveState->setText(tr("Right turn"));
        carControl->vehicleTurnRight();
    }
}

void MainWindow::on_rightButton_released()
{
    if (isConnected) {
        ui->controlState->setText(tr("Unknown"));
        ui->moveState->setText(tr("Stopped"));
        carControl->vehicleStop();
    }
}

void MainWindow::on_backButton_pressed()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Back button warning"),
                             tr("Please connect to the server before pressing the back button"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->moveState->setText(tr("Backward"));
        carControl->vehicleMoveBackward();
    }
}

void MainWindow::on_backButton_released()
{
    if (isConnected) {
        ui->controlState->setText(tr("Unknown"));
        ui->moveState->setText(tr("Stopped"));
        carControl->vehicleStop();
    }
}

void MainWindow::on_connectButton_clicked()
{
    if (!isConnected) {
        newConnect();
        isConnecting = 1;
        ui->connectButton->setEnabled(false);
        ui->actionConnect->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
        ui->actionDisconnect->setEnabled(true);
    }
}

void MainWindow::on_disconnectButton_clicked()
{
    if (isConnected || isConnecting) {
        carControl->tcpSocket->abort();
        isConnected = false;
        ui->netState->setText(tr("Disconnected"));
        ui->connectButton->setEnabled(true);
        ui->actionConnect->setEnabled(true);
        ui->disconnectButton->setEnabled(false);
        ui->actionDisconnect->setEnabled(false);

        ui->frontButton->setEnabled(false);
        ui->backButton->setEnabled(false);
        ui->leftButton->setEnabled(false);
        ui->rightButton->setEnabled(false);
        ui->startCamButton->setEnabled(false);
        ui->stopCamButton->setEnabled(false);
        ui->capFrameButton->setEnabled(false);
        ui->readTempButton->setEnabled(false);
        ui->pwmMotorSlider->setEnabled(false);
        ui->camUpButton->setEnabled(false);
        ui->camDownButton->setEnabled(false);
        ui->camLeftButton->setEnabled(false);
        ui->camRightButton->setEnabled(false);
        ui->back2ModeButton->setEnabled(true);

        /* Stop the camera */
        openvideo = false;
        ui->videoWidget->videotcpSocket->disconnect();
        ui->videoWidget->image.load(":/wifiVehicleImages/image/video_background.png");
        update();
    }
}

void MainWindow::on_startCamButton_clicked()
{
    /* Do not open the camera if client is connecting or not connected to the server */
    if (!isConnected) {
        QMessageBox::warning(this, tr("Start camera warning"),
                             tr("Please connect to the server before starting the camera"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        if (!openvideo) {
            openvideo = true;
            ui->videoWidget->ipAddr     = setup->ipAddr;
            ui->videoWidget->videoPort  = setup->videoPort;
            ui->videoWidget->newConnect();
            ui->camUpButton->setEnabled(true);
            ui->camDownButton->setEnabled(true);
            ui->camLeftButton->setEnabled(true);
            ui->camRightButton->setEnabled(true);
            //update();
        }else {
            QMessageBox::warning(this, tr("Camera warning"),
                                 tr("Camera is already running!"),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        }
    }
}

void MainWindow::on_stopCamButton_clicked()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Stop camera warning"),
                             tr("Please start the camera first!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        openvideo = false;
        ui->videoWidget->videotcpSocket->disconnect();
        ui->videoWidget->image.load(":/wifiVehicleImages/image/video_background.png");
        update();
        ui->camUpButton->setEnabled(false);
        ui->camDownButton->setEnabled(false);
        ui->camLeftButton->setEnabled(false);
        ui->camRightButton->setEnabled(false);
    }
}

void MainWindow::on_capFrameButton_clicked()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera capture warning"),
                             tr("Please start the camera first!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        savePicture();
    }
}

void MainWindow::on_readTempButton_clicked()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Read temperature warning"),
                             tr("Please connect to the server before reading the temperature"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        float temp;
        temp = carControl->readTemperature();
        ui->tempLcdNumber->display(temp);
    }
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::on_actionIP_Setup_IP_triggered()
{
    setup->exec();              // Invoking exec() to enter in Model Dialog
    //setup->show();            // Invoking show() to enter in Modeless Dialog
}

void MainWindow::on_pwmMotorSlider_valueChanged(int value)
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Change motor speed warning"),
                             tr("Please connect to the server before changing the motor speed"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        //qDebug("value = %d\n", value);
        carControl->pwmMotorChange(value);
        ui->pwmMotorLcdNumber->display(value);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    about->exec();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionConnect_triggered()
{
    if (!isConnected) {
        newConnect();
        isConnecting = 1;
        ui->connectButton->setEnabled(false);
        ui->actionConnect->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
        ui->actionDisconnect->setEnabled(true);
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if (isConnected || isConnecting) {
        carControl->tcpSocket->abort();
        isConnected = false;
        ui->netState->setText(tr("Disconnected"));
        ui->connectButton->setEnabled(true);
        ui->actionConnect->setEnabled(true);
        ui->disconnectButton->setEnabled(false);
        ui->actionDisconnect->setEnabled(false);

        ui->frontButton->setEnabled(false);
        ui->backButton->setEnabled(false);
        ui->leftButton->setEnabled(false);
        ui->rightButton->setEnabled(false);
        ui->startCamButton->setEnabled(false);
        ui->stopCamButton->setEnabled(false);
        ui->capFrameButton->setEnabled(false);
        ui->readTempButton->setEnabled(false);
        ui->pwmMotorSlider->setEnabled(false);
        ui->camUpButton->setEnabled(false);
        ui->camDownButton->setEnabled(false);
        ui->camLeftButton->setEnabled(false);
        ui->camRightButton->setEnabled(false);
        ui->back2ModeButton->setEnabled(true);

        /* Stop the camera */
        openvideo = false;
        ui->videoWidget->videotcpSocket->disconnect();
        ui->videoWidget->image.load(":/wifiVehicleImages/image/video_background.png");
        update();
    }
}

void MainWindow::on_actionPicture_directory_setup_triggered()
{
    grap->exec();
}

void MainWindow::savePicture()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString(tr("/") + "yyMMddhhmmss.jpg");

    if (grap->pictureDir.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(NULL, tr("Save as..."), str);   // get the file name
        if (!fileName.isEmpty()) {
            ui->videoWidget->image.save(fileName);
            QMessageBox::information(this, tr("Picture saved"),
                                 tr("The snapshot is saved!"),
                                 QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        }
    }else {
        QString fileName = grap->pictureDir + str;
        if (!fileName.isEmpty()) {
            QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Snapshot saved?",
                                                                   "Do you want to save the snapshot or not ?",
                                                                   QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
            if (rb == QMessageBox::Ok) {
                ui->videoWidget->image.save(fileName);

                QMessageBox::information(this, tr("Snapshot saved"),
                                            "The snapshot is saved to (" + grap->pictureDir + ")",
                                            QMessageBox::Ok, QMessageBox::Ok);
            }
        }
    }
}

void MainWindow::on_camUpButton_pressed()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please open the camera before pressing the cameraServo up button"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->camState->setText(tr("Cam Up"));
        carControl->camServoMoveUp();
    }
}

void MainWindow::on_camUpButton_released()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please start the camera first!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Unknown"));
        ui->camState->setText(tr("Unknown"));
        carControl->camServoStop();
    }
}

void MainWindow::on_camDownButton_pressed()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please open the camera before pressing the cameraServo down button"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->camState->setText(tr("Cam Down"));
        carControl->camServoMoveDown();
    }
}

void MainWindow::on_camDownButton_released()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please start the camera first!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Unknown"));
        ui->camState->setText(tr("Unknown"));
        carControl->camServoStop();
    }
}

void MainWindow::on_camLeftButton_pressed()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please open the camera before pressing the cameraServo left button"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->camState->setText(tr("Cam Left"));
        carControl->camServoMoveLeft();
    }
}

void MainWindow::on_camLeftButton_released()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please start the camera first!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Unknown"));
        ui->camState->setText(tr("Unknown"));
        carControl->camServoStop();
    }
}

void MainWindow::on_camRightButton_pressed()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please open the camera before pressing the cameraServo right button"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Mouse"));
        ui->camState->setText(tr("Cam Right"));
        carControl->camServoMoveRight();
    }
}

void MainWindow::on_camRightButton_released()
{
    if (!openvideo) {
        QMessageBox::warning(this, tr("Camera servo warning"),
                             tr("Please start the camera first!"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Unknown"));
        ui->camState->setText(tr("Unknown"));
        carControl->camServoStop();
    }
}

void MainWindow::on_back2ModeButton_clicked()
{
    //ctrlMode->show();
    //this->hide();
}
