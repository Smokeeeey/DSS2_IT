/*
 * SteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <SteeringProcess.h>


StateSteeringControl steeringState = INIT;
StateSteeringControl oldStateSteering = INIT;
float64_t count = 0.0f;
int32_t tempPosMotor = 0;
int32_t position0 = 0;
int8_t waitingMotorMove = 0;


bool steeringProcess(Event* ev)
	{


	//****************************************************************************
	switch(steeringState){                  // this is the transition state machine

		//-----------------------------------------------------------------------
		case INIT:

			if (ev->id == E_INIT_STEERING)
			{
				steeringState = INIT_STEERING;
			}

			break;
		//-----------------------------------------------------------------------
		case INIT_STEERING:

			if (ev->id == E_FAULT_RESET)
			{
				steeringState = FAULT_RESET;
			}
			else if (ev->id == E_SWITCH_ON_DISABLED)
			{
				steeringState = SWITCH_ON_DISABLED;
			}

			break;
		//-----------------------------------------------------------------------
		case FAULT_RESET:

		    if (ev->id == E_SWITCH_ON_DISABLED)
		    {
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
				case INIT:

					break;

				//-----------------------------------------------------------------------
				case INIT_STEERING:

				    break;
				//-----------------------------------------------------------------------
				case FAULT_RESET:

				    // Fault toujours présent ?
				    if (OD_RAM.x2039_steeringStatusWord & (1 << 3))
				    {
				        // On attend encore
				        XF_post(steeringProcess, E_FAULT_RESET, 50);
				    }
				    else
				    {
				        // Fault Reset réussi
				        XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 50);
				    }

				    break;

				//-----------------------------------------------------------------------
				case SWITCH_ON_DISABLED:

					if ((OD_RAM.x2039_steeringStatusWord & maskStatus) == 0x0021)
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

					if ((OD_RAM.x2039_steeringStatusWord & maskStatus) == 0x0023)
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
					if ((OD_RAM.x2039_steeringStatusWord & maskStatus) == 0x0027)
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

					//Le homing est déjà lancé
					if (OD_RAM.x2036_steeringMode == 0x06)
					{

					    // Démarrage du homing
					    OD_RAM.x2035_steeringControlWord = 0x001F;
					    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);

						// Homing terminé ?
						if (OD_RAM.x2039_steeringStatusWord & (1 << 12))
						{
							// Passage en Profile Position Mode
							OD_RAM.x2036_steeringMode = 0x01;
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

							// EPOS reste en Enable Operation
							OD_RAM.x2035_steeringControlWord = 0x000F;
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);

							//Revenir au milieu
							target_position(10000);
							OD_RAM.x2035_steeringControlWord = 0x3F;
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);


							// On a terminé le homing
							XF_post(steeringProcess, E_REACHED, 50);
						}
						else
						{
							// Homing toujours en cours
							XF_post(steeringProcess, E_FIND0, 50);
						}
						break;
					}


					// On attend de voir si le moteur a bougé
					if (waitingMotorMove)
					{

						int32_t currentPos = OD_RAM.x203A_steeringMotorCurrentPosition;

						// Le moteur a bougé d'au moins 10 ?
						if (currentPos >= tempPosMotor + 10 ||
						currentPos <= tempPosMotor - 10)
						{

							// Oui : le moteur a bien réagi à notre commande
							waitingMotorMove = false;

							// Passage en Homing Mode
							OD_RAM.x2036_steeringMode = 0x06;
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);


							// On revient surveiller le homing
							XF_post(steeringProcess, E_FIND0, 50);
						}
						else
						{

						    // Le moteur n'a pas encore assez bougé
						    sendSinus();

							// Le moteur n'a pas encore assez bougé.
							// On attend encore une nouvelle position.
							XF_post(steeringProcess, E_FIND0, 1);
						}

						break;

					}

					// Première exécution, mémoriser la position
					tempPosMotor = OD_RAM.x203A_steeringMotorCurrentPosition;

					// Envoyer la commande de couple sinus
					sendSinus();

					// On attend que l'EPOS ait eu le temps de bouger
					waitingMotorMove = true;
					XF_post(steeringProcess, E_FIND0, 1);

					break;


				//-----------------------------------------------------------------------
				case REACHED:

					//Remets sur 0 l'envoi
					OD_RAM.x2035_steeringControlWord = 0x2F;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);

				    // Ici le moteur est homé
				    // et déjà revenu en Profile Position Mode

					if (OD_RAM.x2020_joystick[0] != 0)
					{
						XF_post(steeringProcess, E_MOVE, 50);
					}


					break;
				//-----------------------------------------------------------------------
				case MOVE:

					// Regle de 3
					// Joy			|0		|  joy[posx]	| 100
					// Moteur		|pos0	|    target		| 10000

					target_position((OD_RAM.x2020_joystick[0] * 100));

					if (OD_RAM.x203A_steeringMotorCurrentPosition == OD_RAM.x2020_joystick[0] * 100)
					{
						XF_post(steeringProcess, E_REACHED, 50);
					}

					break;
			}

		return false;
	}

	oldStateSteering = steeringState;
	//****************************************************************************
	switch(steeringState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT:


			break;

		//-----------------------------------------------------------------------
		case INIT_STEERING:

			//Reveil de l'epos vu qu'on est master
			CO_NMT_sendCommand(canOpenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL,2);

			//Envoyer pour faire un fault reset
		    XF_post(steeringProcess, E_FAULT_RESET, 1000);
			break;
		//-----------------------------------------------------------------------
		case FAULT_RESET:

		    // Fault Reset
		    OD_RAM.x2035_steeringControlWord = 0x0080;
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);
		    XF_post(steeringProcess, E_FAULT_RESET, 200);

		    break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED:
			OD_RAM.x2035_steeringControlWord = 0x0006; //6
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);
			XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 200);
			break;
		//-----------------------------------------------------------------------
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

			count = 0.0f;

			XF_post(steeringProcess, E_FIND0, 200);
			break;
		//-----------------------------------------------------------------------
		case FIND0:
			XF_post(steeringProcess, E_FIND0, 200);
			break;
		//-----------------------------------------------------------------------
		case REACHED:
			break;
		//-----------------------------------------------------------------------
		case MOVE:

			break;
	}
	return true;
}


/* ======== Functions ========== */



void target_position(int32_t target){


	//Write the steering position in dico
	OD_RAM.x2038_steeringPosition = target;
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);

	//2F = 0
	//3F = 1

	//Envoi la pos
	OD_RAM.x2035_steeringControlWord = 0x3F;
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);

}

void sendSinus()
{
	//Increase count
	count = count + (2.0f * 3.1416f / 8.0f);

	//Mode 10 torque
	OD_RAM.x2036_steeringMode = 0x0A;
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

	//Envoie sinus
	OD_RAM.x2037_steeringTorque = (int16_t) (sin(count) * powerMotor);
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[4]);
}




