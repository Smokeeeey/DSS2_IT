/*
 * NunchuckProcess.c
 *
 *  Created on: May 26, 2026
 *      Author: alessio.ciardo
 *
 */

#include "NunchuckProcess.h"

uint8_t buffer_nunchuck[6];
uint8_t reg = 0x00;

StateControl nunchuckState = INIT;

bool nunchuckProcess(Event* ev){

	int16_t joy_value;

	// Garde la vielle valeur
	static Nunchuck_ST oldNunchuck;
	static StateControl oldNunchuckState;

	//***********************************************
	// 		Transition state machine
	//***********************************************
	switch(nunchuckState){
		//-------------------------------------------
		case INIT:
			if (ev->id == E_INIT) {
					nunchuckState = RECEIVE;
			}
			break;
		//-------------------------------------------
		case RECEIVE:
			if (ev->id == E_SEND) {
					nunchuckState = SEND;
			}
			//Changement en mode joystick
			if (ev->id == E_NON_USED) {
					nunchuckState = NON_USED;
			}
			break;
		//-------------------------------------------
		case SEND:
			if (ev->id == E_RECEIVE) {
					nunchuckState = RECEIVE;
			}
			//Changement en mode joystick
			if (ev->id == E_NON_USED) {
					nunchuckState = NON_USED;
			}
			break;
		//-------------------------------------------
		case NON_USED:
			// Sécurité, qui recheck si le switch est à 1
			if (ev->id == E_SEND && switch_Nunchuck_Joystick) {
					nunchuckState = SEND;
			}
			break;
	}


	//***********************************************
	// 		Entry state machine
	//***********************************************
	if(oldNunchuckState != nunchuckState){
	oldNunchuckState = nunchuckState;

		switch(nunchuckState){
			//-------------------------------------------
			case INIT:
				break;
			//-------------------------------------------
			case RECEIVE:

				HAL_I2C_Master_Receive(phi2c1, NUNCHUCK_ADRR, buffer_nunchuck, 6, HAL_MAX_DELAY);

				//----------Écrit dans la struct du nunchuck--------------

				((adc_ch8 - MIN_JOYSTICK) * COURSE_JOYSTICK) / (MAX_JOYSTICK - MIN_JOYSTICK) - 100

				//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
				joy_value = (buffer_nunchuck[0] - MIN_NUNCHUCK) * COURSE_JOYSTICK / (MAX_NUNCHUCK - MIN_NUNCHUCK) - 100;
				if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
					//Offset pour ajuster le milieu
					Nunchuck_1.x = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
				} else {
					Nunchuck_1.x = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
				}

				//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
				joy_value = (buffer_nunchuck[1] - MIN_NUNCHUCK) * COURSE_JOYSTICK / (MAX_NUNCHUCK - MIN_NUNCHUCK) - 100;
				if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
					//Offset pour ajuster le milieu
					Nunchuck_1.y = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
				} else {
					Nunchuck_1.y = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
				}

				Nunchuck_1.zButton 		= !(buffer_nunchuck[5] & 0b00000001);
				Nunchuck_1.cButton 		= !((buffer_nunchuck[5] >> 1) & 0b00000001);

				//On envoie 20ms plus tard
				XF_post(nunchuckProcess, E_SEND, 20);

				break;
			//-------------------------------------------
			case SEND:

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
			case NON_USED:
				//On ne fait rien, mode joystick activé
				break;
			//-------------------------------------------
		}
	}



	return true;
}






