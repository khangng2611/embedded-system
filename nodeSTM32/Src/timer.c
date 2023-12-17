/*
 * timer.c
 *
 *  Created on: Dec 16, 2023
 *      Author: Acer
 */


#include "timer.h"

#define Timer_Cycle 10

int timer1_counter = 0;
int timer2_counter = 0;
int timer3_counter = 0;

int timer1_flag = 0;
int timer2_flag = 0;
int timer3_flag = 0;


void setTimer1 (int duration) {
	timer1_counter = duration/Timer_Cycle;
	timer1_flag = 0;
}

void setTimer2 (int duration) {
	timer2_counter = duration/Timer_Cycle;
	timer2_flag = 0;
}

void setTimer3 (int duration) {
	timer3_counter = duration/Timer_Cycle;
	timer3_flag = 0;
}

void timerRun(){
	if(timer1_counter > 0) {
		timer1_counter--;
		if(timer1_counter <= 0) {
			timer1_flag = 1;
		}
	}

	if(timer2_counter > 0) {
		timer2_counter--;
		if(timer2_counter <= 0) {
			timer2_flag = 1;
		}
	}

	if(timer3_counter > 0) {
		timer3_counter--;
		if(timer3_counter <= 0) {
			timer3_flag = 1;
		}
	}
}
