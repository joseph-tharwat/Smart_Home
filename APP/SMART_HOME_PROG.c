/*
 * SMART_HOME_PROG.c
 *
 *  Created on: Mar 14, 2023
 *      Author: joseph
 */

#include <avr/delay.h>

#include "STD_TYPES.h"

#include "DIO_INT.h"

#include "ExEEPROM_INT.h"
#include "KEYPAD_INT.h"
#include "LCD_INT.h"
#include "RTC_INT.h"
#include "LED_INT.h"

#include "FINGER_PRINT_INT.h"

#include "SMART_HOME_CFG.h"
#include "SMART_HOME_PRIV.h"
#include "SMART_HOME_TYPES.h"
#include "SMART_HOME_INT.h"

void InitializeSystem()
{
	//RTC and EEPROM has the same init speed
#warning "Need to select I2C speed"
	H_RTC_Init();
	H_ExEEPROM_Init();

	H_FP_Init();

	H_LCD_void_SendString("Enter Password:");
	H_LCD_void_GotoXY(1,0);
	LedControl(LOGIN_ENTER_PASSWORD_MODE);
}

void ReadStoredPassword(u8* Passwprd)
{
	//H_ExEEPROM_WriteBuffer(PASSWPRD_EEPROM_ADDRESS, Passwprd, PASSWORD_LENGTH);//Maybe not work
#if FIRST_TIME_DEBUG == 1
	for(u8 i=0; i<PASSWORD_LENGTH; i++)
	{
		H_ExEEPROM_WriteByte(PASSWPRD_EEPROM_ADDRESS+i, Passwprd[i]);
		_delay_ms(200);
	}
#endif

	//H_ExEEPROM_ReadBuffer(PASSWPRD_EEPROM_ADDRESS, Passwprd, PASSWORD_LENGTH);
	u8 Byte;
	for(u8 i=0; i<PASSWORD_LENGTH; i++)
	{
		H_ExEEPROM_ReadByte(PASSWPRD_EEPROM_ADDRESS+i, &Byte);
		Passwprd[i] = Byte;
		_delay_ms(400);
	}
#if FIRST_TIME_DEBUG == 1
	H_LCD_void_SendChar(Passwprd[0]);
	H_LCD_void_SendChar(Passwprd[1]);
	H_LCD_void_SendChar(Passwprd[2]);
	H_LCD_void_SendChar(Passwprd[3]);
#endif
}

u8 ReadKeyPad(u8* Password, u8* PasswordEnterIndex)
{
	u8 Key = H_KEYPAD_u8_GetPressedKey();
	if(Key != KEYPAD_UNPRESSED)
	{
		Password[*PasswordEnterIndex] = Key;
		(*PasswordEnterIndex)++;
		H_LCD_void_SendChar(Key);
	}
	return Key;
}

void LedControl(Login_Mode* Mode)
{
	switch(*Mode)
	{
	case LOGIN_ENTER_PASSWORD_MODE:
		H_LED_void_TurnOn(LED_BLUE);
		H_LED_void_TurnOff(LED_YELLOW);
		H_LED_void_TurnOff(LED_RED);
		H_LED_void_TurnOff(LED_GREEN);
	break;
	case LOGIN_CHANGE_PASSWORD_MODE:
		H_LED_void_TurnOn(LED_YELLOW);
		H_LED_void_TurnOff(LED_BLUE);
		H_LED_void_TurnOff(LED_RED);
		H_LED_void_TurnOff(LED_GREEN);
	break;
	case LOGIN_STORE_NEW_FINGER_PRINT_MODE:
		H_LED_void_TurnOn(LED_YELLOW);
		H_LED_void_TurnOff(LED_BLUE);
		H_LED_void_TurnOff(LED_RED);
		H_LED_void_TurnOff(LED_GREEN);
	break;
	case LOGIN_BLOCKING_MODE:
		H_LED_void_TurnOn(LED_RED);
		H_LED_void_TurnOff(LED_YELLOW);
		H_LED_void_TurnOff(LED_BLUE);
		H_LED_void_TurnOff(LED_GREEN);
	break;
	case LOGIN_FACTORY_RESET_MODE:
		H_LED_void_TurnOn(LED_RED);
		H_LED_void_TurnOff(LED_YELLOW);
		H_LED_void_TurnOff(LED_BLUE);
		H_LED_void_TurnOff(LED_GREEN);
	break;
	case LOGIN_COMPLETE:
		H_LED_void_TurnOn(LED_GREEN);
		H_LED_void_TurnOff(LED_RED);
		H_LED_void_TurnOff(LED_YELLOW);
		H_LED_void_TurnOff(LED_BLUE);
	break;
	}
}

