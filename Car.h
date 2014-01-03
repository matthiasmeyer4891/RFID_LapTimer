
#ifndef Car_h
#define Car_h


#include <QueueArray.h>
#include <Arduino.h>


class Car
{

public:
  Car();
  void setDriverName(String);
  void setTag(String);
  void setID(int);
  String getDriverName();
  String getTag();
  void setNewLap(unsigned long timeValue);
  unsigned long getLastFinishTime();
  unsigned long dropTimeToDisplay();

private:
  QueueArray <unsigned long> lapTimes;
  byte _ID;
  String _driverName;


};



#endif

