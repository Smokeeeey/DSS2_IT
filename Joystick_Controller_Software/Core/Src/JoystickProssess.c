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


	/* Remplacement temporaire des valeurs en flash qui marchent pas
	 *
	//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
	joy_value = ((adc_ch6 - MIN_JOYSTICK) * COURSE_JOYSTICK) / (MAX_JOYSTICK - MIN_JOYSTICK) - 100;
	if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
		//Offset pour ajuster le milieu
		js.x = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
	} else {
		js.x = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[0];
	}

	//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
	joy_value = ((adc_ch8 - MIN_JOYSTICK) * COURSE_JOYSTICK) / (MAX_JOYSTICK - MIN_JOYSTICK) - 100;
	if (joy_value > OD_PERSIST_COMM.x2001_zeroLimit || joy_value < -OD_PERSIST_COMM.x2001_zeroLimit){
		//Offset pour ajuster le milieu
		js.y = joy_value + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
	} else {
		js.y = 0 + OD_PERSIST_COMM.x2002_nunchuckOffsets[1];
	}
	*/

	//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
	joy_value = ((adc_ch6 - MIN_JOYSTICK) * COURSE_JOYSTICK) / (MAX_JOYSTICK - MIN_JOYSTICK) - 100;
	if (joy_value > ZEROLIMIT_SANS_FLASH || joy_value < -ZEROLIMIT_SANS_FLASH){
		//Offset pour ajuster le milieu
		js.x = joy_value + JOYSTICK_OFFSET_SANS_FLASH;
	} else {
		js.x = 0 + JOYSTICK_OFFSET_SANS_FLASH;
	}

	//Standardisation de -100 à +100 avec un treshold quand on est à l'arret
	joy_value = ((adc_ch8 - MIN_JOYSTICK) * COURSE_JOYSTICK) / (MAX_JOYSTICK - MIN_JOYSTICK) - 100;
	if (joy_value > ZEROLIMIT_SANS_FLASH || joy_value < -ZEROLIMIT_SANS_FLASH){
		//Offset pour ajuster le milieu
		js.y = -(joy_value + JOYSTICK_OFFSET_SANS_FLASH);
	} else {
		js.y = -(0 + JOYSTICK_OFFSET_SANS_FLASH);
	}




	js.button = HAL_GPIO_ReadPin(Joystick_Btn_GPIO_Port, Joystick_Btn_Pin);

	//---------------------------------------------------------

	//Si une des valeurs change
	if(js.x > (oldJS.x + TRESHOLD_NEW_VALUE_SANS_FLASH) || js.x < (oldJS.x - TRESHOLD_NEW_VALUE_SANS_FLASH) ||
	js.y > (oldJS.y + TRESHOLD_NEW_VALUE_SANS_FLASH) || js.y < (oldJS.y - TRESHOLD_NEW_VALUE_SANS_FLASH) ||
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
