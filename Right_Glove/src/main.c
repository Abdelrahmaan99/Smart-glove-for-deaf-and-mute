#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "ADC_interface.h"
#include "DfPlayer_interface.h"


/* Folder Number */
#define DFP_Folder1							1
#define DFP_Folder2							2
#define DFP_Folder3							3

/* Track Number */
#define DFP_Track1							1
#define DFP_Track2							2
#define DFP_Track3							3
#define DFP_Track4							4
#define DFP_Track5							5
#define DFP_Track6							6
#define DFP_Track7							7
#define DFP_Track8							8
#define DFP_Track9							9

#define DFP_FOLDER							0
#define DFP_TRACK							1

#define CHANNEL_NUMBER						9

/* Normal Value */
#define POT1	100
#define POT2	50
#define POT3	50
#define POT4	30
#define POT5	50
#define POT6	20

/* X Y Z POSITIONS */
#define    MAX_POSITVE     400
#define    MIN_NEGATIVE    530

/* Choose Channel number of ADC PINS (0,1,2,3,4,5,6,7,8,9) */
u8 adc_channels[CHANNEL_NUMBER] = {0,1,2,4,5,6,7,8,9};
/* Set Number of channel */
u8 channels = CHANNEL_NUMBER;
/* Array of Data for ADC channel */
u16 analog_rx[CHANNEL_NUMBER] = {0};

/* App Function Prototype */
void SignLanguage(void);

/* Entry Point */
void main()
{
	/* Initialize RCC 8Mhz */
	RCC_voidInitSysClock();

	/************************/

	/* Enable GPIOA */
	RCC_voidEnableClock(RCC_APB2 , 2);

	/* Enable GPIOB */
	RCC_voidEnableClock(RCC_APB2 , 3);

	/* Enable USART1 */
	RCC_voidEnableClock(RCC_APB2 , 14);

	/* Enable USART2 */
	RCC_voidEnableClock(RCC_APB1 , 17);

	/* Enable ADC1 */
	RCC_voidEnableClock(RCC_APB2 , 9);

	/************************/

	/* Enable Systick */
	MSTK_voidInit();

	/************************/
	/* Receiver_Bluetooth on USART2 */
	/* A3 = RX2 input Floating */
	MGPIO_voidSetPinDirection(GPIOA , PIN3 , INPUT_FLOATING);
	/* Initialize USART BaudRate = 9600 */
	MUSART2_voidInit();

	/* DF-Player on USART1 */
	/* A9  = TX1 out 50MHz */
	MGPIO_voidSetPinDirection(GPIOA , PIN9 , OUTPUT_SPEED_50MHZ_AFPP);
	/* A10 = RX1 input Floating */
	MGPIO_voidSetPinDirection(GPIOA , PIN10 , INPUT_FLOATING);
	/* Initialize USART BaudRate = 9600 */
	MUSART1_voidInit();

	/* Receiver_Bluetooth on USART2 */
	/* A3 = RX2 input Floating */
	MGPIO_voidSetPinDirection(GPIOA , PIN3 , INPUT_FLOATING);
	/* Initialize USART BaudRate = 9600 */
	MUSART2_voidInit();

	/************************/

	/* Initialize ADC Multi Channel Mode */
	ADC1_voidMultiChannelInit(adc_channels[0]);

	/************************/

	/* POTS */
	MGPIO_voidSetPinDirection(GPIOA , PIN0 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN1 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN2 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN4 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN5 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOA , PIN6 , INPUT_ANALOG);

	/* ADXL335 */
	MGPIO_voidSetPinDirection(GPIOA , PIN7 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOB , PIN0 , INPUT_ANALOG);
	MGPIO_voidSetPinDirection(GPIOB , PIN1 , INPUT_ANALOG);

	/* RGB */
	MGPIO_voidSetPinDirection(GPIOA , PIN8  , OUTPUT_SPEED_50MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN11 , OUTPUT_SPEED_50MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN12 , OUTPUT_SPEED_50MHZ_PP);

	/************************/

	/* When glove will turn on RGB LED will red */
	/* RED */
	MGPIO_voidSetPinValue(GPIOA , PIN8  , LOW);
	MGPIO_voidSetPinValue(GPIOA , PIN11 , HIGH);
	MGPIO_voidSetPinValue(GPIOA , PIN12 , HIGH);

	/* App Loop */
	while(1)
	{
		/* App Function*/
		SignLanguage();

	}/* end of main while */

}/* end of main */


