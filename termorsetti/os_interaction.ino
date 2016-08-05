#include "os_interaction.h"
#include <Bridge.h>
#include <Process.h>

void logReading(float rValue, int rType){
  updateLeds(1,1,1);
  #ifdef DEBUG
    Serial.println("lR");
  #endif
  String updMessage=shellEntryWriter+" "
    +String(rValue)+" "
    +fileDestinations[rType]+" &";
  #ifdef DEBUG
    Serial.println(" exec <"+updMessage+">");
  #endif
  Process p,q;
  p.runShellCommand(updMessage);
  return;
}

void waitForLinux(){
  #ifdef DEBUG
  Serial.println("start wFL");
  #endif
  Serial1.begin(115200); // get ready to hear from the console
  updateLeds(1,0,0);
  delay(1000);
  do {
    while (Serial1.available() > 0) {
      Serial1.read();
    }
    updateLeds(1,1,0);
    delay(500);
    updateLeds(1,0,0);
    delay(500);
  } while (Serial1.available()>0);
  // part 2: bridge
  Bridge.begin();
  #ifdef DEBUG
  Serial.println("end wFL");
  #endif
  updateLeds(0,0,0);
}

