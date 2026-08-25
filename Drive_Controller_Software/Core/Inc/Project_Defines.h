/*
 * JS_Defines.h
 *
 *  Created on: August 18, 2026
 *      Author: loic.pinuela
 */

#ifndef SRC_PROJECT_DEFINES_H_
#define SRC_PROJECT_DEFINES_H_



//---------------------------Includes---------------------------

#include "CO_app_STM32.h" // Includes the ported CANopen files
#include "OD.h"
#include "xf.h"
#include "flash.h"
#include "stdbool.h"
#include "DriveProcess.h"
#include "SteeringProcess.h"

//---------------------------Defines---------------------------


//1000 = 100%
#define powerMotor 600

//---------------------Emplacements Flash---------------------



//---------------------------ENUM---------------------------


typedef enum {
	INIT_DRIVE,
	PARK,
	REVERSE,
	GEARCHANGE,
	DRIVE,
	ERROR_DRIVE
}StateDriveControl;

typedef enum{
	E_INIT_DRIVE = 1,			// must be not 0 !!!
	E_MODE_P,
	E_MODE_R,
	E_MODE_G,
	E_MODE_D,
	E_ERROR
}EventStateDriveControl;

//***


typedef enum {
	INIT_STEERING		= 10,
	FAULT_RESET			= 20,
	SWITCH_ON_DISABLED	= 30,
	SHUTDOWN			= 40,
	SWITCH_ON			= 50,
	STEERING_ENABLE		= 60,
	FIND0				= 70,
	REACHED				= 80,
	MOVE				= 90
}StateSteeringControl;

typedef enum{
	E_INIT_STEERING = 1,			// must be not 0 !!!
	E_FAULT_RESET,
	E_SWITCH_ON_DISABLED,
	E_SHUTDOWN,
	E_SWITCH_ON,
	E_STEERING_ENABLE,
	E_FIND0,
	E_REACHED,
	E_MOVE
}EventStateSteeringControl;

//---------------------------Structures---------------------------

typedef struct{
	int16_t speed;
	int16_t rpm;
	bool r2d;
}Car_ST;
extern Car_ST Car_1;

typedef struct {
	int16_t position;
}Steering_ST;
extern Steering_ST Steering_1;

//---------------------------CanOpen---------------------------

extern CANopenNodeSTM32 canOpenNodeSTM32;

//---------------------------Variables GLobales---------------------------
extern bool lectureADC;
extern uint32_t adc_ch6; // Channel 6 of the ADC
extern uint32_t adc_ch8; // Channel 8 of the ADC
extern bool switch_Nunchuck_Joystick;
extern I2C_HandleTypeDef *phi2c1;

#endif /* SRC_PROJECT_DEFINES_H_ */
