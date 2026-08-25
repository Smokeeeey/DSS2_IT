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
		static uint8_t oldGearRequest = 0;
		static uint32_t counter_pos1 = 0;
		static uint32_t counter_pos2 = 0;

		//***********************************************
		// 		Transition state machine
		//***********************************************
		switch(gearState){
			//-------------------------------------------
			case INIT:
				if (ev->id == E_INIT) {
						gearState = GO_TO1;
				}
				break;
			//-------------------------------------------
			case GO_TO1:
				if (ev->id == E_REACHED) {
					gearState = REACHED;
				}
				if (ev->id == E_GOTO2) {
					gearState = GO_TO2;
				}
				if (ev->id == E_GEAR_ERROR) {
					gearState = GEARERROR;
				}
				break;
			//-------------------------------------------
			case GO_TO2:
				if (ev->id == E_REACHED) {
					gearState = REACHED;
				}
				if (ev->id == E_GOTO1) {
					gearState = GO_TO1;
				}
				if (ev->id == E_GEAR_ERROR) {
					gearState = GEARERROR;
				}
				break;
				//-------------------------------------------
			case REACHED:
				if (ev->id == E_GOTO1) {
					gearState = GO_TO1;
				}
				if (ev->id == E_GOTO2) {
					gearState = GO_TO2;
				}
				if (ev->id == E_GEAR_ERROR) {
					gearState = GEARERROR;
				}
				break;
			//-------------------------------------------
			case GEARERROR:
				if (ev->id == E_REACHED) {
					gearState = REACHED;
				}
				if (ev->id == E_GOTO1) {
					gearState = GO_TO1;
				}
				if (ev->id == E_GOTO2) {
					gearState = GO_TO2;
				}
				if (ev->id == E_INIT){
					gearState = INIT;
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
					//gear.in_error = 0;
					XF_post(gearProcess, E_INIT, 10);
					break;
				//-------------------------------------------
				case GO_TO1 :
					OD_RAM.x2004_gearTransition = 1;
					counter_pos1 = 0;
					//CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2001_gearPos0);
					//check if pos1 reached
					if (gear.position <= MAXPOS0 && gear.position >= MINPOS0)
					{
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
						XF_post(gearProcess, E_REACHED, 0);
					}
					else if (OD_RAM.x2000_gear == 1)
					{
						XF_post(gearProcess, E_GOTO2, 0);
					}
					else
					{
						XF_post(gearProcess, E_GOTO1, 10);
					}
					break;
				case GO_TO2 :
					counter_pos2 = 0;
					OD_RAM.x2004_gearTransition = 1;
					//CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2002_gearPos1);
					//check if pos2 reached
					if (gear.position <= MAXPOS1 && gear.position >= MINPOS1)
					{
						CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
						XF_post(gearProcess, E_REACHED, 0);
					}
					else if (OD_RAM.x2000_gear == 0)
					{
						XF_post(gearProcess, E_GOTO1, 0);
					}
					else
					{
						XF_post(gearProcess, E_GOTO2, 10);
					}
					break;
				case REACHED :
					OD_RAM.x2004_gearTransition = 0 ;
					//CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					if (OD_RAM.x2000_gear != oldGearRequest)
					{
						oldGearRequest = OD_RAM.x2000_gear;
						if (OD_RAM.x2000_gear == 0)
						{
							XF_post(gearProcess, E_GOTO1, 0);
						}else
						{
							XF_post(gearProcess, E_GOTO2, 0);
						}
					}
					else
					{
						XF_post(gearProcess, E_REACHED, 10);
					}
					break;
				//-------------------------------------------
				case GEARERROR:
					//gear.in_error = 1;
					//go in old gear
					if (GEAR == 0)
						{
							OD_RAM.x2000_gear = 1;
							oldGearRequest = OD_RAM.x2000_gear;
							//send to OD
							XF_post(gearProcess, E_GOTO2, 0);
						}else
						{
							OD_RAM.x2000_gear = 1;
							oldGearRequest = OD_RAM.x2000_gear;
							XF_post(gearProcess, E_GOTO1, 0);
						}
					break;
				//-------------------------------------------
			}
		}
		//***********************************************
		// 		Loop state machine
		//***********************************************
		else
		{
			switch(gearState){
				//-------------------------------------------
				case INIT:
					break;
				//-------------------------------------------
				case GO_TO1 :
					counter_pos1++;
					if (gear.position <= MAXPOS0 && gear.position >= MINPOS0)
					{
						XF_post(gearProcess, E_REACHED, 0);
					}
					else if (OD_RAM.x2000_gear == 1)
					{
						XF_post(gearProcess, E_GOTO2, 0);
					}
					else
					{
						//if after delay pos not right, post error
						if(counter_pos1 == ERRORTIME){
							counter_pos1 = 0;
							XF_post(gearProcess, E_GEAR_ERROR, 0);
						}
						XF_post(gearProcess, E_GOTO1, 10);
					}
					break;
				case GO_TO2 :
					counter_pos2++;
					if (gear.position <= MAXPOS1 && gear.position >= MINPOS1)
					{
						XF_post(gearProcess, E_REACHED, 0);
					}
					else if (OD_RAM.x2000_gear == 0)
					{
						XF_post(gearProcess, E_GOTO1, 0);
					}
					else
					{
						//if after delay pos not right, post error
						if(counter_pos2 == ERRORTIME){
							counter_pos2 = 0;
							XF_post(gearProcess, E_GEAR_ERROR, 0);
						}
						XF_post(gearProcess, E_GOTO1, 10);
					}
					break;
				case REACHED :
					if (OD_RAM.x2000_gear != oldGearRequest)
					{
						oldGearRequest = oldGearRequest;
						if (OD_RAM.x2000_gear == 0)
						{
							XF_post(gearProcess, E_GOTO2, 0);
						}else
						{
							XF_post(gearProcess, E_GOTO1, 0);
						}
					}
					else
					{
						XF_post(gearProcess, E_REACHED, 10);
					}
					break;
				//-------------------------------------------
				case GEARERROR:
					XF_post(gearProcess, E_INIT, 10);
					break;
				//-------------------------------------------
			}
		}

}
