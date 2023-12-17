// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/uart.h"
// #include "driver/gpio.h"
// #include "sdkconfig.h"
// #include "esp_log.h"
// #include "string.h"

// #define ECHO_TEST_TXD 1
// #define ECHO_TEST_RXD 3
// #define ECHO_TEST_RTS 18
// #define ECHO_TEST_CTS 19

// #define ECHO_UART_PORT_NUM UART_NUM_0
// #define ECHO_UART_BAUD_RATE 115200
// #define ECHO_TASK_STACK_SIZE 3072

// #define BUF_SIZE (1024)

// static void echo_task(void *arg)
// {
//     /* Configure parameters of an UART driver,
//      * communication pins and install the driver */
//     uart_config_t uart_config = {
//         .baud_rate = ECHO_UART_BAUD_RATE,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .source_clk = UART_SCLK_DEFAULT,
//     };
//     int intr_alloc_flags = 0;

// #if CONFIG_UART_ISR_IN_IRAM
//     intr_alloc_flags = ESP_INTR_FLAG_IRAM;
// #endif

//     ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 0, NULL, intr_alloc_flags));
//     ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
//     ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

//     // Configure a temporary buffer for the incoming data
//     uint8_t *data = (uint8_t *)malloc(BUF_SIZE);
//     char* test_str = "This is a test string.\n";
// //    uart_write_bytes(uart_num, (const char*)test_str, strlen(test_str));
//     while (1)
//     {
//         // Read data from the UART
//         // int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
//         // // Write data back to the UART
//         uart_write_bytes(ECHO_UART_PORT_NUM, (const char*)test_str, strlen(test_str));
//         // if (len)
//         // {
//         //     data[len] = '\0';
//         //     printf("Recv str: %s\r\n", (char *)data);
//         //     uart_flush(ECHO_UART_PORT_NUM);
//         // }
//     }
// }

// void app_main(void)
// {
//     xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
// }


////////////////////////////////////////////////////////////////////////////////////////////

/* UART asynchronous example, that uses separate RX and TX tasks

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/uart.h"
// #include "driver/gpio.h"
// #include "sdkconfig.h"
// #include "esp_log.h"
// #include "string.h"

// static const int RX_BUF_SIZE = 1024;

// #define TXD_PIN (GPIO_NUM_1)
// #define RXD_PIN (GPIO_NUM_3)

// #define UART UART_NUM_0

// int num = 0;

// void init(void) {
//     const uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .source_clk = UART_SCLK_APB,
//     };
//     // We won't use a buffer for sending data.
//     uart_driver_install(UART, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
//     uart_param_config(UART, &uart_config);
//     uart_set_pin(UART, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
// }

// static void tx_task(void *arg)
// {
// 	char* Txdata = (char*) malloc(30);
//     while (1)
//     {
//     	sprintf (Txdata, "Hello world index = %d\r\n", num++);
//     	uart_write_bytes(UART, Txdata, strlen(Txdata));
//         vTaskDelay(20 / portTICK_PERIOD_MS);
//     }
//     free (Txdata);
// }

// static void rx_task(void *arg)
// {
//     static const char *RX_TASK_TAG = "RX_TASK";
//     esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
//     uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE+1);
//     while (1) {
//         const int rxBytes = uart_read_bytes(UART, data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
//         if (rxBytes > 0) 
//         {
//             data[rxBytes] = '\0';
//             ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
//         }
//     }
//     free(data);
// }

// void app_main(void)
// {
//     init();
//     xTaskCreate(rx_task, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL);
//     xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-2, NULL);
// }

//////////////////////////////////////////////////////////////////////////////////////////////

// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/uart.h"
// #include "driver/gpio.h"
// #include "sdkconfig.h"
// #include "esp_log.h"

// #define ECHO_TEST_TXD (GPIO_NUM_17)
// #define ECHO_TEST_RXD (GPIO_NUM_16)
// #define ECHO_TEST_RTS 18
// #define ECHO_TEST_CTS 19

// #define ECHO_UART_BAUD_RATE 115200
// #define ECHO_TASK_STACK_SIZE 3072

// #define BUF_SIZE (1024)

// static void echo_task(void *arg)
// {
//     /* Configure parameters of an UART driver,
//      * communication pins and install the driver */
//     // Serial.begin(115200);
//     const uart_port_t uart_num = UART_NUM_2;

