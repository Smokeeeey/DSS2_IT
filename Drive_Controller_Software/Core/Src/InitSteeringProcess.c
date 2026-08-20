/*
 * InitSteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <InitSteeringProcess.h>


StateInitControl initState = ETAPE1;

bool initSteeringProcess(Event* ev)
	{
	static StateInitControl oldState = ETAPE1;

	//****************************************************************************
	switch(initState){                  // this is the transition state machine

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

		return false;
	}

	oldState = initState;
	//****************************************************************************
	switch(initState){                  // this is the entry action state machine

			//-----------------------------------------------------------------------
			case ETAPE1:
				OD_RAM.x2035_steeringControlWord = 0x0080;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
				break;
			//-----------------------------------------------------------------------
			case ETAPE2:
				OD_RAM.x2035_steeringControlWord = 0x0006;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
				break;

			//-----------------------------------------------------------------------
			case ETAPE3:
				OD_RAM.x2035_steeringControlWord = 0x0007 ;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
				break;

			//-----------------------------------------------------------------------
			case ETAPE4:
				OD_RAM.x2035_steeringControlWord = 0x000F ;
				CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
				break;
	}
	return true;
}


/* ======== Functions ========== */






