#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "ADC_interface.h"


#define CHANNEL_NUMBER						9

/* Normal Value */
#define POT1	100
#define POT2	100
#define POT3	100
#define POT4	100
#define POT5	100
#define POT6	100

/* X Y Z POSITIONS */

/* if x > 500 negative  ,  x < 500 positive */
#define   X_NORMAL        385

/* if y > 500 negative  ,  y < 500 positive */
#define   Y_NORMAL        568

/* if  z > 500 negative  ,  z < 500 positive */
#define   Z_NORMAL        500

/* IN RANGE */
#define    X_POSITVE     385
#define    X_NEGATIVE    585

#define    Y_POSITVE     390
#define    Y_NEGATIVE    590

#define   Z_POSITVE      390
#define   Z_NEGATIVE     590

/* Choose Channel number of ADC PINS (0,1,2,3,4,5,6,7,8,9) */
u8 adc_channels[CHANNEL_NUMBER] = {0,1,3,4,5,6,7,8,9};
/* Set Number of channel */
u8 channels = CHANNEL_NUMBER;
/* Array of Data for ADC channel */
u16 analog_rx[CHANNEL_NUMBER] = {0};

/* App Function Prototype */
void SendMessage(void);

/* Entry Point */
void main()
{
	/* Initialize RCC 8Mhz */
	RCC_voidInitSysClock();

	/**********************************************************************/

	/* Enable GPIOA */
	RCC_voidEnableClock(RCC_APB2 , 2);

	/* Enable GPIOB */
	RCC_voidEnableClock(RCC_APB2 , 3);

	/* Enable USART2 */
	RCC_voidEnableClock(RCC_APB1 , 17);

	/* Enable ADC1 */
	RCC_voidEnableClock(RCC_APB2 , 9);

	/**********************************************************************/

	/* Enable Systick */
	MSTK_voidInit();

	/**********************************************************************/

	/* Transmitter_Bluetooth on USART2 */
	/* A2 = TX2 input Floating */
	MGPIO_voidSetPinDirection(GPIOA , PIN2 , OUTPUT_SPEED_50MHZ_AFPP);
	/* Initialize USART BaudRate = 9600 */
	MUSART2_voidInit();

	/**********************************************************************/

	/* Initialize ADC Multi Channel Mode */
	ADC1_voidMultiChannelInit(adc_channels[0]);

	/**********************************************************************/

	/* POTS */
	MGPIO_voidSetPinDirection(GPIOA , PIN0 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN1 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN3 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN4 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN5 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN6 , INPUT_ANALOG);

	/* ADXL335 */
	MGPIO_voidSetPinDirection(GPIOA , PIN7 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOB , PIN0 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOB , PIN1 , INPUT_ANALOG);


	/**********************************************************************/


	/* App Loop */
	while(1)
	{
		/* App Function*/
		SendMessage();

	}/* end of main while */

}/* end of main */


/* App Function Implementation */
void SendMessage(void)
{
	/* read variable from POTS and ADXL */
	ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);

	/* sabah */
	/*  F1 C                    ,F2 C                    ,F3 O                    ,F4 O                     ,F5  O                  ,REST O                   ,X IN RANGE                                                   ,Y  Negative                   ,Z IN RANGE                                                  */
	if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && ( (analog_rx[6] < X_NEGATIVE)&&(analog_rx[6] > X_POSITVE) ) && (analog_rx[7] > Y_NORMAL) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)) )
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('a');
	}

	/* MEM */
	/*  F1 C                    ,F2 C                     ,F3 C                    ,F4  C                    ,F5 O                     ,REST O                    ,X IN RANGE                                                   ,Y  Negative                   ,Z IN RANGE                                                  */
	else if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] < POT5) && (analog_rx[5] > POT6) && ( (analog_rx[6] < X_NEGATIVE)&&(analog_rx[6] > X_POSITVE) ) && (analog_rx[7] > Y_NORMAL) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)) )
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('b');
	}

	/* RAA */
	/*  F1 C                    ,F2 O                     ,F3 C                    ,F4  C                    ,F5 C                     ,REST O                    ,X IN RANGE                                                   ,Y  Negative                   ,Z IN RANGE                                                  */
	else if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && ( (analog_rx[6] < X_NEGATIVE)&&(analog_rx[6] > X_POSITVE) ) && (analog_rx[7] > Y_NORMAL) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)) )
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('c');
	}

	/* AEIN */
	/*  F1 C                    ,F2 O                     ,F3 O                    ,F4  C                    ,F5 C                     ,REST O                    ,X Positive                                                   ,Y  IN RANGE                   ,Z IN RANGE                                                  */
	else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < X_NORMAL) && ((analog_rx[7] < Y_NEGATIVE)  && (analog_rx[7] > Y_POSITVE)) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)) )
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('d');
	}

	/* Takol */
	/*  F1 O                    ,F2 O                     ,F3 C                    ,F4  C                    ,F5 C                     ,REST O                    ,X Positive                                                   ,Y  IN RANGE                   ,Z IN RANGE                                                  */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < X_NORMAL) && ((analog_rx[7] < Y_NEGATIVE)  && (analog_rx[7] > Y_POSITVE)) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)) )
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('e');
	}

	/* Maza */
	/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5  C                  ,REST O                   ,X IN RANGE                                                   ,Y  IN RANGE                                                      ,Z Positive             */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && ( (analog_rx[6] < X_NEGATIVE)&&(analog_rx[6] > X_POSITVE) )  && ( (analog_rx[7] < Y_NEGATIVE) && (analog_rx[7] > Y_POSITVE) ) && (analog_rx[8] < Z_NORMAL)  )
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('f');
	}
	/* tazhab */
	/*  F1 C                    ,F2 O                     ,F3 C                        ,F4 C                   ,F5 C                     ,REST                    ,X POSITIVE                  ,Y  IN RANGE                                                    ,Z IN RANGE                                                */
	else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < X_NORMAL) && ((analog_rx[7] < Y_NEGATIVE)  && (analog_rx[7] > Y_POSITVE)) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('g');
	}

	/* LADEI */
	/*       F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                  ,REST  C                  ,X POSITIVE                  ,Y  IN RANGE                                                    ,Z IN RANGE                                                  */
	else if((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < X_NORMAL) && ((analog_rx[7] < Y_NEGATIVE)  && (analog_rx[7] > Y_POSITVE)) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE))  )
	{/* Send Bluetooth Data */
		MUSART2_voidSendChar('h');
	}

	/* EHTBAR */
	/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                     ,REST  O                  ,X IN RANGE                  ,Y  IN RANGE                                                                                          ,Z Negative          */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && ( (analog_rx[6] < X_NEGATIVE)&&(analog_rx[6] > X_POSITVE) )  && ( (analog_rx[7] < Y_NEGATIVE) && (analog_rx[7] > Y_POSITVE) ) && (analog_rx[8] > Z_NORMAL))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('i');
	}
	/* Ready To Speak*/
	/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                     ,REST O                   ,X IN RANGE                                                      ,Y Positive                                                  ,Z IN RANGE              */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && ( (analog_rx[6] < X_NEGATIVE)&&(analog_rx[6] > X_POSITVE) ) && (analog_rx[7] < Y_NORMAL) && ((analog_rx[8] < Z_NEGATIVE) && (analog_rx[8] > Z_POSITVE)))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('0');
	}
	/* nothing doing */
	else
	{
		MUSART2_voidSendChar('z');
	}

}/* end of App Function */