Change_Mode_Status ChangeMode(u8 Key, Login_Mode* Mode)
{
	if(*Mode == LOGIN_FIRST_TIME_MODE)
	{
		return CHANGE_MODE_FALSE;
	}
	if(Key == SELECT_ENTER_PASSWORD_MODE_KEY)
	{
		*Mode = LOGIN_ENTER_PASSWORD_MODE;
		LedControl(Mode);
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Enter Password:");
		H_LCD_void_GotoXY(1,0);
		return CHANGE_MODE_TRUE;
	}
	else if(Key == SELECT_CHANGE_PASSWORD_MODE_KEY)
	{
		*Mode = LOGIN_CHANGE_PASSWORD_MODE;
		LedControl(Mode);
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Enter Old Password:");
		H_LCD_void_GotoXY(1,0);
		return CHANGE_MODE_TRUE;
	}
	else if(Key == SELECT_STORE_NEW_FINGER_MODE_KEY)
	{
		*Mode = LOGIN_STORE_NEW_FINGER_PRINT_MODE;
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Add New Finger");
		_delay_ms(2000);
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Enter Password:");
		H_LCD_void_GotoXY(1,0);
		return CHANGE_MODE_TRUE;
	}
	else if(Key == RESET_PASSWORD_KEY)
	{
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Enter Password:");
		H_LCD_void_GotoXY(1,0);
		return CHANGE_MODE_TRUE;
	}
	else if(Key == FACTORY_RESET_KEY)
	{
		*Mode = LOGIN_FACTORY_RESET_MODE;
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Start Factory reset");
		_delay_ms(2000);
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Enter Password:");
		H_LCD_void_GotoXY(1,0);
		return CHANGE_MODE_TRUE;
	}
	return CHANGE_MODE_FALSE;
}

Entering_Password_Status IsCompleteEnteringPassword(u8 PasswordEnterIndex)
{
	if(PasswordEnterIndex == PASSWORD_LENGTH)
	{
		return COMPLETE_ENTERING_PASSWORD;
	}
	return NOT_COMPLETE_ENTERING_PASSWORD;
}

Password_Status CheckPassword(u8* EnteredPassword, u8* OriginalPassword)
{
	for(u8 i=0; i<PASSWORD_LENGTH; i++)
	{
		if(EnteredPassword[i] != OriginalPassword[i])
		{
			return NOT_CORRECT_PASSWORD;
		}
	}
	return CORRECT_PASSWORD;
}

void OpenDoor()
{
	//Relay on
	//Must make a Hall layer for Relay
	M_DIO_void_SetPinValue(DIO_PC7, DIO_High);
	_delay_ms(10000);
	M_DIO_void_SetPinValue(DIO_PC7, DIO_LOW);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Enter Password:");
	H_LCD_void_GotoXY(1,0);
}

void WelcomMessage()
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Welcom");
}

void DisplayLastLoginTime()
{
	H_LCD_void_GotoXY(1,0);
	H_LCD_void_SendString("Last: ");
	u8 Byte;
	H_ExEEPROM_ReadByte(TIME_HOURS_EEPROM_ADDRESS, &Byte);
	H_LCD_void_SendNumber(Byte);
	H_LCD_void_SendString(":");
	_delay_ms(1);

	H_ExEEPROM_ReadByte(TIME_MINUTES_EEPROM_ADDRESS, &Byte);
	H_LCD_void_SendNumber(Byte);
	H_LCD_void_SendString(":");
	_delay_ms(1);

	H_ExEEPROM_ReadByte(TIME_SECONDS_EEPROM_ADDRESS, &Byte);
	H_LCD_void_SendNumber(Byte);
	H_LCD_void_SendString(" ");
	_delay_ms(1);

	H_ExEEPROM_ReadByte(TIME_AMPM_EEPROM_ADDRESS, &Byte);
	if(Byte == RTC_AM)
	{
		H_LCD_void_SendString("AM");
	}
	else if(Byte == RTC_PM)
	{
		H_LCD_void_SendString("PM");
	}
	_delay_ms(1);

}

