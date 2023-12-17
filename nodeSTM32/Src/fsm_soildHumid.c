/*
 * fsm_soildHumid.c
 *
 *  Created on: Dec 16, 2023
 *      Author: Acer
 */

#include "fsm_soildHumid.h"

void FSM_SOIL_HUMID(void){
	switch (humid_status) {
			case INIT_SOIL_HUMID:
				Moisture_readValue();
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, SET);
				setTimer2(2000);
				if(mySoilHumid >=60 && mySoilHumid <=70 ){
					humid_status = NORMAL_SOIL_HUMID;
				}
				else{
					humid_status = UNUSAL_SOIL_HUMID;
				}
				break;
			case NORMAL_SOIL_HUMID:
				//send data normally
				if(timer2_flag == 1){
					Moisture_readValue();
					if(mySoilHumid < 60 || mySoilHumid > 70){ // get over standard
						led2Control = 1;
						setTimer2(25000);
						humid_status = UNUSAL_SOIL_HUMID;
					}else{
						led2Control = 0;
						setTimer2(25000);
						}
					send_packet(mySoilHumid, myTemp, led2Control, led1Control);
				}
				break;
			case UNUSAL_SOIL_HUMID:
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, RESET);
				if(timer2_flag == 1){ // check temp again
					Moisture_readValue();
					if(mySoilHumid >=60 && mySoilHumid <= 70){
						//normal Humid, return normal state
						led2Control = 0;
						setTimer2(25000);
						//turn off ..
					    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, SET);
						humid_status = NORMAL_SOIL_HUMID;
					}else{
						led2Control = 1;
						setTimer2(25000);
						humid_status = NORMAL_SOIL_HUMID;
					}
					send_packet(mySoilHumid, myTemp, led2Control, led1Control);
				}
				break;
			default:
				break;
	}
}
