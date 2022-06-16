/*********************************************************************************************************/
/******************************** Author      : Abdelrahman Moustafa   ***********************************/
/******************************** Date        : 15 August 2021         ***********************************/
/******************************** Version     : V01                    ***********************************/
/******************************** Description : GPIO REGISTER          ***********************************/
/*********************************************************************************************************/

#include "STD_TYPES.h"


#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "UART_INTERFACE.h"
#include "FPEC_interface.h"

#include "ESP_INTERFACE.h"

#define Buffer_Size     2000

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;


void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08002000;

	addr_to_call = *(Function_t*)(0x08002004);
	addr_to_call();
}


void Parser_voidParseRecord(u8* Copy_u8BufData);
volatile u8 EndFlag = 0;


char DataCome[Buffer_Size] = {0};

void send_rec(void){

	u8 Local_u8Event = 0;
	u16 Local_u16CounterStart = 0;
	u16 Local_u16Counter;
	u8  Local_u8CounterBuffer = 0;
	u8 u8RecBuffer[100] = {0};

	/* Reach to first : */
	SecondColumn:
	while(Local_u8Event == 0)
	{
		if(DataCome[Local_u16CounterStart] == ':')
		{
			Local_u8Event = 1;
		}
		Local_u16CounterStart++;
	}

	/* Start from index of second : */
	for(Local_u16Counter = Local_u16CounterStart; Local_u16Counter < Buffer_Size; Local_u16Counter++)
	{
		if(DataCome[Local_u16Counter] == '\r')
		{
			continue;
		}
		else if((DataCome[Local_u16Counter] == '\n') && (DataCome[Local_u16Counter+1] == '+'))
		{
			Local_u8Event = 0;
			Local_u16CounterStart = Local_u16Counter+1;
			goto SecondColumn;
		}
		else if(DataCome[Local_u16Counter] == '@')
		{
			break;
		}
		else if(DataCome[Local_u16Counter] == '#')
		{
			EndFlag = 1;
			break;
		}
		else
		{
			u8RecBuffer[Local_u8CounterBuffer] = DataCome[Local_u16Counter];
			if(u8RecBuffer[Local_u8CounterBuffer] == '\n')
			{
				u8RecBuffer[Local_u8CounterBuffer]   = '\r';
				u8RecBuffer[Local_u8CounterBuffer+1] = '\n';
				Local_u8CounterBuffer = 0;
				Parser_voidParseRecord(u8RecBuffer);
			}
			else
			{
				Local_u8CounterBuffer++;
			}
		}
	}
}






void main ( void ){

	/* Create Variable To Receive Data From Server */
	u8 status=0;

	/* Initialize RCC to work with 8MHz */
	RCC_voidInitSysClock();

	/* Enable USART 3 */
	RCC_voidEnableClock(RCC_APB1 , 18);

	/* Enable GPIOB */
	RCC_voidEnableClock(RCC_APB2 , 3);

	 /* Enable FPEC */
	RCC_voidEnableClock(RCC_AHB,4);

	/* B10 = TX out 2MHz*/
	MGPIO_voidSetPinDirection(GPIOB , PIN10 , OUTPUT_SPEED_2MHZ_AFPP);

	/* B11 = RX input Floating */
	MGPIO_voidSetPinDirection(GPIOB , PIN11 , INPUT_FLOATING);

	/* Initialize USART BaudRate = 115200 */
	MUSART3_voidInit();
	/* Setting ESP8266 Mode */
	ESP_voidInit();

	/* Connecting To WIFI Network */
	ESP_voidConnectToWiFi((u8*)"IOT" , (u8*)"saleen800139027");


	/* Connecting To overtheair.freevar.com to check if there is a new hex file to burn*/
	ESP_voidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );
	status = ESP_u8ReceiveHttpReq((u8*)"GET http://bionist-ota.freeoda.com/FOTA_WEB/mc_check.txt\r\n" , (u8*)"58");

	if(status == '1')
	{
		FPEC_voidEraseAppArea();

		while(1)
		{
			ESP_voidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

			ESP_voidSendOk( (u8 *)"GET http://bionist-ota.freeoda.com/FOTA_WEB/Reciver.php?Rx=ok\r\n" , (u8 *)"63" );

			ESP_voidConnectToSrvTcp( (u8 *)"162.253.155.226" , (u8 *)"80" );

			ESP_voidReceiveHttpReq( (u8 *)"GET http://bionist-ota.freeoda.com/FOTA_WEB/record.txt\r\n" , (u8 *)"56" , DataCome);

			send_rec();

			if(EndFlag == 1)
			{
				break;
			}
		}
	}

	/*    Jump to the application "Entry Point"      */
	func();
}
