#include <DHT.h>

#define DHTPIN 11
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#include "temperatures.h"
#include "os_interaction.h"

//#define DEBUG

#define INERT_TEMP_DIFFERENCE (1.2)

const int ledPins[3]={4,3,2}; // red, yellow, green

void updateLeds(int r, int y, int g){
  digitalWrite(ledPins[0],r);
  digitalWrite(ledPins[1],y);
  digitalWrite(ledPins[2],g);
  return;
}

void setOneLed(int col){
  switch (col){
    case 0:
      updateLeds(1,0,0);
      break;
    case 1:
      updateLeds(0,1,0);
      break;
    case 2:
      updateLeds(0,0,1);
      break;
  }
  return;
}

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  // put your setup code here, to run once:
  for(int i=0;i<3;i++){
    pinMode(ledPins[i],OUTPUT);
  }
  // initialise the humidity-temperature digital sensor
  dht.begin();
  // initialise os interaction
  waitForLinux();
  // initialise reading containers
  initReadings(millis());
  // display a begin sequence
  makeAShow();
}

void loop() {
  unsigned long int epoch=millis();
  handleReadings(epoch);
  // decide what light to turn on
  float tempDiff=(readings[1].value-readings[0].value); // internal - external
  if (abs(tempDiff)<INERT_TEMP_DIFFERENCE){
    setOneLed(1);
  }else{
    if (tempDiff>0){ // internal is higher
      setOneLed(2);
    }else{ // internal is lower
      setOneLed(0);
    }
  }
  delay(100);
}

void makeAShow(){
  for(int cnt=0;cnt<24;cnt++){
    updateLeds(!!(cnt&4),!!(cnt&2),!!(cnt&1));
    delay(500);
  }
  updateLeds(0,0,0);
}