//     uart_config_t uart_config = {
//         .baud_rate = ECHO_UART_BAUD_RATE,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .rx_flow_ctrl_thresh = 122,
//     };
//     int intr_alloc_flags = 0;

//     ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
//     ESP_ERROR_CHECK(uart_set_pin(uart_num, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

//     // Configure a temporary buffer for the incoming data
//     uint8_t *data = (uint8_t *)malloc(BUF_SIZE);
//     const int uart_buffer_size = (1024 * 2);
//     QueueHandle_t uart_queue;

//     ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size,
//                                         uart_buffer_size, 10, &uart_queue, 0));

//     while (1)
//     {
//         // Read data from the UART
//         int len = 0;
//         ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t *)&len));
//         len = uart_read_bytes(uart_num, data, len, 100);
//         // Write data back to the UART
//         uart_write_bytes(uart_num, (const char *)data, len);
//         if (len)
//         {
//             data[len] = '\0';
//             printf("Recv str: %s\r\n", (char *)data);
//             uart_flush(uart_num);
//         }
//     }
// }

// void app_main(void)
// {
//     xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
// }

///////////////////////////////////////////

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_system.h"
// #include "esp_log.h"
// #include "driver/uart.h"
// #include "string.h"
// #include "driver/gpio.h"
// #include "stdio.h"
// #include "stdint.h"
// #include "stddef.h"
// #include "string.h"
// #include "nvs_flash.h"
// #include "esp_event.h"
// #include "esp_netif.h"

// #include "esp_log.h"
// #include "mqtt_client.h"
// #include "esp_wifi.h"
// #include "esp_netif_ip_addr.h"

// static const char *TAG = "MQTT";

// #define WIFI_SSID "WIFI_NAME_HERE"
// #define WIFI_PASSWORD "WIFI_PASSWORD_HERE"

// #define ADAFRUIT_USERNAME "ADAFRUIT_USERNAME"
// #define ADAFRUIT_AIO_KEY "AIO_KEY"

// esp_mqtt_client_handle_t client = NULL;
// uint8_t broker_connected = 0;
// static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
// {
//     esp_mqtt_event_handle_t event = event_data;
//     esp_mqtt_client_handle_t client = event->client;
//     int msg_id;
//     switch ((esp_mqtt_event_id_t)event_id)
//     {
//     case MQTT_EVENT_CONNECTED:
//         ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
//         broker_connected = 1;
//         esp_mqtt_client_subscribe(client, "MrMPTM/feeds/system-button", 1);
//         break;
//     case MQTT_EVENT_DISCONNECTED:
//         broker_connected = 0;
//         ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
//         break;
//     case MQTT_EVENT_SUBSCRIBED:
//         printf("Subcribed success\n\r");
//         break;
//     case MQTT_EVENT_UNSUBSCRIBED:

//         break;
//     case MQTT_EVENT_PUBLISHED:
//         ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
//         break;
//     case MQTT_EVENT_DATA:
//         ESP_LOGI(TAG, "MQTT_EVENT_DATA");
//         printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
//         printf("DATA=%.*s\r\n", event->data_len, event->data);
//         break;
//     case MQTT_EVENT_ERROR:
//         ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
//         if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT)
//         {
//             ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
//         }
//         break;
//     default:
//         ESP_LOGI(TAG, "Other event id:%d", event->event_id);
//         break;
//     }
// }

// static void mqtt_app_start(void)
// {

//     esp_mqtt_client_config_t mqtt_cfg = {
//         .broker.address.uri = "mqtt://io.adafruit.com:1883",
//         .broker.address.hostname = "io.adafruit.com",
//         .credentials.username = ADAFRUIT_USERNAME,
//         .credentials.set_null_client_id = 1,
//         .credentials.authentication.password = ADAFRUIT_AIO_KEY,
//     };

