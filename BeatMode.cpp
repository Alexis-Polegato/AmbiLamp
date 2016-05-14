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
    uint8_t ledColor;
    uint8_t beat;
	uint8_t index;

	color++;
	for(i= 0; i < NUM_LEDS_PER_FACE; i++) 
	{              
        index = U128_SUM(2*i,7);            
     	beat = U_SUB(sound[index], NOISE_VALUE);           
     	//beat = U_SUB(sound[i+7], NOISE_VALUE);  // Because not enough space for 256 values         
        ledColor = MaxColor(LedRunningInfo.leds[i].r, LedRunningInfo.leds[i].g, LedRunningInfo.leds[i].b);
    	if ((beat > 0x00) && (beat > 3*ledColor))            // Refresh an LED only when the intensity is low
    	{    
            LedRunningInfo.leds[i] = CHSV(color, 255, beat * BRIGHTNESS_FACTOR);
            LedRunningInfo.leds[i+NUM_LEDS_PER_FACE] = CHSV(color, 255, beat * BRIGHTNESS_FACTOR);
        	//LedRunningInfo.leds[i] = CHSV(map(i, 0, 16, ledColor, ledColor+16), 255, beat * BRIGHTNESS_FACTOR);
        }
    	//LedRunningInfo.leds[i].nscale8(224);                                     
        LedRunningInfo.leds[i].nscale8(224);                                     
    	LedRunningInfo.leds[i+NUM_LEDS_PER_FACE].nscale8(224);                                     
    }
}

uint8_t MaxColor(uint8_t a, uint8_t b, uint8_t c)
{
    if(a > b)
    {
        if (a > c)
        {
            return(a);
        }
        else 
        {
            return(c);
        }
    }
    else
    {
        if (b > c)
        {
            return(b);
        }
        else 
        {
            return(c);
        }
    }
}

    //if (tmp > Max(leds[i].r,leds[i].g,leds[i].b))
        //leds[i] = CHSV(hueinc, 255, tmp*micmult);
/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/