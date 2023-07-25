/*
 * FINGER_PRINT_PROG.c
 *
 *  Created on: Mar 12, 2023
 *      Author: joseph
 */

#include "STD_TYPES.h"

#include "UART_INT.h"
#include "LCD_INT.h"

#include "FINGER_PRINT_TYPES.h"
#include "FINGER_PRINT_PRIV.h"
#include "FINGER_PRINT_INT.h"

#include <avr/delay.h>

#define FINGER_PRINT_DEPUG 	1
#define FP_SHACK_HANDS 		0

u8 FingerPrintBuffer[100];
u8 FingerPrintBufferCounter = 0;
extern volatile u8 global_ReceivedData;

static void FP_ISR()
{
	FingerPrintBuffer[FingerPrintBufferCounter] = global_ReceivedData;
	FingerPrintBufferCounter++;
}

void H_FP_Init()
{
	M_UART_Inite(UART_BAUD_9600, UART_8BIT_MODE, UART_PARITY_DISABLED, UART_STOP_1BIT);
	M_UART_ReceiveByteAsynchCallBack(FP_ISR);
}

static void H_FP_SendHeaderAndAddress()
{
	//Header
	M_UART_SendByte(FP_HEADER_UPPER_BYTE);
	M_UART_SendByte(FP_HEADER_LOWER_BYTE);
	//Module Address
	M_UART_SendByte(FP_ADDRESS_BYTE);
	M_UART_SendByte(FP_ADDRESS_BYTE);
	M_UART_SendByte(FP_ADDRESS_BYTE);
	M_UART_SendByte(FP_ADDRESS_BYTE);
}

void H_FP_DisplayBuffer()
{
	//FingerPrintBuffer[FingerPrintBufferCounter] ='\0';
	//H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	//H_LCD_void_SendString(FingerPrintBuffer);
	H_LCD_void_SendString(".");
	//H_LCD_void_SendString("Response= ");
	//H_LCD_void_SendNumber(FingerPrintBuffer[9]);
	FingerPrintBufferCounter = 0;
	//memset(FingerPrintBuffer, 'z', 100);
	//_delay_ms(1000);
}

#if FP_SHACK_HANDS == 1
FP_Confirmation_Code H_FP_HandShake()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x03);

	//Instruction Code
	M_UART_SendByte(FP_HANDSHAKE_COMMAND);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x44);

	u8 Command[] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x40,0x00,0x04};
	for(u8 i =0; i< 10; i++)
	{

	}

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

FP_Confirmation_Code H_FP_CheckSensor()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x03);

	//Instruction Code
	M_UART_SendByte(FP_CHECKSENSOR_COMMAND);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x3A);

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}
#endif

FP_Confirmation_Code H_FP_CollectFingerImage()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x03);

	//Instruction Code
	M_UART_SendByte(FP_COLLECT_FINGER_IMAGE_COMMAND);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x05);

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

FP_Confirmation_Code H_FP_GenerateCharacterFileFirstScan()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x04);

	//Instruction Code
	M_UART_SendByte(FP_GENERATE_CHARACTER_FILE_COMMAND);
	//CharBuffer1
	M_UART_SendByte(0x1);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x08);

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

FP_Confirmation_Code H_FP_GenerateCharacterFileSecondScan()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x04);

	//Instruction Code
	M_UART_SendByte(FP_GENERATE_CHARACTER_FILE_COMMAND);
	//CharBuffer2
	M_UART_SendByte(0x2);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x09);

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

FP_Confirmation_Code H_FP_FirstScan()
{
	FP_Confirmation_Code ConfirmationCode = H_FP_CollectFingerImage();
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Scan Finger..");
		_delay_ms(500);
	}
#endif
	if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
	{
		ConfirmationCode = H_FP_GenerateCharacterFileFirstScan();
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Scan Finger...");
		_delay_ms(500);
	}
#endif
	}
	return ConfirmationCode;
}

FP_Confirmation_Code H_FP_SecondScan()
{
	FP_Confirmation_Code ConfirmationCode = H_FP_CollectFingerImage();
	if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
	{
		ConfirmationCode = H_FP_GenerateCharacterFileSecondScan();
	}
	return ConfirmationCode;
}

FP_Confirmation_Code H_FP_GenerateTemplate()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x03);

	//Instruction Code
	M_UART_SendByte(FP_GENERATE_TEMPLATE_COMMAND);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x09);

	//Wait to receive the Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

//Please send the parameters as hex corresponding
FP_Confirmation_Code H_FP_StoreTemplate(u8 PageID)
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x06);

	//Instruction Code
	M_UART_SendByte(FP_STORE_TEMPLATE_COMMAND);
	//CharBuffer1
	M_UART_SendByte(0x01);
	//PageID
	M_UART_SendByte(0x00);
	M_UART_SendByte(PageID);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(PageID + 0xE);
	//M_UART_SendByte(0xF);

	//Wait to receive the Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}

	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

//Please send the parameters as hex corresponding
FP_Confirmation_Code H_FP_ScanAndStore(u8 PageID)
{
	FP_Confirmation_Code ConfirmationCode = H_FP_FirstScan();
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Scan Finger..");
		_delay_ms(1000);
	}