//     client = esp_mqtt_client_init(&mqtt_cfg);
//     /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
//     esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, &mqtt_event_handler, NULL);

//     /*Let's enqueue a few messages to the outbox to see the allocations*/
//     int msg_id;

//     /* Now we start the client and it's possible to see the memory usage for the operations in the outbox. */
//     esp_mqtt_client_start(client);
// }
// static void wifi_event_handler(void *arg, esp_event_base_t event_base,
//                                int32_t event_id, void *event_data)
// {
//     static uint8_t retry_count = 0;
//     if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
//     {
//         esp_wifi_connect();
//         retry_count = 0;
//     }
//     else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
//     {
//         if (retry_count < 3)
//         {
//             esp_wifi_connect();
//             printf("Esp retry to connect wifi\n\r");
//             retry_count++;
//         }
//     }
//     else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
//     {
//         ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
//         printf("Wifi connected, esp ip:%d.%d.%d.%d\n\r", IP2STR(&event->ip_info.ip));
//         retry_count = 0;
//     }
// }
// void wifi_connect()
// {
//     esp_netif_create_default_wifi_sta();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     esp_wifi_init(&cfg);
//     wifi_config_t wifi_config = {
//         .sta.ssid = WIFI_SSID,
//         .sta.password = WIFI_PASSWORD,
//         .sta.listen_interval = 5000};
//     esp_event_handler_register(WIFI_EVENT,
//                                WIFI_EVENT_STA_START,
//                                &wifi_event_handler,
//                                NULL);
//     esp_event_handler_register(IP_EVENT,
//                                IP_EVENT_STA_GOT_IP,
//                                &wifi_event_handler,
//                                NULL);
//     esp_wifi_set_mode(WIFI_MODE_STA);
//     esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
//     esp_wifi_start();
// }

// static void updateSensor(void *arg)
// {
//     while (1)
//     {
//         if (client != NULL && broker_connected)
//             esp_mqtt_client_enqueue(client, "MrMPTM/feeds/soil-moisture", "10.5", 0, 1, 0, true);
//         // printf("Hello\n\r");
//         vTaskDelay(2000 / portTICK_PERIOD_MS);
//     }
// }

// static const int RX_BUF_SIZE = 1024;

// #define TXD_PIN (GPIO_NUM_17)
// #define RXD_PIN (GPIO_NUM_16)

// #define UART_NUM UART_NUM_2

// void init(void) {
//     const uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .source_clk = UART_SCLK_DEFAULT,
//     };
//     // We won't use a buffer for sending data.
//     uart_driver_install(UART_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
//     uart_param_config(UART_NUM, &uart_config);
//     uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
// }

// static void rx_task(void *arg)
// {
//     static const char *RX_TASK_TAG = "RX_TASK";
//     esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
//     int rx_read_index = 0;
//     uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE + 1);
//     int check_sum;
//     while (1) {
//         const int rxBytes = uart_read_bytes(UART_NUM, data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
//         if (rxBytes > 0) {
//             data[rxBytes] = '\0';
//             if ((data[rx_read_index] == 's')
//                && (data[(rx_read_index + 1) % RX_BUF_SIZE] == 't')
//                && (data[(rx_read_index + 2) % RX_BUF_SIZE] == 'r')) { /* "str" found at correct position */
//                 int sum = 0;
//                 for (int i = 0 ; i < 8 ; i++) {
//                     sum += data[(rx_read_index + i) % RX_BUF_SIZE];
//                 }
//                 check_sum = sum & 0xFF;
//                 if (data[(rx_read_index + 8) % RX_BUF_SIZE] == check_sum) { /* check sum is OK */
// 					uint16_t Humi = (data[(rx_read_index + 4) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 5) % RX_BUF_SIZE];
// 					uint16_t Temp = (data[(rx_read_index + 6) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 7) % RX_BUF_SIZE];
// 					uint16_t Sum = data[(rx_read_index + 8) % RX_BUF_SIZE];
// 					ESP_LOGI(RX_TASK_TAG, "Read %d bytes; Humidity: %d; Temperature: %d; Sum: %d, Checksum: %d", rxBytes, Humi, Temp, Sum, check_sum);
// 					uart_write_bytes(UART_NUM, "OK\n", 3);
//                 }
//                 else {
//                 	uart_write_bytes(UART_NUM, "Corrupted\n", 10);
//                 }
//             }

