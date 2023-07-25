/*
 * main.c
 *
 *  Created on: Feb 17, 2023
 *      Author: joseph
 */

#include <avr/delay.h>

#include "STD_TYPES.h"
#include "DIO_INT.h"
#include "PORT_INT.h"
#include "LED_INT.h"
#include "LCD_INT.h"
#include "KEYPAD_INT.h"
#include "GIE_INT.h"
#include "UART_INT.h"
#include "I2C_INT.h"
#include "ExEEPROM_INT.h"
#include "RTC_INT.h"
#include "FINGER_PRINT_INT.h"

#include "SMART_HOME_INT.h"




extern const Port_Config_Type PORT_Config_Arr[PORT_CONFIG_ARR_SIZE];


int main()
{
	/*Initialization*/
	M_PORT_void_Int(PORT_Config_Arr);

	H_LCD_void_Init();

	M_GIE_Enable();

	InitializeSystem();
////////////////////////

	u8 PageID = 0;

	//Original password that stored
	//Initial password is 1111
#if FIRST_TIME_DEBUG == 1
	u8 OriginalPassword[PASSWORD_LENGTH] = {'1','1','1','1'};
#elif FIRST_TIME_DEBUG == 0
	u8 OriginalPassword[PASSWORD_LENGTH];
#endif

	Login_Mode LoginMode = LOGIN_ENTER_PASSWORD_MODE;

	ReadPageID(&PageID);
	ReadStoredPassword(OriginalPassword);

	//FactoryResetSystem(OriginalPassword, &PageID);
	//if First login
	if(PageID == 0)
	{
		LoginMode = LOGIN_FIRST_TIME_MODE;
	}

	//Pssword that the user will enter
	u8 Password[PASSWORD_LENGTH];
	u8 PasswordEnteringIndex = 0;

	//Variables will be needed in while(1). All variables initaly zero or corresponding to zero
	Change_Mode_Status ChangeModeStatus = CHANGE_MODE_FALSE;
	u8 KeyPressed = KEYPAD_UNPRESSED;
	Entering_Password_Status CompletePasswordStatus = NOT_COMPLETE_ENTERING_PASSWORD;
	Password_Status PasswordStatus = NOT_CORRECT_PASSWORD;
	Enter_password_Number EnterPasswordNumber = FIRST_PASSWORD;
	u8 TrailNumber = 1;
	Blocking_Status BlockingStatus = NOT_BLOCKING_MODE;
	Finger_Print_Status FingerPrintStatus = FINGER_CHECKED_FAILURE;


  	while(1)
	{
  		if(LoginMode != LOGIN_BLOCKING_MODE)
  		{
  			KeyPressed = ReadKeyPad(Password, &PasswordEnteringIndex);

			ChangeModeStatus = ChangeMode(KeyPressed, &LoginMode);
			if(ChangeModeStatus == CHANGE_MODE_TRUE)
			{
				ResetPassword(&PasswordEnteringIndex);
			}

			CompletePasswordStatus = IsCompleteEnteringPassword(PasswordEnteringIndex);
			if(CompletePasswordStatus == COMPLETE_ENTERING_PASSWORD)
			{
				PasswordStatus = CheckPassword(Password, OriginalPassword);
				if(PasswordStatus == CORRECT_PASSWORD || EnterPasswordNumber == SECOND_PASSWORD || LoginMode == LOGIN_FIRST_TIME_MODE)
				{
					TrailNumber = 1;

					if(LoginMode == LOGIN_FIRST_TIME_MODE || EnterPasswordNumber == SECOND_PASSWORD)
					{
						//do nothing
					}
					else
					{
						//Busy wait with time out
						FingerPrintStatus = ScanFingerPrint(PageID);
					}

					if(FingerPrintStatus == FINGER_CHECKED_SUCCESSFUL || LoginMode == LOGIN_FIRST_TIME_MODE || EnterPasswordNumber == SECOND_PASSWORD)
					{
						if(LoginMode == LOGIN_ENTER_PASSWORD_MODE)
						{
							LoginMode = LOGIN_COMPLETE;
							WelcomMessage();
							DisplayLastLoginTime();
							StoreLoginTime();
							StoreLoginDate();
							DisplayLoginTime();
							LedControl(&LoginMode);
							OpenDoor();
							SendStartToMCU2();
							LoginMode = LOGIN_ENTER_PASSWORD_MODE;
							ResetPassword(&PasswordEnteringIndex);
							LedControl(&LoginMode);
						}
						else if(LoginMode == LOGIN_CHANGE_PASSWORD_MODE)
						{
							if(EnterPasswordNumber == FIRST_PASSWORD)
							{
								HandleChangePasswordDisplay(&EnterPasswordNumber);
								ResetPassword(&PasswordEnteringIndex);
							}
							else if(EnterPasswordNumber == SECOND_PASSWORD)
							{
								HandleChangePasswordDisplay(&EnterPasswordNumber);
								StoreNewPassword(Password, OriginalPassword);
								ResetPassword(&PasswordEnteringIndex);

								LoginMode = LOGIN_ENTER_PASSWORD_MODE;
								LedControl(&LoginMode);
							}
						}
						else if(LoginMode == LOGIN_STORE_NEW_FINGER_PRINT_MODE || LoginMode == LOGIN_FIRST_TIME_MODE)
						{
							LedControl(&LoginMode);
							FingerPrintStatus = StoreNewFingerPrint(PageID);
							if(FingerPrintStatus == FINGER_STORE_SUCCESSFUL)
							{
								PageID++;
								StorePageID(PageID);
								HandleFingerPrintDisplay(FINGER_STORE_SUCCESSFUL);

								if(LoginMode == LOGIN_FIRST_TIME_MODE)
								{
									StoreNewPassword(Password, OriginalPassword);
								}

								LoginMode = LOGIN_ENTER_PASSWORD_MODE;
								ResetPassword(&PasswordEnteringIndex);
								LedControl(&LoginMode);
							}
							else//if any error
							{
								HandleFingerPrintDisplay(FINGER_STORE_FAILURE);
								if(LoginMode != LOGIN_FIRST_TIME_MODE)
								{
									LoginMode = LOGIN_ENTER_PASSWORD_MODE;
									ResetPassword(&PasswordEnteringIndex);
								}
							}

						}
						else if(LoginMode == LOGIN_FACTORY_RESET_MODE)
						{
							FactoryResetSystem(OriginalPassword, &PageID);
							LoginMode = LOGIN_FIRST_TIME_MODE;
							ResetPassword(&PasswordEnteringIndex);
						}
					}
					else//if error in finger print
					{
						HandleFingerPrintDisplay(FingerPrintStatus);
						LoginMode = LOGIN_ENTER_PASSWORD_MODE;
						ResetPassword(&PasswordEnteringIndex);
					}
				}
				else if(PasswordStatus == NOT_CORRECT_PASSWORD)
				{
					ResetPassword(&PasswordEnteringIndex);
					BlockingStatus = HandleErrorPassword(&TrailNumber);
					if(BlockingStatus == BLOCKING_MODE)
					{
						BlockAndAlarmTurnOn(&LoginMode);
					}
				}
			}
  		}

	}
	return 0;
}



