/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    LPC845_USART_Interrupt.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_usart.h"
#include "fifo.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

char transmit = false;
char dato;

/*Variable FIFOs definitions */
#define GPS_BUFFER_SIZE 25
unsigned char GPS_Buffer[GPS_BUFFER_SIZE];
union _flag GPS_Flag;
struct _index GPS_Index;
#define GPS_FIFO_Empty FIFO_Empty(&GPS_Flag)
#define GPS_FIFO_Transmit_Set FIFO_Transmit_Set(&GPS_Flag)
#define GPS_FIFO_Transmit_Clear FIFO_Transmit_Clear(&GPS_Flag)
#define GPS_FIFO_Transmit_Get FIFO_Transmit_Get(&GPS_Flag)

/* USART0_IRQn interrupt handler */
void USART0_USART_IRQHANDLER(void) {

  /*  Place your code here */
	/* Consultamos si llego un dato	 */
	if(USART_GetStatusFlags(USART0_PERIPHERAL) & kUSART_RxReady){
		dato = USART_ReadByte(USART0_PERIPHERAL);
		FIFO_Write(&GPS_Flag, &GPS_Index, GPS_BUFFER_SIZE, GPS_Buffer, dato);

		if(dato == 0x0D){
			USART_EnableInterrupts(USART0_PERIPHERAL, kUSART_TxReadyInterruptEnable);
			USART_WriteByte(USART0_PERIPHERAL, FIFO_Read(&GPS_Flag, &GPS_Index, GPS_BUFFER_SIZE, GPS_Buffer));
			GPS_FIFO_Transmit_Set;
		}
	}

	if((USART_GetStatusFlags(USART0_PERIPHERAL) & kUSART_TxReady) && GPS_FIFO_Transmit_Get && (USART_GetEnabledInterrupts(USART0_PERIPHERAL) & kUSART_TxReadyInterruptEnable)){
		USART_WriteByte(USART0_PERIPHERAL, FIFO_Read(&GPS_Flag, &GPS_Index, GPS_BUFFER_SIZE, GPS_Buffer));
		if(GPS_FIFO_Empty){
			USART_DisableInterrupts(USART0_PERIPHERAL, kUSART_TxReadyInterruptEnable);
			GPS_FIFO_Transmit_Clear;
		}
	}




  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    FIFO_Init(&GPS_Flag, &GPS_Index);


    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
    	i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
