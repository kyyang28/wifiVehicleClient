#include "control.h"
#include <QMessageBox>

control::control()
{
    tcpSocket = new QTcpSocket;
    request.camServoDutyNS = MARS_PWM_CAMSERVO_DUTY_TIME_140K;
    //isBuzzerOn = 0;
}

control::~control()
{
    //delete tcpSocket;    // DO NOT delete the tcpSocket in the control destructor, error comes up when exit the program
}

void control::vehicleMoveForward()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_FORWARD;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleMoveBackward()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_BACKWARD;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleTurnLeft()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_LEFT;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleTurnRight()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_MOVE_RIGHT;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::vehicleStop()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_DIRECTION;
    request.dir     = WIFI_VEHICLE_STOP;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

#if 0
void control::buzzerOn()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_BUZZER;
    request.dir     = WIFI_VEHICLE_BUZZER_ON;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    isBuzzerOn = 1;
}

void control::buzzerOff()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_BUZZER;
    request.dir     = WIFI_VEHICLE_BUZZER_OFF;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    isBuzzerOn = 0;
}
#endif

void control::pwmMotorChange(int value)
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_SPEED;
    request.speed   = value;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

float control::readTemperature()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type    = REQ_CMD_TYPE_TEMPERATURE;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
    tcpSocket->read((char *)&request, sizeof(struct reqMsg));
    return request.temp;
}

void control::camServoMoveUp()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoMoveDown()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoMoveLeft()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE;

    if (request.camServoDutyNS >= MARS_PWM_CAMSERVO_DUTY_TIME_219K) {
        QMessageBox::warning(NULL, "Camera Servo Warning",
                             "Duty time reached the maximum capacity!",
                             QMessageBox::Ok, QMessageBox::Ok);
    }

    request.camServoDutyNS += 10000;
    if (request.camServoDutyNS > MARS_PWM_CAMSERVO_DUTY_TIME_219K)
        request.camServoDutyNS = MARS_PWM_CAMSERVO_DUTY_TIME_219K;

    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoMoveRight()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_SET_DUTYRATIO_OPSCODE;

    if (request.camServoDutyNS <= MARS_PWM_CAMSERVO_DUTY_TIME_70K) {
        QMessageBox::warning(NULL, "Camera Servo Warning",
                             "Duty time reached the minimum capacity!",
                             QMessageBox::Ok, QMessageBox::Ok);
    }

    request.camServoDutyNS -= 10000;
    if (request.camServoDutyNS < MARS_PWM_CAMSERVO_DUTY_TIME_70K)
        request.camServoDutyNS = MARS_PWM_CAMSERVO_DUTY_TIME_70K;

    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}

void control::camServoStop()
{
    memset(&request, 0, sizeof(struct reqMsg));
    request.type            = REQ_CMD_TYPE_CAMSERVO_OPERATION;
    request.camServoOpsCode = MARS_PWM_IOCTL_STOP_OPSCODE;
    tcpSocket->write((const char *)&request, sizeof(struct reqMsg));
}
