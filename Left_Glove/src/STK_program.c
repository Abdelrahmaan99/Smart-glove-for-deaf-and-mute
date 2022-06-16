/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 23 August 2021                       */
/* Version     : V01                                  */
/* Description : SYSTICK	                          */
/******************************************************/



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"



static void (*CallBack) (void) = NULL;

static u8 MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;

void MSTK_voidInit(void)
{
#if   Clock_Source == AHB_DIV_BY_8
	STK_CTRL = 0x00000000;
#elif Clock_Source == Processor_clock_AHB
	STK_CTRL = 0x00000004;
#else
#error "Wrong Clock_Source_STK Choice"

#endif
}


void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
	STK_LOAD = Copy_u32Ticks * 1000;
	SET_BIT(STK_CTRL , STK_ENABLE);
	while(GET_BIT(STK_CTRL , STK_COUNTFLAG) == 0 );
	CLR_BIT(STK_CTRL , STK_ENABLE);
}

void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks , void (*Copy_ptr) (void))
{
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	CallBack = Copy_ptr;
	STK_LOAD = Copy_u32Ticks * 1000;
	SET_BIT(STK_CTRL , STK_TICKINT);
	SET_BIT(STK_CTRL , STK_ENABLE);
}


void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*Copy_ptr) (void))
{
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;
	CallBack = Copy_ptr;
	STK_LOAD = Copy_u32Ticks * 1000;
	SET_BIT(STK_CTRL , STK_TICKINT);
	SET_BIT(STK_CTRL , STK_ENABLE);
}

void MSTK_voidStopInterval(void)
{
	CLR_BIT(STK_CTRL , STK_TICKINT);
	CLR_BIT(STK_CTRL , STK_ENABLE);
	STK_LOAD = 0;
	STK_VAL  = 0;
}

u32 MSTK_u32GetElapseTime(void)
{
	u32 Local_u32Ticks = 0;
	Local_u32Ticks = STK_LOAD - STK_VAL;
	return Local_u32Ticks;
}

u32 MSTK_u32GetRemainingTime(void)
{
	u32	Local_u32RemainingTicks = 0;
	Local_u32RemainingTicks = STK_VAL;
	return Local_u32RemainingTicks;
}
void SysTick_Handler(void)
{
	u8 Local_u8ReadFlag = 0;
	Local_u8ReadFlag++;
	Local_u8ReadFlag--;
	if(MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		CLR_BIT(STK_CTRL , STK_TICKINT);
		CLR_BIT(STK_CTRL , STK_ENABLE);
		STK_LOAD = 0;
		STK_VAL  = 0;
	}
	CallBack();
	Local_u8ReadFlag = GET_BIT(STK_CTRL , STK_COUNTFLAG);
}
