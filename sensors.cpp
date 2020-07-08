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


#include "./sensors.h"
#include "./SHT3x.h"

#ifdef MOD_SENSORS
unsigned long  sensors_last_meas=0;// second since last sensor reading
SHT3x sht30(SHT30_ADDRESS);
SENData         senData; 
#endif

/* ======================================================================
Function: sensors_setup
Purpose : prepare and init stuff, configuration, ..
Input   : -
Output  : true if sensor module found, false otherwise
Comments: -
====================================================================== */
bool sensors_setup(void)
{
	bool ret = false;
	Debug("Initializing sensor SHT30...Searching...");
    Debugflush();

	#if defined (ESP8266)
    // Sepecific ESP8266 to set I2C Speed
    Wire.setClock(100000);
	#endif
	
// Détection du SHT30
    if (!i2c_detect(SHT30_ADDRESS))
    {
      Debugln("Not found!");
      Debugflush();
      return (false);
    }
    else 
	{
	  Debug("Setup...");
      Debugflush();

      // et l'initialiser
	sht30.SetAddress(SHT30_ADDRESS);
	sht30.SetMode(SHT3x::Single_HighRep_NoClockStretch);
	sht30.Begin();

      Debugln("OK!");
      Debugflush();
	sensors_First_reading(); //first reading initiate senData structure
    }
  
	#if defined (ESP8266)
    // Sepecific ESP8266 to set I2C Speed
    Wire.setClock(400000);
	#endif
  // ou l'a trouvé
  return (true);
}

/* ======================================================================
Function: sensors_read
Purpose :
Input   : -
Output  : e
Comments: -
====================================================================== */
void sensors_read(void)
{
	Wire.setClock(100000);
	sht30.UpdateData();
	Wire.setClock(400000);	
		
	senData.ptemp=senData.temp;
	senData.phum=senData.hum;
	senData.ptime=senData.time;
	senData.temp=sht30.GetTemperature();
	senData.hum=sht30.GetRelHumidity();
	//https://github.com/arduino-libraries/NTPClient
	senData.time=timeClient.getEpochTime();
	
	
if 	((senData.time/ 86400L)!=(senData.ptime/ 86400L)) { //changement de jour
	senData.tmin=senData.temp;
	senData.tmax=senData.temp;
	senData.hmin=senData.hum;
	senData.hmax=senData.hum;
} else {
	if (senData.temp < senData.tmin)
		senData.tmin=senData.temp;
	if (senData.temp > senData.tmax)
		senData.tmax=senData.temp;
	if (senData.hum < senData.hmin)
		senData.hmin=senData.hum;
	if (senData.hum > senData.hmax)
		senData.hmin=senData.hum;
}
	Debugln("sensor read");
	Debugflush();
}

/* ======================================================================
Function: sensors_First_reading
Purpose : prepare and init stuff, configuration, ..
Input   : -
Output  : true if sensor module found, false otherwise
Comments: -
====================================================================== */
void sensors_First_reading(void)
{
	sht30.UpdateData();
	senData.temp=sht30.GetTemperature();
	senData.hum=sht30.GetRelHumidity();
	senData.time=timeClient.getEpochTime();
	senData.ptemp=senData.temp;
	senData.phum=senData.hum;
	senData.ptime=senData.time;
	senData.tmin=senData.temp;
	senData.tmax=senData.temp;
	senData.hmin=senData.hum;
	senData.hmax=senData.hum;
}