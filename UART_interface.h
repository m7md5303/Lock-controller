/*
 * UART_interface.h
 *
 *  Created on: 12 Sep 2023
 *      Author: ????
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);
void UART_voidSendData(u8 Copy_u8Data);
u8 UART_voidReceiveData(void);
void UART_voidReceiverEnable(void);
void UART_voidReceiverDisable(void);
void UART_voidTransmitterEnable(void);
void UART_voidTransmitterDisable(void);

#endif /* UART_INTERFACE_H_ */
