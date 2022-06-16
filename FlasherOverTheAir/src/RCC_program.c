/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 13 August 2021                       */
/* Version     : V01                                  */
/* Description : RCC REGISTER                         */
/******************************************************/



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_config.h"
#include "RCC_private.h"

void RCC_voidInitSysClock(void)
{	
	/* Choose Clock System */
	/* Crystal */
	#if	RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		RCC_CR   = 0x00010000; /* Enable HSE With no bypass */
		RCC_CFGR = 0x00000001; /* System clock switch is HSE With no bypass*/
		
	/* RC_External */
	#elif RCC_CLOCK_TYPE == RCC_HSE_RC
		RCC_CR   = 0x00050000; /* Enable HSE With bypass */
		RCC_CFGR = 0x00000001; /* System clock switch is HSE With bypass*/
		
	/* RC_Internal */
	#elif RCC_CLOCK_TYPE == RCC_HSI
		RCC_CR   = 0x00000081; /* Enable HSI  + Trimming = 0*/
		RCC_CFGR = 0x00000000;/* System clock switch is HSI*/
		
	/* PLL */	
	#elif RCC_CLOCK_TYPE == RCC_PLL
		#if RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2

		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2

		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE

		#endif

		#else
			#error("You Choose Wrong Clock type")
	#endif
	
	/* Clock security system */
	#if RCC_Clock_security_system == RCC_CCS_ENABLE
		SET_BIT(RCC_CR,CSSON);	/* Clock security system is enabled */
	#elif RCC_Clock_security_system == RCC_CCS_DISABLE
		CLR_BIT(RCC_CR,CSSON);	/* Clock security system is disabled */
	#else
		#error("Clock security system: Wrong Option")
	#endif
	
	
}

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if(Copy_u8PerId <= 31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  :  SET_BIT(RCC_AHBENR  ,Copy_u8PerId);    break;
			case RCC_APB1 :  SET_BIT(RCC_APB1ENR ,Copy_u8PerId);	break;
			case RCC_APB2 :  SET_BIT(RCC_APB2ENR ,Copy_u8PerId);	break;
		}
	}
	else
	{
		/* Return Error */
	}
}


void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if(Copy_u8PerId <= 31)
	{
		switch(Copy_u8BusId)
		{
			case RCC_AHB  :  CLR_BIT(RCC_AHBENR  ,Copy_u8PerId);    break;
			case RCC_APB1 :  CLR_BIT(RCC_APB1ENR ,Copy_u8PerId);	break;
			case RCC_APB2 :  CLR_BIT(RCC_APB2ENR ,Copy_u8PerId);	break;
		}
	}
	else
	{
		/* Return Error */
	}
}
