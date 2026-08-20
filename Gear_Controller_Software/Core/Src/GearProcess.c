/*
 * GearProcess.c
 *
 *  Created on: August 19, 2026
 *      Author: loic.pinuela
 */
#include <GearProcess.h>

StateControl gearState = INIT;

bool gearProcess(Event* ev){

		// Garde la vielle valeur
		static Gear_ST oldGear;
		static StateControl oldGearState;
		uint8_t oldActualGear;

		//***********************************************
		// 		Transition state machine
		//***********************************************
		switch(gearState){
			//-------------------------------------------
			case INIT:
				if (ev->id == E_INIT) {
						gearState = ENGAGED;
				}
				break;
			//-------------------------------------------
			case ENGAGED:
				if (ev->id == E_GEAR_TRANSIT) {
					gearState = TRANSITION;
				}
				if (ev->id == E_GEAR_ERROR) {
					gearState = ERROR;
				}
				break;
			//-------------------------------------------
			case TRANSITION:
				if (ev->id == E_GEAR_ENGAGED) {
					gearState = ENGAGED;
				}
				//if in this state for too long send error
				if (ev->id == E_GEAR_ERROR) {
					gearState = ERROR;
				}
				break;
			//-------------------------------------------
			case ERROR:
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
					break;
				//-------------------------------------------
				case ENGAGED:
					gear.in_transition = 0;
					gear.position = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
					//request the other gear of what is currently engaged
					if (gear.actual_gear == 0)
					{
						gear.gear_requested = 1;
						//send to OD
					}else
					{
						gear.gear_requested = 0;
						//send to OD
					}
					break;
				//-------------------------------------------
				case TRANSITION:
					gear.in_transition = 1;
					//check position to allow engaged state
					gear.position = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
					if (gear.position <= 100 && gear.position >= 90)
					{
						gear.actual_gear = 1;
						XF_post(gearProcess, E_GEAR_ENGAGED, 0);
					}else if (gear.position <= 200 && gear.position >= 150)
					{
						gear.actual_gear = 0;
						XF_post(gearProcess, E_GEAR_ENGAGED, 0);
					}
					//if over ...s post error

					break;
				//-------------------------------------------
				case ERROR:
					gear.in_error = 1;
					break;
				//-------------------------------------------
			}
		}



		return true;
}
