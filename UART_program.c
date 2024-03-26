/*
 * UART_program.c
 *
 *  Created on: 12 Sep 2023
 *      Author: ????
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_register.h"
#include "UART_private.h"
#include "UART_config.h"
#include "UART_interface.h"

void UART_voidInit(void){
	u8 Local_UCSRC=0b10000110;
//Disable Double speed U2X->0
	CLR_BIT(UCSRA , 1);
//Set character size 8 bit
    CLR_BIT(UCSRB , 2);
    SET_BIT(Local_UCSRC , 1);
    SET_BIT(Local_UCSRC , 2);
//Register Select : UCSRC
    SET_BIT(Local_UCSRC , 7);
//Asynchronous Mode
    CLR_BIT(Local_UCSRC , 6);
//Disable Parity
    CLR_BIT(Local_UCSRC , 5);
    CLR_BIT(Local_UCSRC , 4);
//Select Stop bit
    SET_BIT(Local_UCSRC , 3);


//Assign the value to the register
   UCSRC = Local_UCSRC;
//Set the Baud rate to 9600 bit/sec
   UBRRL = 51;


//Enable receiver
    UART_voidReceiverEnable();
//Enable transmitter
    UART_voidTransmitterEnable();

}
void UART_voidSendData(u8 Copy_u8Data){
     while(GET_BIT(UCSRA,5)!=1){
    	 asm("NOP");
     }
     UDR=Copy_u8Data;
}
u8 UART_voidReceiveData(void){
    while(GET_BIT(UCSRA,7)!=1){
    	asm("NOP");
    }
    return UDR;
}



void UART_voidReceiverEnable(void){
	SET_BIT(UCSRB , 4);
}
void UART_voidReceiverDisable(void){
	CLR_BIT(UCSRB , 4);
}
void UART_voidTransmitterEnable(void){
	SET_BIT(UCSRB , 3);
}
void UART_voidTransmitterDisable(void){
	CLR_BIT(UCSRB , 3);
}
