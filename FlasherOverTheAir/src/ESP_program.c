/******************************************************/
/* Author      : Abdelrahman Moustafa                 */
/* Date        : 30 August 2021                       */
/* Version     : V01                                  */
/* Description : ESP            			          */
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "STK_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"


#define Buffer_Size     2000


void ESP_voidInit(void)
{
	char Local_charDataReceive1[6] = {0};
	char Local_charDataReceive2[6] = {0};
	u8 Local_u8Event = 0;
	u8 Local_u8Counter = 0;

	/* stop ECHO */
	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)"ATE0\r\n");
		MUSART3_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(100);
	}

	Local_u8Event = 0;

	/* Set station mode */
	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)"AT+CWMODE=1\r\n");
		MUSART3_voidReceiveBuffer(Local_charDataReceive2 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive2[Local_u8Counter] == 'O') && (Local_charDataReceive2[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(100);
	}

}


void ESP_voidConnectToWiFi(u8 *Copy_name , u8 *Copy_pass)
{
	char Local_charDataReceive1[255] = {0};
	char Local_charDataReceive2[255] = {0};

	MUSART3_voidTransmit((u8*)"AT+CWJAP_CUR=\"");
	MUSART3_voidTransmit((u8*)Copy_name);
	MUSART3_voidTransmit((u8*)"\",\"");
	MUSART3_voidTransmit((u8*)Copy_pass);
	MUSART3_voidTransmit((u8*)"\"\r\n");
	MUSART3_voidReceiveBuffer(Local_charDataReceive1 , 255);
	MUSART3_voidReceiveBuffer(Local_charDataReceive2 , 255);
	MSTK_voidSetBusyWait(10);
}


void ESP_voidConnectToSrvTcp (u8 *Copy_u8Domain , u8 *Copy_u8Port)
{
	char Local_charDataReceive[25] = {0};

	/* connect to server */
	MUSART3_voidTransmit((u8*)"AT+CIPSTART=\"TCP\",\"");
	MUSART3_voidTransmit((u8*)Copy_u8Domain);
	MUSART3_voidTransmit((u8*)"\",");
	MUSART3_voidTransmit((u8*)Copy_u8Port);
	MUSART3_voidTransmit((u8*)"\r\n");
	MUSART3_voidReceiveBuffer(Local_charDataReceive , 25);
}


u8   ESP_u8ReceiveHttpReq(u8 *Copy_u8ChannelID , u8 *Copy_u8Length)
{
	char Local_charDataReceive1[6] = {0};
	char Local_charDataReceive2[60] = {0};
	u8 Local_u8Event = 0;
	u8 Local_u8Counter = 0;

	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)"AT+CIPSEND=");
		MUSART3_voidTransmit((u8*)Copy_u8Length);
		MUSART3_voidTransmit((u8*)"\r\n");
		MUSART3_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(10);
	}

	Local_u8Event = 0;

	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)Copy_u8ChannelID);
		MUSART3_voidReceiveBuffer(Local_charDataReceive2 , 60);

		for(Local_u8Counter = 0; Local_u8Counter < 60; Local_u8Counter++)
		{
			if((Local_charDataReceive2[Local_u8Counter] == '+') && (Local_charDataReceive2[Local_u8Counter+1] == 'I') && (Local_charDataReceive2[Local_u8Counter+2] == 'P')&& (Local_charDataReceive2[Local_u8Counter+3] == 'D') && (Local_charDataReceive2[Local_u8Counter+4] == ',') && (Local_charDataReceive2[Local_u8Counter+5] == '1') && (Local_charDataReceive2[Local_u8Counter+6] == ':'))
			{
				Local_u8Event = Local_charDataReceive2[Local_u8Counter+7];
				break;

			}
		}
		MSTK_voidSetBusyWait(500);
	}
	return Local_u8Event;
}


void ESP_voidSendOk(u8 * Copy_u8ChannelID , u8 * Copy_u8Length)
{
	char Local_charDataReceive1[6] = {0};
	char Local_charDataReceive2[70] = {0};
	u8 Local_u8Event = 0;
	u8 Local_u8Counter = 0;

	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)"AT+CIPSEND=");
		MUSART3_voidTransmit((u8*)Copy_u8Length);
		MUSART3_voidTransmit((u8*)"\r\n");
		MUSART3_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(10);
	}

	Local_u8Event = 0;

	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)Copy_u8ChannelID);
		MUSART3_voidReceiveBuffer(Local_charDataReceive2 , 70);
		for(Local_u8Counter = 0; Local_u8Counter < 70; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(10);
	}
}


void ESP_voidReceiveHttpReq(u8 * Copy_u8ChannelID , u8 * Copy_u8Length , char* Data)
{
	char Local_charDataReceive1[6] = {0};
	u8 Local_u8Event = 0;
	u16 Local_u8Counter = 0;

	/*Clear Data*/
	for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++)
	{
		Data[Local_u8Counter] = 0;
	}

	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)"AT+CIPSEND=");
		MUSART3_voidTransmit((u8*)Copy_u8Length);
		MUSART3_voidTransmit((u8*)"\r\n");
		MUSART3_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(10);
	}

	Local_u8Event = 0;

	while(Local_u8Event == 0)
	{
		MUSART3_voidTransmit((u8*)Copy_u8ChannelID);
		MUSART3_voidReceiveBuffer(Data , Buffer_Size);

		for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++)
		{
			if((Data[Local_u8Counter] == '@') || (Data[Local_u8Counter] == '#') )
			{
				Local_u8Event = 1;
				break;
			}
		}
		MSTK_voidSetBusyWait(500);
	}
}
