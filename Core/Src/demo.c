/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: larry kiser
 */

#include <stdio.h>
#include <string.h>
#include <stm32wb55xx.h>
#include <stm32wbxx.h>
#include <system_stm32wbxx.h>
#include <core_cm4.h>

#include "LED.h"
#include "UART.h"
#include "demo.h"
//#include "stm32l4xx.h"



//static void demo_of_printf_scanf(){
//	char rxByte;
//	char *prompt = "Give Red LED control input (Y = On, N = off):\r\n" ;
//	char *LED_off = "LED is Off\r\n\r\n" ;
//	char *LED_on = "LED is On\r\n\r\n" ;
//
//	USART_Write( USART2, (uint8_t *)prompt, strlen( prompt ) ) ;
//	scanf ("%c", &rxByte);
//
//	if (rxByte == 'N' || rxByte == 'n'){
//		LED_Off();
//		USART_Write( USART2, (uint8_t *)LED_off, strlen( LED_off ) ) ;
//	}
//	else if (rxByte == 'Y' || rxByte == 'y'){
//		LED_On();
//		USART_Write( USART2, (uint8_t *)LED_on, strlen( LED_on ) ) ;
//	}
//}

static void delay_loop( int value )
{
	// spin loop consuming CPU to spend time.
	for (int i = 0; i < value; i++)
		;
}

static void init_systick()
{
	// Use the SysTick global structure pointer to do the following in this
	// exact order with separate lines for each step:
	//
	// Disable SysTick by clearing the CTRL (CSR) register.
	SysTick->CTRL = 0;
	// Set the LOAD (RVR) to 8 million to give us a 100 milliseconds timer.
	SysTick->LOAD = 0x7A1200;
	// Set the clock source bit in the CTRL (CSR) to the internal clock.
	SysTick->CTRL |= 1 << SysTick_CTRL_CLKSOURCE_Pos;
	// Set the enable bit in the CTRL (CSR) to start the timer.
	SysTick->CTRL |= 1;
}

static void delay_systick()
{
	// Using the SysTick global structure pointer do the following:
	// Create a for loop that loops 10 times
	// Inside that for loop check the COUNTFLAG bit in the CTRL (CSR)
	// register in a loop. When that bit is set exit this inner loop
	// to do another pass in the outer loop of 10.
	int outer_counter;
	int count_complete;
	for (outer_counter=0; (outer_counter==10) ; outer_counter++){
		count_complete = 0;
		while(count_complete == 0){
			count_complete = SysTick->CTRL |= SysTick_CTRL_COUNTFLAG_Msk;
		}
	}
}

static void demo_of_UART_print(int a){
	//int n ;
	//uint8_t buffer[BUFFER_SIZE];

	//n = sprintf((char *)buffer, "a = %d\r\n", a);
	//USART_Write(USART2, buffer, n);

	//delay_loop( 8000000 ) ;	// comment this out when you are ready to test delay_systick
	delay_systick() ;	// enable this when you are ready to test

	LED_Toggle();
}

void run_demo(){
	int a = 0;

	init_systick() ;

	while (1){
		//demo_of_printf_scanf();
		demo_of_UART_print(a);
		a++;
	}
}

