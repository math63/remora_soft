// **********************************************************************************
// SHT31 sensor module management headers file for remora project
// **********************************************************************************
// Creative Commons Attrib Share-Alike License
// You are free to use/extend but please abide with the CC-BY-SA license:
// http://creativecommons.org/licenses/by-sa/4.0/
//
// Written by Mathieu DELBOS
//
// History : V1.00 2020-05-08 - First release
//
// All text above must be included in any redistribution.
//
// **********************************************************************************

#ifndef SENSORS_h
#define SENSORS_h

#include "remora.h"
#include "./SHT3x.h"

#define SHT30_ADDRESS 0x45

typedef struct
{
  float  	temp;    /* temperature  */
  float  	hum;     /* Humidity   */
  unsigned long    time;   	/* date of last measure  */
  float  	ptemp;  	/* previous temperature  */
  float  	phum;     /* previous Humidity   */
  unsigned long    ptime;   	/* date of previous measure  */
  float  	tmin;     /* temperature min since 00h00  */
  float  	tmax;    /* temperature max since 00h00   */
  float  	hmin; 	/* Humidity min since 00h00   */
  float  	hmax;    /* Humidity max since 00h00  */
} SENData;


// Variables exported to other source file
// ========================================
// define sesnor var for whole project
extern SHT3x sht30;
extern unsigned long  sensors_last_meas;// second since last sensor reading
extern SENData         senData;     // data received

// Function exported for other source file
// =======================================
bool sensors_setup(void);
void sensors_read(void);
void sensors_First_reading(void);


#endif