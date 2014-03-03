/****************************************************
 * Global definitions
 * Prefix: DEFINES
 ****************************************************/

#ifndef DEFINES_H
#define DEFINES_H

#include "Arduino.h"

//debug
#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.println (x)
  #define DEBUG_TIME()  time = micros();
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_TIME()
#endif

#define TRUE 1
#define FALSE 0

//pins
#define LWHEEL_DIR 12
#define LWHEEL_ENABLE 3
#define LWHEEL_BRAKE 9
#define RWHEEL_DIR 13
#define RWHEEL_ENABLE 11
#define RWHEEL_BRAKE 8

#define ROTATOR 10
#define SHOOTER 6
#define MINER 5
// free for now - pins 4,7 (also 0,1 - serial)


//Mux pins define
//also for LineFind
#define REAR_LINESENSOR 10
#define FRONTR_LINESENSOR 11
#define FRONTL_LINESENSOR 12



//BeaconSens 

#define SERVER_BEACON 1
#define EXCHANGE_BEACON 2

/*---------------- Module Functions -------------------------*/


#endif /* DEFINES_H */


