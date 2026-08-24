/*
 * SteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <SteeringProcess.h>


StateSteeringControl steeringState = INIT_STEERING;
StateSteeringControl oldStateSteering = INIT_STEERING;
int16_t count = 0;
int32_t tempPosMotor = 0;


bool steeringProcess(Event* ev)
	{


	//****************************************************************************
	switch(steeringState){                  // this is the transition state machine
		//-----------------------------------------------------------------------
		case INIT_STEERING:
			if (ev->id == E_SWITCH_ON_DISABLED){
				steeringState = SWITCH_ON_DISABLED;
			}
				break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED:
			if (ev->id == E_SHUTDOWN){
				steeringState = SHUTDOWN;
			}
				break;
		//-----------------------------------------------------------------------
		case SHUTDOWN:
			if (ev->id == E_SWITCH_ON){
				steeringState = SWITCH_ON;
			}
				break;
		//-----------------------------------------------------------------------
		case SWITCH_ON:
			if (ev->id == E_STEERING_ENABLE){
				steeringState = STEERING_ENABLE;
			}
				break;
		//-----------------------------------------------------------------------
		case STEERING_ENABLE:
			if (ev->id == E_FIND0){
				steeringState = FIND0;
			}
				break;
		//-----------------------------------------------------------------------
		case FIND0:
			if (ev->id == E_REACHED){
				steeringState = REACHED;
			}
			break;
		//-----------------------------------------------------------------------
		case REACHED:
			if (ev->id == E_MOVE){
				steeringState = MOVE;
			}
			break;
		//-----------------------------------------------------------------------
		case MOVE:
			if (ev->id == E_REACHED){
				steeringState = REACHED;
			}
			break;
	}
	//****************************************************************************
	if(steeringState == oldStateSteering){			// this is the loop actions

		switch(steeringState){

				//-----------------------------------------------------------------------
				case INIT_STEERING:

					//Reveil de l'epos vu qu'on est master
					CO_NMT_sendCommand(canOpenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL,2);

					if ((OD_RAM.x2039_steeringStatusWord & 0x006F) == 0x0040)
					{
						XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 100);
					}
					else
					{
						XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 100);
					}

					break;

				//-----------------------------------------------------------------------
				case SWITCH_ON_DISABLED:

					if ((OD_RAM.x2039_steeringStatusWord & 0x006F) == 0x0021)
					{
						XF_post(steeringProcess, E_SHUTDOWN, 100);
					}
					else
					{
						XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 100);
					}

					break;
				//-----------------------------------------------------------------------
				case SHUTDOWN:

					if ((OD_RAM.x2039_steeringStatusWord & 0x006F) == 0x0023)
					{
						XF_post(steeringProcess, E_SWITCH_ON, 100);
					}
					else
					{
						XF_post(steeringProcess, E_SHUTDOWN, 100);
					}

					break;
				//-----------------------------------------------------------------------
				case SWITCH_ON:
					if ((OD_RAM.x2039_steeringStatusWord & 0x006F) == 0x0027)
					{
						XF_post(steeringProcess, E_STEERING_ENABLE, 100);
					}
					else
					{
						XF_post(steeringProcess, E_SWITCH_ON, 100);
					}

					break;
				//-----------------------------------------------------------------------
				case STEERING_ENABLE:


					break;

				//-----------------------------------------------------------------------
				case FIND0:

					//Empeche la boucle pendant le homming
					if (OD_RAM.x2036_steeringMode == 0x06){
						if (OD_RAM.x2039_steeringStatusWord == 0x0C){
							XF_post(steeringProcess, E_REACHED, 0);
						}
						XF_post(steeringProcess, E_FIND0, 50);

						break;
					}

					//Stock pos motor
					tempPosMotor = OD_RAM.x203A_steeringMotorCurrentPosition;

					//Sequence for the sinus
					sendSinus();

					//Check si moteur a bouge de 10 au moins
					if (OD_RAM.x203A_steeringMotorCurrentPosition >= tempPosMotor + 10 || OD_RAM.x203A_steeringMotorCurrentPosition <= tempPosMotor - 10)
					{
						//Mode 6 homming
						OD_RAM.x2036_steeringMode = 0x06;
						//Envoie sur le can
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);

					} else
					{
						HAL_Delay(1);
						sendSinus();
					}


					XF_post(steeringProcess, E_REACHED, 0);
					break;
				//-----------------------------------------------------------------------
				case REACHED:

					XF_post(steeringProcess, E_MOVE, 0);

					break;
				//-----------------------------------------------------------------------
				case MOVE:

					XF_post(steeringProcess, E_REACHED, 0);
					break;
			}

		return false;
	}

	oldStateSteering = steeringState;
	//****************************************************************************
	switch(steeringState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT_STEERING:
			break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED:
			OD_RAM.x2035_steeringControlWord = 0x0006; //6
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);
			XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 200);
			break;
		case SHUTDOWN:
			OD_RAM.x2035_steeringControlWord = 0x0007; //7
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);
			XF_post(steeringProcess, E_SHUTDOWN, 200);
			break;
		//-----------------------------------------------------------------------
		case SWITCH_ON:
			OD_RAM.x2035_steeringControlWord = 0x000F; //F
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);
			XF_post(steeringProcess, E_SWITCH_ON, 200);
			break;
		//-----------------------------------------------------------------------
		case STEERING_ENABLE:
			break;
		//-----------------------------------------------------------------------
		case FIND0:
			break;
		//-----------------------------------------------------------------------
		case REACHED:
			break;
		//-----------------------------------------------------------------------
		case MOVE:
			//target_position();

			break;
	}
	return true;
}


/* ======== Functions ========== */



void target_position(int32_t target){


	//Write the steering position in dico
	OD_RAM.x2038_steeringPosition = target;

	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);

}

void sendSinus()
{
	//Increase count
	count = count + (2 * 3.1416 / 8);

	//Mode 10 torque
	OD_RAM.x2036_steeringMode = 0x0A;

	//Envoie sinus
	OD_RAM.x2037_steeringTorque = (int16_t) sin(count) * powerMotor;

	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
	HAL_Delay(50);
}




