/*
 * SMART_HOME_PRIV.h
 *
 *  Created on: Mar 15, 2023
 *      Author: joseph
 */

#ifndef APP_SMART_HOME_PRIV_H_
#define APP_SMART_HOME_PRIV_H_

#define PASSWPRD_EEPROM_ADDRESS					0x0000

#define TIME_HOURS_EEPROM_ADDRESS				0x50
#define TIME_MINUTES_EEPROM_ADDRESS				0x60//there is an error in location 0x51
#define TIME_SECONDS_EEPROM_ADDRESS				0x52
#define TIME_AMPM_EEPROM_ADDRESS				0x53
#define TIME_MODE_EEPROM_ADDRESS				0x54

#define Date_DAY_EEPROM_ADDRESS					0x55
#define DATE_DAYDATE_EEPROM_ADDRESS				0x56
#define Date_MONTH_EEPROM_ADDRESS				0x57
#define DATE_YEAR_EEPROM_ADDRESS				0x58

#define FP_PAGE_ID_ADDRESS						0x70

#endif /* APP_SMART_HOME_PRIV_H_ */
