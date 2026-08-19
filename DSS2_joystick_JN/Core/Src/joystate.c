/*
 * joystate.c
 *
 *  Created on: May 26, 2026
 *      Author: jennifer.harries
 */
#include "CO_app_STM32.h"
#include "OD.h"
#include "xf.h"
#include <stdbool.h>
#include "joystate.h"


//variables declarations
extern int16_t x_axis_conv, y_axis_conv;
extern CANopenNodeSTM32 canOpenNodeSTM32;

bool processJoystick (Event *ev)
{
	typedef enum
	{
		IDLE,
		CHANGED,
		NOTCHANGED
	}State;

	static State state = IDLE;

	//transitions between states
	switch(state)
	{
		case IDLE :
			if(ev->id==E_CHANGED)
			{
				state = CHANGED;
			}
			break;
		case CHANGED:
			if(ev->id==E_NOTCHANGED)
			{
				state = NOTCHANGED;
			}
			break;
		case NOTCHANGED :
			if(ev->id==E_CHANGED)
			{
				state = CHANGED;
			}
			break;
	}
	//actions in state
	switch (state)
	{
		case IDLE:
			//do nothing
			break;
		case CHANGED:
			//see where to declare
			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
			XF_post(processJoystick,E_NOTCHANGED , 0);
			break;
		case NOTCHANGED :
			//do nothing (don't send) (mesure)

			break;
	}


}


