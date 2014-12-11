#ifndef CONTROL_H
#define CONTROL_H

#include <QtNetwork>

/* request type */
#define REQ_CMD_TYPE_DIRECTION                  0
#define REQ_CMD_TYPE_BUZZER                     1
#define REQ_CMD_TYPE_SPEED                      2
#define REQ_CMD_TYPE_TEMPERATURE                3
#define REQ_CMD_TYPE_CAMSERVO_OPERATION         4
#define REQ_CMD_TYPE_LEDS_ONOFF_OPERATION       5
#define REQ_CMD_TYPE_LEDS_PWM_OPERATION         6

/* Vehicle movements related */
#define WIFI_VEHICLE_MOVE_FORWARD               0
#define WIFI_VEHICLE_MOVE_BACKWARD              1
/* DONOT use number '2', since ioctl is taken this number. If you have to use 2, then use magic number */
/* We don't use ioctl's magic number here, because our app is Windows Qt, it cannot use <sys/ioctl> header file */
#define WIFI_VEHICLE_MOVE_LEFT                  3
#define WIFI_VEHICLE_MOVE_RIGHT                 4
#define WIFI_VEHICLE_STOP                       5

#if 0
/* Buzzer related */
#define WIFI_VEHICLE_BUZZER_ON                  6
#define WIFI_VEHICLE_BUZZER_OFF                 7
#endif

/* Leds related */
#define WIFI_VEHICLE_LEDS_ON                    1
#define WIFI_VEHICLE_LEDS_OFF                   0

/* Camera servo related */
#define MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE	1
#define MARS_PWM_IOCTL_STOP_OPSCODE		0

#define MARS_PWM_CAMSERVO_TYPE_HORIZONTAL       0
#define MARS_PWM_CAMSERVO_TYPE_VERTICAL         1

#define MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_70K         700000            // 180бу
#define MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_100K        1000000           // 135бу
#define MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_140K        1400000           // 90бу
#define MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_180K        1800000           // 45бу
#define MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_219K        2190000           // 0бу

#define MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_120K          1200000            // 180бу
#define MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_146K          1460000           // 135бу
#define MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_178K          1780000           // 90бу
#define MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_234K          2340000           // 45бу
#define MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_269K          2690000           // 0бу

struct reqMsg {
    unsigned char type;
    unsigned char dir;
    unsigned int  camServoType;
    unsigned int  camServoOpsCode;
    unsigned int  camServoHorizontalDutyNS;
    unsigned int  camServoVerticalDutyNS;
    unsigned char speed;            /* 0 ~ 100 */
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
    void ledsOn();
    void ledsOff();
    //void buzzerOn();
    //void buzzerOff();
    void pwmMotorChange(int value);
    void pwmLedsChange(int value);
    float readTemperature();
    void camServoMoveUp();
    void camServoMoveDown();
    void camServoMoveLeft();
    void camServoMoveRight();
    void camServoStop();
    QTcpSocket *tcpSocket;
    int isLedsOn;
    //int isBuzzerOn;

private:
    struct reqMsg request;
    //int controlData;
};

#endif // CONTROL_H
