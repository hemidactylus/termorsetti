#include "os_interaction.h"
#include <Bridge.h>
#include <Process.h>

void init_OS(){
  Bridge.begin();
}

void logReading(float rValue, int rType){
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
  q.runShellCommand(shellDateUpdater);
  delay(FILE_WRITE_DELAY);
  return;
}
