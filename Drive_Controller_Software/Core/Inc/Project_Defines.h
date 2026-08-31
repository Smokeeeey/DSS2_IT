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
#include "SteeringProcess.h"
#include "DriveProcess.h"

//---------------------------Defines---------------------------


//1000 = 100%
#define powerMotor 				1000
#define maskStatus 				0x006F

//Mode of operation
#define torqueMode 				0x0A
#define homingMode 				0x06
#define profilePositionMode 	0x01

//Control word
#define newSetpointImediatly 	0x3F
#define resetSetpoint 			0x2F
#define homingStartOperation 	0x1F
#define enableOperation 		0x0F
#define faultReset 				0x80
#define switchOnDisabled 		0x06
#define shutDown				0x07
#define switchOn				0x0F

//Values
#define toCenterPosition 		750		//A voir combien il faut pour etre au centre en partant du 0 du homing
#define maxSteering				750
#define reductionDrive			200		// = reduction / (π × diam roue × 60 / 1000)​




//---------------------Emplacements Flash---------------------



//---------------------------ENUM---------------------------

//------- Control controller-----

typedef enum {
	INIT_CONTROL				= 10,
	MODE_P						= 20,
	MODE_R						= 30,
	MODE_G						= 40,
	MODE_D						= 50,
	ERROR_CONTOL				= 999
}StateController;

typedef enum{
	E_INIT_CONTROL = 1,			// must be not 0 !!!
	E_MODE_P,
	E_MODE_R,
	E_MODE_G,
	E_MODE_D,
	E_ERROR
}EventStateController;

//------- Steering controller------


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
	MOVE				= 90,
	WAIT 				= 100
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
	E_MOVE,
	E_WAIT
}EventStateSteeringControl;

//------- Drive controller-------

typedef enum {
	INIT_D					= 1,
	INIT_DRIVE				= 10,
	FAULT_RESET_D			= 20,
	SWITCH_ON_DISABLED_D	= 30,
	SHUTDOWN_D				= 40,
	SWITCH_ON_D				= 50,
	DRIVE_ENABLE			= 60,
	STOP_DRIVE				= 70,
	MOVE_DRIVE				= 80,
}StateDriveControl;

typedef enum{
	E_INIT_D			= 1,
	E_INIT_DRIVE,
	E_FAULT_RESET_D,
	E_SWITCH_ON_DISABLED_D,
	E_SHUTDOWN_D,
	E_SWITCH_ON_D,
	E_DRIVE_ENABLE,
	E_STOP_DRIVE,
	E_MOVE_DRIVE
}EventStateDriveControl;

//---------------------------Structures---------------------------

typedef struct{
	int32_t positionSteering;
	int16_t torqueDrive;
	int16_t speed;
	int8_t  gearPos;
	bool handBreakSwitch;
	//uint8_t oldinTransition;
}Car_ST;
extern Car_ST Car_1;

//---------------------------CanOpen---------------------------

extern CANopenNodeSTM32 canOpenNodeSTM32;

//------------------------ID CanOpen---------------------------

//Transmit
#define  ID_DRIVE_TORQUE 			0
#define  ID_DRIVE_CONTROL_WORD 		1
#define  ID_DRIVE_MODE 				2
#define  ID_STEERING_MODE			3
#define  ID_STEERING_TORQUE			4
#define  ID_STEERING_STATE_MACHINE	5
#define  ID_GEARPOS					6
#define  ID_STEERING_CONTROL_WORD	7
#define  ID_STEERING_POSITION		8
#define  ID_SPEED					9






//---------------------------Variables GLobales---------------------------
extern bool lectureADC;
extern uint32_t adc_ch6; // Channel 6 of the ADC
extern uint32_t adc_ch8; // Channel 8 of the ADC
extern bool switch_Nunchuck_Joystick;
extern I2C_HandleTypeDef *phi2c1;

#endif /* SRC_PROJECT_DEFINES_H_ */
