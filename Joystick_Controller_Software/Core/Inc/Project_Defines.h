/*
 * JS_Defines.h
 *
 *  Created on: May 26, 2026
 *      Author: alessio.ciardo
 */

#ifndef SRC_PROJECT_DEFINES_H_
#define SRC_PROJECT_DEFINES_H_

//---------------------------Includes---------------------------

#include "CO_app_STM32.h" // Includes the ported CANopen files
#include "OD.h"
#include "xf.h"
#include "flash.h"
#include "stdbool.h"
#include "JoystickProssess.h"
#include "NunchuckProcess.h"

//---------------------------Defines---------------------------

//not master
//#define CO_CONFIG_SDO_CLI CO_CONFIG_SDO_CLI_ENABLE // Mandatory to act as SDO client !!!
//#define CO_CONFIG_NMT (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_GLOBAL_FLAG_TIMERNEXT|CO_CONFIG_NMT_MASTER)

#define ZEROLIMIT_ADR 8
#define NUNCHUCK_OFFSET_ADR 16
#define JOYSTICK_OFFSET_ADR 24
#define TRESHOLD_NEW_VALUE_ADR 32

#define NUNCHUCK_ADRR (0x52 << 1)
#define MAX_JOYSTICK 905
#define MIN_JOYSTICK 85
#define MAX_NUNCHUCK 230
#define MIN_NUNCHUCK 30
#define COURSE_JOYSTICK 200

#define TRESHOLD_NEW_VALUE 2

//---------------------Emplacements Flash---------------------

#define POS0_ADDR 8
#define POS1_ADDR 16


//---------------------------ENUM---------------------------

typedef enum {
	E_INIT = 1,
	E_DEFAULT = 2,
	E_NON_USED = 3,
	E_SEND = 4,
	E_RECEIVE = 5
}EventList;

typedef enum {
	INIT = 1,
	DEFAULT = 2,
	NON_USED = 3,
	SEND = 4,
	RECEIVE = 5
}StateControl;

//---------------------------Structures---------------------------

typedef struct{
	int16_t x;
	int16_t y;
	bool zButton;
	bool cButton;
}Nunchuck_ST;
extern Nunchuck_ST Nunchuck_1;

typedef struct {
	int16_t x;
	int16_t y;
	bool button;
}Joystick;
extern Joystick js;

//---------------------------CanOpen---------------------------

extern CANopenNodeSTM32 canOpenNodeSTM32;

//---------------------------Variables GLobales---------------------------
extern bool lectureADC;
extern uint32_t adc_ch6; // Channel 6 of the ADC
extern uint32_t adc_ch8; // Channel 8 of the ADC
extern bool switch_Nunchuck_Joystick;
extern I2C_HandleTypeDef *phi2c1;

#endif /* SRC_PROJECT_DEFINES_H_ */
