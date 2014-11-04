#ifndef DISPLAYVIDEO_H
#define DISPLAYVIDEO_H

#include <QWidget>
#include <QPainter>
#include <QtNetwork>

class displayVideo : public QWidget
{
    Q_OBJECT
public:
    explicit displayVideo(QWidget *parent = 0);
    QTcpSocket *videotcpSocket;
    QImage image;                       //QImage 类对象，用于在其上绘图
    QRgb backColor;                     //QRgb 颜色对象，存储 image 的背景色
    QByteArray tmpbytearray;            //临时存放接收过来的数据
    QByteArray photodata;               //存放接收到的一帧图片的数据
    QString ipAddr;
    QString videoPort;
    int datasize;                       //可接收的字节数
    int tmp;                            //接收到的字节数
    int length;                         //一帧图片的字节数
    void newConnect();                  //连接服务器
    int getpicturesize(QString str);    //获取图片大小

protected:
    void paintEvent(QPaintEvent *);     //重绘事件

private slots:
    void displayError(QAbstractSocket::SocketError); //显示错误
    void tcpReadyRead();                //接收到数据时的处理
    void go();                          //连接成功后
};

#endif // DISPLAYVIDEO_H