//         }
//     }
//     free(data);
// }

// void app_main(void)
// {
//     init();
//     xTaskCreate(rx_task, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
//     // Turn on this to test publishing
//     // xTaskCreate(&updateSensor, "Update sensor", 4096, NULL, 1, NULL);
// }


//////////////////////////'
/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
/* MQTT (over TCP) Example with custom outbox

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stddef.h>
// #include <string.h>
// #include "esp_system.h"
// #include "nvs_flash.h"
// #include "esp_event.h"
// #include "esp_netif.h"

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// #include "esp_log.h"
// #include "mqtt_client.h"
// #include "esp_wifi.h"
// #include "esp_netif_ip_addr.h"

// #include "driver/uart.h"
// #include "driver/gpio.h"

// static const int RX_BUF_SIZE = 1024;

// #define TXD_PIN (GPIO_NUM_17)
// #define RXD_PIN (GPIO_NUM_16)

// #define UART_NUM UART_NUM_2

// static const char *TAG = "MQTT";

// #define WIFI_SSID "Home Coffee 2"
// #define WIFI_PASSWORD "hihomies"

// #define ADAFRUIT_USERNAME "jakunai"
// #define ADAFRUIT_AIO_KEY "aio_IApz30pWRQDXotR14VHQKfcPwAW3"

// /*
//  * @brief Event handler registered to receive MQTT events
//  *
//  *  This function is called by the MQTT client event loop.
//  *
//  * @param handler_args user data registered to the event.
//  * @param base Event base for the handler(always MQTT Base in this example).
//  * @param event_id The id for the received event.
//  * @param event_data The data for the event, esp_mqtt_event_handle_t.
//  */
// esp_mqtt_client_handle_t client = NULL;
// uint8_t broker_connected = 0;
// static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
// {
//     esp_mqtt_event_handle_t event = event_data;
//     esp_mqtt_client_handle_t client = event->client;
//     int msg_id;
//     switch ((esp_mqtt_event_id_t)event_id)
//     {
//     case MQTT_EVENT_CONNECTED:
//         ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
//         broker_connected = 1;
//         // cái này viết cái url của feed vô
//         esp_mqtt_client_subscribe(client, "jakunai/feeds/led", 1);
//         esp_mqtt_client_subscribe(client, "jakunai/feeds/buzzer", 1);
//         esp_mqtt_client_subscribe(client, "jakunai/feeds/soil-humid", 1);
//         esp_mqtt_client_subscribe(client, "jakunai/feeds/temp", 1);
//         break;
//     case MQTT_EVENT_DISCONNECTED:
//         broker_connected = 0;
//         ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
//         break;
//     case MQTT_EVENT_SUBSCRIBED:
//         printf("Subcribed success\n\r");
//         break;
//     case MQTT_EVENT_UNSUBSCRIBED:

//         break;
//     case MQTT_EVENT_PUBLISHED:
//         ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
//         break;
//     case MQTT_EVENT_DATA:
//         ESP_LOGI(TAG, "MQTT_EVENT_DATA");
//         printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
//         printf("DATA=%.*s\r\n", event->data_len, event->data);
//         break;
//     case MQTT_EVENT_ERROR:
//         ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
//         if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT)
//         {
//             ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
//         }
//         break;
//     default:
//         ESP_LOGI(TAG, "Other event id:%d", event->event_id);
//         break;
//     }
// }

// static void mqtt_app_start(void)
// {

//     esp_mqtt_client_config_t mqtt_cfg = {
//         .broker.address.uri = "mqtt://io.adafruit.com:1883",
//         .broker.address.hostname = "io.adafruit.com",
//         .credentials.username = ADAFRUIT_USERNAME,
//         .credentials.set_null_client_id = 1,
//         .credentials.authentication.password = ADAFRUIT_AIO_KEY,
//     };

