/*
 * DriveProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */
#include <DriveProcess.h>


StateDriveControl driveState = INIT_DRIVE;

bool driveProcess(Event* ev)
	{
	static StateDriveControl oldState = INIT_DRIVE;
	//****************************************************************************
	switch(driveState){                  // this is the transition state machine
		//-----------------------------------------------------------------------
		case INIT_DRIVE:
			if (ev->id == E_MODE_D){
				carState = DRIVE;
			}

			if (ev->id == E_MODE_P){
				carState = DRIVE;
			}
				break;
		//-----------------------------------------------------------------------
		case PARK:
			if (ev->id == E_CONTACT_OFF){
				carState = OFF;
			}
			if (ev->id == E_MODE_D){
				carState = DRIVE;
			}
			if (ev->id == E_MODE_R){
				carState = REVERSE;
			}
			if (ev->id == E_MODE_N){
				carState = NEUTRAL;
			}
			break;
		//-----------------------------------------------------------------------
		case REVERSE:
			if (ev->id == E_CONTACT_OFF){
				carState = OFF;
			}
			if (ev->id == E_MODE_P){
				carState = PARK;
			}
			if (ev->id == E_MODE_N){
				carState = NEUTRAL;
			}
			break;
		//-----------------------------------------------------------------------
		case NEUTRAL:
			if (ev->id == E_CONTACT_OFF){
				carState = OFF;
			}
			if (ev->id == E_MODE_P){
				carState = PARK;
			}
			if (ev->id == E_MODE_R){
				carState = REVERSE;
			}
			if (ev->id == E_MODE_D){
				carState = DRIVE;
			}

			break;
		//-----------------------------------------------------------------------
		case DRIVE:
			if (ev->id == E_CONTACT_OFF){
				carState = OFF;
			}
			if (ev->id == E_MODE_N){
				carState = NEUTRAL;
			}
			if (ev->id == E_TEMPOMAT_ON){
				carState = TEMPOMAT;
			}


			break;

	}
	//****************************************************************************
	if(driveState == oldState){			// this is the loop actions
		return false;
	}

	oldState = driveState;
	//****************************************************************************
	switch(driveState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case CAR_INIT:
			break;
		//-----------------------------------------------------------------------
		case OFF:
			XF_post(lightControl, E_LIGHT_OFF, 0);
			break;
		//-----------------------------------------------------------------------
		case PARK:
			XF_post(motorControl, E_MOTOR_GEAR0, 0);
			break;
		//-----------------------------------------------------------------------
		case REVERSE:
			XF_post(motorControl, E_MOTOR_GEAR0, 0);
			break;
		//-----------------------------------------------------------------------
		case NEUTRAL:
			XF_post(motorControl, E_MOTOR_NEUTRAL, 0);
			break;
		//-----------------------------------------------------------------------
		case DRIVE:
			if (memOldState != TEMPOMAT){
				XF_post(motorControl, E_MOTOR_GEAR0, 0);
			}
			break;
		//-----------------------------------------------------------------------
		case TEMPOMAT:

			break;
	}
	return true;
}
