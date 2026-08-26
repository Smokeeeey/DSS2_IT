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

		    if (ev->id == E_SINUS_MOVE){
		        driveState = SINUS_MOVE;
		    }

		    break;
		//-----------------------------------------------------------------------
		case REACHED_DRIVE:
			if (ev->id == E_MOVE_DRIVE){
				driveState = MOVE_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case MOVE_DRIVE:
			if (ev->id == E_WAIT_DRIVE){
				driveState = WAIT_DRIVE;
			}
			break;
		//-----------------------------------------------------------------------
		case WAIT_DRIVE:
			if (ev->id == E_REACHED_DRIVE){
				driveState = REACHED_DRIVE;
			}
			if (ev->id == E_MOVE_DRIVE){
				driveState = MOVE_DRIVE;
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
				case REACHED_DRIVE:


					break;
				//-----------------------------------------------------------------------
				case MOVE_DRIVE:


					break;
				//-----------------------------------------------------------------------
				case WAIT_DRIVE:

					break;

			}

		return false;
	}

	oldStateDrive = driveState;
	//****************************************************************************
	switch(driveState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT_D:


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
		    CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
		    XF_post(driveProcess, E_FAULT_RESET_D, 200);

		    break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_DISABLED_D:
			OD_RAM.x2034_driveControlWord= switchOnDisabled; 	//6
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
			XF_post(driveProcess, E_SWITCH_ON_DISABLED_D, 200);
			break;
		//-----------------------------------------------------------------------
		case SHUTDOWN_D:
			OD_RAM.x2034_driveControlWord= SHUTDOWN_D; 			//7
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
			XF_post(driveProcess, E_SHUTDOWN_D, 200);
			break;
		//-----------------------------------------------------------------------
		case SWITCH_ON_D:
			OD_RAM.x2034_driveControlWord= switchOn; 			//F
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[6]);
			XF_post(driveProcess, E_SWITCH_ON_D, 200);
			break;
		//-----------------------------------------------------------------------
		case DRIVE_ENABLE:

			XF_post(driveProcess, E_SINUS_MOVE, 200);
			break;

		//-----------------------------------------------------------------------
		case REACHED_DRIVE:
			XF_post(driveProcess, E_REACHED_DRIVE, 10);
			break;
		//-----------------------------------------------------------------------
		case MOVE_DRIVE:
			XF_post(driveProcess, E_MOVE_DRIVE, 10);

			break;

		//-----------------------------------------------------------------------
		case WAIT_DRIVE:
			XF_post(driveProcess, E_WAIT_DRIVE, 10);

			break;


	}


	return true;
}


/* ======== Functions ========== */



