#include "SoundAnalysis.h"
#include "LedControl.h"
#include "BeatMode.h"

//#include <FHT.h>

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/


/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

static uint8_t Color;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void RandomBeatMode(int *sound)
{
	uint8_t i;
    uint8_t beat;
    uint8_t newColor;
    uint8_t newBrightness;

	Color++;
	for(i= 0; i < NUM_LEDS_PER_FACE; i++) 
	{                               
     	beat = U_SUB(sound[i+7], BEAT_MODE_NOISE_VALUE);    // Removing Noise, but keep > 0     

        if (beat > (LedRunningInfo.leds[i].r + LedRunningInfo.leds[i].g + LedRunningInfo.leds[i].b))           // Refresh an LED only when the intensity is low
    	{    
            newColor      = beat * COLOR_FACTOR + Color;         // Get a Random Color for current leds[i]
            newBrightness = beat * BRIGHTNESS_FACTOR;            // Higher the Beat => Higher the brightness
            LedRunningInfo.leds[i]                   = CHSV(newColor, SATURATION_MAX, newBrightness);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(newColor, SATURATION_MAX, newBrightness);
        }
        LedRunningInfo.leds[i].nscale8(224);                                     
    	LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
}

void ColorBeatMode(int *sound)
{
	uint8_t i;
    uint8_t beat;
    uint8_t currentColor;
    uint8_t newBrightness;

	Color++;
	for(i= 0; i < NUM_LEDS_PER_FACE; i++) 
	{                                    
     	beat = U_SUB(sound[i+7], BEAT_MODE_NOISE_VALUE);
        currentColor = MaxColor(LedRunningInfo.leds[i].r, LedRunningInfo.leds[i].g, LedRunningInfo.leds[i].b);
    	if (beat > 3 * currentColor)  
    	{    
            newBrightness = beat * BRIGHTNESS_FACTOR;            // Higher the Beat => Higher the brightness
            LedRunningInfo.leds[i]                   = CHSV(Color, SATURATION_MAX, newBrightness);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(Color, SATURATION_MAX, newBrightness);
        }                                     
        LedRunningInfo.leds[i].nscale8(224);                                     
    	LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
}


/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/