/*
 * ControllerProcess.h
 *
 *  Created on: August 18, 2026
 *      Author: pinuela.loic
 */

#ifndef SRC_CONTROLLERPROCESS_H_
#define SRC_CONTROLLERPROCESS_H_

#include "Project_Defines.h"

void transformValue();
void transmitValue();
void handBreak();
void changingGear();

bool controllerProcess(Event* ev);

#endif /* SRC_CONTROLLERPROCESS_H_ */
