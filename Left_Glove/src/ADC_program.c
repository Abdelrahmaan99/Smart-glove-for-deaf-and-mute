/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 18 Septemper 2021                    */
/* Version     : V01                                  */
/* Description : ADC1                    		      */
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"





void ADC1_voidSingleChannelInit(u8 Copy_u8Channel)
{
	/* Clear All CR2 */
	ADC1->CR2  = 0;

	/* Set Number Channel of ADC */
	ADC1->SQR3 = Copy_u8Channel;

	/* ADC ON */
	ADC1->CR2 |= 1;

	/* wait for stability */
	MSTK_voidSetBusyWait(100);

	/* ADC ON again */
	ADC1->CR2 |= 1;

	/* Set Continuous conversion */
	ADC1->CR2 |= 2;
}

u8 ADC1_u8SingleChannelCheck(void)
{
	u8 Local_u8Check = 0;

	/* Check Flag of EOC */
	if(ADC1->SR & 2)
	{
		Local_u8Check = 1;
	}
	return Local_u8Check;
}

void ADC1_voidSingleChannelRX(u16 * Copy_pu16Data)
{
	u16 Local_u16Data   = 0;

	/* Read Data of ADC from Dr Register */
	Local_u16Data = ADC1->DR;

	/* range of value of ADC of 3.3v (0 : 985), and of 5v(0 : 1000) */
	/* If you want to set range from(0 : 4035)(resolution 12 bits)of 3.3v or from(0 : 4095)(resolution 12 bits)of 5v, you don't need this equation */
	*Copy_pu16Data  = (Local_u16Data*1000)/0xfff;

}

void ADC1_voidMultiChannelInit(u8 Copy_u8FirstChannel)
{
	/* Clear All CR2 */
	ADC1->CR2  = 0;

	/* ADC ON */
	ADC1->CR2 |= 1;

	/* wait for stability */
	MSTK_voidSetBusyWait(100);

	/* Set Number of first Channel of ADC */
	ADC1->SQR3 = Copy_u8FirstChannel;

	/* Set Continuous conversion */
	ADC1->CR2 |= 2;

	/* ADC ON again */
	ADC1->CR2 |= 1;
}

void ADC1_voidSetNextChannel(u8 Copy_u8NextChannel)
{
	/* Set Number of Next Channel of ADC */
	ADC1->SQR3 = Copy_u8NextChannel;
}

void ADC1_voidMultiChannel_RX(u8 Copy_u8Channels , u8 * Copy_pu8AdcChannels , u16 * Copy_pu16AnalogRX)
{
	u16 Local_u16TempRX = 0;
	u8 Local_u8Counter  = 0;
	while (1)
	{
		/* Check Flag of EOC */
		if(ADC1_u8SingleChannelCheck())
		{
			/* Read Data of ADC from Dr Register */
			ADC1_voidSingleChannelRX(&Local_u16TempRX);

			/* Assign this data in array */
			Copy_pu16AnalogRX[Local_u8Counter] = Local_u16TempRX;
			Local_u8Counter++;

			/* Check if all channel has a value or not */
			if(Local_u8Counter == Copy_u8Channels)
			{
				Local_u8Counter = 0;
				ADC1_voidSetNextChannel(Copy_pu8AdcChannels[Local_u8Counter]);
				break;
			}
			else
			{
				ADC1_voidSetNextChannel(Copy_pu8AdcChannels[Local_u8Counter]);
			}
		}
	}
}
