#include "inc/tm4c123gh6pm.h"
#include "inc/STD_TYPES.h"
#include "inc/GPIO_CNFG.h"
#include "inc/GPIO.h"
#include "inc/LCD.h"

/***************************************************************
*					DG12 -----------> C5
*					DG2  -----------> C6
*					DG3  -----------> C7
*					
*					A --------------> C4
*					B --------------> D2
*					C --------------> D3
*					D --------------> E2
*					E --------------> E3
*					F --------------> E4
*					G --------------> E5
*****************************************************************/

void vDISPLAY_ENABLE(uint8 DISNUM){
	switch(DISNUM){
		case DG1:
			vGPIODATA_RESET(GPIOC, DG1);
			break;
		case DG2:
			vGPIODATA_RESET(GPIOC, DG2);
			break;
		case DG3:
			vGPIODATA_RESET(GPIOC, DG3);
			break;
	}
}

void vDISPLAY_DISABLE(uint8 DISNUM){
	switch(DISNUM){
		case DG1:
			vGPIODATA_SET(GPIOC, DG1);
			break;
		case DG2:
			vGPIODATA_SET(GPIOC, DG2);
			break;
		case DG3:
			vGPIODATA_SET(GPIOC, DG3);
			break;
	}
}









// IF YOU INSERT A DIGIT ABOVE 999 IT WON'T WORK
void vLED_WRITE(uint16 NUM){
	int x = 100; // FOR THE MAIN LOOP 100 - 1 SECOND
	int count = 0; // FOR INTERNAL LOOP
	int Number = 0;
	int remainder = 0;
	if(NUM > 999)
		return;
	while(x--){ // SHOULD BE WHILE(x--)
		count = 10000;
		Number = NUM;
		remainder = Number % 100;
		Number = Number - remainder;
		if(Number >= 100){
			vDISPLAY_ENABLE(DG1);
			vDISPLAY_DISABLE(DG2);
			vDISPLAY_DISABLE(DG3);
			vDIGIT_NUMBER((int)(Number / 100));
		}
		else{
			vDISPLAY_ENABLE(DG1);
			vDISPLAY_DISABLE(DG2);
			vDISPLAY_DISABLE(DG3);
			vDIGIT_NUMBER((int)(Number / 100));
		}
		while(count--);
		count = 10000;
		Number = remainder;
		remainder = Number % 10;
		Number = Number - remainder;
		if(Number >= 10){
			vDISPLAY_ENABLE(DG2);
			vDISPLAY_DISABLE(DG1);
			vDISPLAY_DISABLE(DG3);
			vDIGIT_NUMBER((int)(Number / 10));
		}
		else{
			vDISPLAY_ENABLE(DG2);
			vDISPLAY_DISABLE(DG1);
			vDISPLAY_DISABLE(DG3);
			vDIGIT_NUMBER((int)(Number / 10));
		}
		while(count--);
		count = 10000;
		Number = remainder;
		vDISPLAY_ENABLE(DG3);
		vDISPLAY_DISABLE(DG1);
		vDISPLAY_DISABLE(DG2);
		vDIGIT_NUMBER((int)Number);
		while(count--);
	}
}


void vRESET_PrevNumber(){
	vGPIODATA_RESET(GPIOC, 4);
	vGPIODATA_RESET(GPIOD, 2);
	vGPIODATA_RESET(GPIOD, 3);
	vGPIODATA_RESET(GPIOE, 2);
	vGPIODATA_RESET(GPIOE, 3);
	vGPIODATA_RESET(GPIOE, 4);
	vGPIODATA_RESET(GPIOE, 5);
}

