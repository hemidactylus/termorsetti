#include <DHT.h>
#define DHTPIN 11
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#include "temperatures.h"

const int ledPins[3]={2,3,4}; // green, yellow, red

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for(int i=0;i<3;i++){
    pinMode(ledPins[i],OUTPUT);
  }
  // initialise the humidity-temperature digital sensor
  dht.begin();
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
  
  Serial.print((1.0*millis())/1000);
  Serial.print("\t");
  Serial.print(temperature0);
  Serial.print("\t");
  Serial.print(temperature1);
  Serial.print("\t|\t");
  Serial.print(digTem);
  Serial.print("\t");
  Serial.print(digHum);
  Serial.println(" %");
}


