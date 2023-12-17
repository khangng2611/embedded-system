/*
 * DHT.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Acer
 */

#include "DHT.h"
#include "global.h"
#include "stdio.h"
#include "string.h"

extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

float    humidity          = 0;
float    temperature       = 0;
float    humidityOffset    = 0;
float    temperatureOffset = 0;

uint8_t checksum;

uint8_t buf[7] = {0};
uint8_t readCMD[3] = {0xAC, 0x33, 0x00};
uint32_t _lastRequest = 0;
uint32_t _lastRead = 0;

void DHT_scanI2CAddresses() {
	char str[20] = {0};
    for (uint8_t address = 0; address < 128; address++) {
        if (HAL_I2C_IsDeviceReady(&hi2c1, address, 1, 10) == HAL_OK) {
        	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!address=%02X#\r\n", address), 100);
        }
    }
}

uint8_t DHT20_isConnected(){
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, DHT20, 1, 100);
	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!connectDHT=%02X#\r\n", status), 1000);
    return status;
}

uint8_t DHT20_getAddress(){
	return DHT20;
}

float DHT20_getHumid (){
	return (humidity + humidityOffset);
}

float DHT20_getTemp(){
	return temperature + temperatureOffset;
}

void DHT20_setHumidOffset(float offset ){
      humidityOffset = offset;
}
void DHT20_setTemperatureOffset(float offset){
	temperatureOffset = offset;
}
float DHT20_getHumidOffset(){
     return humidityOffset;
}
float DHT20_getTemperatureOffset(){
	return temperatureOffset;
}
uint8_t DHT20_requestData(){
	  HAL_StatusTypeDef ret;
	  ret =  HAL_I2C_Master_Transmit(&hi2c1, DHT20, readCMD, 3, 1000);
      return ret;
}

uint8_t DHT20_resetRegister(uint8_t reg){
	if(HAL_I2C_Master_Transmit(&hi2c1, DHT20, reg, 1, 100) != HAL_OK){
		return 0x00;
	}
	if(HAL_I2C_Master_Transmit(&hi2c1, DHT20, 0x00, 1, 100)){
		return 0x00;
	}
    HAL_Delay(100);

    uint8_t receivedData[3];
    HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(&hi2c1, DHT20, receivedData, 3, 1000);
    if(ret == HAL_OK){
    	HAL_I2C_Master_Transmit(&hi2c1, DHT20, (0xB0 | reg), 1, 100);
    	HAL_I2C_Master_Transmit(&hi2c1, DHT20, &receivedData[1], 1, 100);
    	HAL_I2C_Master_Transmit(&hi2c1, DHT20, &receivedData[2], 1, 100);
    	return 0x01;
    }
    HAL_Delay(100);
    return 0x00;
}
uint8_t DHT20_readStatus(){
    uint8_t data[1];
	HAL_StatusTypeDef ret ;
	uint8_t readstatus = 0x71;
	ret = HAL_I2C_Master_Transmit(&hi2c1, DHT20, readstatus , 1, 100);
	HAL_Delay(10);
	ret = HAL_I2C_Master_Receive(&hi2c1, DHT20, data, 1, 100);
    return data[0];
}
void DHT20_resetSensor(){
       uint8_t count = 255;
       if(DHT20_readStatus() & 0x18 != 0x18){
    	   count++;
    	   if(DHT20_resetRegister(0x1B)) count++;
    	   if(DHT20_resetRegister(0x1C)) count++;
    	   if(DHT20_resetRegister(0x1E)) count++;
    	   HAL_Delay(20);
       }
}
uint8_t DHT20_crc8(uint8_t *ptr, uint8_t len)
{
	uint8_t crc = 0xFF;
	while(len--){
		crc ^= *ptr++;
		for(uint8_t i = 0; i< 8; ++i)
		{
			if(crc & 0x80)
			{
				crc <<= 1;
				crc ^= 0x31;
			}
			else
			{
				crc <<= 1;
			}
		}
	}
	return crc;
}
int DHT20_Read(){
	HAL_StatusTypeDef ret ;
	if(DHT20_isConnected() != HAL_OK){
		return DHT20_ERROR_CONNECT;
	}
    uint8_t request_data = DHT20_requestData();
    if(request_data == HAL_OK){
    	HAL_Delay(1000);
    	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!result=%s#\r\n", "OK"), 1000);
    	ret = HAL_I2C_Master_Receive(&hi2c1, DHT20, buf, 7, 100);
    	HAL_Delay(100);
    	   if(ret == HAL_OK){
    		   return DHT20_Convert();
    	   }

    }
    return DHT20_ERROR_BYTES_ALL_ZERO;
}

int DHT20_Convert(){
	   //  convert temperature
	   uint32_t raw = buf[1];
	   raw <<= 8;
	   raw += buf[2];
	   raw <<= 4;
	   raw += (buf[3] >> 4);
	   humidity = raw * 9.5367431640625e-5;   // ==> / 1048576.0 * 100%;
	   HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "Humid=%.2f\r\n", humidity), 1000);

		//  convert humidity
	    raw = (buf[3] & 0x0F);
	    raw <<= 8;
	    raw += buf[4];
	    raw <<= 8;
	    raw += buf[5];
	    temperature = raw * 1.9073486328125e-4 - 50;  //  ==> / 1048576.0 * 200 - 50;
	    HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "temp=%f\r\n", temperature), 1000);

	    // Checksum
	    uint8_t crc = DHT20_crc8(buf, 6);
	    if(crc != buf[6]){
//	      	HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!CRC=%s#\r\n", "NOT OK"), 1000);
	    	return DHT20_ERROR_CHECKSUM;
	    }
//		HAL_UART_Transmit(&huart2 , (void *)str , sprintf(str, "!CRC=%s#\r\n", "OK"), 1000);
	    return DHT20_OK;
}

