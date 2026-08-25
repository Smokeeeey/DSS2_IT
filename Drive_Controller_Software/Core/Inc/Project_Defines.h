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
#define maskStatus 0x006F

//---------------------Emplacements Flash---------------------



//---------------------------ENUM---------------------------


typedef enum {
	INIT_DRIVE					= 10,
	FAULT_RESET_DRIVE			= 20,
	SWITCH_ON_DISABLED_DRIVE	= 30,
	SHUTDOWN_DRIVE				= 40,
	SWITCH_ON_DRIVE				= 50,
	DRIVE_ENABLE				= 60,
	MODE_P						= 70,
	MODE_R						= 80,
	MODE_G						= 90,
	MODE_D						= 100,
	ERROR_DRIVE					= 999
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
	INIT				= 1,
	INIT_STEERING		= 10,
	FAULT_RESET			= 20,
	SWITCH_ON_DISABLED	= 30,
	SHUTDOWN			= 40,
	SWITCH_ON			= 50,
	STEERING_ENABLE		= 60,
	SINUS_MOVE          = 65,
	FIND0				= 70,
	REACHED				= 80,
	MOVE				= 90
}StateSteeringControl;

typedef enum{
	E_INIT			= 1,
	E_INIT_STEERING,
	E_FAULT_RESET,
	E_SWITCH_ON_DISABLED,
	E_SHUTDOWN,
	E_SWITCH_ON,
	E_STEERING_ENABLE,
	E_SINUS_MOVE,
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
