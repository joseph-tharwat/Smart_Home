/*
 * SMART_HOME_INT.h
 *
 *  Created on: Mar 14, 2023
 *      Author: joseph
 */

#ifndef APP_SMART_HOME_INT_H_
#define APP_SMART_HOME_INT_H_

#include "SMART_HOME_TYPES.h"
#include "SMART_HOME_CFG.h"

#define FIRST_TIME_DEBUG  0

void InitializeSystem();

void ReadStoredPassword(u8* Passwprd);

u8 ReadKeyPad(u8* Password, u8* PasswordEnterIndex);

void LedControl(Login_Mode* Mode);

Change_Mode_Status ChangeMode(u8 Key, Login_Mode* Mode);

Entering_Password_Status IsCompleteEnteringPassword(u8 PasswordEnterIndex);

Password_Status CheckPassword(u8* EnteredPassword, u8* OriginalPassword);

void OpenDoor();

void WelcomMessage();

void StoreLoginTime();

void StoreLoginDate();

void DisplayLastLoginTime();

void DisplayLoginTime();

void DisplayLoginDate();

void SendStartToMCU2();

void HandleChangePasswordDisplay(Enter_password_Number* PasswordNumber);

void StoreNewPassword(u8* NewPassword,u8* OriginalPassword);

void ResetPassword(u8* PasswordEnterIndex);

Blocking_Status HandleErrorPassword(u8* TrailNumber);

void BlockAndAlarmTurnOn(Login_Mode* Mode);

Finger_Print_Status ScanFingerPrint(u8 PageID);

void HandleFingerPrintDisplay(Finger_Print_Status Status);

Finger_Print_Status StoreNewFingerPrint(u8 PageID);

//PageID must be in hex corresponding
void StorePageID(u8 PageID);

void ReadPageID(u8* PageID);

void FactoryResetSystem(u8* OriginalPassword, u8* PageID);

#endif /* APP_SMART_HOME_INT_H_ */
