#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define LED_PIN   10
#define LED_DT 	  LED_PIN

#define HEIGHT 		15
#define WIDTH     10
#define WIDTH_PER_FACE 		5
#define NUM_LEDS  HEIGHT * WIDTH
#define NUM_LEDS_PER_FACE 	HEIGHT * WIDTH_PER_FACE


/* How hot is "hot"? Increase for brighter fire */
#define COOLING 90
#define HOT 180
#define MAXHOT HOT*HEIGHT

#define FPS 20
#define FPS_DELAY 1000/FPS

#define BRIGHTNESS_MIN    		0x00
#define BRIGHTNESS_BOOT   		BRIGHTNESS_MIN
#define BRIGHTNESS_HALF       0x7F
#define BRIGHTNESS_MAX    		0xFF
#define LED_TYPE    			WS2812B
#define COLOR_ORDER 			GRB
#define FRAMES_PER_SECOND  		60
#define LED_CONTROL_TIME_OUT	1500

#define MAX_DIMENSION ((WIDTH>HEIGHT) ? WIDTH : HEIGHT)

typedef struct cordinate_t
{
  uint16_t x;
  uint16_t y;
  uint16_t z;
}cordinate_s;

typedef struct LedInformation_t
{
  CRGB      leds[NUM_LEDS];
  int        Brightness;
  uint8_t    gHue; 
  CRGBPalette16 currentPalette;
  uint8_t     noise[MAX_DIMENSION][MAX_DIMENSION]; 
  cordinate_s   coordinate;
  uint8_t     ExternaLight;
} LedInformation_s;

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

extern LedInformation_s LedRunningInfo;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitLeds();
void PowerLeds();
void VuMeterLeds(int *soundMeasure);
void VuMeterLedsTest(int value);


/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

#endif