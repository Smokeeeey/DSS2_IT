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

		//***********************************************
		// 		Transition state machine
		//***********************************************
		switch(gearState){
			//-------------------------------------------
			case INIT:
				if (ev->id == E_INIT) {
						nunchuckState = ENGAGED;
				}
				break;
			//-------------------------------------------
			case ENGAGED:
				if (ev->id == E_TRANSITION) {
					gearState = TRANSITION;
				}
				if (ev->id == E_ERROR) {
					gearState = ERROR;
				}
				break;
			//-------------------------------------------
			case TRANSITION:
				if (ev->id == E_ENGAGED) {
					gearState = ENGAGED;
				}
				if (ev->id == E_ERROR) {
					gearState = ERROR;
				}
				break;
			//-------------------------------------------
			case ERROR:
				if (ev->id == E_ENGAGED) {
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

					/*
					 * reads if the gear change button is pressed (joystick or nunchuck btn)
					 * if the button is pressed, change state to transition
					 * if error (position) change to error
					 * while in this state: register current gear and gear engaged and position
					 */
					//Gear.change = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin); 	//read button value

					//Gear.position = ...

//					HAL_I2C_Master_Receive(phi2c1, NUNCHUCK_ADRR, buffer_nunchuck, 6, HAL_MAX_DELAY);
//
//					//----------Écrit dans la struct du nunchuck--------------
//					//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
//					joy_value = buffer_nunchuck[0] * COURSE_JOYSTICK / (MAX_NUNCHUCK - MIN_NUNCHUCK) - 120;
//					if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
//						//Offset pour ajuster le milieu
//						Nunchuck_1.x = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
//					} else {
//						Nunchuck_1.x = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
//					}
//
//					//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
//					joy_value = buffer_nunchuck[1] * COURSE_JOYSTICK / (MAX_NUNCHUCK - MIN_NUNCHUCK) - 120;
//					if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
//						//Offset pour ajuster le milieu
//						Nunchuck_1.y = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
//					} else {
//						Nunchuck_1.y = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
//					}
//
//					Nunchuck_1.zButton 		= !(buffer_nunchuck[5] & 0b00000001);
//					Nunchuck_1.cButton 		= !((buffer_nunchuck[5] >> 1) & 0b00000001);
//
//					//On envoie 20ms plus tard
					XF_post(nunchuckProcess, E_SEND, 20);

					break;
				//-------------------------------------------
				case TRANSITION:

					// Si une des valeurs change plus que l'offset
					if(Nunchuck_1.x > (oldNunchuck.x + OD_PERSIST_COMM.x2004_treshold_NewValue) || Nunchuck_1.x < (oldNunchuck.x - OD_PERSIST_COMM.x2004_treshold_NewValue) ||
							Nunchuck_1.y > (oldNunchuck.y + OD_PERSIST_COMM.x2004_treshold_NewValue) || Nunchuck_1.y < (oldNunchuck.y - OD_PERSIST_COMM.x2004_treshold_NewValue) ||
							oldNunchuck.zButton != Nunchuck_1.zButton){

						  //On écrit dans le dictionnaire
						  OD_RAM.x2020_joystick[0] = Nunchuck_1.x ;
						  OD_RAM.x2020_joystick[1] = Nunchuck_1.y ;
						  OD_RAM.x2020_joystick[2] = Nunchuck_1.zButton;

						  //Envoie sur le can
						  CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
					}

					oldNunchuck = Nunchuck_1;

					//Nouvelle demande
					HAL_I2C_Master_Transmit(phi2c1, NUNCHUCK_ADRR, &reg, 1, HAL_MAX_DELAY);

					//On va lire 20ms plus tard
					XF_post(nunchuckProcess, E_RECEIVE, 20);

					break;
				//-------------------------------------------
				case ERROR:
					//On ne fait rien, mode joystick activé
					break;
				//-------------------------------------------
			}
		}



		return true;
}
