#include "Arduino.h"
#include "SoundAnalysis.h"

#include <FHT.h>

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

/**************************************************************/
/*                        PRIVATE DATA                        */
/**************************************************************/

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void InitSoundAnalysis()
{
  // Because we power Sound Detector with 3.3 Volts
  analogReference(EXTERNAL);
  // Init ADC (Pin A0 Used here)
  //TIMSK0 = 0x00; 
	// ADCSRA = 0xE5; 
	// ADMUX  = 0x40; 
	// DIDR0  = 0x01; 
	// TODO Add a "Debug Define to display data"
	//Serial.begin(115200);
}


void ProcessSoundAnalysis(int *soundMeasure)
{
  uint8_t i;
  cli();  
  SoundAcquisition();
  SoundProcessing();
  // TODO Add a "Debug Define to display data"
  //SoundDisplay();

  #if OCTAVE == 1
  for(i = 0; i < FHT_OCTAVE_NUMBER; i++)
  {
    soundMeasure[i] = fht_oct_out[i];
  }
  #endif

  #if LOG_OUT == 1
  for(i = 0; i < FHT_SAMPLE_NUMBER; i++)
  {
    soundMeasure[i] = fht_log_out[i];
  }
  #endif

  
  sei();
}

uint8_t MeanSoundAnalysis()
{
  uint8_t i;
  uint16_t total = 0;

  SoundAcquisition();
  SoundProcessing();
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
  // for(i = 0; i < FHT_HALF_SAMPLE_NUMBER; i++)
  // {
  //   total += fht_log_out[i];
  // }
  // total = total / FHT_HALF_SAMPLE_NUMBER;
  for(i = 0; i < FHT_HALF_SAMPLE_NUMBER; i++)
  {
    total += fht_log_out[2*i+2];
  }
  total = total / FHT_HALF_SAMPLE_NUMBER;
  #endif

  


  return (total);
}

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void SoundAcquisition()
{
/*  uint8_t adcLow, adcHigh;
	int measure;
	for (int i = 0 ; i < FHT_SAMPLE_NUMBER ; i++) 
  { 
    while(!(ADCSRA & 0x10));
    ADCSRA = 0xF5;
    adcLow = ADCL; 
    adcHigh = ADCH;
    measure = (adcHigh << 8) |  adcLow;
    //measure = (ADCH << 8) |  ADCL;
    measure -= 0x0200; 	// form into a signed int
    measure <<= 6; 		// form into a 16b signed int
    fht_input[i] = measure; 
  }*/
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

  cli();
  for (int i = 0 ; i < FHT_SAMPLE_NUMBER ; i++)
  {
      fht_input[i] = analogRead(0) - 512;
  }  
  sei();

/*  fht_window();                                               // Window the data for better frequency response.
  fht_reorder();                                              // Reorder the data before doing the fht.
  fht_run();                                                  // Process the data in the fht.
  fht_mag_log();*/
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
  Serial.write(fht_log_out, FHT_HALF_SAMPLE_NUMBER); 
  //Serial.write(fht_oct_out, FHT_HALF_SAMPLE_NUMBER);

  // #if OCTAVE == 1
  // uint8_t i;
  // for(i = 0; i < FHT_OCTAVE_NUMBER; i++)
  // {
  //   Serial.print("FHT ");
  //   Serial.print(i);
  //   Serial.print(" = ");
  //   Serial.println(fht_oct_out[i]);
  // }
  // #endif

  // #if LOG_OUT == 1
  // uint8_t i;
  // for(i = 0; i < FHT_SAMPLE_NUMBER; i++)
  // {
  //   Serial.print("FHT ");
  //   Serial.print(i);
  //   Serial.print(" = ");
  //   Serial.println(fht_log_out[i]);
  // }
  // #endif
}
