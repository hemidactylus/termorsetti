#ifndef _LIB_TEMPERATURES
#define _LIB_TEMPERATURES

const int tempAnalogIns[2]={A0,A5}; // long-wire, short-wire respectively (external, internal)
float temperatureDeltas[2]={0.0,0.0}; // additive adjustments to the sensors (calibration=both in the same place, make them yield same T)
const float digitalTempDelta=-2.0; // additive adjustment to the digital temperature sensor

#define NUM_MEASUREMENTS (3)

// the first within a class, the second is counting all measurement events. Both conditions have to be met for a measurement to be performed.
#define DELAY_BETWEEN_MEASUREMENTS (30000)
#define DELAY_BETWEEN_ANY_MEASUREMENT (5000)

struct sensorReading{
  float measures[NUM_MEASUREMENTS];
  float value;
  int mindex;
  unsigned long int birth;
};

sensorReading readings[5];

unsigned long int lastMeasurementEpoch;

#endif

