/*
* @Author: Alexis Lutun
* @Date:   2016-05-14 13:32:38
* @Last Modified by:   Alexis Lutun
* @Last Modified time: 2016-05-14 16:39:07
*/

#include "SwitchMode.h"
#include "SoundAnalysis.h"
#include "Arduino.h"

/**************************************************************/
/*                         PUBLIC DATA                        */
/**************************************************************/

switchInfo_s switchInfo;
	
/**************************************************************/
/*                         PRIVATE DATA                       */
/**************************************************************/

/**************************************************************/
/*                         PUBLIC FUNCTIONS                   */
/**************************************************************/

void SwitchModeInit()
{
	switchInfo.timerSecond           = TIMER_ONE_SECOND_RESET;  
	switchInfo.timerMs               = TIMER_MS_RESET;  
	switchInfo.currentMode           = MODE_NORMAL;
	switchInfo.currentSoundState     = SOUND_NORMAL_STATE;
	switchInfo.timerSecondSoundLevel = TIMER_ONE_SECOND_RESET;
}

void SwitchModeTick()
{
	short  trash;

	if (updateTimer() == 1)
	{
		updateSoundLevel();
		checkIfModeShouldSwitch();
	}
	else
	{
		GetSoundLevel((uint16_t*)&trash, (uint16_t*)&trash);
	}
}


char getActualMode()
{
	return(switchInfo.currentMode);	
}
/**************************************************************/
/*                         PRIVATE FUNCTIONS                  */
/**************************************************************/

static void switchToNewMode(char newMode)
{
	switchInfo.timerSecondSoundLevel = TIMER_ONE_SECOND_RESET;
	switchInfo.currentMode           = newMode;	
}

static void checkIfModeShouldSwitch()
{
	if(switchInfo.currentSoundState == switchInfo.currentMode)
		return;

	if(switchInfo.currentMode == MODE_NORMAL)
	{
		SwitchModeWhenNormal();
	}
	else if(switchInfo.currentMode == MODE_PARTY)
	{
		SwitchModeWhenParty();		
	}
	else if(switchInfo.currentMode == MODE_OFF)
	{
		SwitchModeWhenOff();		
	}
}	

static void SwitchModeWhenNormal()
{
	if (switchInfo.currentSoundState == SOUND_PARTY_LEVEL && switchInfo.timerSecondSoundLevel > 0x05)
		switchToNewMode(MODE_PARTY);
	if (switchInfo.currentSoundState == SOUND_OFF_STATE && switchInfo.timerSecondSoundLevel > 0x0A)
		switchToNewMode(MODE_OFF);
}

static void SwitchModeWhenParty()
{
	if (switchInfo.currentSoundState == SOUND_NORMAL_STATE && switchInfo.timerSecondSoundLevel > 0x1E)
		switchToNewMode(MODE_NORMAL);
	if (switchInfo.currentSoundState == SOUND_OFF_STATE && switchInfo.timerSecondSoundLevel > 0x0A)
		switchToNewMode(MODE_NORMAL);
}

static void SwitchModeWhenOff()
{
	if (switchInfo.currentSoundState == SOUND_NORMAL_STATE && switchInfo.timerSecondSoundLevel > 0x0A)
		switchToNewMode(MODE_NORMAL);
	if (switchInfo.currentSoundState == SOUND_PARTY_LEVEL && switchInfo.timerSecondSoundLevel > 0x02)
		switchToNewMode(MODE_NORMAL);
}

static void updateSoundLevel()
{
	char soundlevel;
	char soundlevelState;
	short soundAvg;

	soundlevel = GetSoundLevel((uint16_t*)&soundAvg, (uint16_t*)&soundAvg);
	if(soundlevel <= SOUND_OFF_LEVEL)
	{
		soundlevelState = SOUND_OFF_STATE;
		Serial.print(soundlevel);
		Serial.println("  : SOUND LEVEL IS OFF");
	}
	else if(soundlevel > SOUND_OFF_LEVEL && soundlevel < SOUND_PARTY_LEVEL)
	{
		soundlevelState = SOUND_NORMAL_STATE;
		Serial.print(soundlevel);
		Serial.println("  : SOUND LEVEL IS NORMAL");
	}
	else if(soundlevel >= SOUND_PARTY_LEVEL)
	{
		soundlevelState = SOUND_PARTY_STATE;
		Serial.print(soundlevel);
		Serial.println("  : SOUND LEVEL IS PARTY");
	}

	if(soundlevelState != switchInfo.currentSoundState)
	{
		switchInfo.currentSoundState = soundlevel;
		switchInfo.timerSecondSoundLevel = TIMER_ONE_SECOND_RESET;			
	}		
}

static char updateTimer()
{
  	switchInfo.timerMs++;
  	if (switchInfo.timerMs > TIMER_MS_ONE_SECOND)
	{
		switchInfo.timerMs = TIMER_MS_RESET;
		switchInfo.timerSecond += TIMER_ONE_SECOND;
		switchInfo.timerSecondSoundLevel += TIMER_ONE_SECOND;

		return (1);
	}	
	return (0);
}
