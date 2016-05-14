#include "AmbiLamp.h"
#include "SoundAnalysis.h"
#include "LedControl.h"
#include "WaterEffect.h"
#include "BeatMode.h"
#include "VuMeter.h"

// #if OCTAVE == 1
// int SoundMeasure[FHT_OCTAVE_NUMBER];
// #endif

// #if LOG_OUT == 1
// int SoundMeasure[FHT_SAMPLE_NUMBER];
// #endif

// void SoundMeasureTable()
// {
// 	#if OCTAVE == 1
// 	int SoundMeasure[FHT_OCTAVE_NUMBER];
// 	#endif

// 	#if LOG_OUT == 1
// 	int SoundMeasure[FHT_SAMPLE_NUMBER];
// 	#endif

// 	ProcessSoundAnalysis(SoundMeasure);
// 	RandomBeatMode(SoundMeasure);
// }

int SoundMeasure[FHT_SAMPLE_NUMBER];

void setup() 
{
  //analogReference(EXTERNAL);                                  // Connect 3.3V to AREF pin for any microphones using 3.3V
  InitSoundAnalysis();
  InitLeds();
  //SetupWaterEffect();
  Serial.begin(57600);                                        // use the serial port
}


void loop() 
{
	while(1)
	{
		EVERY_N_MILLISECONDS(20)
		{
			//SoundMeasureTable();
			ProcessSoundAnalysis(&SoundMeasure[0]);
			ColorBeatMode(SoundMeasure);
			//RandomBeatMode(&SoundMeasure[0]);
			//VuMeter(SoundMeasure);
		}
		PowerLeds();
		// EVERY_N_MILLISECONDS(50)
		// {
		// 	//VuMeterSimple();
		// 	LoveMode();
		// 	PowerLeds();
		// }
	}

	// uint8_t cmt = 0;
	// uint8_t color = 0;
	// uint8_t sound = 0;
	// uint8_t music = MUSIC_OFF;
	// uint8_t state = STATE_MUSIC_OFF;
	// while(1)
	// {
	// 	EVERY_N_MILLISECONDS(50)
	// 	{
	// 		cmt++;
	// 		sound = MeanSoundAnalysis();
	// 		if(sound >= MEAN_SOUND_THS)
	// 		{
	// 			music = MUSIC_ON;
	// 		}
	// 		if(cmt == 10)
	// 		{
	// 			cmt = 0;
	// 			color += sound;
	// 			if(music == MUSIC_ON) // 4 seconds
	// 			{
	// 				state = STATE_MUSIC_ON;		
	// 			}
	// 			else if(music == 10) // 4 seconds
	// 			{
	// 				state = STATE_MUSIC_PAUSE;
	// 			}
	// 			else if(music == 20)	// 4 seconds de plus
	// 			{
	// 				state = STATE_MUSIC_OFF;
	// 			}
	// 			music++;
	// 		}

	// 			switch (state) 
	// 			{
	// 			    case STATE_MUSIC_ON:
	// 			      RunWaterEffectWithColor(color, sound*10);
	// 			      //Serial.println("State Music ON");
	// 			      break;
	// 			    case STATE_MUSIC_OFF:
	// 			      RunWaterEffect(sound*5);
	// 			      //Serial.println("State Music OFF");
	// 			      break;
	// 			    case STATE_MUSIC_PAUSE:
	// 			      StopWaterEffect();
	// 			      //Serial.println("State Music Pause");
	// 			      break;
	// 			    default:
	// 			      // do something
	// 			      break;
	// 			}
	// 	}
	// 	PowerLeds();
                             
		 	//ProcessSoundAnalysis(SoundMeasure);
			//RunWaterEffect(10);
			
			//VuMeterLeds(SoundMeasure);
			// VuMeterLedsTest(color);
}  

// void InitLeds()
// {
//   LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
//   FastLED.setBrightness(125);
//   // FastLED.setBrightness(BRIGHTNESS_HALF);
//   set_max_power_in_volts_and_milliamps(5, 2500);  // TODO Ajust this value ??
//   //FastLED.delay(1000);
  
// }



// #include <TimerOne.h>
// #include <RBD_Timer.h>
// #include <FastLED.h>
// #include "LedControl.h"
// #include "SoundAnalysis.h"

// RBD::Timer GeneralTimer;

// volatile int tick;
// int SoundMeasure[FHT_OCTAVE_NUMBER];
// int testValue;

// void Interrupt()
// {
// 	tick = 1;
// 	testValue++;
// 	if(testValue > 15)
// 	{
// 		testValue = 0;
// 	}
	
// 	//ProcessSoundAnalysis(SoundMeasure);
//     // VuMeterLeds(SoundMeasure);
   
// }

// void setup() 
// {
// 	Serial.begin(57600);
// 	// GeneralTimer.setTimeout(100);
// 	// GeneralTimer.restart();
// 	Timer1.initialize(2000000);	// Every X µs
//   	Timer1.attachInterrupt(Interrupt); 
//   	//InitSoundAnalysis();
// 	InitLeds();
// 	delay(2000);
// }


// void loop() 
// {
// 	tick = 0;
// 	Serial.println("Debut Test");
// 	testValue = 0;
// 	Serial.println(testValue);
// 	uint8_t i = 0;
//   	while(1)
//   	{
//   		if(tick == 1)
//   		{
//   			Serial.println(testValue);
//   			VuMeterLedsTest(testValue);
// 		    tick = 0;
//   		}
//   	    PowerLeds();
//       	//show_at_max_brightness_for_power();
//   		//}
//     	// PowerLeds();
//   	}

// }
