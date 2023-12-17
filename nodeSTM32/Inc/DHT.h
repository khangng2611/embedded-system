/*
 * DHT.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Acer
 */

#ifndef INC_DHT_H_
#define INC_DHT_H_

#include "main.h"
#include <stdio.h>

#define DHT20 0x70

#define DHT20_OK                             0
#define DHT20_ERROR_CHECKSUM                -10
#define DHT20_ERROR_CONNECT                 -11
#define DHT20_MISSING_BYTES                 -12
#define DHT20_ERROR_BYTES_ALL_ZERO          -13
#define DHT20_ERROR_READ_TIMEOUT            -14
#define DHT20_ERROR_LASTREAD                -15

void 			  DHT_scanI2CAddresses();
int				  DHT20_Read          ();
uint8_t           DHT20_isConnected   ();
uint8_t           DHT20_readStatus    ();
uint8_t           DHT20_getAddress    ();
float    		  DHT20_getHumid  	();
float             DHT20_getTemp		();
int 			  DHT20_Convert       ();
uint8_t 		  DHT20_crc8          (uint8_t *ptr, uint8_t len);
uint8_t			  DHT20_requestData   ();
uint8_t           DHT20_resetRegister (uint8_t reg);
void              DHT20_resetSensor		  ();
//  OFFSET  1st order adjustments
void             DHT20_setHumidOffset (float offset);
void             DHT20_setTemperatureOffset(float offset);
float            DHT20_getHumidOffset ();
float            DHT20_getTemperatureOffset();


#endif /* INC_DHT_H_ */
