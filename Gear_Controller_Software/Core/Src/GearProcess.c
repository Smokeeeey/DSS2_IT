/*
 * GearProcess.c
 *
 *  Created on: August 19, 2026
 *      Author: Jennifer.Harries
 */
#include <GearProcess.h>

StateControl gearState = INIT;

bool gearProcess(Event* ev){

		// keep old value
		static StateControl oldGearState;
		static uint8_t oldGearRequest = 0;
		static uint32_t counter_pos = 0;
		//values to put in OD (test values)
		gear.gear1 = 200;
		gear.gear2 = 2650;
		gear.gearN = 1300;

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
//				if (ev->id == E_GOTO_N) {
//					gearState = GO_TO_N;
//				}
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
//				if (ev->id == E_GOTO_N) {
//					gearState = GO_TO_N;
//				}
				if (ev->id == E_GEAR_ERROR) {
					gearState = GEARERROR;
				}
				break;
//			case GO_TO_N:
//				if (ev->id == E_REACHED) {
//					gearState = REACHED;
//				}
//				if (ev->id == E_GOTO1) {
//					gearState = GO_TO1;
//				}
//				if (ev->id == E_GOTO1) {
//					gearState = GO_TO2;
//				}
//				if (ev->id == E_GEAR_ERROR) {
//					gearState = GEARERROR;
//				}
				//-------------------------------------------
			case REACHED:
				if (ev->id == E_GOTO1) {
					gearState = GO_TO1;
				}
				if (ev->id == E_GOTO2) {
					gearState = GO_TO2;
				}
//				if (ev->id == E_GOTO_N) {
//					gearState = GO_TO_N;
//				}
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
					XF_post(gearProcess, E_INIT, 10);
					break;
				//-------------------------------------------
				case GO_TO1 :
					//notify car gear changing (not torque allowed) and send CAN
					OD_RAM.x2004_gearTransition = 1;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);

					//counter restart
					counter_pos = 0;

					//send to can transition
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);

					//go to pos set by OD
					//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2001_gearPos0);
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, gear.gear1);
					if (gear.position <= MAXPOS0 && gear.position >= MINPOS0)
					{
						XF_post(gearProcess, E_REACHED, 0);
					}
					//if new gear request
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
					//notify car gear changing (not torque allowed) and send CAN
					OD_RAM.x2004_gearTransition = 1;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);

					//reset counter
					counter_pos = 0;

					//go to pos set by OD
					//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2002_gearPos1);
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, gear.gear2);

					if (gear.position <= MAXPOS1 && gear.position >= MINPOS1)
					{
						XF_post(gearProcess, E_REACHED, 100);
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
//				case GO_TO_N :
//					//notify car gear changing (not torque allowed) and send CAN
//					OD_RAM.x2004_gearTransition = 1;
//					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
//
//					//go to pos set by OD
//					//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2002_gearPos1);
//					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, gear.gearN);
//
//					//check if posN reached
//					if (gear.position <= MAXN && gear.position >= MINN)
//					{
//						XF_post(gearProcess, E_REACHED, 0);
//					}
//					//check if new gear change requested
//					else if (OD_RAM.x2000_gear == 0)
//					{
//						XF_post(gearProcess, E_GOTO1, 0);
//					}
//					else if (OD_RAM.x2000_gear == 1)
//					{
//						XF_post(gearProcess, E_GOTO2, 0);
//					}
//					else
//					{
//						XF_post(gearProcess, E_GOTO_N, 10);
//					}
//					break;
				case REACHED :
					//gear engaged, torque allowed
					OD_RAM.x2004_gearTransition = 0 ;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);


					XF_post(gearProcess, E_REACHED, 10);

					break;
				//-------------------------------------------
				case GEARERROR:
					//go in old gear
					OD_RAM.x2004_gearTransition = 1;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					if (GEAR == 0)
						{
							OD_RAM.x2000_gear = 1;
							oldGearRequest = OD_RAM.x2000_gear;
							//send to OD
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO2, 0);
						}else
						{
							OD_RAM.x2000_gear = 0;
							oldGearRequest = OD_RAM.x2000_gear;
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
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
					//count every time this state is looped, after X times, run error
					counter_pos++;

					//continuously send pos requested
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, gear.gear1);
					if (gear.position <= MAXPOS0 && gear.position >= MINPOS0)
					{
						XF_post(gearProcess, E_REACHED, 0);
					}
					//if new gear request
					else if (OD_RAM.x2000_gear == 1)
					{
						XF_post(gearProcess, E_GOTO2, 0);
					}
//					else if (OD_RAM.x2000_gear == 2)
//					{
//						XF_post(gearProcess, E_GOTO_N, 0);
//					}
					else
					{
						//post error
						if(counter_pos == ERRORTIME){
							counter_pos = 0;
							XF_post(gearProcess, E_GEAR_ERROR, 0);
						}
						else
						{
							XF_post(gearProcess, E_GOTO1, 10);
						}
					}
					break;
				case GO_TO2 :
					//count every time this state is looped, after X times, run error
					counter_pos++;

					//continuously send pos requested
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, gear.gear2);
					//HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2002_gearPos1);
					if (gear.position <= MAXPOS1 && gear.position >= MINPOS1)
					{
						XF_post(gearProcess, E_REACHED, 100);
					}
					else if (OD_RAM.x2000_gear == 0)
					{
						XF_post(gearProcess, E_GOTO1, 0);
					}
//					else if (OD_RAM.x2000_gear == 2)
//					{
//						XF_post(gearProcess, E_GOTO_N, 0);
//					}
					else
					{
						//if after delay pos not right, post error
						if(counter_pos == ERRORTIME){
							counter_pos = 0;
							XF_post(gearProcess, E_GEAR_ERROR, 0);
						}
						else
						{
							XF_post(gearProcess, E_GOTO2, 10);
						}
					}
					break;
//				case GO_TO_N :
//					//continuously send pos requested
//					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, gear.gearN);
//					if (gear.position <= MAXN && gear.position >= MINN)
//					{
//						XF_post(gearProcess, E_REACHED, 0);
//					}
//					else if (OD_RAM.x2000_gear == 0)
//					{
//						XF_post(gearProcess, E_GOTO1, 0);
//					}
//					else if (OD_RAM.x2000_gear == 1)
//					{
//						XF_post(gearProcess, E_GOTO2, 0);
//					}
//					else
//					{
//						XF_post(gearProcess, E_GOTO_N, 10);
//					}
//					break;
				case REACHED :
					//continuously check if new request came in
					if (OD_RAM.x2000_gear != oldGearRequest)
					{
						oldGearRequest = OD_RAM.x2000_gear;
						if (OD_RAM.x2000_gear == 1)
						{
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO2, 0);
						}else
						{
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO1, 0);
						}
//						else
//						{
//							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
//							XF_post(gearProcess, E_GOTO_N, 0);
//						}
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
