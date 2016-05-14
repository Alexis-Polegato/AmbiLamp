#include "LedControl.h"
#include "BeatMode.h"

//#include <FHT.h>

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/


/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

static uint8_t color;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void RandomBeatMode(int *sound)
{
    uint8_t index;
	uint8_t i;
	uint8_t beat;

	color++;
	for(i= 0; i < NUM_LEDS; i++) 
	{   
        index = U128_SUM(2*i,2);                      
     	beat = U_SUB(sound[index], NOISE_VALUE);           
     	//beat = U_SUB(sound[i+7], NOISE_VALUE);  // Because not enough space for 256 values         

        //if (beat > (LedRunningInfo.leds[i].r + LedRunningInfo.leds[i].g + LedRunningInfo.leds[i].b))            // Refresh an LED only when the intensity is low
        if ((beat > 0x00) && (beat > 2*(LedRunningInfo.leds[i].r + LedRunningInfo.leds[i].g + LedRunningInfo.leds[i].b)))            // Refresh an LED only when the intensity is low
    	{    
            LedRunningInfo.leds[i] = CHSV(beat * COLOR_FACTOR + color, 255, beat * BRIGHTNESS_FACTOR);
        	//LedRunningInfo.leds[i] = CHSV(beat * COLOR_FACTOR + color, 255, BRIGHTNESS_MAX);
        }
    	LedRunningInfo.leds[i].nscale8(224);                                     
    }
}

void ColorBeatMode(int *sound)
{
	uint8_t i;
	uint8_t beat;

	color++;
	for(i= 0; i < NUM_LEDS/2; i++) 
	{                        
     	beat = U_SUB(sound[2*i+2], NOISE_VALUE);           
     	//beat = U_SUB(sound[i+7], NOISE_VALUE);  // Because not enough space for 256 values         

    	if ((beat > 0x00) && (beat > (LedRunningInfo.leds[i].r + LedRunningInfo.leds[i].g + LedRunningInfo.leds[i].b)))            // Refresh an LED only when the intensity is low
    	{    
        	LedRunningInfo.leds[i] = CHSV(color, 255, beat * BRIGHTNESS_FACTOR);
        }
    	//LedRunningInfo.leds[i].nscale8(224);                                     
    	LedRunningInfo.leds[i].nscale8(224);                                     
    }
}

    //if (tmp > Max(leds[i].r,leds[i].g,leds[i].b))
        //leds[i] = CHSV(hueinc, 255, tmp*micmult);
/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/