void DisplayLoginTime()
{
	RTC_Time_Struct T = H_RTC_GetTime();
	//H_RTC_DisplayTime(T);//Not work
	H_LCD_void_GotoXY(2,0);
	H_LCD_void_SendString("Now: ");

	H_LCD_void_SendNumber(T.Hours);
	H_LCD_void_SendChar(' ');
	H_LCD_void_SendNumber(T.Minutes);
	H_LCD_void_SendChar(' ');
	H_LCD_void_SendNumber(T.Seconds);
	H_LCD_void_SendChar(' ');
	if(T.Mode12_24 == RTC_12_MODE)
	{
		if(T.AM_PM == RTC_AM)
			H_LCD_void_SendString("AM");
		else if(T.AM_PM == RTC_PM)
			H_LCD_void_SendString("PM");
		_delay_ms(50);
	}

}

void DisplayLoginDate()
{
	RTC_Date_Struct DateStruct = H_RTC_GetDate();
	switch(DateStruct.Day)
	{
	case RTC_SUNDAY:
		H_LCD_void_SendString("SUN ");
	break;
	case RTC_MONDAY:
		H_LCD_void_SendString("MON ");
	break;
	case RTC_TUESDAY:
		H_LCD_void_SendString("TUES ");
	break;
	case RTC_WEDNESDAY:
		H_LCD_void_SendString("WEDNES ");
	break;
	case RTC_THURSDAY:
		H_LCD_void_SendString("THURS ");
	break;
	case RTC_FRIDAY:
		H_LCD_void_SendString("FRI ");
	break;
	case RTC_SATURDAY:
		H_LCD_void_SendString("SAT ");
	break;
	}
	H_LCD_void_SendNumber(DateStruct.DayDate);
	H_LCD_void_SendChar(' ');
	H_LCD_void_SendNumber(DateStruct.Month);
	H_LCD_void_SendChar(' ');
	H_LCD_void_SendNumber(DateStruct.Year);
	H_LCD_void_SendChar(' ');
}

void StoreLoginTime()
{
	RTC_Time_Struct T = H_RTC_GetTime();
	_delay_ms(2);
	H_ExEEPROM_WriteByte(TIME_HOURS_EEPROM_ADDRESS,T.Hours);
	_delay_ms(2);
	H_ExEEPROM_WriteByte(TIME_MINUTES_EEPROM_ADDRESS,T.Minutes);
	_delay_ms(2);
	H_ExEEPROM_WriteByte(TIME_SECONDS_EEPROM_ADDRESS,T.Seconds);
	_delay_ms(2);
	H_ExEEPROM_WriteByte(TIME_AMPM_EEPROM_ADDRESS,T.AM_PM);
	_delay_ms(2);
	H_ExEEPROM_WriteByte(TIME_MODE_EEPROM_ADDRESS,T.Mode12_24);
	_delay_ms(2);
}

void StoreLoginDate()
{
	RTC_Date_Struct D = H_RTC_GetDate();
	H_ExEEPROM_WriteByte(Date_DAY_EEPROM_ADDRESS,D.Day);
	_delay_ms(1);
	H_ExEEPROM_WriteByte(DATE_DAYDATE_EEPROM_ADDRESS,D.DayDate);
	_delay_ms(1);
	H_ExEEPROM_WriteByte(Date_MONTH_EEPROM_ADDRESS,D.Month);
	_delay_ms(1);
	H_ExEEPROM_WriteByte(DATE_YEAR_EEPROM_ADDRESS,D.Year);
	_delay_ms(1);
}


void SendStartToMCU2()
{
	//Put Logic Heigh on Oin that connected to MCU2
	M_DIO_void_SetPinValue(DIO_PA7 ,DIO_High);
}

void HandleChangePasswordDisplay(Enter_password_Number* PasswordNumber)
{
	switch(*PasswordNumber)
	{
	case FIRST_PASSWORD:
		*PasswordNumber = SECOND_PASSWORD;
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("New Password:");
		H_LCD_void_GotoXY(1,0);
	break;
	case SECOND_PASSWORD:
		*PasswordNumber = FIRST_PASSWORD;//reset
		H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
		H_LCD_void_SendString("Enter Password:");
		H_LCD_void_GotoXY(1,0);
	break;
	}
}

void StoreNewPassword(u8* NewPassword,u8* OriginalPassword)
{
	for(u8 i=0; i<PASSWORD_LENGTH; i++)
	{
		OriginalPassword[i] = NewPassword[i];
		H_ExEEPROM_WriteByte(PASSWPRD_EEPROM_ADDRESS+i, NewPassword[i]);
		_delay_ms(200);
		NewPassword[i] = '\0';
	}
	//H_ExEEPROM_WriteBuffer(PASSWPRD_EEPROM_ADDRESS, NewPassword, PASSWORD_LENGTH);//Not Work

	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Password is changed");
	_delay_ms(2000);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Enter Password:");
	H_LCD_void_GotoXY(1,0);
}

