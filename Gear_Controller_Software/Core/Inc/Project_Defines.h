/*
 * JS_Defines.h
 *
 *  Created on: May 26, 2026
 *      Author: alessio.ciardo
 */

#ifndef SRC_PROJECT_DEFINES_H_
#define SRC_PROJECT_DEFINES_H_

//---------------------------Includes---------------------------

#include <GearProcess.h>
#include "CO_app_STM32.h" // Includes the ported CANopen files
#include "OD.h"
#include "xf.h"
#include "flash.h"
#include "stdbool.h"

//---------------------------Defines---------------------------

#define CO_CONFIG_SDO_CLI CO_CONFIG_SDO_CLI_ENABLE // Mandatory to act as SDO client !!!
#define CO_CONFIG_NMT (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_GLOBAL_FLAG_TIMERNEXT|CO_CONFIG_NMT_MASTER)


//---------------------------Values---------------------------
//#define NUNCHUCK_ADRR (0x52 << 1)
//#define MAX_JOYSTICK 905
//#define MIN_JOYSTICK 85
//#define MAX_NUNCHUCK 230
//#define MIN_NUNCHUCK 30
//#define COURSE_JOYSTICK 200
//
//#define TRESHOLD_NEW_VALUE 2
#define POS_GEAR_1 0
#define POS_GEAR_2 1

//----------------------------Flash---------------------------

#define ZEROLIMIT_ADR 8
#define NUNCHUCK_OFFSET_ADR 16
#define JOYSTICK_OFFSET_ADR 32
#define TRESHOLD_NEW_VALUE_ADR 48


//---------------------------ENUM---------------------------

typedef enum {
	E_INIT = 1,
	E_GEAR_ENGAGED = 2,
	E_GEAR_TRANSIT = 3,
	E_GEAR_ERROR = 4,
}EventList;

typedef enum {
	INIT = 1,
	ENGAGED = 2,
	TRANSITION = 3,
	GEARERROR = 4,
}StateControl;

//---------------------------Structures---------------------------

typedef struct{
	int16_t position;		//exact pos
	uint8_t actual_gear;	//gear num
	uint8_t gear_requested; //requested gear (depends on old gear)
	bool in_transition;		//is gear in between
	bool in_error;
	bool change_gear;  //if request from joy btn
}Gear_ST;
extern Gear_ST gear;


//---------------------------CanOpen---------------------------

extern CANopenNodeSTM32 canOpenNodeSTM32;

//---------------------------Variables GLobales---------------------------
extern bool lectureADC;
extern uint32_t adc_ch6; // Channel 6 of the ADC
extern uint32_t adc_ch8; // Channel 8 of the ADC
extern bool switch_Nunchuck_Joystick;
extern I2C_HandleTypeDef *phi2c1;

#endif /* SRC_PROJECT_DEFINES_H_ */
