/*
 * uart_esp.c
 *
 *  Created on: Dec 15, 2023
 *      Author: Acer
 */

#include "uart_esp.h"
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart2;
uint8_t Data_Out[N];
// Đợi ACK từ ESP32
int receive_ack(void)
{
    char buf[ACK_LEN + 1];
    int ack_index = 0;
    int result = ACK_NO;
    int timeout_count = 1000;

    // Lặp đợi ACK
    for (;;)
    {
    	HAL_StatusTypeDef status;
		uint8_t c = 0;

		// Đợi 1 byte từ UART
		status = HAL_UART_Receive(&huart6, &c, 1, timeout_count);

		// Khi Nhận được 1 byte từ UART
	    if (status == HAL_OK)
	    {
	        // Nếu nhận được 'n' hay 'r', kiểm tra xem có phải là "OK" không, rồi thoát vòng lặp
	        if (c == '\n' || c == '\r')
	        {
	        	buf[ack_index] = 0;
	            if (strncmp(buf, "OK", ack_index) == 0)
	            {
	            	result = ACK_OK;
	            	break;
	            }
	        }
	        else if (ack_index < ACK_LEN + 1)
	        {
	            buf[ack_index] = c;
	            ack_index++;
	            if (ack_index >= ACK_LEN) {
	                buf[ACK_LEN] = 0 ;
	            }
	        }
	    }
	    // Khi Timeout hết mà chưa nhận được ACK
	    else if (status == HAL_TIMEOUT)
	    {
	        result = ACK_TIMEOUT;
	        break;
	    }
    }

    return(result) ;
}

void send_packet(uint16_t humi, uint16_t temp, uint8_t light, uint8_t buzzer)
{
    int result = ACK_NO;
    uint16_t  sum = 0;
    int i, data_num = 0 ;

    Data_Out[data_num++] = 's';
    Data_Out[data_num++] = 't';
    Data_Out[data_num++] = TRUE;
    Data_Out[data_num++] = (humi >> 8) & 0xFF;
    Data_Out[data_num++] = humi & 0xFF;
    Data_Out[data_num++] = (temp >> 8) & 0xFF;
    Data_Out[data_num++] = temp & 0xFF;
    Data_Out[data_num++] = light;
    Data_Out[data_num++] = buzzer;
    for (i = 0 ; i < data_num ; i++ ) {
        sum += Data_Out[i];
    }
    Data_Out[data_num++] = sum;
    Data_Out[data_num++] = '\r';

    while (result == ACK_NO || result == ACK_TIMEOUT)
    {
		HAL_UART_Transmit(&huart6, Data_Out, sizeof(Data_Out), 100);
		result = receive_ack();
    }
}

