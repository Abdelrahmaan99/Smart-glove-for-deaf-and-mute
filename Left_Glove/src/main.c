#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "ADC_interface.h"

#define CHANNEL_NUMBER						9

/* Normal Value */
#define POT1	30
#define POT2	30
#define POT3	30
#define POT4	30
#define POT5	30
#define POT6	980


/* X Y Z POSITIONS */
#define    MAX_POSITVE     400
#define    MIN_NEGATIVE    530

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
	/*  F1 C                    ,F2 C                    ,F3 O                    ,F4 O                     ,F5  O                  ,REST O                  ,Y  Negative                */
	if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] > POT6) && (analog_rx[7] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('a');
	}

	/* elkhair */
	/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5  C                  ,REST O                      ,Y  Negative               */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[7] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('b');
	}

	/*ana*/
	/*  F1 C                    ,F2 O                     ,F3 C                        ,F4 C                   ,F5 C                     ,REST C                    ,X POSITIVE                */
	else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('c');
	}

	/* AEIN */
	/*       F1 C                     ,F2 O                    ,F3 O                    ,F4  C                   ,F5 C                    ,REST O                 ,X Positive                 */
	else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('d');
	}
	/* LADEI */
	/*       F1 O                    ,F2 C                     ,F3 C                    ,F4 C                   ,F5 C                     ,REST  C                ,X POSITIVE                */
	else if((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		trace_printf("LADEI\n");
		MUSART2_voidSendChar('e');
	}

	/* EHTBAR */
	/*       F1 O                     ,F2 O                    ,F3 O                   ,F4 O                    ,F5 O                     ,REST  O                 ,Z Negative                 */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] > POT6) && (analog_rx[8] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('f');
	}

	/* wdaa3n */
	/*      F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5  O                  ,REST O                  ,Y  Negative                */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] > POT6) && (analog_rx[7] > MIN_NEGATIVE))
	{
		/* Send Bluetooth Data */
		trace_printf("wdaa3n\n");
		MUSART2_voidSendChar('g');
	}

	/*Ready To Speak*/
	/*       F1 O                    ,F2 O                     ,F3 O                    ,F4 O                    ,F5 O                    ,REST O                 ,Y Positive               */
	else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] > POT6) && (analog_rx[7] < MAX_POSITVE))
	{
		/* Send Bluetooth Data */
		MUSART2_voidSendChar('h');
	}
	/* nothing doing */
	else
	{
		MUSART2_voidSendChar('z');
	}

}/* end of App Function */
