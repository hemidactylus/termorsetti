#include <DHT.h>

#define DHTPIN 11
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#include "temperatures.h"
#include "os_interaction.h"

//#define DEBUG

const int ledPins[3]={2,3,4}; // green, yellow, red

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
  init_OS();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<3;i++){
    digitalWrite(ledPins[(i+2)%3],LOW);
    digitalWrite(ledPins[i],HIGH);
    delay(662);
  }
  // temp hum/temp
  float digHum = dht.readHumidity();
  float digTem = dht.readTemperature()-2.0;

  float temperature0=read_analog_temperature(0);
  delay(12);
  float temperature1=read_analog_temperature(1);

  logReading(temperature0,0);
  delay(1000);
  logReading(temperature1,1);
  delay(1000);
  logReading(digTem,2);
  delay(1000);
  logReading(digHum,3);
  delay(1000);
}

