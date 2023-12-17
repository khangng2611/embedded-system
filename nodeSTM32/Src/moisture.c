/*
 * moisture.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Acer
 */

#include "global.h"
#include "moisture.h"
#include "stdio.h"
#include "main.h"


#define MAX_ADC_VALUE 4095
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;


void Moisture_readValue(){
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	mySoilHumid =  HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	Moisture_convert();
	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!ADC_Value=%lu\r\n", mySoilHumid), 1000);
}

void Moisture_convert(){
	mySoilHumid =  (mySoilHumid*100/MAX_ADC_VALUE);
}

