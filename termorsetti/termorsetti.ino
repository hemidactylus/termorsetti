#include <DHT.h>
#define DHTPIN 11
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const int ledPins[3]={2,3,4}; // green, yellow, red

const int analogIns[2]={A0,A5}; // long-wire

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for(int i=0;i<3;i++){
    pinMode(ledPins[i],OUTPUT);
  }
  //
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<3;i++){
    digitalWrite(ledPins[(i+2)%3],LOW);
    digitalWrite(ledPins[i],HIGH);
    delay(666);
  }
  // temp hum/temp
  float digHum = dht.readHumidity();
  float digTem = dht.readTemperature();
  // temporary analog:
  int tempReading=analogRead(analogIns[0]);
  int tempReading2=analogRead(analogIns[1]);
  Serial.print((1.0*millis())/1000);
  Serial.print("\t");
  Serial.print(temperature_from_reading(tempReading,0.0));
  Serial.print("\t");
  Serial.print(temperature_from_reading(tempReading2,-1.2));
  Serial.print("\t|\t");
  Serial.print(digTem);
  Serial.print("\t");
  Serial.print(digHum);
  Serial.println(" %");
}

float temperature_from_reading(int reading,float delta){
  return delta-25.58 + 0.1097*reading-2.1578e-05*pow(reading,2.0);
}

