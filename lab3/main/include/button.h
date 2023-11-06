#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "driver/gpio.h"

// #define USE_DOUBLE_CLICK

#define NUM_OF_BTN 1
#define NORMAL_STATE 1
#define PRESSED_STATE 0
#define TIMER_CYCLE 10
#define DOUBLE_CLICK_INTERVAL 500
void BTN_INIT(gpio_num_t port, uint8_t idx);
void button_reading(int idx);
void reset_button_flag(int idx);
int button_pressed(int idx);

int button_pressed_1s(int idx);

#ifdef USE_DOUBLE_CLICK
int button_doubleClicked(int idx);
extern int flagForDoubleClicked[NUM_OF_BTN];
#endif

#endif /* INC_BUTTON_H_ */