void ResetPassword(u8* PasswordEnterIndex)
{
	*PasswordEnterIndex = 0;
}

Blocking_Status HandleErrorPassword(u8* TrailNumber)
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Wrong Password");
	if(TRAIL_NUMBER_ACCEPTED - *TrailNumber == 0)
	{
		_delay_ms(1000);
		return BLOCKING_MODE;
	}

	H_LCD_void_GotoXY(1,0);
	H_LCD_void_SendNumber(TRAIL_NUMBER_ACCEPTED - *TrailNumber);
	H_LCD_void_SendString(" Trails Only");
	_delay_ms(2000);

	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Enter Password:");
	H_LCD_void_GotoXY(1,0);

	(*TrailNumber)++;
	return NOT_BLOCKING_MODE;
}

void BlockAndAlarmTurnOn(Login_Mode* Mode)
{
	*Mode = LOGIN_BLOCKING_MODE;
	LedControl(Mode);

	//Buzzer Turn on
	//Must make a Hall layer for buzzer
	M_DIO_void_SetPinValue(DIO_PC6, DIO_High);

	H_LCD_void_GotoXY(1,0);
	H_LCD_void_SendString("Blocking...");
}

Finger_Print_Status ScanFingerPrint(u8 PageID)
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Athunticate Finger");
	_delay_ms(1000);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Put Your Finger");
	FP_Confirmation_Code ConfirmationCode;

	u16 TimeOut = 0;
	while(ConfirmationCode != COMMAND_EXECUTION_COMPLETE)
	{
		TimeOut++;
		if(TimeOut == 10)
		{
			if(ConfirmationCode == FAIL_FIND_MATCHING_FINGER)
			{
				return FINGER_NOT_DETECTED;
			}
			else//if time out
			{
				return TIME_OUT;
			}
		}
		_delay_ms(500);
		ConfirmationCode = H_FP_ScanAndSearch(0x00, PageID);
	}
	return FINGER_CHECKED_SUCCESSFUL;
}

void HandleFingerPrintDisplay(Finger_Print_Status Status)
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	if(Status == FINGER_STORE_SUCCESSFUL)
	{
		H_LCD_void_SendString("Succssful New Finger");
	}
	else if(Status == FINGER_STORE_FAILURE)
	{
		H_LCD_void_SendString("Error New Finger");
	}
	else if(Status == NO_FINGER_DETECTED)
	{
		H_LCD_void_SendString("No Finger Detected");
	}
	else if(Status == TIME_OUT)
	{
		H_LCD_void_SendString("Time Out");
	}
	else// if(Status == UNDEFINED_ERROR)
	{
		H_LCD_void_SendString("Error");
	}
	_delay_ms(2000);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Enter Password");
	H_LCD_void_GotoXY(1,0);
}

Finger_Print_Status StoreNewFingerPrint(u8 PageID)
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Store New Finger");
	_delay_ms(2000);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Put Your Finger");

	FP_Confirmation_Code ConfirmationCode = 0x1;

	u16 TimeOut = 0;
	while(ConfirmationCode != COMMAND_EXECUTION_COMPLETE)
	{
		TimeOut++;
		if(TimeOut == 10)
		{
			return TIME_OUT;
		}
		_delay_ms(1000);

		ConfirmationCode = H_FP_ScanAndStore(PageID);
		/*if(ConfirmationCode == NO_FINGER_DETECTED)
		{
			H_LCD_void_SendString("Error New Finger");
			_delay_ms(2000);
			return FINGER_NOT_DETECTED;
		}*/
	}
	return FINGER_STORE_SUCCESSFUL;
}

void StorePageID(u8 PageID)
{
	H_ExEEPROM_WriteByte(FP_PAGE_ID_ADDRESS, PageID);
}

void ReadPageID(u8* PageID)
{
	H_ExEEPROM_ReadByte(FP_PAGE_ID_ADDRESS, PageID);
}



void FactoryResetSystem(u8* OriginalPassword, u8* PageID)
{
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Factory Reset...");
	*PageID = 0;
	StorePageID(0);

	H_FP_EmptyLibrary();

	u8 InitialPaswword[PASSWORD_LENGTH];
	for(u8 i=0; i<PASSWORD_LENGTH; i++)
	{
		InitialPaswword[i] = '1';
	}
	StoreNewPassword(InitialPaswword, OriginalPassword);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Reset Complete");
	_delay_ms(2000);
	H_LCD_void_SendCommand(LCD_CLEAR_DISPLAY);
	H_LCD_void_SendString("Enter Password:");
	H_LCD_void_GotoXY(1,0);
}
