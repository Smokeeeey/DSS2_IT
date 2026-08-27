/*
 * ControllerProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */
#include <ControllerProcess.h>

StateController controllerState = INIT_CONTROL;
StateController oldState = INIT_CONTROL;

bool controllerProcess(Event* ev)
	{
	//static StateController oldState = INIT_CONTROL;
	static uint8_t oldTransition = 0;
	Car_1.handBreakSwitch = false;
	//****************************************************************************
	switch(controllerState){                  // this is the transition state machine
		//-----------------------------------------------------------------------
		case INIT_CONTROL:
			if (ev->id == E_INIT_CONTROL){
				controllerState = MODE_D;
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
		switch(controllerState){

			case INIT_CONTROL:
				break;
			//-----------------------------------------------------------------------
			case MODE_P:

				//don't allow gear change
				if (Car_1.handBreakSwitch == false && OD_RAM.x203D_gearTransition == 0)
				{
					XF_post(controllerProcess, E_MODE_D, 10);
				}else
				{
					XF_post(controllerProcess, E_MODE_P, 10);
				}

				break;
			//-----------------------------------------------------------------------
			case MODE_R:
				if (handBrake())
				{
					break;
				}
				if (OD_RAM.x2020_joystick[3] == 1)
				{
					XF_post(controllerProcess, E_MODE_G, 0);
				}else
				{
					XF_post(controllerProcess, E_MODE_R, 10);
				}

				break;
			//-----------------------------------------------------------------------
			case MODE_G:
				if (handBrake())
				{
					break;
				}else if (oldTransition != OD_RAM.x203D_gearTransition)				//continuously check if gear reached
				{
					oldTransition = OD_RAM.x203D_gearTransition;
					if (OD_RAM.x203D_gearTransition == 0)
					{
						XF_post(controllerProcess, E_MODE_D, 50);
					}else
					{
						XF_post(controllerProcess, E_MODE_G, 50);
					}
				}else
				{
					XF_post(controllerProcess, E_MODE_G, 50);
				}

				break;
			//-----------------------------------------------------------------------
			case MODE_D:
				//Check hand brake
				if (handBrake())
				{
					break;
				}
				//Check if gear change requested
				else if (OD_RAM.x2020_joystick[3] == 1)
				{
					XF_post(controllerProcess, E_MODE_G, 0);
				}else
				{
					XF_post(controllerProcess, E_MODE_D, 10);
				}

				break;
			//-----------------------------------------------------------------------
			case ERROR_CONTOL:

				break;

		}

		return false;
	}



	oldState = controllerState;
	//****************************************************************************
	switch(controllerState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT_CONTROL:
			break;
		//-----------------------------------------------------------------------
		case MODE_P:
			//cut torque
			XF_post(driveProcess, E_STOP_DRIVE, 0);


			XF_post(controllerProcess, E_MODE_P, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_R:
			//go back in drive
			XF_post(driveProcess, E_MOVE_DRIVE, 0);

			XF_post(controllerProcess, E_MODE_R, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_G:
			//no torque while in transition
			XF_post(driveProcess, E_STOP_DRIVE, 0);

			//gear change sequence
			OD_RAM.x203E_gearPos = OD_RAM.x203E_gearPos % 1;
			if (OD_RAM.x203E_gearPos == 0)
			{
				nextGear();
			}else if (OD_RAM.x203E_gearPos == 1)
			{
				nextGear();
			}

			XF_post(controllerProcess, E_MODE_G, 0);
			break;
		//-----------------------------------------------------------------------
		case MODE_D:
			//go back in drive
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

bool handBrake()
{
	//read gpio pin
	//Car_1.handBreakSwitch = HAL_GPIO_ReadPin(External_Btn_GPIO_Port, External_Btn_Pin);
	if (Car_1.handBreakSwitch)
	{
		XF_post(controllerProcess, E_MODE_P, 10);
		return true;
	}
	return false;
}


void nextGear()
{
	//increment gear
	OD_RAM.x203E_gearPos++;
	//send to OD
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_GEARPOS]);
}

void transformValue()
{
	Car_1.speed = OD_RAM.x2031_driveMotorSpeed / reductionDrive;
}

void transmitValue()
{

}




