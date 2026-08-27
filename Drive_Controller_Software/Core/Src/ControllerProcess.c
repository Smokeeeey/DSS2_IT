/*
 * ControllerProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */
#include <ControllerProcess.h>


StateController controllerState = INIT_CONTROL;
//uint8_t gearCounter = OD_RAM.x203E_gearPos;

bool controllerProcess(Event* ev)
	{
	static StateController oldState = INIT_CONTROL;
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

				//Interdit de changer de vitesse
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
				if (handBreak())
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
				if (handBreak())
				{
					break;
				}




				XF_post(controllerProcess, E_MODE_G, 50);



				break;
			//-----------------------------------------------------------------------
			case MODE_D:
				//Check si frein a main
				if (handBreak())
				{
					break;
				}
				//Check si on veux changer de vitesse
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
			//Coupe le mode torque
			XF_post(driveProcess, E_STOP_DRIVE, 10);


			XF_post(controllerProcess, E_MODE_P, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_R:
			//Relance le mode drive
			XF_post(driveProcess, E_MOVE_DRIVE, 10);

			XF_post(controllerProcess, E_MODE_R, 10);
			break;
		//-----------------------------------------------------------------------
		case MODE_G:
			//gear change sequence
			OD_RAM.x203E_gearPos = OD_RAM.x203E_gearPos % 2;
			if (OD_RAM.x203E_gearPos == 0)
			{
				nextGear();
			}else if (OD_RAM.x203E_gearPos == 1)
			{
				nextGear();
			}
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

bool handBreak()
{
	//lire pin gpio HB
	Car_1.handBreakSwitch = HAL_GPIO_ReadPin(External_Btn_GPIO_Port, External_Btn_Pin);
	if (Car_1.handBreakSwitch)
	{
		XF_post(controllerProcess, E_MODE_P, 10);
		return true;
	}
	return false;
}

//void changingGear()
//{
//	if (OD_RAM.x203D_gearTransition == 1)
//	{
//		XF_post(controllerProcess, E_MODE_G, 10);
//		break;
//	}
//}

void nextGear()
{
	//incrementer la gear de 1
	OD_RAM.x203E_gearPos++;
	//send to OD
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_GEARPOS]);

	//check if transition fini
	if (OD_RAM.x203D_gearTransition == 0)
	{
		XF_post(controllerProcess, E_MODE_D, 10);
	}
}

void transformValue()
{
	Car_1.speed = OD_RAM.x2031_driveMotorSpeed / reductionDrive;
}

void transmitValue()
{

}




