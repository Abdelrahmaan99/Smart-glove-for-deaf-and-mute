/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 13 August 2021                       */
/* Version     : V01                                  */
/* Description : RCC REGISTER                         */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* CCS Configration*/
/* options: RCC_CCS_ENABLE
			RCC_CCS_DISABLE
             			             */
#define RCC_Clock_security_system	RCC_CCS_DISABLE



/* Select Clock */
/* options:    RCC_HSE_CRYSTAL
			   RCC_HSE_RC
			   RCC_HSI
			   RCC_PLL                */
#define RCC_CLOCK_TYPE	 			RCC_HSI


/* options: RCC_PLL_IN_HSI_DIV_2
			RCC_PLL_IN_HSE_DIV_2
			RCC_PLL_IN_HSE           */
/* Note: Select value only if you have PLL as input clock source */
#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT				RCC_PLL_IN_HSE_DIV_2
#endif


/* Options: 2 to 16 */
/* Note: Select value only if you have PLL as input clock source */
#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL				4
#endif

#endif
