/*
 * FINGER_PRINT_TYPES.h
 *
 *  Created on: Mar 12, 2023
 *      Author: joseph
 */

#ifndef FINGER_PRINT_FINGER_PRINT_TYPES_H_
#define FINGER_PRINT_FINGER_PRINT_TYPES_H_

typedef enum
{
	COMMAND_EXECUTION_COMPLETE=0x00,
	ERROR_WHEN_RECEIVING_DATA_PACKAGE=0x01,
	NO_FINGER_DETECTED = 0x02,
	FAIL_ENROLL_FINGER=0x03,
	FAIL_GENERATE_CHARACTER_OVER_DISORDERLY	= 0x06,
	FAIL_GENERATE_CHARACTER_LACKNESS_OVER_SMALLNESS = 0x07,
	FINGER_DOSENOT_MATCH=0x08,
	FAIL_FIND_MATCHING_FINGER=0x09,
	FAIL_COMBINE_CHARACTER_FILE=0x0A,
	ADDRESSING_PAGEID_BEYOND_FINGER_LIBRARY=0x0B,
	ERROR_READING_TEMPLATE_OR_TEMPLATE_INVALID=0x0C,
	ERROR_UPLOADING_TEMPLATE=0x0D,
	MODULE_CANNOT_RECEIVE_FOLLOWING_DATA_PACKAGES=0x0E,
	ERROR_UPLOADING_IMAGE=0x0F,
	FAIL_DELETE_TEMPLATE=0x10,
	FAIL_CLEAR_FINGER_LIBRARY=0x11,
	WRONG_PASSWORD=0x13,
	FAIL_GENERATE_IMAGE_LACKNESS_VALID_PRIMARY_IMAE=0x15,
	ERROR_WRITING_FLASH=0x18,
	NO_DEFINITION_ERROR=0x19,
	INVALID_REGISTER_NUMBER=0x1A,
	INCORRECT_CONFIGURATION_REGISTER=0x1B,
	WRONG_NOTEPAD_PAGE_NUMBER=0x1C,
	FAIL_OPERATE_COMMUNICATION_PORT=0x1D,

	SENSOR_ABNORMAL=0x29,

	//Not in the datasheet
	INPUT_SCAN_NUMBER_OUT_OF_RANGE = 0x99

}FP_Confirmation_Code;

typedef enum
{
	FP_FIRST_SCAN=1,
	FP_SECOND_SCAN=2,
}FP_Scan_Number;


#endif /* FINGER_PRINT_FINGER_PRINT_TYPES_H_ */
