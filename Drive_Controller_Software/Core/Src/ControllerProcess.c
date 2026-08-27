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

		//-----------------------------------------------------------------------
		case INIT_DRIVE:
			break;
		//-----------------------------------------------------------------------
		case MODE_P:

			//Interdit de changer de vitesse
			if (Car_1.handBreakSwitch == false && OD_RAM.x203D_gearTransition == 0)
			{
				XF_post(controllerProcess, E_MODE_D, 10);
			}

			break;
		//-----------------------------------------------------------------------
		case MODE_R:
			handBreak();
			if (OD_RAM.x2020_joystick[3] == 1)
			{
				XF_post(controllerProcess, E_MODE_G, 0);
			}

			break;
		//-----------------------------------------------------------------------
		case MODE_G:
			handBreak();

			Car_1.gearCounter= Car_1.gearCounter % 2;
			if (Car_1.gearCounter == 0)
			{
				//transmit to od gear 1
			}else if (Car_1.gearCounter == 1)
			{
				//gear N
			}else
			{
				//gear 2
			}

			break;
		//-----------------------------------------------------------------------
		case MODE_D:

			//Check si frein a main
			handBreak();

			//Check si on veux changer de vitesse
			if (OD_RAM.x2020_joystick[3] == 1)
			{
				XF_post(controllerProcess, E_MODE_G, 0);
			}


			XF_post(controllerProcess, E_MODE_D, 10);

			break;
		//-----------------------------------------------------------------------
		case ERROR_CONTOL:

			break;


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
			//Coupe le mode torque
			XF_post(driveProcess, E_STOP_DRIVE, 10);


			XF_post(controllerProcess, E_MODE_P, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_R:
			XF_post(controllerProcess, E_MODE_R, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_G:
			XF_post(controllerProcess, E_MODE_G, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_D:
			//Relance le mode drive
			XF_post(driveProcess, E_MOVE_DRIVE, 10);

			XF_post(controllerProcess, E_MODE_D, 10);
			break;
		//-----------------------------------------------------------------------
		case ERROR_CONTOL:
			XF_post(controllerProcess, E_ERROR, 10);
			break;
	}
	return true;
}


/* ======== Functions ========== */

void handBreak()
{
	if (Car_1.handBreakSwitch)
	{
		XF_post(controllerProcess, E_MODE_P, 10);
	}
}

void changingGear()
{
	if (OD_RAM.x203D_gearTransition == 1)
	{
		XF_post(controllerProcess, E_MODE_G, 10);
	}
}

void transformValue()
{
	Car_1.speed = OD_RAM.x2031_driveMotorSpeed / reductionDrive;
}

void transmitValue()
{

}




