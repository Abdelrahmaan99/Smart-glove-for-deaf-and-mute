/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 29 August 2021                       */
/* Version     : V01                                  */
/* Description : UART                                 */
/******************************************************/


/******************************************************/
/* guard of file will call one time in .c  			  */
/******************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void MUSART1_voidInit(void);
void MUSART1_voidTransmit(u8 *ptr);
u8   MUSART1_u8Receive(void);
u8   MUSART1_u8ReceiveTimeOut(void);
void MUSART1_voidReceiveBuffer(char *Copy_ptrBuffer , u32 Copy_SizeBuffer);
void MUSART1_voidSendChar(u8 Copy_u8Data);


void MUSART2_voidInit(void);
void MUSART2_voidTransmit(u8 *ptr);
u8   MUSART2_u8Receive(void);
u8   MUSART2_u8ReceiveTimeOut(void);
void MUSART2_voidReceiveBuffer(char *Copy_ptrBuffer , u32 Copy_SizeBuffer);
void MUSART2_voidSendChar(u8 Copy_u8Data);


void MUSART3_voidInit(void);
void MUSART3_voidTransmit(u8 *ptr);
u8   MUSART3_u8Receive(void);
u8   MUSART3_u8ReceiveTimeOut(void);
void MUSART3_voidReceiveBuffer(char *Copy_ptrBuffer , u32 Copy_SizeBuffer);

#endif
