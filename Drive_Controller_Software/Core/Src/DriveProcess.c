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
				driveState = MODE_D;
			}

			if (ev->id == E_MODE_P){
				driveState = MODE_P;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
				break;
		//-----------------------------------------------------------------------
		case MODE_P:
			if (ev->id == E_MODE_G){
				driveState = MODE_G;
			}
			if (ev->id == E_MODE_D){
				driveState = MODE_D;
			}
			if (ev->id == E_MODE_R){
				driveState = MODE_R;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case MODE_R:
			if (ev->id == E_MODE_D){
				driveState = MODE_D;
			}
			if (ev->id == E_MODE_P){
				driveState = MODE_P;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case MODE_D:
			if (ev->id == E_MODE_P){
				driveState = MODE_P;
			}
			if (ev->id == E_MODE_R){
				driveState = MODE_R;
			}
			if (ev->id == E_MODE_G){
				driveState = MODE_G;
			}
			if (ev->id == E_ERROR){
				driveState = ERROR_DRIVE;
			}

			break;
		//-----------------------------------------------------------------------
		case MODE_G:
			if (ev->id == E_MODE_P){
				driveState = MODE_P;
			}
			if (ev->id == E_MODE_D){
				driveState = MODE_D;
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
		case MODE_P:
			break;
		//-----------------------------------------------------------------------
		case MODE_R:

			break;
		//-----------------------------------------------------------------------
		case MODE_G:

			break;
		//-----------------------------------------------------------------------
		case MODE_D:
			XF_post(driveProcess, E_MODE_R, 0);
			break;
		//-----------------------------------------------------------------------
		case ERROR_DRIVE:

			break;
	}
	return true;
}



