#include "Arduino.h"
#include "LedControl.h"
#include "SoundAnalysis.h"


#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

CRGBPalette16 gPal;
LedInformation_s LedRunningInfo;


/**************************************************************/
/*                        PRIVATE DATA                        */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitLeds()
{
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(LedRunningInfo.leds, NUM_LEDS);
  FastLED.setBrightness(0xFF);
  // FastLED.setBrightness(BRIGHTNESS_HALF);
  set_max_power_in_volts_and_milliamps(5, 1500);  // TODO Ajust this value ??
  //FastLED.delay(1000);
  
}

void PowerLeds()
{
  //FastLED.show();
  show_at_max_brightness_for_power();
}

void VuMeterLeds(int *soundMeasure)
{
  uint8_t i;
  uint8_t top[WIDTH_PER_FACE];

  top[0] = ((soundMeasure[0] + soundMeasure[1]) >> 1) / 20;
  top[1] = ((soundMeasure[2] + soundMeasure[3]) >> 1) / 20;
  top[3] = ((soundMeasure[4] + soundMeasure[5]) >> 1) / 20;
  top[4] = ((soundMeasure[6] + soundMeasure[7]) >> 1) / 20;
  top[2] = (top[1] + top[3]) >> 1;

/*  for(i = 0; i < 8; i++)
  {
    Serial.print("Sound Mesure ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(soundMeasure[i]);
  }
  Serial.println();
  for(i = 0; i < WIDTH_PER_FACE; i++)
  {
    Serial.print("Top de");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(top[i]);
  }*/
  for(i = 0; i < HEIGHT; i++)
  {
    if(i > top[i])
    {  
      LedRunningInfo.leds[i+0*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+2*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+4*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+6*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+8*HEIGHT].setRGB(0, 0, 0);
    }
    else
    {
      LedRunningInfo.leds[i+0*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+2*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+4*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+6*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+8*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
    }
  }

  for(i = HEIGHT; i > 0; i--)
  {
    if ((HEIGHT - i) >= top[i])   
    {
      LedRunningInfo.leds[i+1*HEIGHT].setRGB( 0, 0,0);
      LedRunningInfo.leds[i+3*HEIGHT].setRGB( 0, 0,0);
      LedRunningInfo.leds[i+5*HEIGHT].setRGB( 0, 0,0);
      LedRunningInfo.leds[i+7*HEIGHT].setRGB( 0, 0,0);
      LedRunningInfo.leds[i+9*HEIGHT].setRGB( 0, 0,0);
    }
    else
    {
      LedRunningInfo.leds[i+1*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,30,150), 255, 255);
      LedRunningInfo.leds[i+3*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,30,150), 255, 255);
      LedRunningInfo.leds[i+5*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,30,150), 255, 255);
      LedRunningInfo.leds[i+7*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,30,150), 255, 255);
      LedRunningInfo.leds[i+9*HEIGHT] = CHSV(map(HEIGHT - i,0,HEIGHT-1,30,150), 255, 255);
    }
  }
}

void VuMeterLedsTest(int value)
{
  int i;
/*  for(i = 0; i < 8; i++)
  {
    Serial.print("Sound Mesure ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(soundMeasure[i]);
  }
  Serial.println();
  for(i = 0; i < WIDTH_PER_FACE; i++)
  {
    Serial.print("Top de");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(top[i]);
  }*/
  for(i = 0; i < HEIGHT; i++)
  {
    if(i > value)
    {  
      LedRunningInfo.leds[i+0*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+2*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+4*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+6*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+8*HEIGHT].setRGB(0, 0, 0);
    }
    else
    {
      LedRunningInfo.leds[i+0*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+2*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+4*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+6*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+8*HEIGHT] = CHSV(map(i, 0, HEIGHT-1, 30, 150), 255, 255);
    }
  }

  for(i = HEIGHT; i > 0; i--)
  {
    if ((HEIGHT - i) >= value)   
    {
      LedRunningInfo.leds[i+1*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+3*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+5*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+7*HEIGHT].setRGB(0, 0, 0);
      LedRunningInfo.leds[i+9*HEIGHT].setRGB(0, 0, 0);
    }
    else
    {
      LedRunningInfo.leds[i+1*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+3*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+5*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+7*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, 30, 150), 255, 255);
      LedRunningInfo.leds[i+9*HEIGHT] = CHSV(map(HEIGHT - i, 0, HEIGHT - 1, 30, 150), 255, 255);
    }
  }
}



/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/