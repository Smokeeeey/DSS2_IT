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
					XF_post(gearProcess, E_INIT, 10);
					break;
				//-------------------------------------------
				case GO_TO1 :
					OD_RAM.x2006_gearState = 2;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);
					oldGearRequest = OD_RAM.x2000_gear;
					//notify car gear changing (not torque allowed) and send CAN
					OD_RAM.x2004_gearTransition = 1;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);

					//counter restart
					gear.counter = 0;

					//go to pos set by OD
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2001_gearPos0);
					if (gear.position <= MAXPOS0 && gear.position >= MINPOS0)
					{
						XF_post(gearProcess, E_REACHED, 100);
					}
					else
					{
						XF_post(gearProcess, E_GOTO1, 10);
					}

					break;
				case GO_TO2 :
					OD_RAM.x2006_gearState = 3;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);
					oldGearRequest = OD_RAM.x2000_gear;
					//notify car gear changing (not torque allowed) and send CAN
					OD_RAM.x2004_gearTransition = 1;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);

					//reset counter
					gear.counter = 0;

					//go to pos set by OD
					HAL_DAC_SetValue(&hdac1,DAC_CHANNEL_1 , DAC_ALIGN_12B_R, OD_PERSIST_COMM.x2002_gearPos1);

					if (gear.position <= MAXPOS1 && gear.position >= MINPOS1)
					{
						XF_post(gearProcess, E_REACHED, 100);
					}
					else
					{
						XF_post(gearProcess, E_GOTO2, 10);
					}
					break;
				case REACHED :
					OD_RAM.x2006_gearState = 4;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);
					//gear engaged, torque allowed
					gear.counter = 0;
					OD_RAM.x2004_gearTransition = 0 ;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);

					XF_post(gearProcess, E_REACHED, 100);

					break;
				//-------------------------------------------
				case GEARERROR:
					OD_RAM.x2006_gearState = 6;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);
					//go in old gear
					OD_RAM.x2004_gearTransition = 1;
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[1]);
					if (OD_RAM.x2000_gear == 0)
						{
							OD_RAM.x2000_gear = 1;
							oldGearRequest = OD_RAM.x2000_gear;
							//send to OD
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO2, 100);
						}else
						{
							OD_RAM.x2000_gear = 0;
							oldGearRequest = OD_RAM.x2000_gear;
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO1, 100);
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
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[2]);
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

					//count every time this state is looped, after X times, run error
					gear.counter ++;

					//continuously check if in gear
					if (gear.position <= MAXPOS0 && gear.position >= MINPOS0)
					{
						XF_post(gearProcess, E_REACHED, 100);
					}
					//if new gear request
					else if (OD_RAM.x2000_gear == 1)
					{
						XF_post(gearProcess, E_GOTO2, 100);
					}
					else
					{
						//post error
						if(gear.counter == ERRORTIME){
							gear.counter = 0;
							XF_post(gearProcess, E_GEAR_ERROR, 100);
						}
						else
						{
							XF_post(gearProcess, E_GOTO1, 10);
						}
					}
					break;
				case GO_TO2 :
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[2]);
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

					//count every time this state is looped, after X times, run error
					gear.counter++;

					if (gear.position <= MAXPOS1 && gear.position >= MINPOS1)
					{
						XF_post(gearProcess, E_REACHED, 100);
					}
					else if (OD_RAM.x2000_gear == 0)
					{
						XF_post(gearProcess, E_GOTO1, 10);
					}
					else
					{
						//if after delay pos not right, post error
						if(gear.counter == ERRORTIME){
							gear.counter = 0;
							XF_post(gearProcess, E_GEAR_ERROR, 100);
						}
						else
						{
							XF_post(gearProcess, E_GOTO2, 10);
						}
					}
					break;
				case REACHED :
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[2]);
					CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[3]);

					//continuously check if new request came in
					if (OD_RAM.x2000_gear != oldGearRequest)
					{
						oldGearRequest = OD_RAM.x2000_gear;
						if (OD_RAM.x2000_gear == 1)
						{
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO2, 100);
						}else
						{
							CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
							XF_post(gearProcess, E_GOTO1, 100);
						}
					}
					else
					{
						XF_post(gearProcess, E_REACHED, 100);
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
