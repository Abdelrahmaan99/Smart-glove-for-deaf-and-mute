/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 15 August 2021                       */
/* Version     : V01                                  */
/* Description : GPIO REGISTER                        */
/******************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


u8 Local_u8Result = 0;

void MGPIO_voidSetPinDirection(u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Mode)
{
	switch(Copy_u8PORT)
	{
		case GPIOA :
					if(Copy_u8PIN <= 7)
					{
						GPIOA_CRL &= ~((0b1111) << (Copy_u8PIN * 4));
						GPIOA_CRL |= ((Copy_u8Mode) << (Copy_u8PIN * 4));
					}
					else if(Copy_u8PIN <= 15)
					{
						Copy_u8PIN -= 8;
						GPIOA_CRH &= ~((0b1111) << (Copy_u8PIN * 4));
						GPIOA_CRH |= ((Copy_u8Mode) << (Copy_u8PIN * 4));
					}
					break;
		case GPIOB :
					if(Copy_u8PIN <= 7)
					{
						GPIOB_CRL &= ~((0b1111) << (Copy_u8PIN * 4));
						GPIOB_CRL |= ((Copy_u8Mode) << (Copy_u8PIN * 4));
					}
					else if(Copy_u8PIN <= 15)
					{
						Copy_u8PIN -= 8;
						GPIOB_CRH &= ~((0b1111) << (Copy_u8PIN * 4));
						GPIOB_CRH |= ((Copy_u8Mode) << (Copy_u8PIN * 4));
					}
					break;
		case GPIOC :
					if(Copy_u8PIN <= 7)
					{
						GPIOC_CRL &= ~((0b1111) << (Copy_u8PIN * 4));
						GPIOC_CRL |= ((Copy_u8Mode) << (Copy_u8PIN * 4));
					}
					else if(Copy_u8PIN <= 15)
					{
						Copy_u8PIN -= 8;
						GPIOC_CRH &= ~((0b1111) << (Copy_u8PIN * 4));
						GPIOC_CRH |= ((Copy_u8Mode) << (Copy_u8PIN * 4));
					}
					break;
		default :   break;
	}
}

void MGPIO_voidSetPinValue(u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value)
{
	switch(Copy_u8PORT)
	{
		case GPIOA :
					if(Copy_u8Value == HIGH)
					{
						SET_BIT(GPIOA_ODR,Copy_u8PIN);
					}
					else if(Copy_u8Value == LOW)
					{
						CLR_BIT(GPIOA_ODR,Copy_u8PIN);
					}
					break;
		case GPIOB :
					if(Copy_u8Value == HIGH)
					{
						SET_BIT(GPIOB_ODR,Copy_u8PIN);
					}
					else if(Copy_u8Value == LOW)
					{
						CLR_BIT(GPIOB_ODR,Copy_u8PIN);
					}
					break;
		case GPIOC :
					if(Copy_u8Value == HIGH)
					{
						SET_BIT(GPIOC_ODR,Copy_u8PIN);
					}
					else if(Copy_u8Value == LOW)
					{
						CLR_BIT(GPIOC_ODR,Copy_u8PIN);
					}
					break;
		default :   break;
	}
}

u8 MGPIO_u8GetPinValue(u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	switch(Copy_u8PORT)
	{
		case GPIOA :	Local_u8Result = GET_BIT(GPIOA_IDR , Copy_u8PIN);
					break;
		case GPIOB :	Local_u8Result = GET_BIT(GPIOB_IDR , Copy_u8PIN);
					break;
		case GPIOC :	Local_u8Result = GET_BIT(GPIOC_IDR , Copy_u8PIN);
					break;
		default :   break;
	}
	return Local_u8Result;
}




/***********************************************************/
/* Make by me*/
void MGPIO_voidSetLowPortDirection(u8 Copy_u8PORT , u32 Copy_u8Mode)
{
	switch(Copy_u8PORT)
	{
	case GPIOA:		GPIOA_CRL = Copy_u8Mode;	break;
	case GPIOB:		GPIOB_CRL = Copy_u8Mode;	break;
	default   : 								break;
	}

}

void MGPIO_voidSetHighPortDirection(u8 Copy_u8PORT , u32 Copy_u8Mode)
{
	switch(Copy_u8PORT)
	{
	case GPIOA:		GPIOA_CRH = Copy_u8Mode;	break;
	case GPIOB:		GPIOB_CRH = Copy_u8Mode;	break;
	default   : 								break;
	}

}

void MGPIO_voidWritePortValue(u8 Copy_u8PORT , u16 Copy_u8Value)
{
	switch(Copy_u8PORT)
	{
	case GPIOA:		GPIOA_ODR = Copy_u8Value;	break;
	case GPIOB:		GPIOB_ODR = Copy_u8Value;	break;
	default   : 								break;
	}
}
/***********************************************************/

void MGPIO_voidSetPinBSRR(u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	switch(Copy_u8PORT)
	{
	case GPIOA:
		GPIOA_BSR =	(1 <<  Copy_u8PIN);
		break;

	case GPIOB:
		GPIOB_BSR =	(1 <<  Copy_u8PIN);
		break;

	case GPIOC:
		GPIOC_BSR =	(1 <<  Copy_u8PIN);
		break;

	default   :			break;
	}
}

void MGPIO_voidResetPinBSRR(u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	switch(Copy_u8PORT)
	{
	case GPIOA:
		GPIOA_BSR =	(1 <<  (Copy_u8PIN + 16));
		break;

	case GPIOB:
		GPIOB_BSR =	(1 <<  (Copy_u8PIN + 16));
		break;

	case GPIOC:
		GPIOC_BSR =	(1 <<  (Copy_u8PIN + 16));
		break;

	default   :			break;
	}
}

void MGPIO_voidResetPinBRR(u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	switch(Copy_u8PORT)
	{
	case GPIOA:
		GPIOA_BRR =	(1 <<  (Copy_u8PIN));
		break;

	case GPIOB:
		GPIOB_BRR =	(1 <<  (Copy_u8PIN));
		break;

	case GPIOC:
		GPIOC_BRR =	(1 <<  (Copy_u8PIN));
		break;

	default   :			break;
	}
}

void MGPIO_voidLockPin(u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	u32 Local_u8Lock;
	switch(Copy_u8PORT)
	{
	case GPIOA:
		Local_u8Lock = ((1 << GPIO_LCK_LCKK) | (1 << Copy_u8PIN));

		GPIOA_LCK    = Local_u8Lock;
		GPIOA_LCK    =	(1 <<  (Copy_u8PIN));
		GPIOA_LCK    = Local_u8Lock;
		Local_u8Lock = GET_BIT(GPIOA_LCK,GPIO_LCK_LCKK);
		Local_u8Lock = GET_BIT(GPIOA_LCK,GPIO_LCK_LCKK);
		break;

	case GPIOB:
		GPIOB_LCK =	(1 <<  (Copy_u8PIN));
		break;

	case GPIOC:
		GPIOC_LCK =	(1 <<  (Copy_u8PIN));
		break;

	default   :			break;
	}
}
