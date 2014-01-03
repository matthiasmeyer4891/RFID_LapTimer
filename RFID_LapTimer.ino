/////////////////////////////////////////////
/*  RFID Lap Timer for R/C Cars            */
/*                                         */
/*  Written by M. Dekker and M.Meyer       */
/*  2014                                   */
/*                                         */
/*                                         */
/*                                         */
/////////////////////////////////////////////


#include <SoftwareSerial.h>
#include "Car.h"
#include <avr/pgmspace.h>
#include <QueueArray.h>



#define DEBUG

const unsigned long initialmillis = 0UL; // it is 0, i tried it out :p
unsigned long time = 0UL;

int value;
int counter = 0;
int lastCounter = 0;
const int txRFID = 3;
const int rxRFID = 4;
byte buttonPin = 6;
byte ledPin = 7;
byte buttonState;
byte lastButtonState = 0;
Car cars[10];

SoftwareSerial RFID(rxRFID, txRFID);


void setup(){
  Serial.begin(9600);
  RFID.begin(9600);
  delay(500);
  initGame();
  setupDisplay();
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(13,OUTPUT);
  time = millis();
  attachInterrupt(0, scanTag, RISING);
  
}

void loop(){

  if(counter > lastCounter){              //Interrupt happened
    //if(Serial.overflow()) Serial.println("Serial overflow !!");
    Serial.println(lastCounter);


    lastCounter++;
  }


  buttonState = digitalRead(buttonPin);


  if(buttonState != lastButtonState){
    Serial.println(buttonState);
    digitalWrite(13,buttonState);
    lastButtonState = buttonState;
  }



  if(RFID.available()){

    value = RFID.read();
    if(value == '0'){
      digitalWrite(ledPin, LOW);
    }

    else if(value == '1'){
      digitalWrite(ledPin,HIGH);
    }

  }

}

void initGame(){
  Serial.println("Anzahl Fahrer ? (1-10): ");
  while(!Serial.available()){
    delay(10);
  }
  
  while(Serial.peek() <'1' || Serial.peek() > '10'){               //Buggy
   Serial.println("Kein gueltiger Wert !");
   Serial.flush();
   Serial.println("Anzahl Fahrer ? (1-10): ");
   delay(1000);
   }
   
   int driverCount = Serial.parseInt();
   
   for(int i=0; i < driverCount;i++){
   cars[i].setID(i);
   String tmp = "Fahrer " + String((i+1)) +(" Name ?: ");
   Serial.print(tmp);
   
   cars[i].setDriverName(askDriverName());
   
   String tmp2 = cars[i].getDriverName();
   tmp2 += ", fahr ueber den Leser!";
   Serial.print(tmp2);
   cars[i].setTag(askDriverTag());
   }
   
   

}

String askDriverName(){
  while(!Serial.available()); // Wait until Input

  String name = "";                                   // Empty String

  while(Serial.peek() > 0) {              //Read bytes and appends to String
    name += char(Serial.read());
    delay(1);
  }

  Serial.println(name);
  return name;

}

String askDriverTag(){
  while(!Serial.available()); // Wait until Input
  String driverTag = "";

  while(Serial.peek() > 0) {              //Read bytes and appends to String u
    driverTag += char(Serial.read());
    delay(1);
  }
  Serial.println(driverTag);
  return driverTag;

}



void scanTag(){            //ISR for processing a scanned RFID-tag -----------  Not yet fully Implemented  /  Tested
  if((millis() - 20) < time) return;      //Debounce
  time = millis();
  //Serial.println("exiting ISR");
  counter++;
}

void setupDisplay(){
}



/* IVARS */













