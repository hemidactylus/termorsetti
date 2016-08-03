#include "temperatures.h"

float read_analog_temperature(int sensorIndex){
  int tempReading=analogRead(tempAnalogIns[sensorIndex]);
  return temperature_from_reading(tempReading,temperatureDeltas[sensorIndex]);
}

float temperature_from_reading(int reading,float delta){
  return delta-25.58 + 0.1097*reading-2.1578e-05*pow(reading,2.0);
}