//     client = esp_mqtt_client_init(&mqtt_cfg);
//     /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
//     esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, &mqtt_event_handler, NULL);

//     /*Let's enqueue a few messages to the outbox to see the allocations*/
//     int msg_id;

//     /* Now we start the client and it's possible to see the memory usage for the operations in the outbox. */
//     esp_mqtt_client_start(client);
// }
// static void wifi_event_handler(void *arg, esp_event_base_t event_base,
//                                int32_t event_id, void *event_data)
// {
//     static uint8_t retry_count = 0;
//     if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
//     {
//         esp_wifi_connect();
//         retry_count = 0;
//     }
//     else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
//     {
//         if (retry_count < 3)
//         {
//             esp_wifi_connect();
//             printf("Esp retry to connect wifi\n\r");
//             retry_count++;
//         }
//     }
//     else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
//     {
//         ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
//         printf("Wifi connected, esp ip:%d.%d.%d.%d\n\r", IP2STR(&event->ip_info.ip));
//         retry_count = 0;
//     }
// }
// void wifi_connect()
// {
//     esp_netif_create_default_wifi_sta();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     esp_wifi_init(&cfg);
//     wifi_config_t wifi_config = {
//         .sta.ssid = WIFI_SSID,
//         .sta.password = WIFI_PASSWORD,
//         .sta.listen_interval = 5000};
//     esp_event_handler_register(WIFI_EVENT,
//                                WIFI_EVENT_STA_START,
//                                &wifi_event_handler,
//                                NULL);
//     esp_event_handler_register(IP_EVENT,
//                                IP_EVENT_STA_GOT_IP,
//                                &wifi_event_handler,
//                                NULL);
//     esp_wifi_set_mode(WIFI_MODE_STA);
//     esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
//     esp_wifi_start();
// }

// static void updateSensor(uint16_t humid, uint16_t temp)
// {
//     static const char *updateSensorTask = "UpdateSensor";
//     esp_log_level_set(updateSensorTask , ESP_LOG_INFO);
//     // Đổi uint16 thành string
//     int humid_length = snprintf(NULL, 0, "%d", humid);
//     int temp_length = snprintf(NULL, 0, "%d", temp);

//     char *strHumid = malloc(humid_length + 1);
//     char *strTemp = malloc(temp_length + 1);
//     ESP_LOGI(updateSensorTask, " Humidity: %d; Temperature: %d; ", humid, temp);
//     snprintf(strHumid, humid_length + 1, "%d", humid);
//     snprintf(strTemp, temp_length + 1, "%d", temp);

//     if (client != NULL && broker_connected)
//     {
//         esp_mqtt_client_enqueue(client, "jakunai/feeds/soil-humid", strHumid, 0, 1, 0, true);
//         esp_mqtt_client_enqueue(client, "jakunai/feeds/temp", strTemp, 0, 1, 0, true);
//     }

//     free(strHumid);
//     free(strTemp);
// }

// void init(void)
// {
//     const uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//         .source_clk = UART_SCLK_DEFAULT,
//     };
//     // We won't use a buffer for sending data.
//     uart_driver_install(UART_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
//     uart_param_config(UART_NUM, &uart_config);
//     uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
// }

// static void rx_task(void *arg)
// {
//     static const char *RX_TASK_TAG = "RX_TASK";
//     esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
//     int rx_read_index = 0;
//     uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
//     int check_sum;
//     while (1)
//     {
//         const int rxBytes = uart_read_bytes(UART_NUM, data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
//         if (rxBytes > 0)
//         {
//             data[rxBytes] = '\0';
//             if ((data[rx_read_index] == 's') && (data[(rx_read_index + 1) % RX_BUF_SIZE] == 't') && (data[(rx_read_index + 2) % RX_BUF_SIZE] == 'r'))
//             { /* "str" found at correct position */
//                 int sum = 0;
//                 for (int i = 0; i < 8; i++)
//                 {
//                     sum += data[(rx_read_index + i) % RX_BUF_SIZE];
//                 }
//                 check_sum = sum & 0xFF;
//                 if (data[(rx_read_index + 8) % RX_BUF_SIZE] == check_sum)
//                 { /* check sum is OK */
//                     uint16_t Humi = (data[(rx_read_index + 4) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 5) % RX_BUF_SIZE];
//                     uint16_t Temp = (data[(rx_read_index + 6) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 7) % RX_BUF_SIZE];
//                     uint16_t Sum = data[(rx_read_index + 8) % RX_BUF_SIZE];
//                     updateSensor(Humi, Temp);
//                     ESP_LOGI(RX_TASK_TAG, "Read %d bytes; Humidity: %d; Temperature: %d; Sum: %d, Checksum: %d", rxBytes, Humi, Temp, Sum, check_sum);
//                     uart_write_bytes(UART_NUM, "OK\n", 3);
//                 }
//                 else
//                 {
//                     uart_write_bytes(UART_NUM, "Corrupted\n", 10);
//                 }
//             }
//         }
//     }
//     free(data);
// }