#endif

	if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
	{
		ConfirmationCode = H_FP_SecondScan();
#if FINGER_PRINT_DEPUG == 1
		if(ConfirmationCode == 0x00)
		{
			H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
			H_LCD_void_SendString("Scan Finger...");
			_delay_ms(1000);
		}
#endif

		if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
		{
			H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
			H_LCD_void_SendString("Processing.");
			_delay_ms(1000);
			ConfirmationCode = H_FP_GenerateTemplate();
#if FINGER_PRINT_DEPUG == 1
			if(ConfirmationCode == 0x00)
			{
				H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
				H_LCD_void_SendString("Processing..");
				_delay_ms(1000);
			}
#endif
			if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
			{
				ConfirmationCode = H_FP_StoreTemplate(PageID);
#if FINGER_PRINT_DEPUG == 1
				if(ConfirmationCode == 0x00)
				{
					H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
					H_LCD_void_SendString("Processing...");
					_delay_ms(1000);
				}
#endif
			}

		}
	}
	return ConfirmationCode;

}

FP_Confirmation_Code H_FP_MatchTwoFingerTemplates()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x03);

	//Instruction Code
	M_UART_SendByte(FP_MATCHING_TWO_FINGER_COMMAND);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x07);

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

//Please send the parameters as hex corresponding
FP_Confirmation_Code H_FP_SearchFingerLibrary(u16 StartPageNumber,u16 SearchingNumbers)
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x08);

	//Instruction Code
	M_UART_SendByte(FP_SEARCH_FINGER_LIBRARY_COMMAND);
	//CharBuffer1
	M_UART_SendByte(0x1);
	//Start page number
	//M_UART_SendByte((u8)((StartPageNumber & 0b1111111100000000)>>8));
	M_UART_SendByte(0x00);
	M_UART_SendByte((u8)(StartPageNumber));
	//M_UART_SendByte(0x01);//work
	//Searching numbers
	//M_UART_SendByte((u8)((SearchingNumbers & 0b1111111100000000)>>8));
	M_UART_SendByte(0x00);
	M_UART_SendByte((u8)(SearchingNumbers));
	//M_UART_SendByte(0x0F);//work

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x0E + StartPageNumber + SearchingNumbers);
	//M_UART_SendByte(0x01E);//work

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 15)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	if(FingerPrintBuffer[9] == COMMAND_EXECUTION_COMPLETE)
	{
		H_LCD_void_SendString("ID= ");
		H_LCD_void_SendNumber(FingerPrintBuffer[11]);
		_delay_ms(1000);
	}
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

//Please send the parameters as hex corresponding
FP_Confirmation_Code H_FP_ScanAndSearch(u16 StartPageNumber,u16 SearchingNumbers)
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Scan Finger.");
	FP_Confirmation_Code ConfirmationCode = H_FP_FirstScan();
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Scan Finger..");
		_delay_ms(500);
	}
#endif
	if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Checking...");
		_delay_ms(500);
		ConfirmationCode = H_FP_SearchFingerLibrary(StartPageNumber, SearchingNumbers);
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Finish");
		_delay_ms(500);
	}
#endif
	}
	return ConfirmationCode;
}

FP_Confirmation_Code H_FP_ReadTemplate(u8 PageID)
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x06);

	//Instruction Code
	M_UART_SendByte(0x07);
	//CharBuffer2
	M_UART_SendByte(0x02);
	//PageID
	M_UART_SendByte(0x00);
	M_UART_SendByte(PageID);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(PageID + 0x10);

	//Wait to receive the Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}

FP_Confirmation_Code H_FP_ScanAndVerify(u8 PageID)
{
	FP_Confirmation_Code ConfirmationCode = H_FP_FirstScan();
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("FirstScan");
		_delay_ms(500);
	}
#endif
	if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
	{
		ConfirmationCode = H_FP_ReadTemplate(PageID);
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("ReadTemplete");
		_delay_ms(500);
	}
#endif
		if(ConfirmationCode == COMMAND_EXECUTION_COMPLETE)
		{
			ConfirmationCode = H_FP_MatchTwoFingerTemplates();
#if FINGER_PRINT_DEPUG == 1
	if(ConfirmationCode == 0x00)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("MatchTemplete");
		_delay_ms(500);
	}
#endif
		}
	}
	return ConfirmationCode;
}

FP_Confirmation_Code H_FP_EmptyLibrary()
{
	H_FP_SendHeaderAndAddress();

	//PAckage Identifier
	M_UART_SendByte(FP_IDENTIFIER_COMMAND);

	//Package Length
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x03);

	//Instruction Code
	M_UART_SendByte(0x0d);

	//CheckSum
	M_UART_SendByte(0x00);
	M_UART_SendByte(0x11);

	//Receive Acknowledge
	while(FingerPrintBufferCounter < 11)
	{

	}
	FingerPrintBuffer[FingerPrintBufferCounter] = '\0';
	H_FP_DisplayBuffer();
	//Confirmation Response
	return FingerPrintBuffer[9];
}
