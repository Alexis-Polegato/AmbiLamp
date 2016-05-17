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
  SetupWaterEffect();
  Serial.begin(57600);                                        // use the serial port
}


void loop() 
{
	int SoundMeasure[FHT_SAMPLE_NUMBER];
	uint8_t mode;

	while(1)
	{
		EVERY_N_MILLISECONDS(20)
		{
			BeatMode();
			//RunWaterEffect(3);
			
			//ProcessSoundAnalysisTable(SoundMeasure);
			//ColorBeatMode(SoundMeasure);
			//BackgroundMode(BACKGROUND_RED);
			
			//VuMeter(SoundMeasure);
				
			 //SwitchModeTick();
			 //mode = getActualMode();
			// switch (mode) 
	 	// 		{
	 	// 		    case MODE_NORMAL:
	 	// 		    RunWaterEffect(1);
	 	// 		    //BeatMode();
	 	// 		    //BackgroundMode(BACKGROUND_RED);
			// 	   //RandomBeatMode(SoundMeasure);
			// 	    //RandomBeatMode(SoundMeasure);
	 	// 		      break;
	 	// 		    case MODE_PARTY:
   //    				//RandomBeatMode(SoundMeasure);
   //    				BeatMode();
	 	// 		    break;
			// 	}
		}
		PowerLeds();
	}
}