// void app_main(void)
// {
//     ESP_LOGI(TAG, "[APP] Startup..");
//     ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
//     ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

//     esp_log_level_set("*", ESP_LOG_INFO);
//     esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
//     esp_log_level_set("MQTT_WIFI_TEST", ESP_LOG_VERBOSE);
//     esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
//     esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
//     esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
//     esp_log_level_set("custom_outbox", ESP_LOG_VERBOSE);

//     ESP_ERROR_CHECK(nvs_flash_init());
//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());

//     /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
//      * Read "Establishing Wi-Fi or Ethernet Connection" section in
//      * examples/protocols/README.md for more information about this function.
//      */
//     wifi_connect();
//     mqtt_app_start();

//     init();
//     xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
//     // Turn on this to test publishing
//     // xTaskCreate(&updateSensor, "Update sensor", 4096, NULL, 1, NULL);
// }


//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_wifi.h"
#include "esp_netif_ip_addr.h"

#include "driver/uart.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 1024;

#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)

#define UART_NUM UART_NUM_2

static const char *TAG = "MQTT";

#define WIFI_SSID "MANG DAY KTX H2-224"
#define WIFI_PASSWORD "chocaiconcac"
    
#define ADAFRUIT_USERNAME "jakunai"
#define ADAFRUIT_AIO_KEY "aio_IApz30pWRQDXotR14VHQKfcPwAW3"


/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
esp_mqtt_client_handle_t client = NULL;
uint8_t broker_connected = 0;
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        broker_connected = 1;
        // cái này viết cái url của feed vô
        esp_mqtt_client_subscribe(client, "jakunai/feeds/led2", 1);
        esp_mqtt_client_subscribe(client, "jakunai/feeds/led1", 1);
        esp_mqtt_client_subscribe(client, "jakunai/feeds/soil-humid", 1);
        esp_mqtt_client_subscribe(client, "jakunai/feeds/temp", 1);
        break;
    case MQTT_EVENT_DISCONNECTED:
        broker_connected = 0;
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        printf("Subcribed success\n\r");
        break;
    case MQTT_EVENT_UNSUBSCRIBED:

        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT)
        {
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

static void mqtt_app_start(void)
{

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://io.adafruit.com:1883",
        .broker.address.hostname = "io.adafruit.com",
        .credentials.username = ADAFRUIT_USERNAME,
        .credentials.set_null_client_id = 1,
        .credentials.authentication.password = ADAFRUIT_AIO_KEY,
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, MQTT_EVENT_ANY, &mqtt_event_handler, NULL);

    /*Let's enqueue a few messages to the outbox to see the allocations*/
    int msg_id;

    /* Now we start the client and it's possible to see the memory usage for the operations in the outbox. */
    esp_mqtt_client_start(client);
}
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    static uint8_t retry_count = 0;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
        retry_count = 0;
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if (retry_count < 3)
        {
            esp_wifi_connect();
            printf("Esp retry to connect wifi\n\r");
            retry_count++;
        }
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        printf("Wifi connected, esp ip:%d.%d.%d.%d\n\r", IP2STR(&event->ip_info.ip));
        retry_count = 0;
    }
}
void wifi_connect()
{
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    wifi_config_t wifi_config = {
        .sta.ssid = WIFI_SSID,
        .sta.password = WIFI_PASSWORD,
        .sta.listen_interval = 5000};
    esp_event_handler_register(WIFI_EVENT,
                               WIFI_EVENT_STA_START,
                               &wifi_event_handler,
                               NULL);
    esp_event_handler_register(IP_EVENT,
                               IP_EVENT_STA_GOT_IP,
                               &wifi_event_handler,
                               NULL);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();
}

