/*
 * InitSteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <InitSteeringProcess.h>


StateInitControl initState = INIT;

bool initSteeringProcess(Event* ev)
	{
	static StateInitControl oldState = INIT;

	//****************************************************************************
	switch(initState){                  // this is the transition state machine

		//-----------------------------------------------------------------------
		case INIT:
			if (ev->id == E_ETAPE1){
				initState = ETAPE1;
			}
			break;
		//-----------------------------------------------------------------------
		case ETAPE1:
			if (ev->id == E_ETAPE2){
				initState = ETAPE2;
			}
				break;
		//-----------------------------------------------------------------------
		case ETAPE2:
			if (ev->id == E_ETAPE3){
				initState = ETAPE3;
			}
			break;
		//-----------------------------------------------------------------------
		case ETAPE3:
			if (ev->id == E_ETAPE4){
				initState = ETAPE4;
			}
			break;
		//-----------------------------------------------------------------------
		case ETAPE4:

			break;

	}
	//****************************************************************************
	if(initState == oldState){			// this is the loop actions

		switch(initState){

			case INIT:
					//Reveil de l'epos vu qu'on est master
					//CO_NMT_sendCommand(canOpenNodeSTM32.canOpenStack->NMT, CO_NMT_ENTER_OPERATIONAL,2);
					XF_post(initSteeringProcess, E_ETAPE1, 0);
					break;
			//-----------------------------------------------------------------------

			case ETAPE1:	//Switch on disabled
					if ((OD_RAM.x2030_driveStatusWord & 0x006F) == 0x0021)
					{
						XF_post(initSteeringProcess, E_ETAPE2, 0);
					}
					XF_post(initSteeringProcess, E_ETAPE1, 50);

					break;
			//-----------------------------------------------------------------------
			case ETAPE2:	//Ready to switch on
					if ((OD_RAM.x2030_driveStatusWord & 0x006F) == 0x0023)
					{
						XF_post(initSteeringProcess, E_ETAPE3, 0);
					}
					XF_post(initSteeringProcess, E_ETAPE2, 50);
				break;
			//-----------------------------------------------------------------------
			case ETAPE3:	//Switched on
					if ((OD_RAM.x2030_driveStatusWord & 0x006F) == 0x0027)
					{
						XF_post(initSteeringProcess, E_ETAPE4, 0);
					}
					XF_post(initSteeringProcess, E_ETAPE3, 50);
				break;
			//-----------------------------------------------------------------------
			case ETAPE4:
				// moteur opérationnel
				break;
		}

		return false;
	}

	oldState = initState;
	//****************************************************************************
	switch(initState){                  // this is the entry action state machine

			//-----------------------------------------------------------------------
			case ETAPE1:
				OD_RAM.x2035_steeringControlWord = 0x0006;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[7]);
				break;
			//-----------------------------------------------------------------------
			case ETAPE2:
				OD_RAM.x2035_steeringControlWord = 0x0007;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[7]);
				break;

			//-----------------------------------------------------------------------
			case ETAPE3:
				OD_RAM.x2035_steeringControlWord = 0x000F;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[7]);
				break;

			//-----------------------------------------------------------------------
			case ETAPE4:
				break;
	}
	return true;
}


/* ======== Functions ========== */






