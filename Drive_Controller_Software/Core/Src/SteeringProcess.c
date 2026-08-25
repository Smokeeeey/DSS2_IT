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
float64_t count = 1.0f;
int32_t tempPosMotor = 0;
int32_t position0 = 0;
int8_t waitingMotorMove = 0;

bool temp3264;
bool startHoming = true;


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

		    if (ev->id == E_SINUS_MOVE){
		        steeringState = SINUS_MOVE;
		    }

		    break;
		//-----------------------------------------------------------------------
		case SINUS_MOVE:

		    if (ev->id == E_FIND0)
		    {
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
				case SINUS_MOVE:

				    int32_t currentPos = OD_RAM.x203A_steeringMotorCurrentPosition;

				    // Le moteur a bougé d'au moins 10 ?
				    if (currentPos >= tempPosMotor + 150 ||
				        currentPos <= tempPosMotor - 150)
				    {
				        // Le moteur a suffisamment bougé
				        waitingMotorMove = false;

				        // Petit délai avant de passer en homing
				        XF_post(steeringProcess, E_FIND0, 50);
				    }
				    else
				    {
				        // Le moteur n'a pas encore assez bougé
				        sendSinus();

				        // On vérifie à nouveau dans 1 ms
				        XF_post(steeringProcess, E_SINUS_MOVE, 50);
				    }

				    break;
				//-----------------------------------------------------------------------
				case FIND0:

					if(startHoming)
					{
					    // Démarrage du homing
					    OD_RAM.x2035_steeringControlWord = 0x001F;
					    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);

					    startHoming = false;
					}


					temp3264 = OD_RAM.x2039_steeringStatusWord & (1 << 12);

				    // Homing terminé ?
				    if (temp3264)
				    {
				        // Passage en Profile Position Mode
				        OD_RAM.x2036_steeringMode = 0x01;

				        CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

				        // Enable Operation
				        OD_RAM.x2035_steeringControlWord = 0x000F;

				        CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);

				        // Revenir au milieu
				        target_position(10000);

				        // Nouveau positionnement
				        OD_RAM.x2035_steeringControlWord = 0x3F;

				        CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);

				        XF_post(steeringProcess, E_REACHED, 100);
				    }
				    else
				    {
				        XF_post(steeringProcess, E_FIND0, 10);
				    }

				    break;

				//-----------------------------------------------------------------------
				case REACHED:

					//Remets sur 0 l'envoi
					OD_RAM.x2035_steeringControlWord = 0x2F;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);

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
		    XF_post(steeringProcess, E_FAULT_RESET, 3000);
			break;
		//-----------------------------------------------------------------------
		case FAULT_RESET:

		    // Fault Reset
		    OD_RAM.x2035_steeringControlWord = 0x0080;
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
		    XF_post(steeringProcess, E_FAULT_RESET, 200);

		    break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED:
			OD_RAM.x2035_steeringControlWord = 0x0006; //6
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
			XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 200);
			break;
		//-----------------------------------------------------------------------
		case SHUTDOWN:
			OD_RAM.x2035_steeringControlWord = 0x0007; //7
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
			XF_post(steeringProcess, E_SHUTDOWN, 200);
			break;
		//-----------------------------------------------------------------------
		case SWITCH_ON:
			OD_RAM.x2035_steeringControlWord = 0x000F; //F
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
			XF_post(steeringProcess, E_SWITCH_ON, 200);
			break;
		//-----------------------------------------------------------------------
		case STEERING_ENABLE:

			count = 0.0f;

			XF_post(steeringProcess, E_SINUS_MOVE, 200);
			break;

		//-----------------------------------------------------------------------
		case SINUS_MOVE:

			// Mémoriser la position de départ
			tempPosMotor = OD_RAM.x203A_steeringMotorCurrentPosition;

			// Mode Torque
			OD_RAM.x2036_steeringMode = 0x0A;

			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

			// Premier couple sinusoidal
			sendSinus();

			// Vérifier le déplacement dans 1 ms
			XF_post(steeringProcess, E_SINUS_MOVE, 1);

			break;
		//-----------------------------------------------------------------------
		case FIND0:

		    // Passage en Homing Mode
		    OD_RAM.x2036_steeringMode = 0x06;
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);



		    // Vérifier le homing
		    XF_post(steeringProcess, E_FIND0, 100);

		    break;
		//-----------------------------------------------------------------------
		case REACHED:
			break;
		//-----------------------------------------------------------------------
		case MOVE:

			break;
	}

	// Mode Torque
	//OD_RAM.x203C_steeringStateMachine = (int8_t) steeringState;
	//CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[5]);


	return true;
}


/* ======== Functions ========== */



void target_position(int32_t target){


	//Write the steering position in dico
	OD_RAM.x2038_steeringPosition = target;
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[7]);

	//2F = 0
	//3F = 1

	//Envoi la pos
	OD_RAM.x2035_steeringControlWord = 0x3F;
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);

}

void sendSinus()
{
	//Increase count
	count = count + (2.0f * 3.1416f / 8.0f);

	//Envoie sinus
	OD_RAM.x2037_steeringTorque = (int16_t) (sin(count) * powerMotor);
	//OD_RAM.x2037_steeringTorque = (int16_t) (sin(count));
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[4]);
}