// static void updateSensor(uint16_t humid, uint16_t temp, uint8_t light, uint8_t buzzer)
// {
//     // Đổi uint16 thành string
//     int humid_length = snprintf(NULL, 0, "%d", humid);
//     int temp_length = snprintf(NULL, 0, "%d", temp);
//     int light_length = snprintf(NULL, 0, "%d", humid);
//     int buzzer_length = snprintf(NULL, 0, "%d", temp);

//     char *strHumid = malloc(humid_length + 1);
//     char *strTemp = malloc(temp_length + 1);
//     char *strLight = malloc(light_length + 1);
//     char *strBuzzer = malloc(buzzer_length + 1);

//     snprintf(strHumid, humid_length + 1, "%d", humid);
//     snprintf(strTemp, temp_length + 1, "%d", temp);
//     snprintf(strLight, humid_length + 1, "%d", light);
//     snprintf(strBuzzer, temp_length + 1, "%d", buzzer);

//     if (client != NULL && broker_connected)
//     {
//         esp_mqtt_client_enqueue(client, "jakunai/feeds/soil-humid", strHumid, 0, 1, 0, true);
//         esp_mqtt_client_enqueue(client, "jakunai/feeds/temp", strTemp, 0, 1, 0, true);
//         esp_mqtt_client_enqueue(client, "jakunai/feeds/led", strLight, 0, 1, 0, true);
//         esp_mqtt_client_enqueue(client, "jakunai/feeds/buzzer", strBuzzer, 0, 1, 0, true);
//     }

//     free(strHumid);
//     free(strTemp);
//     free(strLight);
//     free(strBuzzer);
// }

static void updateSensor(uint16_t humid, uint16_t temp, uint8_t light, uint8_t buzzer)
{
    // Đổi uint16 thành string
    int humid_length = snprintf(NULL, 0, "%d", humid);
    int temp_length = snprintf(NULL, 0, "%d", temp);
    int light_length = snprintf(NULL, 0, "%d", humid);
    int buzzer_length = snprintf(NULL, 0, "%d", temp);

    char *strHumid = malloc(humid_length + 1);
    char *strTemp = malloc(temp_length + 1);
    char *strLight = malloc(light_length + 1);
    char *strBuzzer = malloc(buzzer_length + 1);

    snprintf(strHumid, humid_length + 1, "%d", humid);
    snprintf(strTemp, temp_length + 1, "%d", temp);
    snprintf(strLight, humid_length + 1, "%d", light);
    snprintf(strBuzzer, temp_length + 1, "%d", buzzer);

    if (client != NULL && broker_connected)
    {
        esp_mqtt_client_enqueue(client, "jakunai/feeds/soil-humid", strHumid, 0, 1, 0, true);
        esp_mqtt_client_enqueue(client, "jakunai/feeds/temp", strTemp, 0, 1, 0, true);
        esp_mqtt_client_enqueue(client, "jakunai/feeds/led2", strLight, 0, 1, 0, true);
        esp_mqtt_client_enqueue(client, "jakunai/feeds/led1", strBuzzer, 0, 1, 0, true);
    }

    free(strHumid);
    free(strTemp);
    free(strLight);
    free(strBuzzer);
}
void init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

