/*
 * DriveProcess.h
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */

#ifndef INC_DRIVEPROCESS_H_
#define INC_DRIVEPROCESS_H_

#include "Project_Defines.h"
#include <math.h>


void send_speed(int32_t rpm);


bool driveProcess(Event* ev);


#endif /* INC_DRIVEPROCESS_H_ */
