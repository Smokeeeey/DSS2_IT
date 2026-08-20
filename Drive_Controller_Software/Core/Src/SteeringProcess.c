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

		switch(steeringState){

				//-----------------------------------------------------------------------
				case INIT_STEERING:
					initialisation_steering();
					break;
				//-----------------------------------------------------------------------
				case REACHED:
					if (){

						XF_post(steeringProcess, E_MOVE, 0);
					}
					break;
				//-----------------------------------------------------------------------
				case MOVE:

					XF_post(steeringProcess, E_REACHED, 0);
					break;
			}

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

			break;
		//-----------------------------------------------------------------------
		case MOVE:

			target_position(OD_PERSIST_COMM.x200);

			break;
	}
	return true;
}


/* ======== Functions ========== */

void initialisation_steering(){




	//Envoie sur le can



	XF_post(steeringProcess, E_REACHED, 0);
}

int target_position(){


}




