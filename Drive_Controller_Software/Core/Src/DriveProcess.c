/*
 * DriveProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <DriveProcess.h>

//--------- Variables ---------
StateDriveControl driveState = INIT_D;
StateDriveControl oldStateDrive = INIT_D;
int8_t oldJoystickY;
int16_t calculTorque;
uint8_t oldinTransition;
uint8_t oldJoystickPin;

//-------------------------------


bool driveProcess(Event* ev)
	{


	//****************************************************************************
	switch(driveState){                  // this is the transition state machine

		//-----------------------------------------------------------------------
		case INIT_D:

			if (ev->id == E_INIT_DRIVE)
			{
				driveState = INIT_DRIVE;
			}
			if (ev->id == E_MOVE_DRIVE)
			{
				driveState = MOVE_DRIVE;
			}

			break;
		//-----------------------------------------------------------------------
		case INIT_DRIVE:

			if (ev->id == E_FAULT_RESET_D)
			{
				driveState = FAULT_RESET_D;
			}
			else if (ev->id == E_SWITCH_ON_DISABLED_D)
			{
				driveState = SWITCH_ON_DISABLED_D;
			}

			break;
		//-----------------------------------------------------------------------
		case FAULT_RESET_D:

		    if (ev->id == E_SWITCH_ON_DISABLED_D)
		    {
		        driveState = SWITCH_ON_DISABLED_D;
		    }

		    break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED_D:
			if (ev->id == E_SHUTDOWN_D){
				driveState = SHUTDOWN_D;
			}
				break;
		//-----------------------------------------------------------------------
		case SHUTDOWN_D:
			if (ev->id == E_SWITCH_ON_D){
				driveState = SWITCH_ON_D;
			}
				break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_D:
			if (ev->id == E_DRIVE_ENABLE){
				driveState = DRIVE_ENABLE;
			}
				break;
		//-----------------------------------------------------------------------
		case DRIVE_ENABLE:

		    if (ev->id == E_STOP_DRIVE){
		        driveState = STOP_DRIVE;
		    }

		    break;
		//-----------------------------------------------------------------------
		case STOP_DRIVE:
			if (ev->id == E_MOVE_DRIVE){
				driveState = MOVE_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case MOVE_DRIVE:
			if (ev->id == E_STOP_DRIVE){
				driveState = STOP_DRIVE;
			}
			break;
	}
	//****************************************************************************
	if(driveState == oldStateDrive){			// this is the loop actions

		switch(driveState){

				//-----------------------------------------------------------------------
				case INIT_D:

					break;

				//-----------------------------------------------------------------------
				case INIT_DRIVE:

				    break;
				//-----------------------------------------------------------------------
				case FAULT_RESET_D:

				    // Fault toujours présent ?
				    if (OD_RAM.x2030_driveStatusWord & (1 << 3))
				    {
				        XF_post(driveProcess, E_FAULT_RESET_D, 50);
				    }
				    else
				    {
				        // Fault Reset réussi
				        XF_post(driveProcess, E_SWITCH_ON_DISABLED_D, 50);
				    }

				    break;

				//-----------------------------------------------------------------------
				case SWITCH_ON_DISABLED_D:

					if ((OD_RAM.x2030_driveStatusWord & maskStatus) == 0x0021)
					{
						XF_post(driveProcess, E_SHUTDOWN_D, 100);
					}
					else
					{
						XF_post(driveProcess, E_SWITCH_ON_DISABLED_D, 100);
					}

					break;
				//-----------------------------------------------------------------------
				case SHUTDOWN_D:

					if ((OD_RAM.x2030_driveStatusWord & maskStatus) == 0x0023)
					{
						XF_post(driveProcess, E_SWITCH_ON_D, 100);
					}
					else
					{
						XF_post(driveProcess, E_SHUTDOWN_D, 100);
					}

					break;
				//-----------------------------------------------------------------------
				case SWITCH_ON_D:
					if ((OD_RAM.x2030_driveStatusWord & maskStatus) == 0x0027)
					{
						XF_post(driveProcess, E_DRIVE_ENABLE, 100);
					}
					else
					{
						XF_post(driveProcess, E_SWITCH_ON_D, 100);
					}

					break;
				//-----------------------------------------------------------------------
				case DRIVE_ENABLE:
					break;

				//-----------------------------------------------------------------------
				case STOP_DRIVE:
					if (OD_RAM.x2020_joystick[1] != 0)
					{
						XF_post(driveProcess, E_MOVE_DRIVE, 10);
					}
					else
					{
						XF_post(driveProcess, E_STOP_DRIVE, 10);
					}

					break;
				//-----------------------------------------------------------------------
				case MOVE_DRIVE:

					if (OD_RAM.x2020_joystick[1] != oldJoystickY)
					{
						//Envoie torque
						calculTorque = (int16_t) (OD_RAM.x2020_joystick[1] * 10);

						if (calculTorque >= 1000)
						{
							OD_RAM.x2032_driveTorque = 1000;
						}
						else if (calculTorque <= -1000)
						{
							OD_RAM.x2032_driveTorque = -1000;
						}
						else
						{
							OD_RAM.x2032_driveTorque = calculTorque;
						}


						//check hand brake
						if (!HAL_GPIO_ReadPin(External_Btn_GPIO_Port, External_Btn_Pin))
						{
							OD_RAM.x2032_driveTorque = 0;
						}

						//check if button pressed
						if ((OD_RAM.x2020_joystick[2] != oldJoystickPin))
						{
							oldJoystickPin = OD_RAM.x2020_joystick[2];
							if (OD_RAM.x2020_joystick[2] == 1)
							{
								OD_RAM.x203E_gearPos++;
								OD_RAM.x203E_gearPos = OD_RAM.x203E_gearPos % 2;
								CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_GEARPOS]);
								OD_RAM.x2032_driveTorque = 0;
							}

						}

						//check if gear reached
						if (OD_RAM.x203D_gearTransition)
						{
							OD_RAM.x2032_driveTorque = 0;
						}

						//Envoie sur le can
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_DRIVE_TORQUE]);

						oldJoystickY = OD_RAM.x2020_joystick[1];
						XF_post(driveProcess, E_MOVE_DRIVE, 10);
					}
					else
					{
						XF_post(driveProcess, E_MOVE_DRIVE, 10);
					}


					break;
			}

		return false;
	}

	oldStateDrive = driveState;
	//****************************************************************************
	switch(driveState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT_D:
//			XF_post(driveProcess, E_MOVE_DRIVE, 100);


			break;

		//-----------------------------------------------------------------------
		case INIT_DRIVE:

			//Reveil de l'epos vu qu'on est master
			CO_NMT_sendCommand(canOpenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL,1);

			//Envoyer pour faire un fault reset
		    XF_post(driveProcess, E_FAULT_RESET_D, 3000);
			break;
		//-----------------------------------------------------------------------
		case FAULT_RESET_D:
		    OD_RAM.x2034_driveControlWord= faultReset;			//80
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_DRIVE_CONTROL_WORD]);
		    XF_post(driveProcess, E_FAULT_RESET_D, 200);

		    break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED_D:
			OD_RAM.x2034_driveControlWord= switchOnDisabled; 	//6
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_DRIVE_CONTROL_WORD]);
			XF_post(driveProcess, E_SWITCH_ON_DISABLED_D, 200);
			break;
		//-----------------------------------------------------------------------
		case SHUTDOWN_D:
			OD_RAM.x2034_driveControlWord = shutDown; 			//7
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_DRIVE_CONTROL_WORD]);
			XF_post(driveProcess, E_SHUTDOWN_D, 200);
			break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_D:
			OD_RAM.x2034_driveControlWord= switchOn; 			//F
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_DRIVE_CONTROL_WORD]);
			XF_post(driveProcess, E_SWITCH_ON_D, 200);
			break;
		//-----------------------------------------------------------------------
		case DRIVE_ENABLE:

			// Mode Torque
			OD_RAM.x2033_driveMode = torqueMode;
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[ID_DRIVE_MODE]);

			//Joystick init
			oldJoystickY = OD_RAM.x2020_joystick[1];

			XF_post(driveProcess, E_STOP_DRIVE, 100);
			break;

		//-----------------------------------------------------------------------
		case STOP_DRIVE:
			XF_post(driveProcess, E_STOP_DRIVE, 10);
			break;
		//-----------------------------------------------------------------------
		case MOVE_DRIVE:
			XF_post(driveProcess, E_MOVE_DRIVE, 10);

			break;



	}


	return true;
}


/* ======== Functions ========== */



