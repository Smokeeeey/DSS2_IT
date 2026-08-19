/*
 * joystate.h
 *
 *  Created on: May 26, 2026
 *      Author: jennifer.harries
 */

#ifndef INC_JOYSTATE_H_
#define INC_JOYSTATE_H_
#endif /* INC_JOYSTATE_H_ */

#include "CO_app_STM32.h"
#include "OD.h"

typedef enum
{
	E_IDLE,
	E_CHANGED,
	E_NOTCHANGED

}EventList;

bool processJoystick (Event *ev);
