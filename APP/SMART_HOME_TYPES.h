/*
 * SMART_HOME_TYPES.h
 *
 *  Created on: Mar 14, 2023
 *      Author: joseph
 */

#ifndef APP_SMART_HOME_TYPES_H_
#define APP_SMART_HOME_TYPES_H_

typedef enum
{
	LOGIN_ENTER_PASSWORD_MODE = 0,
	LOGIN_CHANGE_PASSWORD_MODE = 1,
	LOGIN_BLOCKING_MODE = 2,
	LOGIN_PASSWORD_COMPLETE = 3,
	LOGIN_COMPLETE = 3,
	LOGIN_STORE_NEW_FINGER_PRINT_MODE = 4,
	LOGIN_FACTORY_RESET_MODE = 5,
	LOGIN_FIRST_TIME_MODE = 6,
}Login_Mode;

typedef enum
{
	CHANGE_MODE_FALSE = 0,
	CHANGE_MODE_TRUE = 1,
}Change_Mode_Status;

typedef enum
{
	NOT_COMPLETE_ENTERING_PASSWORD = 0,
	COMPLETE_ENTERING_PASSWORD = 1,
}Entering_Password_Status;

typedef enum
{
	NOT_CORRECT_PASSWORD = 0,
	CORRECT_PASSWORD = 1,
}Password_Status;

typedef enum
{
	FIRST_PASSWORD = 1,
	SECOND_PASSWORD = 2,
}Enter_password_Number;

typedef enum
{
	NOT_BLOCKING_MODE =0,
	BLOCKING_MODE =1,
}Blocking_Status;

typedef enum
{
	FINGER_NOT_DETECTED = 0,
	FINGER_CHECKED_SUCCESSFUL = 1,
	FINGER_STORE_SUCCESSFUL = 1,
	FINGER_CHECKED_FAILURE = 2,
	FINGER_STORE_FAILURE =3,
	TIME_OUT = 4,
	UNDEFINED_ERROR = 5,
}Finger_Print_Status;

#endif /* APP_SMART_HOME_TYPES_H_ */
