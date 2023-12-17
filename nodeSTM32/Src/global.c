/*
 * global.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Acer
 */


#include "global.h"

uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t str[12] = "GOATMESSI";
//uint32_t ADC_Moisture_Value = 0;
//communication between esp32 and stm32
uint8_t Data_In = 0;
int buffer_size = 0;

uint8_t temp_status =  0;
uint8_t humid_status = 0;

int mySoilHumid = 0;
int myTemp = 0;
int led1Control = FALSE;
int led2Control = FALSE;
