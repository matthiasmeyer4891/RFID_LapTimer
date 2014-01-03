#include <QueueArray.h>

#include <Arduino.h>
#include "car.h"


QueueArray <unsigned long> lapTimes;
unsigned long _lastLapTime = 0;
String _driverName;
String _driverTag;
byte _ID;

Car::Car(){
}

void Car::setID(int id){
  _ID = char(id);
}

void Car::setDriverName(String name){
  _driverName = name;
}

String Car::getDriverName(){
  return _driverName;
}

void Car::setTag(String tag){
  _driverTag = tag;
}

String Car::getTag(){
  return _driverTag;
}

void Car::setNewLap(unsigned long timeValue){
  lapTimes.push(timeValue);
  _lastLapTime = timeValue;
}

unsigned long Car::getLastFinishTime(){
  return _lastLapTime;

}

unsigned long Car::dropTimeToDisplay(){
  return lapTimes.pop();
}

