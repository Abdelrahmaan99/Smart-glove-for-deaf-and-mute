/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 29 August 2021                       */
/* Version     : V01                                  */
/* Description : UART                                 */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

typedef struct
{
	volatile u32	SR;
	volatile u32	DR;
	volatile u32	BRR;
	volatile u32	CR1;
	volatile u32	CR2;
	volatile u32	CR3;
	volatile u32	GRPR;
}MUART_t;

#define MUSART1 ((volatile MUART_t *) 0x40013800)
#define MUSART2 ((volatile MUART_t *) 0x40004400)
#define MUSART3 ((volatile MUART_t *) 0x40004800)




#endif
