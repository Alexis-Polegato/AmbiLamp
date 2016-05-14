#include "Arduino.h"
#include "BackgroundLed.h"
#include "AmbiLamp.h"
#include "SoundAnalysis.h"
#include "LedControl.h"
#include "WaterEffect.h"
#include "BeatMode.h"
#include "VuMeter.h"
#include "SwitchMode.h"

void setup() 
{
  //analogReference(EXTERNAL);                                  // Connect 3.3V to AREF pin for any microphones using 3.3V
  InitSoundAnalysis();
  InitLeds();
  SwitchModeInit();
  //SetupWaterEffect();
  Serial.begin(57600);                                        // use the serial port
}


void loop() 
{
	uint8_t mode;

	while(1)
	{
		EVERY_N_MILLISECONDS(50)
		{
			//fhtsound();
			//RunWaterEffect(3);
			//SoundMeasureTable();
			//ProcessSoundAnalysis();
			//BackgroundMode(BACKGROUND_RED);
			BeatMode();
			//VuMeter(SoundMeasure);
			//RandomBeatMode(SoundMeasure);
				
			//SwitchModeTick();
			/*
			mode = getActualMode();
			switch (mode) 
	 			{
	 			    case MODE_NORMAL:
				      RunWaterEffect(3);
	 			      Serial.println("NORMAL");
	 			      break;
	 			    case MODE_PARTY:
	 			      //RunWaterEffect(sound*5);
	 			      Serial.println("PARTY");
	 			      break;
	 			    case MODE_OFF:
	 			      //StopWaterEffect();
	 			      Serial.println("OFF");
	 			      break;
				}
			*/
			//ColorBeatMode(SoundMeasure);
		}
		PowerLeds();
		//Serial.println("PING");
	}
}