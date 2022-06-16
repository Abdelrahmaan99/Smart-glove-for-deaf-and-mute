/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 13 August 2021                       */
/* Version     : V01                                  */
/* Description : RCC REGISTER                         */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/* Register Definitions */
#define RCC_CR		   			*((u32*)0x40021000)	
#define RCC_CFGR	   			*((u32*)0x40021004)
#define RCC_CIR		   			*((u32*)0x40021008)
#define RCC_APB2RSTR   			*((u32*)0x4002100C)
#define RCC_APB1RSTR   			*((u32*)0x40021010)
#define RCC_AHBENR	   			*((u32*)0x40021014)
#define RCC_APB2ENR	   			*((u32*)0x40021018)
#define RCC_APB1ENR	   			*((u32*)0x4002101C)
#define RCC_BDCR	   			*((u32*)0x40021020)
#define RCC_CSR		   			*((u32*)0x40021024)	 

/* Register Bit Definitions */
#define CSSON					19
#define PLLON					24		


/* Clock Types */
#define RCC_HSE_CRYSTAL			1
#define RCC_HSE_RC				2
#define RCC_HSI					3
#define RCC_PLL					4


/* PLL Options*/
#define RCC_PLL_IN_HSI_DIV_2	1
#define RCC_PLL_IN_HSE_DIV_2	2
#define RCC_PLL_IN_HSE			3


/*  Clock security system */
#define RCC_CCS_ENABLE			1			
#define RCC_CCS_DISABLE			2

#endif
