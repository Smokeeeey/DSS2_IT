///*
// * joystate.c
// *
// *  Created on: May 26, 2026
// *      Author: jennifer.harries
// */
//#include "CO_app_STM32.h"
//#include "OD.h"
//#include "xf.h"
//#include <stdbool.h>
//#include "nunstate.h"
//
//
////variables declarations
//extern int16_t x_axis_conv, y_axis_conv;
//extern CANopenNodeSTM32 canOpenNodeSTM32;
//#define DATALEN 2
//extern NUNCKADD;
//int data [2] = {0xF0, 0x55};
//bool processNunchuck (Event *ev)
//{
//	typedef enum
//	{
//		NIDLE,
//		NMESURE,
//		NCHANGED,
//		NNOTCHANGED
//	}State;
//
//	static State state = NIDLE;
//
//	//transitions between states
//	switch(state)
//	{
//		case NIDLE :
//			  HAL_I2C_Master_Transmit(&hi2c1, NUNCKADD, data, DATALEN, 2);
//			  HAL_Delay(100);
//			  data[0] = 0xFB;
//			  data[1] = 0x00;
//			  HAL_I2C_Master_Transmit(&hi2c1, NUNCKADD, data, DATALEN, 2);
//			  state = NMESURE;
//			break;
//		case NMESURE:
//			 HAL_I2C_Master_Transmit(&hi2c1, NUNCKADD, data, DATALEN, 2);
//
//					break;
//		case NCHANGED:
//			if(ev->id==E_NNOTCHANGED)
//			{
//				state = NNOTCHANGED;
//			}
//			break;
//		case NNOTCHANGED :
//			if(ev->id==E_NCHANGED)
//			{
//				state = NCHANGED;
//			}
//			break;
//	}
//	//actions in state
//	switch (state)
//	{
//		case NIDLE:
//			//do nothing
//			break;
//		case NCHANGED:
//			//see where to declare
//			CO_TPDOsendRequest(&canOpenNodeSTM32.canOpenStack->TPDO[0]);
//			XF_post(processNunchuck,E_NNOTCHANGED , 0);
//			break;
//		case NNOTCHANGED :
//			//do nothing (don't send) (mesure)
//
//			break;
//	}
//
//
//}
//
//
