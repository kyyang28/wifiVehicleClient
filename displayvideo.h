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
    QImage image;                       //QImage ��������������ϻ�ͼ
    QRgb backColor;                     //QRgb ��ɫ���󣬴洢 image �ı���ɫ
    QByteArray tmpbytearray;            //��ʱ��Ž��չ���������
    QByteArray photodata;               //��Ž��յ���һ֡ͼƬ������
    QString ipAddr;
    QString videoPort;
    int datasize;                       //�ɽ��յ��ֽ���
    int tmp;                            //���յ����ֽ���
    int length;                         //һ֡ͼƬ���ֽ���
    void newConnect();                  //���ӷ�����
    int getpicturesize(QString str);    //��ȡͼƬ��С

protected:
    void paintEvent(QPaintEvent *);     //�ػ��¼�

private slots:
    void displayError(QAbstractSocket::SocketError); //��ʾ����
    void tcpReadyRead();                //���յ�����ʱ�Ĵ���
    void go();                          //���ӳɹ���
};

#endif // DISPLAYVIDEO_H
