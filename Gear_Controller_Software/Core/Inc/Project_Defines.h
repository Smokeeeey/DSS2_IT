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
#include "GearProcess.h"


//---------------------------Defines---------------------------

//if master
//#define CO_CONFIG_SDO_CLI CO_CONFIG_SDO_CLI_ENABLE // Mandatory to act as SDO client !!!
//#define CO_CONFIG_NMT (CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_GLOBAL_FLAG_TIMERNEXT|CO_CONFIG_NMT_MASTER)

//#define CAN_DEBUG(val) CO_TPDOsendRequest(val)
//#define CAN_DEBUG(val) ()

//---------------------------Values---------------------------

#define GEAR OD_RAM.x2000_gear
#define MAXPOS0 3900
#define MINPOS0 3700
#define MAXPOS1	1500
#define MINPOS1 1100
#define MAXN 3000
#define MINN 2700
#define ERRORTIME 400

//----------------------------Flash---------------------------

//#define ZEROLIMIT_ADR 8


//---------------------------ENUM---------------------------

typedef enum {
	E_INIT = 1,
	E_GOTO1 = 2,
	E_GOTO2 = 3,
	E_REACHED = 4,
//	E_GOTO_N = 5,
	E_GEAR_ERROR = 6,
}EventList;

typedef enum {
	INIT = 1,
	GO_TO1 = 2,
	GO_TO2 = 3,
	REACHED = 4,
//	GO_TO_N = 5,
	GEARERROR = 6,
}StateControl;

//---------------------------Structures---------------------------

typedef struct{
	int16_t position;		//exact pos
	bool in_error;
	//used for tests
	uint16_t gear1;
	uint16_t gear2;
	uint16_t gearN;
}Gear_ST;
extern Gear_ST gear;



//---------------------------CanOpen---------------------------

extern CANopenNodeSTM32 canOpenNodeSTM32;

//---------------------------Variables GLobales---------------------------
extern bool lectureADC;
extern I2C_HandleTypeDef *phi2c1;
extern DAC_HandleTypeDef hdac1;


#endif /* SRC_PROJECT_DEFINES_H_ */
