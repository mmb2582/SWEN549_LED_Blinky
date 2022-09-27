/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: larry kiser & mallory
 */

#include <stdio.h>
#include <string.h>
#include <stm32wb55xx.h>
#include <stm32wbxx.h>
#include <system_stm32wbxx.h>
#include <core_cm4.h>

#include "LED.h"
#include "demo.h"
#include "switch.h"
#include "main.h"


static void delay_loop( int value )
{
	// spin loop consuming CPU to spend time.
	for (int i = 0; i < value; i++)
		;
}

static void increase_cycle_time(void){
	cycle_time = cycle_time / 2;
	SysTick->LOAD = cycle_time;
}

static void decrease_cycle_time(void){
	//make sure we don't get a negative cycle time
	if (cycle_time <= 500000){
		cycle_time = 1;
	}
	else{
		cycle_time = cycle_time*2;
	}
	SysTick->LOAD = cycle_time;
}

void run_demo(){

	while (1){

		//enable these once you get the buttons to work
		if (Is_Switch_1_Pressed()){
			decrease_cycle_time();
		}
		else if(Is_Switch_2_Pressed()){
			increase_cycle_time();
		}
		delay_loop(3200000);
	}
}

