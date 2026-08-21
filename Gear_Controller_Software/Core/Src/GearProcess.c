/*
 * GearProcess.c
 *
 *  Created on: August 19, 2026
 *      Author: loic.pinuela
 */
#include <GearProcess.h>

StateControl gearState = INIT;

bool gearProcess(Event* ev){

		// keep old value
		static StateControl oldGearState;
		static uint8_t stateNum;

		//***********************************************
		// 		Transition state machine
		//***********************************************
		switch(gearState){
			//-------------------------------------------
			case INIT:
				stateNum=1;
				if (ev->id == E_INIT) {
						gearState = TRANSITION;
				}
				break;
			//-------------------------------------------
			case ENGAGED:
				stateNum=2;
				if (ev->id == E_GEAR_TRANSIT) {
					gearState = TRANSITION;
				}
				if (ev->id == E_GEAR_ERROR) {
					gearState = GEARERROR;
				}
				break;
			//-------------------------------------------
			case TRANSITION:
				stateNum=3;
				if (ev->id == E_GEAR_ENGAGED) {
					gearState = ENGAGED;
				}
				//if in this state for too long send error
				if (ev->id == E_GEAR_ERROR) {
					gearState = GEARERROR;
				}
				break;
			//-------------------------------------------
			case GEARERROR:
				stateNum=4;
				if (ev->id == E_GEAR_ENGAGED) {
					gearState = ENGAGED;
				}
				break;
		}


		//***********************************************
		// 		Entry state machine
		//***********************************************
		if(oldGearState != gearState){
		oldGearState = gearState;

			switch(gearState){
				//-------------------------------------------
				case INIT:
					gear.actual_gear = 0;
					break;
				//-------------------------------------------
				case ENGAGED:
					OD_RAM.x2004_gearTransition = 0 ;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					//check if gear engaged is actually gear requested
					if(gear.actual_gear != GEAR_REQUESTED)
					{
						XF_post(gearProcess, E_GEAR_TRANSIT, 0);
					}
					//check if driver requested gear change
					//if (gear.change_gear)
					if (OD_RAM.x2000_gear != oldGearRequest)
					{
						oldGearRequest = OD_RAM.x2000_gear;
						//request the other gear of what is currently engaged
						if (gear.actual_gear == 0)
						{
							HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2002_gearPos1);
							XF_post(gearProcess, E_GEAR_TRANSIT, 0);
						}else
						{
							HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2001_gearPos0);
							XF_post(gearProcess, E_GEAR_TRANSIT, 0);
						}
					}
					break;
				//-------------------------------------------
				case TRANSITION:
					OD_RAM.x2004_gearTransition = 1 ;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					//check position to allow engaged state
					//delay to wait for gear to reach
					if (gear.position <= 100 && gear.position >= 90)
					{
						gear.actual_gear = 1;
						OD_RAM.x2000_gear = gear.actual_gear; 								//write in dictionary
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);		//send on can
						XF_post(gearProcess, E_GEAR_ENGAGED, 0);
					}else if (gear.position <= 200 && gear.position >= 150)
					{
						gear.actual_gear = 0;
						OD_RAM.x2000_gear = gear.actual_gear; 								//write in dictionary
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);		//send on can
						XF_post(gearProcess, E_GEAR_ENGAGED, 0);
					}
					//if over ...s post error

					break;
				//-------------------------------------------
				case GEARERROR:
					gear.in_error = 1;
					break;
				//-------------------------------------------
			}
		}



		return true;
}
