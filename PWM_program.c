/*
 * PWM_program.c
 *
 *  Created on: 5 Sep 2023
 *      Author: ????
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PWM_register.h"
#include "PWM_private.h"
#include "PWM_interface.h"
#include "PWM_config.h"


void PWM_voidinit(void){
	//clear on compare match, set on top
	//toggle the functionality for the opposite operations
	SET_BIT(TCCR1A , 7);
	CLR_BIT(TCCR1A , 6);

	//select Fast PWM (Mode14)
	SET_BIT(TCCR1A , 1);
	CLR_BIT(TCCR1A , 0);
	SET_BIT(TCCR1B , 4);
	SET_BIT(TCCR1B , 3);

	//Clock pre-scalar selection:Division by 8 Mode
	CLR_BIT(TCCR1B , 2);
	SET_BIT(TCCR1B , 1);
	CLR_BIT(TCCR1B , 0);
}
void PWM_voidSetTopValue(u16 Copy_u16TopValue){
          ICR1 = Copy_u16TopValue;
}
void PWM_voidSetOCRValue(u16 Copy_u16OCRValue){
          OCR1A = Copy_u16OCRValue;
}



