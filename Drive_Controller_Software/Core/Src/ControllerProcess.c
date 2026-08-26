/*
 * ControllerProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */
#include <ControllerProcess.h>


StateController controllerState = INIT_CONTROL;

bool controllerProcess(Event* ev)
	{
	static StateController oldState = INIT_CONTROL;
	//****************************************************************************
	switch(controllerState){                  // this is the transition state machine
		//-----------------------------------------------------------------------
		case INIT_DRIVE:
			if (ev->id == E_MODE_D){
				controllerState = MODE_D;
			}

			if (ev->id == E_MODE_P){
				controllerState = MODE_P;
			}
			if (ev->id == E_ERROR){
				controllerState = ERROR_CONTOL;
			}
				break;
		//-----------------------------------------------------------------------
		case MODE_P:
			if (ev->id == E_MODE_G){
				controllerState = MODE_G;
			}
			if (ev->id == E_MODE_D){
				controllerState = MODE_D;
			}
			if (ev->id == E_MODE_R){
				controllerState = MODE_R;
			}
			if (ev->id == E_ERROR){
				controllerState = ERROR_CONTOL;
			}
			break;
		//-----------------------------------------------------------------------
		case MODE_R:
			if (ev->id == E_MODE_D){
				controllerState = MODE_D;
			}
			if (ev->id == E_MODE_P){
				controllerState = MODE_P;
			}
			if (ev->id == E_ERROR){
				controllerState = ERROR_CONTOL;
			}
			break;
		//-----------------------------------------------------------------------
		case MODE_D:
			if (ev->id == E_MODE_P){
				controllerState = MODE_P;
			}
			if (ev->id == E_MODE_R){
				controllerState = MODE_R;
			}
			if (ev->id == E_MODE_G){
				controllerState = MODE_G;
			}
			if (ev->id == E_ERROR){
				controllerState = ERROR_CONTOL;
			}

			break;
		//-----------------------------------------------------------------------
		case MODE_G:
			if (ev->id == E_MODE_P){
				controllerState = MODE_P;
			}
			if (ev->id == E_MODE_D){
				controllerState = MODE_D;
			}
			if (ev->id == E_ERROR){
				controllerState = ERROR_CONTOL;
			}
			break;

		//-----------------------------------------------------------------------
		case ERROR_CONTOL:

			break;

	}
	//****************************************************************************
	if(controllerState == oldState){			// this is the loop actions
		return false;
	}

	oldState = controllerState;
	//****************************************************************************
	switch(controllerState){                  // this is the entry action state machine

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
			XF_post(controllerProcess, E_MODE_R, 0);
			break;
		//-----------------------------------------------------------------------
		case ERROR_CONTOL:

			break;
	}
	return true;
}



