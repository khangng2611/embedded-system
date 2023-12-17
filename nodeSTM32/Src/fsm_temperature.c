/*
 * fsm_temperature.c
 *
 *  Created on: Dec 16, 2023
 *      Author: Acer
 */


#include "fsm_temperature.h"
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
void FSM_TEMP(void){
	switch (temp_status) {
			case INIT_TEMP:
				myTemp = ceil(DHT20_getTemp());
//			    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, SET);
			    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
				HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!result=%d\r\n", myTemp), 1000);
				setTimer1(2000);
				if(myTemp >=21 && myTemp <= 27 ){
					temp_status = NORMAL_TEMP;
				}
				else{
					temp_status = UNUSAL_TEMP;
				}
				break;
			case NORMAL_TEMP:
				//send data normally
				if(timer1_flag == 1){
					myTemp = ceil(DHT20_getTemp());
					if(myTemp <21 || myTemp >27){ // get over standard
						led1Control = 1;
						setTimer1(20000);
						temp_status = UNUSAL_TEMP;
					}else{
					led1Control = 0;
					setTimer1(20000);
					}
					send_packet(mySoilHumid, myTemp, led2Control, led1Control);
				}
				break;
			case UNUSAL_TEMP:
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, RESET);
				if(timer1_flag == 1){ // check temp again
					myTemp = ceil(DHT20_getTemp());
					if(myTemp >= 21 && myTemp <= 27){
						//normal temp, return normal state
						led1Control = 0;
						setTimer1(20000);
						//turn off ..
					    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, SET);
						temp_status = NORMAL_TEMP;
					}else{
						led1Control = 1;
						setTimer1(20000);
						temp_status = NORMAL_TEMP;
					}
					send_packet(mySoilHumid, myTemp, led2Control, led1Control);
				}
				break;
			default:
				break;
	}
}
