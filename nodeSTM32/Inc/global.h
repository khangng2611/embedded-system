/*
 * global.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Acer
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "DHT.h"

#define MAX_BUFFER_SIZE 30

#define INIT_TEMP 0
#define INIT_SOIL_HUMID 0

extern uint8_t temp;
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
extern uint8_t str[12];
//extern uint32_t ADC_Moisture_Value;

extern uint8_t temp_status;
extern uint8_t humid_status;

//communication between esp32 and stm32
#define STR_BUF_LEN 64
#define N 10 //Length of message out
#define N_In 1
#define TRUE 1
#define FALSE 0
#define ACK_OK 0
#define ACK_NO 1
#define ACK_TIMEOUT 2
#define ACK_LEN 16

/*buzzer*/
#define BUZZER_ON 5
#define BUZZER_OFF 6
/*LED*/
#define LED_ON 2
#define LED_OFF 3

// fsm temperature
#define NORMAL_TEMP 8
#define UNUSAL_TEMP 9

//fsm soid humid
#define NORMAL_SOIL_HUMID 11
#define UNUSAL_SOIL_HUMID 12

/*Define parameter of send_packet*/
extern int mySoilHumid;
extern int myTemp;
extern int led1Control;
extern int led2Control;
#endif /* INC_GLOBAL_H_ */
