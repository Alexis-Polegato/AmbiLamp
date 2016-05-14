#ifndef BEAT_MODE_H
#define BEAT_MODE_H

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define U_SUB(a,b) 											((a>b) ? a-b : 0)	 
#define U128_SUM(a,b) 										((a+b) > 128 ? a+b-128 : a+b)	 
#define U150_SUM(a,b) 										((a+b) > 150 ? a+b-150 : a+b)	 
#define U150_SUB(a,b) 										((a>b) ? a-b : 0)

// TODO: Adjust value for NOISE / SENSITIVTY
#define NOISE_VALUE											0x2A	

// TODO: Customize for effect
#define BRIGHTNESS_FACTOR									0x16	
#define COLOR_FACTOR										0x0A	

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/
void RandomBeatMode(int *sound);
void ColorBeatMode(int *sound);

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

#endif