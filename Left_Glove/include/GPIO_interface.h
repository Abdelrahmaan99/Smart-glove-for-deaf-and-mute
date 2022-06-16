/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 15 August 2021                       */
/* Version     : V01                                  */
/* Description : GPIO REGISTER                        */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/* PIN VALUE */
#define	HIGH						    1
#define	LOW							    0

#define GPIOA 						    0
#define GPIOB 						    1
#define GPIOC 						    2


#define PIN0						    0
#define PIN1						    1
#define PIN2						    2
#define PIN3						    3
#define PIN4						    4
#define PIN5						    5
#define PIN6						    6
#define PIN7						    7
#define PIN8						    8
#define PIN9						    9
#define PIN10						    10
#define PIN11						    11
#define PIN12						    12
#define PIN13						    13
#define PIN14						    14
#define PIN15						    15

/* PIN_Mode */
#define INPUT_ANALOG				    0b0000
#define INPUT_FLOATING				    0b0100
#define INPUT_PULL_UP_DOWN			    0b1000


#define OUTPUT_SPEED_10MHZ_PP		    0b0001
#define OUTPUT_SPEED_10MHZ_OD		    0b0101
#define OUTPUT_SPEED_10MHZ_AFPP		    0b1001
#define OUTPUT_SPEED_10MHZ_PPOD		    0b1101

#define OUTPUT_SPEED_2MHZ_PP		    0b0010
#define OUTPUT_SPEED_2MHZ_OD		    0b0110
#define OUTPUT_SPEED_2MHZ_AFPP		    0b1010
#define OUTPUT_SPEED_2MHZ_PPOD		    0b1110


#define OUTPUT_SPEED_50MHZ_PP			0b0011
#define OUTPUT_SPEED_50MHZ_OD			0b0111
#define OUTPUT_SPEED_50MHZ_AFPP			0b1011
#define OUTPUT_SPEED_50MHZ_PPOD			0b1111

/***********************************************************/
/*Half PORT Mode*/
#define PORT_INPUT_ANALOG				0x00000000
#define PORT_INPUT_FLOATING				0x44444444
#define PORT_INPUT_PULL_UP_DOWN			0x88888888

#define PORT_OUTPUT_SPEED_10MHZ_PP		0x11111111
#define PORT_OUTPUT_SPEED_10MHZ_OD		0x55555555
#define PORT_OUTPUT_SPEED_10MHZ_AFPP    0x99999999
#define PORT_OUTPUT_SPEED_10MHZ_PPOD	0xDDDDDDDD

#define PORT_OUTPUT_SPEED_2MHZ_PP		0x22222222
#define PORT_OUTPUT_SPEED_2MHZ_OD		0x66666666
#define PORT_OUTPUT_SPEED_2MHZ_AFPP		0xAAAAAAAA
#define PORT_OUTPUT_SPEED_2MHZ_PPOD		0xEEEEEEEE

#define PORT_OUTPUT_SPEED_50MHZ_PP		0x33333333
#define PORT_OUTPUT_SPEED_50MHZ_OD		0x77777777
#define PORT_OUTPUT_SPEED_50MHZ_AFPP	0xBBBBBBBB
#define PORT_OUTPUT_SPEED_50MHZ_PPOD	0xFFFFFFFF
/***********************************************************/


void MGPIO_voidSetPinDirection(u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Mode);

void MGPIO_voidSetPinValue(u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value);

u8 MGPIO_u8GetPinValue(u8 Copy_u8PORT , u8 Copy_u8PIN);


/***********************************************************/
/* Make by me*/
void MGPIO_voidSetLowPortDirection(u8 Copy_u8PORT , u32 Copy_u8Mode);

void MGPIO_voidSetHighPortDirection(u8 Copy_u8PORT , u32 Copy_u8Mode);

void MGPIO_voidWritePortValue(u8 Copy_u8PORT , u16 Copy_u8Value);
/***********************************************************/

void MGPIO_voidSetPinBSRR(u8 Copy_u8PORT , u8 Copy_u8PIN);
void MGPIO_voidResetPinBSRR(u8 Copy_u8PORT , u8 Copy_u8PIN);
void MGPIO_voidResetPinBRR(u8 Copy_u8PORT , u8 Copy_u8PIN);
void MGPIO_voidLockPin(u8 Copy_u8PORT , u8 Copy_u8PIN);

#endif
