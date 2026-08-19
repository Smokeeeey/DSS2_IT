/*
 * JoystickProssess.c
 *
 *  Created on: May 26, 2026
 *      Author: alessio.ciardo
 */
#include "JoystickProssess.h"




bool joystickProssess(Event* ev){

	int16_t joy_value;
	static Joystick oldJS;

	//----------Écrit dans la struct du nunchuck--------------

	//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
	joy_value = (adc_ch6 * COURSE_JOYSTICK)/(MAX_JOYSTICK - MIN_JOYSTICK) - 120;
	if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
		//Offset pour ajuster le milieu
		js.x = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
	} else {
		js.x = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
	}

	//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
	joy_value = -((adc_ch8 * COURSE_JOYSTICK)/(MAX_JOYSTICK - MIN_JOYSTICK) - 120);
	if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
		//Offset pour ajuster le milieu
		js.y = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
	} else {
		js.y = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
	}

	js.button = HAL_GPIO_ReadPin(Joystick_Btn_GPIO_Port, Joystick_Btn_Pin);

	//---------------------------------------------------------

	//Si une des valeurs change
	if(js.x > (oldJS.x + OD_PERSIST_COMM.x2004_treshold_NewValue) || js.x < (oldJS.x - OD_PERSIST_COMM.x2004_treshold_NewValue) ||
	js.y > (oldJS.y + OD_PERSIST_COMM.x2004_treshold_NewValue) || js.y < (oldJS.y - OD_PERSIST_COMM.x2004_treshold_NewValue) ||
	oldJS.button != js.button){

		//Écrit dans le dictionnaire
		OD_RAM.x2020_joystick[0] = js.x;
		OD_RAM.x2020_joystick[1] = js.y;
		OD_RAM.x2020_joystick[2] = js.button;

		//Envoie sur le can
		CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);

	}

	//On demande d'aller lire l'ADC
	lectureADC = true;

	//Se rappelle automatiquement si le switch est dans le mode joystick
	if(!HAL_GPIO_ReadPin(SLIDER_GPIO_Port, SLIDER_Pin)) XF_post(joystickProssess, E_DEFAULT, 100);

	oldJS = js;
	return true;
}
