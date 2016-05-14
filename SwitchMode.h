#ifndef _SWITCH_MODE_H_
#define _SWITCH_MODE_H_

/**************************************************************/
/*                        DEFINE & TYPEDEF                    */
/**************************************************************/

#define TIMER_MS_ONE_SECOND		0x50
#define TIMER_MS_RESET			0x00
#define TIMER_ONE_SECOND_RESET	0x00000000
#define TIMER_ONE_SECOND		0x00000001
#define TIMER_SECONE_MINUTE		0x00000E10
#define MINUTE_DELAY_SWITCH		0x01 // switch to 5 minute later

#define MODE_NORMAL				0x00
#define MODE_PARTY				0x01
#define MODE_OFF				0x02

#define SOUND_NORMAL_STATE		0x00
#define SOUND_PARTY_STATE		0x01
#define SOUND_OFF_STATE			0x02

#define SOUND_NORMAL_LEVEL		0x32
#define SOUND_PARTY_LEVEL		0x46
#define SOUND_OFF_LEVEL			0x1E // 0x030


typedef struct switchInfo_t	
{
  int 		timerSecond;
  char  	timerMs;
  char 	currentMode;
  char 	currentSoundState;
  int 		timerSecondSoundLevel;
}switchInfo_s;

/**************************************************************/
/*                        PUBLIC DATA                         */
/**************************************************************/

extern switchInfo_s switchInfo;

/**************************************************************/
/*                        PUBLIC FUNCTIONS                    */
/**************************************************************/

void SwitchModeTick();
void SwitchModeInit();
char getActualMode();

/**************************************************************/
/*                        PRIVATE FUNCTIONS                   */
/**************************************************************/

static void switchToNewMode(char newMode);
static void checkIfModeShouldSwitch();
static void SwitchModeWhenNormal();
static void SwitchModeWhenParty();
static void SwitchModeWhenOff();
static void updateSoundLevel();
static char updateTimer();


#endif