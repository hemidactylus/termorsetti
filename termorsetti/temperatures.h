#ifndef _LIB_TEMPERATURES
#define _LIB_TEMPERATURES

const int tempAnalogIns[2]={A0,A5}; // long-wire, short-wire respectively
float temperatureDeltas[2]={0.0,0.0}; // additive adjustments to the sensors (calibration=both in the same place, make them yield same T)

#endif

