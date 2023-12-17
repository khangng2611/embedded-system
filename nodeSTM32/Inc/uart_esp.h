/*
 * uart_esp.h
 *
 *  Created on: Dec 15, 2023
 *      Author: Acer
 */

#ifndef INC_UART_ESP_H_
#define INC_UART_ESP_H_

#include "global.h"
#include "string.h"

int receive_ack(void);
void send_packet(uint16_t humi, uint16_t temp, uint8_t light, uint8_t buzzer);

#endif /* INC_UART_ESP_H_ */
