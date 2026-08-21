/*
 * SteeringProcess.h
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */

#ifndef INC_STEERINGPROCESS_H_
#define INC_STEERINGPROCESS_H_

#include "Project_Defines.h"
#include <math.h>



bool steeringProcess(Event* ev);

void target_position(int32_t target);
void sendSinus();


#endif /* INC_STEERINGPROCESS_H_ */
