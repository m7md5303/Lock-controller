//includes: std_types, bit_math, dio, uart, servo
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "CLCD_interface.h"
#include "PWM_interface.h"
#include <util/delay.h>

void Servo_voidSetAngle(u8 Copy_u8DesiredAngle);
void Right_Response (void);
void close (void);
u8 re_close = 1;
//main
int main(void){
	//setting the input and output ports
	DIO_voidSetPinDirection(DIO_u8PORTD , 0 , DIO_u8INPUT);
    DIO_voidSetPinDirection(DIO_u8PORTD , 7 , DIO_u8INPUT);
    DIO_voidSetPinDirection(DIO_u8PORTD , 5 , DIO_u8OUTPUT);
	DIO_VoidSetPortDirection(DIO_u8PORTA,DIO_u8PORTHIGH);
	DIO_VoidSetPortDirection(DIO_u8PORTB,DIO_u8PORTHIGH);
	DIO_VoidSetPortDirection(DIO_u8PORTC,DIO_u8PORTHIGH);
	//Lighting the red LEDs and setting the pull up switch
	DIO_voidSetPinValue(DIO_u8PORTA,0,DIO_u8HIGH);
	DIO_voidSetPinValue(DIO_u8PORTA,1,DIO_u8HIGH);
	DIO_voidSetPinValue(DIO_u8PORTA,2,DIO_u8HIGH);
    DIO_voidSetPinValue(DIO_u8PORTD , 7 , DIO_u8HIGH);
    //Initializations
	PWM_voidinit();
	CLCD_voidInit();
	CLCD_voidClearDisplay();
	CLCD_voidSendString("CLOSED");
	Servo_voidSetAngle(0);
	UART_voidInit();
	while(1){
//if the switch is off then the lock will reclose if it was opened
		re_close=DIO_u8GetPinValue(DIO_u8PORTD , 7);
		//if the password was correct the uart will receive correct and then the lock is opened
		if(UART_voidReceiveData()){
			Right_Response();
		}
		 if (!re_close){
			close();
		}
	}
}
void Servo_voidSetAngle(u8 Copy_u8DesiredAngle){
	u16 Time=((Copy_u8DesiredAngle*10.5))+600;
	PWM_voidSetTopValue(20000);
	PWM_voidSetOCRValue(Time);
	_delay_ms(500);
}
void Right_Response (void){
	Servo_voidSetAngle(90);
	DIO_voidSetPinValue(DIO_u8PORTA, 7 , DIO_u8HIGH);
	DIO_voidSetPinValue(DIO_u8PORTA, 8 , DIO_u8HIGH);
	DIO_voidSetPinValue(DIO_u8PORTA,0,DIO_u8LOW);
	DIO_voidSetPinValue(DIO_u8PORTA,1,DIO_u8LOW);
	DIO_voidSetPinValue(DIO_u8PORTA,2,DIO_u8LOW);
	CLCD_voidClearDisplay();
	CLCD_voidSendString("Welcome");
}

void close (void){
	CLCD_voidClearDisplay();
	CLCD_voidSendString("CLosed");
	DIO_voidSetPinValue(DIO_u8PORTA,0,DIO_u8HIGH);
	DIO_voidSetPinValue(DIO_u8PORTA,1,DIO_u8HIGH);
	DIO_voidSetPinValue(DIO_u8PORTA,2,DIO_u8HIGH);
	Servo_voidSetAngle(0);
	DIO_voidSetPinValue(DIO_u8PORTA, 7 , DIO_u8LOW);
	DIO_voidSetPinValue(DIO_u8PORTA, 8 , DIO_u8LOW);
	re_close=1;
}
