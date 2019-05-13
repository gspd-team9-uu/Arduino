// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
  Name:       test_bluetooth.ino
  Created:  5/9/2019 2:50:13 PM
  Author:     DESKTOP-KEFN9DR\lione
*/
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_SI1145.h"
#include "DHT.h"

SoftwareSerial BTSerial(19, 18);   //bluetooth module Tx:Digital 2 Rx:Digital 3
String message; //string that stores the incoming message


Adafruit_SI1145 uv = Adafruit_SI1145();
DHT dht(7, DHT22);

// The setup() function runs once each time the micro-controller starts
void setup()
{
  BTSerial.begin(9600); //set baud rate
  dht.begin();
  uv.begin();
}

// Add the main program code into the continuous loop() function
void loop()
{

  while (BTSerial.available())
  {//while there is data available on the serial monitor
    message += char(BTSerial.read());//store string from serial command
  }
  if (!BTSerial.available())
  {
    if (message != "")
    {//if data is available
      BTSerial.println(message); //show the data
      message = ""; //clear the data
    } else
    {
      String temp = String(dht.readTemperature());
      String uvSring = String(uv.readUV());
      BTSerial.println(temp); //show the data
      delay(500); //delay
      BTSerial.println(uvSring); //show the data
    }
  }
  delay(2000); //delay
}