// static void rx_task(void *arg)
// {
//     static const char *RX_TASK_TAG = "RX_TASK";
//     esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
//     int rx_read_index = 0;
//     uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
//     int check_sum;
//     while (1)
//     {
//         const int rxBytes = uart_read_bytes(UART_NUM, data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
//         if (rxBytes > 0)
//         {
//             data[rxBytes] = '\0';
//             if ((data[rx_read_index] == 's') && (data[(rx_read_index + 1) % RX_BUF_SIZE] == 't') && (data[(rx_read_index + 2) % RX_BUF_SIZE] == 'r'))
//             { /* "str" found at correct position */
//                 int sum = 0;
//                 for (int i = 0; i < 8; i++)
//                 {
//                     sum += data[(rx_read_index + i) % RX_BUF_SIZE];
//                 }
//                 check_sum = sum & 0xFF;
//                 if (data[(rx_read_index + 8) % RX_BUF_SIZE] == check_sum)
//                 { /* check sum is OK */
//                     uint16_t Humi = (data[(rx_read_index + 4) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 5) % RX_BUF_SIZE];
//                     uint16_t Temp = (data[(rx_read_index + 6) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 7) % RX_BUF_SIZE];
//                     uint8_t Light_Status = data[(rx_read_index + 8) % RX_BUF_SIZE];
//                     uint8_t Buzzer_Status = data[(rx_read_index + 9) % RX_BUF_SIZE];
//                     uint16_t Sum = data[(rx_read_index + 10) % RX_BUF_SIZE];
//                     updateSensor(Humi, Temp, Light_Status, Buzzer_Status);
//                     ESP_LOGI(RX_TASK_TAG, "Read %d bytes; Humidity: %d; Temperature: %d; Light: %d; Buzzer: %d; Sum: %d, Checksum: %d", rxBytes, Humi, Temp, Light_Status, Buzzer_Status, Sum, check_sum);
//                     uart_write_bytes(UART_NUM, "OK\n", 3);
//                 }
//                 else
//                 {
//                     uart_write_bytes(UART_NUM, "Corrupted\n", 10);
//                 }
//             }
//         }
//     }
//     free(data);
// }

static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    int rx_read_index = 0;
    uint8_t *data = (uint8_t *)malloc(RX_BUF_SIZE + 1);
    int check_sum;
    while (1)
    {
        const int rxBytes = uart_read_bytes(UART_NUM, data, RX_BUF_SIZE, 500 / portTICK_PERIOD_MS);
        if (rxBytes > 0)
        {
            data[rxBytes] = '\0';
            if ((data[rx_read_index] == 's') && (data[(rx_read_index + 1) % RX_BUF_SIZE] == 't'))
            { /* "str" found at correct position */
                int sum = 0;
                for (int i = 0; i < 9; i++)
                {
                    sum += data[(rx_read_index + i) % RX_BUF_SIZE];
                }
                check_sum = sum & 0xFF;
                if (data[(rx_read_index + 9) % RX_BUF_SIZE] == check_sum)
                { /* check sum is OK */
                    uint16_t Humi = (data[(rx_read_index + 3) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 4) % RX_BUF_SIZE];
                    uint16_t Temp = (data[(rx_read_index + 5) % RX_BUF_SIZE] << 8) | data[(rx_read_index + 6) % RX_BUF_SIZE];
                    uint8_t Light_Status = data[(rx_read_index + 7) % RX_BUF_SIZE];
                    uint8_t Buzzer_Status = data[(rx_read_index + 8) % RX_BUF_SIZE];
                    uint16_t Sum = data[(rx_read_index + 9) % RX_BUF_SIZE];
                    updateSensor(Humi, Temp, Light_Status, Buzzer_Status);
                    ESP_LOGI(RX_TASK_TAG, "Read %d bytes; Humidity: %d; Temperature: %d; Light1: %d; Light2: %d; Sum: %d, Checksum: %d", rxBytes, Humi, Temp, Light_Status, Buzzer_Status, Sum, check_sum);
                    uart_write_bytes(UART_NUM, "OK\n", 3);
                }
                else
                {
                    uart_write_bytes(UART_NUM, "Corrupted\n", 10);
                }
            }
        }
    }
    free(data);
}
void app_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_WIFI_TEST", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("custom_outbox", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    wifi_connect();
    mqtt_app_start();

    init();
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES, NULL);
    // Turn on this to test publishing
    // xTaskCreate(&updateSensor, "Update sensor", 4096, NULL, 1, NULL);
}
