/**************************************************************************

 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 
 * SDA -  A4
 * SCL - A5
 * WAK - GND
 * 
 ***************************************************************************/

#include "Adafruit_CCS811.h"
#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;
Adafruit_CCS811 ccs;
File dataFile;

void setup() {
  Serial.begin(9600);

  Serial.println("CCS811 test");
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  dataFile = SD.open("datalog.txt", FILE_WRITE);

}

void loop() {
  String dataString = "";
  if(ccs.available()){
    if(!ccs.readData()){
      dataString += String(millis());
      dataString += ", ";
      dataString += String(ccs.geteCO2());
      dataString += ", ";
      dataString += String(ccs.getTVOC());

      Serial.println(dataString);

      if (dataFile) {
        dataFile.println(dataString);
        dataFile.flush();
        //dataFile.close();
      }


      
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(1000);
}
