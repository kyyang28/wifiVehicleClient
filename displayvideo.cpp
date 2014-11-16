#include "displayvideo.h"
#include <QMessageBox>

displayVideo::displayVideo(QWidget *parent) :
    QWidget(parent)
{
    image = QImage(640,480,QImage::Format_RGB32);       //初始化画布的大小，使用 32位颜色
    backColor = qRgb(255,255,255);                      //画布初始化背景色使用白色
    image.fill(backColor);
    image.load(":/wifiVehicleImages/image/video_background.png");         //加载一张背景图
    update();                                           //刷新画面
    videotcpSocket = new QTcpSocket(this);

    ipAddr      = "192.168.10.1";
    videoPort   = "8080";

    //connect(videotcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    //connect(videotcpSocket, SIGNAL(connected()), this, SLOT(go()));
}

void displayVideo::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0,0,image);
    painter.end();
}

void displayVideo::newConnect()
{
    videotcpSocket->abort();                                    //取消已有的连接
    videotcpSocket->connectToHost(ipAddr, videoPort.toInt());   //连接到主机, 这里从界面获取主机地址和端口号

    qDebug() << "ipAddr = " << ipAddr;
    qDebug("videoPort = %d", videoPort.toInt());

    //连接失败
    connect(videotcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

    //连接成功
    connect(videotcpSocket, SIGNAL(connected()), this, SLOT(go()));
}

void displayVideo::displayError(QAbstractSocket::SocketError)
{
    qDebug() << videotcpSocket->errorString();          //输出错误信息
    QMessageBox::critical(this, tr("Camera connection failure"),
                          tr("Please start the mjpg-streamer server first and\n STOP THE CAMERA!"),
                          QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
}

//连接成功后, 准备接收数据
void displayVideo::go()
{
    videotcpSocket->write("GET /?action=stream\n\n");
    connect(videotcpSocket, SIGNAL(readyRead()), this, SLOT(tcpReadyRead()));
}

//接收到数据时的处理
void displayVideo::tcpReadyRead()
{
    datasize = videotcpSocket->bytesAvailable();

    //开始接收新的图像数据
    if (length == 0) {
        tmpbytearray = videotcpSocket->readLine();

        if (tmpbytearray.contains("Content-Type: image/jpeg")) {
            tmpbytearray = videotcpSocket->readLine();
            if (tmpbytearray.contains("Content-Length:")) {
                length = getFrameSize(tmpbytearray);

                //判断可接收数据大小的是否等于一帧数据
                if (datasize >= length) {
                    photodata = videotcpSocket->read(length);
                    image.loadFromData(photodata,"jpeg");
                    update();
                    photodata.clear();
                    length = 0;
                    tmp = 0;
                    return;
                }else {         //接收的数据还不够一帧图像
                    //tmpbytearray=videotcpSocket->readLine();
                    tmpbytearray = videotcpSocket->readLine();
                    photodata = videotcpSocket->readAll();
                    tmp = photodata.size();
                    return;
                }
            }
        }
    }

    //接收剩余的数据
    if (length != 0) {
        tmp = tmp + datasize; //已经接收的数据大小

        //接收剩余的数据
        if (tmp < length) {
            tmpbytearray = videotcpSocket->readAll();
            photodata.append(tmpbytearray);
            return;
        }else {     //接收完完整的图像
            tmpbytearray = videotcpSocket->read(length-photodata.size());
            photodata.append(tmpbytearray);
            image.loadFromData(photodata,"jpeg");
            update();
            photodata.clear();
            length = 0;
            tmp = 0;
            return;
        }
    }
}

//获取图片大小
int displayVideo::getFrameSize(QString str)
{
    QString pattern("(Content-Length): (.....)");
    QRegExp rx(pattern);
    int pos = str.indexOf(rx);
    if ( pos >= 0 )
        return rx.cap(2).toInt(); //把提取的字符串转为整型
    else
        return pos;
}
