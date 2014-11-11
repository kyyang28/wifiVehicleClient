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
    setWindowTitle(tr("Wifi surveillant vehicle (智能监控无人车)"));
    setObjectName("MainWindow");
    setStyleSheet("#MainWindow{border-image:url(:/wifiVehicleImages/image/background.png);}");

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
}

void MainWindow::socketFailed()
{
    ui->netState->setText(tr("Connection failure"));
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Key press warning"),
                             tr("Please connect to the server before pressing the direction keys"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        ui->controlState->setText(tr("Keyboard"));
        if ( (keyEvent->key() == Qt::Key_W) && (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Forward"));
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
            ui->moveState->setText(tr("Turn left"));
            carControl->vehicleTurnLeft();
            ui->leftButton->setEnabled(false);
            keyEvent->ignore();
        }

        if ( (keyEvent->key() == Qt::Key_D) && (keyEvent->isAutoRepeat() == false) ) {
            ui->moveState->setText(tr("Turn right"));
            carControl->vehicleTurnRight();
            ui->rightButton->setEnabled(false);
            keyEvent->ignore();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (isConnected) {
        ui->controlState->setText(tr("Unknown"));
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
        ui->moveState->setText(tr("Forward"));
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
        ui->moveState->setText(tr("Turn left"));
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
        ui->moveState->setText(tr("Turn right"));
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
        ui->buzzerButton->setText(tr("Buzzer"));

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

void MainWindow::on_buzzerButton_clicked()
{
    if (!isConnected) {
        QMessageBox::warning(this, tr("Buzzer warning"),
                             tr("Please connect to the server before operating on the buzzer"),
                             QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }else {
        if (!carControl->isBuzzerOn) {
            carControl->buzzerOn();
            ui->buzzerButton->setText(tr("Buzzer ON"));
        }else {
            carControl->buzzerOff();
            ui->buzzerButton->setText(tr("Buzzer OFF"));
        }
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
        ui->buzzerButton->setText(tr("Buzzer"));

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
