/*
 * joystate.h
 *
 *  Created on: May 26, 2026
 *      Author: jennifer.harries
 */

#ifndef INC_NUNSTATE_H_
#define INC_NUNSTATE_H_
#endif /* INC_NUNSTATE_H_ */

#include "CO_app_STM32.h"
#include "OD.h"

typedef enum
{
	E_NIDLE,
	E_NCHANGED,
	E_NNOTCHANGED

}N_EventList;

bool processNunchuck (Event *ev);
