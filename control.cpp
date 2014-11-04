#include "control.h"

control::control()
{
    tcpSocket = new QTcpSocket;
    isBuzzerOn = 0;
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