/* App Function Implementation */
void SignLanguage(void)
{
	/* Declare and Initialize Local Variable */
	int Indx_record[10][2] = {0};
	u8 Local_u8RecordCounter = 0;
	u8 Local_u8Counter;
	u8 Local_u8BlutoothData;
	u8 Local_u8Lock = 0;

	ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
	/* Arabic language <- F1 C */
	if(analog_rx[1] > POT1)
	{
		while(1)
		{
			/* PURPLE */
			MGPIO_voidSetPinValue(GPIOA , PIN8  , LOW);
			MGPIO_voidSetPinValue(GPIOA , PIN11 , HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN12 , LOW);

			/* read variable from POTS , ADXL and Bluetooth */
			ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
			Local_u8BlutoothData = MUSART2_u8Receive();

			/* sabah */
			/*  F1 C                    ,F2 C                    ,F3 O                    ,F4 O                    ,F5  O                   ,REST O                  ,Y Negative                        ,Left Hand                */
			if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE) && (Local_u8BlutoothData == 'a'))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track1;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE) && (Local_u8BlutoothData == 'a'))
				{
					/* read variable from POTS , ADXL and Bluetooth */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}

			/* elkhair */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5  C                  ,REST O                      ,Y  Negative               */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track2;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* keifa */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5  C                  ,REST O                      ,Z Positive                */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[8] < MAX_POSITVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track3;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[8] < MAX_POSITVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* halek -- arak lahkn */
			/*  F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST  O                   ,X POSITIVE                */
			else if((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
			{
				MSTK_voidSetBusyWait(500);
				ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);

				/* Arak lahkn */
				/*  F1 O                    ,F2 O                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST  O              ,X POSITIVE                */
				if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track9;

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
					{
						/* read variable from POTS , ADXL */
						ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					}
				}

				/* halek */
				else
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track4;

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[8] < MAX_POSITVE))
					{
						/* read variable from POTS , ADXL */
						ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					}
				}
			}

			/* OMAR */
			/* AEIN */
			/* Left Hand */
			else if((Local_u8BlutoothData == 'd'))
			{
				while(Local_u8Lock == 0)
				{
					/* read variable from Bluetooth */
					Local_u8BlutoothData = MUSART2_u8Receive();

					/* MEM */
					/* Left Hand */
					if(Local_u8BlutoothData == 'b')
					{
						Local_u8Lock = 1;
					}

				}

				Local_u8Lock = 0;

				/* Still in this loop until new word*/
				while(Local_u8BlutoothData == 'b')
				{
					/* read variable from Bluetooth */
					Local_u8BlutoothData = MUSART2_u8Receive();
				}

				while(Local_u8Lock == 0)
				{
					/* read variable from Bluetooth */
					Local_u8BlutoothData = MUSART2_u8Receive();

					/* RAA */
					/* Left Hand */
					if((Local_u8BlutoothData == 'c') && (Local_u8Lock == 0))
					{
						Local_u8Lock = 1;
						/* Set record Indx */
						Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
						Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track5;

						/* Increment for next position of array_reacord */
						Local_u8RecordCounter++;
					}

				}

				Local_u8Lock = 0;

				/* Still in this loop until new word*/
				while(Local_u8BlutoothData == 'c')
				{
					/* read variable from Bluetooth */
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}

			/* Maza */
			/* Left Hand */
			else if(Local_u8BlutoothData == 'f')
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track6;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while(Local_u8BlutoothData == 'f')
				{
					/* read variable from POTS , ADXL */
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}

			/* takol */
			/* Left Hand */
			else if(Local_u8BlutoothData == 'e')
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track7;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while(Local_u8BlutoothData == 'e')
				{
					/* read variable from Bluetooth */
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}

			/* shokrn  --  sllam alekm*/
			/*  F1 C                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5  O                  ,REST O                      ,Z Negative                 */
			else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[8] > MIN_NEGATIVE))
			{
				MSTK_voidSetBusyWait(500);
				ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);

				/* sllam alekm */
				/*  F1 C                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST  O              ,X POSITIVE                */
				if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track1;

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
					{
						/* read variable from POTS , ADXL */
						ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					}
				}
				/* shokrn */
				else
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder1;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track8;

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[8] > MIN_NEGATIVE))
					{
						/* read variable from POTS , ADXL */
						ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					}
				}
			}



			/************************************************************************************************************************************************************************/

			/* AEINA */
			/*  F1 C                    ,F2 C                    ,F3 O                    ,F4 O                     ,F5  O                  ,REST O                        ,Y  Negative               */
			else if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track2;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL and Bluetooth */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* tazhab */
			/*  F1 C                    ,F2 O                     ,F3 C                        ,F4 C                   ,F5 C                     ,REST  O                  ,X POSITIVE                     , Left Hand    */
			else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE) && (Local_u8BlutoothData == 'g'))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track3;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE) && (Local_u8BlutoothData == 'g'))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}



			/************************************************************************************************************************************************************************/
			/* LADEI */
			/*       F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                  ,REST  C                 ,X POSITIVE                     , Left hand                 */
			else if((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < MAX_POSITVE) && (Local_u8BlutoothData == 'h'))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track4;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < MAX_POSITVE) && (Local_u8BlutoothData == 'h'))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}

			/* EkhTBAR */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                     ,REST  O                   ,Z Negative                      , Left hand                 */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[8] > MIN_NEGATIVE) && (Local_u8BlutoothData == 'i'))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track5;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[8] > MIN_NEGATIVE) && (Local_u8BlutoothData == 'i'))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					Local_u8BlutoothData = MUSART2_u8Receive();
				}
			}

			/* wdaa3n */
			/*      F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5  O                  ,REST O                  ,Y  Negative                */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track6;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}


			/* ana */
			/*  F1 C                    ,F2 O                     ,F3 C                        ,F4 C                   ,F5 C                     ,REST                    ,X POSITIVE                */
			else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < MAX_POSITVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track7;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] > POT6) && (analog_rx[6] < MAX_POSITVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* Ready To Speak*/
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                     ,REST O                    ,Y Positive                     ,Left Hand                  */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] < MAX_POSITVE) && (Local_u8BlutoothData == '0'))
			{
				/* turquoise */
				MGPIO_voidSetPinValue(GPIOA , PIN8  , HIGH);
				MGPIO_voidSetPinValue(GPIOA , PIN11 , LOW);
				MGPIO_voidSetPinValue(GPIOA , PIN12 , LOW);

				/* Iterate on array Indx_record */
				for(Local_u8Counter = 0; Local_u8Counter < Local_u8RecordCounter; Local_u8Counter++)
				{
					/* play track */
					DFP_PlayTrackInFolder(Indx_record[Local_u8Counter][DFP_FOLDER],Indx_record[Local_u8Counter][DFP_TRACK]);

					/* wait 1s between each track */
					MSTK_voidSetBusyWait(1000);
				}

				/* Reset Variable */
				Local_u8RecordCounter = 0;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] < MAX_POSITVE) && (Local_u8BlutoothData == '0'))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}
		}/* end of arabic while */
	}/* end of if Arabic */

	/* English language <- F2  C */
	else if(analog_rx[1] > POT2)
	{
		while(1)
		{
			/* Blue */
			MGPIO_voidSetPinValue(GPIOA , PIN8  , HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN11 , HIGH);
			MGPIO_voidSetPinValue(GPIOA , PIN12 , LOW);

			/* read variable from POTS , ADXL */
			ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
			Local_u8BlutoothData = MUSART2_u8Receive();

			/* Stop */
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                     ,REST O               ,Y Negative                  */
			if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track8;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* I feel pain */
			/*  F1 C                    ,F2 C                     ,F3 C                    ,F4 C                    ,F5 C                    ,REST O                      ,Y Negative             */
			else if((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder2;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track9;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* victory */
			/*  F1 C                    ,F2 O                     ,F3 O                    ,F4 C                     ,F5 C                     ,REST O                     ,Y Negative                */
			else if((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder3;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track1;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] > POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}
			/* I Love You */
			/*  F1 O                    ,F2 O                     ,F3 C                    ,F4 C                     ,F5 O                     ,REST O                    ,Y Negative                 */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
			{
				/* Set record Indx */
				Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder3;
				Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track2;

				/* Increment for next position of array_reacord */
				Local_u8RecordCounter++;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] > MIN_NEGATIVE))
				{
					/* read variable from POTS , ADXL */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}

			/* See You Later  --  Good Job */
			/*  F1 O                    ,F2 C                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST O                     ,X POSITIVE               */
			else if((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
			{
				MSTK_voidSetBusyWait(500);
				ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);

				/* See You Later */
				/*  F1 O                    ,F2 O                     ,F3 C                    ,F4 C                     ,F5 C                     ,REST O               ,X POSITIVE                */
				if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder3;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track3;

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
					{
						/* read variable from POTS , ADXL */
						ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					}
				}
				/* Good job */
				else
				{
					/* Set record Indx */
					Indx_record[Local_u8RecordCounter][DFP_FOLDER] = DFP_Folder3;
					Indx_record[Local_u8RecordCounter][DFP_TRACK]  = DFP_Track4;

					/* Increment for next position of array_reacord */
					Local_u8RecordCounter++;

					/* Still in this loop until new word*/
					while((analog_rx[0] < POT1) && (analog_rx[1] > POT2) && (analog_rx[2] > POT3) && (analog_rx[3] > POT4) && (analog_rx[4] > POT5) && (analog_rx[5] < POT6) && (analog_rx[6] < MAX_POSITVE))
					{
						/* read variable from POTS , ADXL */
						ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
					}
				}
			}
			/* Ready To Speak*/
			/*  F1 O                    ,F2 O                     ,F3 O                    ,F4 O                     ,F5 O                     ,REST O                    ,Y Positive                     ,Left Hand                  */
			else if((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] < MAX_POSITVE) && (Local_u8BlutoothData == '0'))
			{
				/* turquoise */
				MGPIO_voidSetPinValue(GPIOA , PIN8  , HIGH);
				MGPIO_voidSetPinValue(GPIOA , PIN11 , LOW);
				MGPIO_voidSetPinValue(GPIOA , PIN12 , LOW);

				/* Iterate on array Indx_record */
				for(Local_u8Counter = 0; Local_u8Counter < Local_u8RecordCounter; Local_u8Counter++)
				{
					/* play track */
					DFP_PlayTrackInFolder(Indx_record[Local_u8Counter][DFP_FOLDER],Indx_record[Local_u8Counter][DFP_TRACK]);

					/* wait 1s between each track */
					MSTK_voidSetBusyWait(1000);
				}

				/* Reset Variable */
				Local_u8RecordCounter = 0;

				/* Still in this loop until new word*/
				while((analog_rx[0] < POT1) && (analog_rx[1] < POT2) && (analog_rx[2] < POT3) && (analog_rx[3] < POT4) && (analog_rx[4] < POT5) && (analog_rx[5] < POT6) && (analog_rx[7] < MAX_POSITVE) && (Local_u8BlutoothData == '0'))
				{
					/* read variable from POTS , ADXL and Bluetooth */
					ADC1_voidMultiChannel_RX(channels , adc_channels , analog_rx);
				}
			}
		}/* end of English while */
	}/* end of if ENGLISH */
}/* end of App Function */
