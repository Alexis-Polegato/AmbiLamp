#include "Arduino.h"
#include "SoundAnalysis.h"

#include <FHT.h>

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PRIVATE DATA                        */
/**************************************************************/

static int SoundLevel;
static int SoundVolume[VOLUME_SAMPLES];
static uint8_t volumeIndex;
static uint16_t MinLevelAvg;                                              // For dynamic adjustment of graph low & high
static uint16_t MaxLevelAvg;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitSoundAnalysis()
{
  // Because we power Sound Detector with 3.3 Volts
  analogReference(EXTERNAL);
  // Init ADC (Pin A0 Used here)
  //TIMSK0 = 0x00; 
/*	ADCSRA = 0xE5; 
	ADMUX  = 0x40; 
	DIDR0  = 0x01; */
	// TODO Add a "Debug Define to display data"
	//Serial.begin(115200);
  SoundLevel = 12;
  MinLevelAvg = 0;
  MaxLevelAvg = 512;
}

int GetSoundLevel(uint16_t *minLvlAvg, uint16_t *maxLvlAvg)
{
  int measure;
  uint8_t i;
  uint16_t minLvl, maxLvl;

  measure = analogRead(0);
  measure = abs(measure - DIFF_TO_BUILD_SIGNED_INT - DC_OFFSET);

  measure = REMOVE_NOISE(measure, NOISE);
  SoundLevel = ((SoundLevel * 7) + measure) >> 3;

  SoundVolume[volumeIndex] = measure;                                     
  if (++volumeIndex >= VOLUME_SAMPLES)
  {
    volumeIndex = 0x00;
  } 
 
  // Get volume range of prior frames
  minLvl = SoundVolume[0];
  maxLvl = SoundVolume[0];
  for(i = 1; i < VOLUME_SAMPLES; i++) 
  {
    if (SoundVolume[i] < minLvl)
    {
      minLvl = SoundVolume[i];
    }      
    else if (SoundVolume[i] > maxLvl) 
    { 
      maxLvl = SoundVolume[i];
    }
  }
  if((maxLvl - minLvl) < TOP)
  {
    maxLvl = minLvl + TOP;
  }
  MinLevelAvg = (MinLevelAvg * 63 + minLvl) >> 6;                
  MaxLevelAvg = (MaxLevelAvg * 63 + maxLvl) >> 6;

  *minLvlAvg = MinLevelAvg;
  *maxLvlAvg = MaxLevelAvg;

  return (SoundLevel);
}


void ProcessSoundAnalysis(int *soundMeasure)
{
  int i;
  cli();  
  for (i = 0 ; i < FHT_SAMPLE_NUMBER ; i++)
  {
    fht_input[i] = analogRead(0) - 512;
  } 
  sei();
    // Apply FHT
  fht_window(); 
  fht_reorder(); 
  fht_run();
  fht_mag_log();
  
  for(i = 0; i < FHT_SAMPLE_NUMBER; i++)
  {
    soundMeasure[i] = fht_log_out[i];
  }
}

uint16_t MeanSoundAnalysis()
{
  uint8_t i;
  uint16_t total = 0;
  cli();
  SoundAcquisition();
  SoundProcessing();
  sei(); 
  // TODO Add a "Debug Define to display data"
  //SoundDisplay();

  #if OCTAVE == 1
  for(i = 0; i < FHT_OCTAVE_NUMBER; i++)
  {
    total += fht_oct_out[i];
  }
  total /= FHT_OCTAVE_NUMBER;
  #endif

  #if LOG_OUT == 1
  for(i = 0; i < FHT_HALF_SAMPLE_NUMBER; i++)
  {
    total += fht_log_out[i];
  }
  total = total / FHT_HALF_SAMPLE_NUMBER;
/*  for(i = 0; i < FHT_HALF_SAMPLE_NUMBER; i++)
  {
    total += fht_log_out[2*i+2];
  }
  total = total / FHT_HALF_SAMPLE_NUMBER;*/
  #endif

  return (total);
}

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void SoundAcquisition()
{
 //  uint8_t adcLow, adcHigh;
	// int measure;
	// for (int i = 0 ; i < FHT_SAMPLE_NUMBER ; i++) 
 //  { 
 //    while(!(ADCSRA & 0x10));      // Waiting for ADC Ready
 //    ADCSRA = 0xF5;
 //    adcLow = ADCL; 
 //    adcHigh = ADCH;
 //    measure = (adcHigh << 8) | adcLow;
 //    measure -= DIFF_TO_BUILD_SIGNED_INT; 	
 //    //measure <<= FACTOR_TO_BUILD_SIGNED_SHORT; 
 //    fht_input[i] = measure; 
 //  }
  
  /* for (int i = 0 ; i < FHT_SAMPLE_NUMBER ; i++) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      //fht_input[i] = k; // put real data into bins
      fht_input[i] = k; 
    }*/

  //cli();
  for (int i = 0 ; i < FHT_SAMPLE_NUMBER ; i++)
  {
      fht_input[i] = analogRead(0) - 512;
  }  
  //sei();
}

static void SoundProcessing()
{
	  // Apply FHT
	  fht_window(); 
    fht_reorder(); 
    fht_run();
	  // TODO Select log or octave with define
    #if OCTAVE == 1
    fht_mag_octave();
    #endif

    #if LOG_OUT == 1
    fht_mag_log(); 
    #endif
}

// To Read with processing
static void SoundDisplay()
{
	Serial.write(255);
  //Serial.write(fht_log_out, FHT_HALF_SAMPLE_NUMBER); 
  //Serial.write(fht_oct_out, FHT_HALF_SAMPLE_NUMBER);

  // #if OCTAVE == 1
  // uint8_t i;
  // for(i = 0; i < FHT_OCTAVE_NUMBER; i++)
  // {
  //   Serial.print("FHT ");
  //   Serial.print(i);
  //   Serial.print(" = ");
  //   //Serial.println(fht_oct_out[i]);
  // }
  // #endif

  // #if LOG_OUT == 1
  // uint8_t i;
  // for(i = 0; i < FHT_SAMPLE_NUMBER; i++)
  // {
  //   Serial.print("FHT ");
  //   Serial.print(i);
  //   Serial.print(" = ");
  //   //Serial.println(fht_log_out[i]);
  // }
  // #endif
}
