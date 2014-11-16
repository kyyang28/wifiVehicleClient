#include "displayvideo.h"
#include <QMessageBox>

displayVideo::displayVideo(QWidget *parent) :
    QWidget(parent)
{
    image = QImage(640,480,QImage::Format_RGB32);       //��ʼ�������Ĵ�С��ʹ�� 32λ��ɫ
    backColor = qRgb(255,255,255);                      //������ʼ������ɫʹ�ð�ɫ
    image.fill(backColor);
    image.load(":/wifiVehicleImages/image/video_background.png");         //����һ�ű���ͼ
    update();                                           //ˢ�»���
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
    videotcpSocket->abort();                                    //ȡ�����е�����
    videotcpSocket->connectToHost(ipAddr, videoPort.toInt());   //���ӵ�����, ����ӽ����ȡ������ַ�Ͷ˿ں�

    qDebug() << "ipAddr = " << ipAddr;
    qDebug("videoPort = %d", videoPort.toInt());

    //����ʧ��
    connect(videotcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

    //���ӳɹ�
    connect(videotcpSocket, SIGNAL(connected()), this, SLOT(go()));
}

void displayVideo::displayError(QAbstractSocket::SocketError)
{
    qDebug() << videotcpSocket->errorString();          //���������Ϣ
    QMessageBox::critical(this, tr("Camera connection failure"),
                          tr("Please start the mjpg-streamer server first and\n STOP THE CAMERA!"),
                          QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
}

//���ӳɹ���, ׼����������
void displayVideo::go()
{
    videotcpSocket->write("GET /?action=stream\n\n");
    connect(videotcpSocket, SIGNAL(readyRead()), this, SLOT(tcpReadyRead()));
}

//���յ�����ʱ�Ĵ���
void displayVideo::tcpReadyRead()
{
    datasize = videotcpSocket->bytesAvailable();

    //��ʼ�����µ�ͼ������
    if (length == 0) {
        tmpbytearray = videotcpSocket->readLine();

        if (tmpbytearray.contains("Content-Type: image/jpeg")) {
            tmpbytearray = videotcpSocket->readLine();
            if (tmpbytearray.contains("Content-Length:")) {
                length = getFrameSize(tmpbytearray);

                //�жϿɽ������ݴ�С���Ƿ����һ֡����
                if (datasize >= length) {
                    photodata = videotcpSocket->read(length);
                    image.loadFromData(photodata,"jpeg");
                    update();
                    photodata.clear();
                    length = 0;
                    tmp = 0;
                    return;
                }else {         //���յ����ݻ�����һ֡ͼ��
                    //tmpbytearray=videotcpSocket->readLine();
                    tmpbytearray = videotcpSocket->readLine();
                    photodata = videotcpSocket->readAll();
                    tmp = photodata.size();
                    return;
                }
            }
        }
    }

    //����ʣ�������
    if (length != 0) {
        tmp = tmp + datasize; //�Ѿ����յ����ݴ�С

        //����ʣ�������
        if (tmp < length) {
            tmpbytearray = videotcpSocket->readAll();
            photodata.append(tmpbytearray);
            return;
        }else {     //������������ͼ��
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

//��ȡͼƬ��С
int displayVideo::getFrameSize(QString str)
{
    QString pattern("(Content-Length): (.....)");
    QRegExp rx(pattern);
    int pos = str.indexOf(rx);
    if ( pos >= 0 )
        return rx.cap(2).toInt(); //����ȡ���ַ���תΪ����
    else
        return pos;
}
