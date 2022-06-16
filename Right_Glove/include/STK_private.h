/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 23 August 2021                       */
/* Version     : V01                                  */
/* Description : SYSTICK                              */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#define STK_CTRL			                *((volatile u32 *)(0xE000E010)        )
#define STK_LOAD			                *((volatile u32 *)(0xE000E010 + 0x04) )
#define STK_VAL				                *((volatile u32 *)(0xE000E010 + 0x08) )

#define STK_ENABLE			                0
#define STK_TICKINT			                1
#define STK_CLKSOURCE		                2
#define STK_COUNTFLAG			            16

#define AHB_DIV_BY_8        	            1
#define Processor_clock_AHB	                2

#define NULL					            0

#define			MSTK_SINGLE_INTERVAL		0
#define			MSTK_PERIOD_INTERVAL		1

#endif
