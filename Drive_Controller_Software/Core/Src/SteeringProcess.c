/*
 * SteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <SteeringProcess.h>

//--------- Variables ---------
StateSteeringControl steeringState = INIT;
StateSteeringControl oldStateSteering = INIT;

float64_t count = 1.0f;

int32_t tempPosMotor = 0;
int32_t position0 = 0;
int32_t rouesCentre = 0;
int8_t waitingMotorMove = 0;

float64_t calculTarget;

int8_t oldJoystickx;
float64_t joystickX;

bool endHoming;
bool startHoming = true;

//-------------------------------

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
			if (ev->id == E_WAIT){
				steeringState = WAIT;
			}
			break;
		//-----------------------------------------------------------------------
		case WAIT:
			if (ev->id == E_REACHED){
				steeringState = REACHED;
			}
			if (ev->id == E_MOVE){
				steeringState = MOVE;
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
					    OD_RAM.x2035_steeringControlWord = homingStartOperation; 		//0x001F
					    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);

					    startHoming = false;
					}


					endHoming = OD_RAM.x2039_steeringStatusWord & (1 << 12);

				    // Homing terminé ?
				    if (endHoming)
				    {
				        // Passage en Profile Position Mode
				        OD_RAM.x2036_steeringMode = profilePositionMode;
				        CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_MODE]);

				        // Enable Operation
				        OD_RAM.x2035_steeringControlWord = enableOperation;
				        CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);

				        // Revenir au milieu
				        target_position(centerPosition);

				        // Nouveau positionnement
				        OD_RAM.x2035_steeringControlWord = newSetpointImediatly;
				        CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);

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
					OD_RAM.x2035_steeringControlWord = resetSetpoint;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);

				    //Ici le moteur est homé
				    //et déjà revenu en Profile Position Mode

					if (OD_RAM.x2020_joystick[0] != oldJoystickx)
					{
						XF_post(steeringProcess, E_MOVE, 10);
					}
					else
					{
						XF_post(steeringProcess, E_REACHED, 10);
					}


					break;
				//-----------------------------------------------------------------------
				case MOVE:


					joystickX = OD_RAM.x2020_joystick[0];

					if (joystickX >= 100)
					{
						joystickX = 100;
					}
					else if (joystickX <= -100)
					{
						joystickX = -100;
					}
					else if (joystickX >= -5 && joystickX <= 5)
					{
						joystickX = 0;
					}

					calculTarget = ((((joystickX) + 100) / 200) * 836700);

					target_position((int32_t) calculTarget);

					XF_post(steeringProcess, E_WAIT, 10);

					break;
				//-----------------------------------------------------------------------
				case WAIT:


					if ((int32_t) abs(OD_RAM.x203A_steeringMotorCurrentPosition - OD_RAM.x2038_steeringPosition) < 20)
					{
						XF_post(steeringProcess, E_REACHED, 10);
					}
					else
					{
						//Remets sur 0 l'envoi
						OD_RAM.x2035_steeringControlWord = resetSetpoint;
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);

						XF_post(steeringProcess, E_MOVE, 10);
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
		    OD_RAM.x2035_steeringControlWord = faultReset;			//80
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);
		    XF_post(steeringProcess, E_FAULT_RESET, 200);

		    break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED:
			OD_RAM.x2035_steeringControlWord = switchOnDisabled; 	//6
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);
			XF_post(steeringProcess, E_SWITCH_ON_DISABLED, 200);
			break;
		//-----------------------------------------------------------------------
		case SHUTDOWN:
			OD_RAM.x2035_steeringControlWord = shutDown; 			//7
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);
			XF_post(steeringProcess, E_SHUTDOWN, 200);
			break;
		//-----------------------------------------------------------------------
		case SWITCH_ON:
			OD_RAM.x2035_steeringControlWord = switchOn; 			//F
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);
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
			OD_RAM.x2036_steeringMode = torqueMode;
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_MODE]);

			// Premier couple sinusoidal
			sendSinus();

			// Vérifier le déplacement dans 1 ms
			XF_post(steeringProcess, E_SINUS_MOVE, 1);

			break;
		//-----------------------------------------------------------------------
		case FIND0:

		    // Passage en Homing Mode
		    OD_RAM.x2036_steeringMode = homingMode;
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_MODE]);

		    // Vérifier le homing
		    XF_post(steeringProcess, E_FIND0, 100);

		    break;
		//-----------------------------------------------------------------------
		case REACHED:
			oldJoystickx = OD_RAM.x2020_joystick[0];
			XF_post(steeringProcess, E_REACHED, 10);
			break;
		//-----------------------------------------------------------------------
		case MOVE:
			XF_post(steeringProcess, E_MOVE, 10);

			break;

		//-----------------------------------------------------------------------
		case WAIT:
			//Remets sur 0 l'envoi
			OD_RAM.x2035_steeringControlWord = resetSetpoint;
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);
			XF_post(steeringProcess, E_WAIT, 10);

			break;


	}


	return true;
}


/* ======== Functions ========== */



void target_position(int32_t target){


	//Write the steering position in dico
	OD_RAM.x2038_steeringPosition = target;
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_POSITION]);

	//2F = 0
	//3F = 1

	//Envoi la pos
	OD_RAM.x2035_steeringControlWord = newSetpointImediatly;
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_CONTROL_WORD]);

}

void sendSinus()
{
	//Increase count
	count = count + (2.0f * 3.1416f / 8.0f);

	//Envoie sinus
	OD_RAM.x2037_steeringTorque = (int16_t) (sin(count) * powerMotor);
	//OD_RAM.x2037_steeringTorque = (int16_t) (sin(count));
	//Envoie sur le can
	CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_STEERING_TORQUE]);
}




