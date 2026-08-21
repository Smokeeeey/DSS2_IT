/*
 * SteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <SteeringProcess.h>
#include <InitSteeringProcess.h>


StateSteeringControl steeringState = INIT_STEERING;
int16_t count = 0;
int32_t tempPosMotor = 0;

bool steeringProcess(Event* ev)
	{
	static StateSteeringControl oldState = INIT_STEERING;

	//****************************************************************************
	switch(steeringState){                  // this is the transition state machine
		//-----------------------------------------------------------------------
		case INIT_STEERING:
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
	if(steeringState == oldState){			// this is the loop actions

		switch(steeringState){

				//-----------------------------------------------------------------------
				case INIT_STEERING:
					if (initState == ETAPE4)
					{
						XF_post(steeringProcess, E_FIND0, 0);
					}
					break;
				//-----------------------------------------------------------------------
				case FIND0:

					//Check si moteur a bouge de 10 au moins
					if (OD_RAM.x203A_steeringMotorCurrentPosition >= 10 + tempPosMotor || OD_RAM.x203A_steeringMotorCurrentPosition <= 10 - tempPosMotor)
					{

					} else
					{
						HAL_Delay(1);

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

	oldState = steeringState;
	//****************************************************************************
	switch(steeringState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT_STEERING:
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
	//Stock pos motor
	tempPosMotor = OD_RAM.x203A_steeringMotorCurrentPosition;

	//Increase count
	count = count + (2 * 3.1416 / 8);

	//Mode 10 torque
	OD_RAM.x2036_steeringMode = 0x0A;

	//Envoie sinus
	OD_RAM.x2037_steeringTorque = sin(count);

	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
	HAL_Delay(50);
}




