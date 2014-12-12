#include "control.h"
#include <QMessageBox>
#include <QDebug>

control::control()
{
    tcpSocket = new QTcpSocket;
    memset(&request, 0, sizeof(struct reqMsg));
    request.camServoHorizontalDutyNS    = MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_140K;
    request.camServoVerticalDutyNS      = MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_269K - 40000;
    isLedsOn = 0;
    //qDebug("request.camServoDutyNS = %u\n", request.camServoDutyNS);
    //isBuzzerOn = 0;
}

control::~control()
{
    //delete tcpSocket;    // DO NOT delete the tcpSocket in the control destructor, error comes up when exit the program
}

void control::vehicleMoveForward()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_FORWARD;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleMoveBackward()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_BACKWARD;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleTurnLeft()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_LEFT;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleTurnRight()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_RIGHT;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleStop()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_STOP;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

#if 0
void control::buzzerOn()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_BUZZER;
    request.dir     = WIFI_VEHICLE_BUZZER_ON;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    isBuzzerOn = 1;
}

void control::buzzerOff()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_BUZZER;
    request.dir     = WIFI_VEHICLE_BUZZER_OFF;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    isBuzzerOn = 0;
}
#endif

void control::ledsOn()
{
    //qDebug("ledsOn\n");
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_LEDS_ONOFF_OPERATION;
    request.dir     = WIFI_VEHICLE_LEDS_ON;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    isLedsOn = 1;
}

void control::ledsOff()
{
    //qDebug("ledsOff\n");
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_LEDS_ONOFF_OPERATION;
    request.dir     = WIFI_VEHICLE_LEDS_OFF;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    isLedsOn = 0;
}

void control::pwmMotorChange(int value)
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_SPEED;
    request.motorSpeed      = value;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::pwmLedsChange(int value)
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type                        = REQ_CMD_TYPE_LEDS_PWM_OPERATION;
    request.nightVisionBrightness       = value;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

float control::readTemperature()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_TEMPERATURE;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    tcpSocket->read((char *)&request, sizeof(struct reqMsg));
    return request.temp;
}

void control::camServoMoveUp()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE;
    request.camServoType    = MARS_PWM_CAMSERVO_TYPE_VERTICAL;

    if (request.camServoVerticalDutyNS <= MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_120K) {
        QMessageBox::warning(NULL, "Camera Servo Warning",
                             "Duty time reached the upper maximum capacity!",
                             QMessageBox::Ok, QMessageBox::Ok);
    }

    request.camServoVerticalDutyNS -= 40000;
    if (request.camServoVerticalDutyNS < MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_120K)
        request.camServoVerticalDutyNS = MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_120K;

    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoMoveDown()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE;
    request.camServoType    = MARS_PWM_CAMSERVO_TYPE_VERTICAL;

    if (request.camServoVerticalDutyNS >= MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_269K) {
        QMessageBox::warning(NULL, "Camera Servo Warning",
                             "Duty time reached the lower minimum capacity!",
                             QMessageBox::Ok, QMessageBox::Ok);
    }

    request.camServoVerticalDutyNS += 40000;
    if (request.camServoVerticalDutyNS > MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_269K)
        request.camServoVerticalDutyNS = MARS_PWM_CAMSERVO_VERTICAL_DUTY_TIME_269K;

    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoMoveLeft()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE;
    request.camServoType    = MARS_PWM_CAMSERVO_TYPE_HORIZONTAL;

    if (request.camServoHorizontalDutyNS >= MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_219K) {
        QMessageBox::warning(NULL, "Camera Servo Warning",
                             "Duty time reached the maximum capacity!",
                             QMessageBox::Ok, QMessageBox::Ok);
    }

    request.camServoHorizontalDutyNS += 40000;
    if (request.camServoHorizontalDutyNS > MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_219K)
        request.camServoHorizontalDutyNS = MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_219K;

    //qDebug("request.camServoDutyNS = %u\n", request.camServoDutyNS);

    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoMoveRight()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE;
    request.camServoType    = MARS_PWM_CAMSERVO_TYPE_HORIZONTAL;

    if (request.camServoHorizontalDutyNS <= MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_70K) {
        QMessageBox::warning(NULL, "Camera Servo Warning",
                             "Duty time reached the minimum capacity!",
                             QMessageBox::Ok, QMessageBox::Ok);
    }

    request.camServoHorizontalDutyNS -= 40000;
    if (request.camServoHorizontalDutyNS < MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_70K)
        request.camServoHorizontalDutyNS = MARS_PWM_CAMSERVO_HORIZONTAL_DUTY_TIME_70K;

    //qDebug("request.camServoDutyNS = %u\n", request.camServoDutyNS);

    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoStop()
{
    //memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_STOP_OPSCODE;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}
