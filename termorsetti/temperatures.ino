#include "temperatures.h"

float read_analog_temperature(int sensorIndex){
  int tempReading=analogRead(tempAnalogIns[sensorIndex]);
  return temperature_from_reading(tempReading,temperatureDeltas[sensorIndex]);
}

float temperature_from_reading(int reading,float delta){
  return delta-25.58 + 0.1097*reading-2.1578e-05*pow(reading,2.0);
}

float read_rain_input(){
  int rainQuids=analogRead(rainAnalogIn);
  return rainQuids*1.0/1024.0;
}

float celsius(float fah){
  return (fah-32.0)/1.8;
}
float fahrenheit(float cel){
  return 32.0+(1.8*cel);
}
float heat_index(float cel, float rh){
    float f=fahrenheit(cel);
    float h_i= -42.379 + (2.04901523 * f + 10.14333127 * rh) - (0.22475541 * f * rh) -
        (.00683783 * f * f) - (.05481717 * rh *rh) + (.00122874 * f * f * rh)
        + (.00085282 * f * rh * rh) - (.00000199 * f * f * rh * rh);
    return celsius(h_i);
}

void initReadings(unsigned long int epoch){
  for(int ire=0;ire<5;ire++){
    readings[ire].mindex=-1; // special meaning
    for(int ime=0;ime<NUM_MEASUREMENTS;ime++){
      readings[ire].measures[ime]=0.0;
    }
    readings[ire].birth=epoch-(unsigned long int)(0.8*DELAY_BETWEEN_MEASUREMENTS);
    readings[ire].value=0.0;
  }
  lastMeasurementEpoch=epoch-0.8*DELAY_BETWEEN_MEASUREMENTS;
  return;
}

void handleReadings(unsigned long int epoch){
  // if epoch is too early for all measurements, do nothing, else update at most a measurement
  if ((epoch-lastMeasurementEpoch)<DELAY_BETWEEN_ANY_MEASUREMENT){
    return;
  }
  int readingChanged=-1;
  for(int ire=0;ire<6;ire++){
    if ((ire!=4)&&((epoch-readings[ire].birth)>DELAY_BETWEEN_MEASUREMENTS)){
      // proceed with this measurement
      float newVal;
      updateLeds(1,0,1);
      switch(ire){
        case 0:
        case 1:
          newVal=read_analog_temperature(ire);
          break;
        case 2:
          newVal=dht.readTemperature()+digitalTempDelta;
          break;
        case 3:
          newVal=dht.readHumidity();
          break;
         case 5:
          newVal=read_rain_input();
          break;
      }
      readingChanged=ire;
      readings[ire].birth=epoch;
      if (readings[ire].mindex==-1){
        for(int ime=0;ime<NUM_MEASUREMENTS;ime++){
          readings[ire].measures[ime]=newVal;
        }
        readings[ire].mindex=0;
      }else{
        readings[ire].mindex=(readings[ire].mindex+1)%NUM_MEASUREMENTS;
        readings[ire].measures[readings[ire].mindex]=newVal;
      }
      // re-evaluate the average
      readings[ire].value=0.0;
      for(int ime=0;ime<NUM_MEASUREMENTS;ime++){
        readings[ire].value+=readings[ire].measures[ime];
      }
      readings[ire].value/=(1.0*NUM_MEASUREMENTS);
      break;
    }
  }
  if (readingChanged>-1){
    // 1. update heat index? (also on file)
    if ((readingChanged==1) || (readingChanged==3)){
      readings[4].value=heat_index(readings[1].value,readings[3].value);
      logReading(readings[4].value,4);
    }
    // 2. flush to file (also heat index if relevant)
    logReading(readings[readingChanged].value,readingChanged);
  }
  updateLeds(0,0,0);
  return;
}
