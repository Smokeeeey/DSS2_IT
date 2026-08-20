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
				driveState = DRIVE;
			}

			if (ev->id == E_MODE_P){
				driveState = PARK;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
				break;
		//-----------------------------------------------------------------------
		case PARK:
			if (ev->id == E_MODE_G){
				driveState = GEARCHANGE;
			}
			if (ev->id == E_MODE_D){
				driveState = DRIVE;
			}
			if (ev->id == E_MODE_R){
				driveState = REVERSE;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case REVERSE:
			if (ev->id == E_MODE_D){
				driveState = DRIVE;
			}
			if (ev->id == E_MODE_P){
				driveState = PARK;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case DRIVE:
			if (ev->id == E_MODE_P){
				driveState = PARK;
			}
			if (ev->id == E_MODE_R){
				driveState = REVERSE;
			}
			if (ev->id == E_MODE_G){
				driveState = GEARCHANGE;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}

			break;
		//-----------------------------------------------------------------------
		case GEARCHANGE:
			if (ev->id == E_MODE_P){
				driveState = PARK;
			}
			if (ev->id == E_MODE_D){
				driveState = DRIVE;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
			break;

		//-----------------------------------------------------------------------
		case ERROR_DRIVE:

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
		case INIT_DRIVE:
			break;
		//-----------------------------------------------------------------------
		case PARK:
			break;
		//-----------------------------------------------------------------------
		case REVERSE:

			break;
		//-----------------------------------------------------------------------
		case GEARCHANGE:

			break;
		//-----------------------------------------------------------------------
		case DRIVE:
			XF_post(driveProcess, E_MODE_R, 0);
			break;
		//-----------------------------------------------------------------------
		case ERROR_DRIVE:

			break;
	}
	return true;
}



