#include "switch.h"

//Switch 1: PC4, Switch 2: PD0

//These check the switches to see if they are pressed or not
//If the button has been pressed, it reads as 0, so we flip that into
//a 1 so it makes sense (I think I can change that, but I'm done
//messing with these button settings). 🕺🕺🕺

int Is_Switch_1_Pressed(void){
	GPIO_PinState is_on = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4);
	return !is_on;
}

int Is_Switch_2_Pressed(void){
	uint16_t is_on = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0);
	return !is_on;
}
