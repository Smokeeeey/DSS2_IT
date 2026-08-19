/*
 * SteeringProcess.c
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 *
 */

#include <SteeringProcess.h>


StateSteeringControl steeringState = INIT_STEERING;

bool steeringProcess(Event* ev)
	{
	static StateSteeringControl oldState = INIT_STEERING;
	//****************************************************************************
	switch(steeringState){                  // this is the transition state machine
		//-----------------------------------------------------------------------
		case INIT_STEERING:
			if (ev->id == E_REACHED){
				steeringState = REACHED;
			}
				break;
		//-----------------------------------------------------------------------
		case REACHED:
			if (ev->id == E_MOVE){
				steeringState = MOVE;
			}
			break;
		//-----------------------------------------------------------------------
		case MOVE:
			if (ev->id == E_REACHED){
				steeringState = REACHED;
			}
			break;
	}
	//****************************************************************************
	if(steeringState == oldState){			// this is the loop actions
		return false;
	}

	oldState = steeringState;
	//****************************************************************************
	switch(steeringState){                  // this is the entry action state machine

		//-----------------------------------------------------------------------
		case INIT_STEERING:
			break;
		//-----------------------------------------------------------------------
		case REACHED:
			//XF_post();
			break;
		//-----------------------------------------------------------------------
		case MOVE:

			break;
	}
	return true;
}





