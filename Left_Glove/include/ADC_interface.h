/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 18 Septemper 2021                    */
/* Version     : V01                                  */
/* Description : ADC1                    		      */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

/*
 * A0
 * A1
 * A2
 * A3
 * A4
 * A5
 * A6
 * A7
 * A8
 * B0
 * B1
 */


#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H




void ADC1_voidSingleChannelInit(u8 Copy_u8Channel);
u8   ADC1_u8SingleChannelCheck(void);
void ADC1_voidSingleChannelRX(u16 * Copy_pu16Data);

void ADC1_voidMultiChannelInit(u8 Copy_u8FirstChannel);
void ADC1_voidSetNextChannel(u8 Copy_u8NextChannel);
void ADC1_voidMultiChannel_RX(u8 Copy_u8Channels , u8 * Copy_pu8AdcChannels , u16 * Copy_pu16AnalogRX);

#endif
