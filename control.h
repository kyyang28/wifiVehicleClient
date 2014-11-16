#ifndef CONTROL_H
#define CONTROL_H

#include <QtNetwork>

/* request type */
#define REQ_CMD_TYPE_DIRECTION              0
#define REQ_CMD_TYPE_BUZZER                 1
#define REQ_CMD_TYPE_SPEED                  2
#define REQ_CMD_TYPE_TEMPERATURE            3

#define WIFI_VEHICLE_MOVE_FORWARD           0
#define WIFI_VEHICLE_MOVE_BACKWARD          1
/* DONOT use number '2', since ioctl is taken this number. If you have to use 2, then use magic number */
/* We don't use ioctl's magic number here, because our app is Windows Qt, it cannot use <sys/ioctl> header file */
#define WIFI_VEHICLE_MOVE_LEFT              3
#define WIFI_VEHICLE_MOVE_RIGHT             4
#define WIFI_VEHICLE_STOP                   5

#define WIFI_VEHICLE_BUZZER_ON              6
#define WIFI_VEHICLE_BUZZER_OFF             7

struct reqMsg {
    unsigned char type;
    unsigned char dir;
    unsigned char speed;        /* 0 ~ 100 */
    float temp;
};

class control
{
public:
    control();
    ~control();

    void vehicleMoveForward();
    void vehicleMoveBackward();
    void vehicleTurnLeft();
    void vehicleTurnRight();
    void vehicleStop();
    void buzzerOn();
    void buzzerOff();
    void pwmMotorChange(int value);
    float readTemperature();
    QTcpSocket *tcpSocket;
    int isBuzzerOn;

private:
    struct reqMsg request;
    //int controlData;
};

#endif // CONTROL_H
