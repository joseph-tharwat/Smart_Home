/*
 * ExEEPROM_PROG.c
 *
 *  Created on: Mar 9, 2023
 *      Author: joseph
 */

#include "STD_TYPES.h"

#include "I2C_INT.h"

#include "ExEEPROM_CFG.h"
#include "ExEEPROM_PRIV.h"
#include "ExEEPROM_TYPES.h"
#include "ExEEPROM_INT.h"

#include <avr/delay.h>

#define READ_WRITE_BUFFER 	0

void H_ExEEPROM_Init()
{
	M_I2C_Init(I2C_CLK_DIV_1, 100000);
}

void H_ExEEPROM_WriteByte(u16 Address, u8 Byte)
{
	u8 DeviceAddress = ((Address & 0x30000)>>7) | 0b10100000;
	M_I2C_SendStart();
	M_I2C_SendByte(DeviceAddress);//Send Address
	u8 LowerAddressByte = Address;//Send Rest of Address
	M_I2C_SendByte(LowerAddressByte);
	M_I2C_SendByte(Byte);
	M_I2C_SendStop();
}
#if READ_WRITE_BUFFER == 1
void H_ExEEPROM_WriteBuffer(u16 Address, u8* Buffer, u16 Count)
{
	u8 DeviceAddress = ((Address & 0x30000)>>7) | 0b10100000;
	M_I2C_SendStart();
	M_I2C_SendByte(DeviceAddress);//Send Address
	u8 LowerAddressByte = Address;//Send Rest of Address
	M_I2C_SendByte(LowerAddressByte);

	for(u16 i=0; i<Count; i++)
	{
		M_I2C_SendByte(Buffer[i]);
		_delay_ms(400);
	}
	M_I2C_SendStop();
}
#endif

void H_ExEEPROM_ReadByte(u16 Address, u8* Byte)
{
	u8 DeviceAddress = ((Address & 0x30000)>>7) | 0b10100000;
	M_I2C_SendStart();
	M_I2C_SendByte(DeviceAddress);//Send Address
	u8 LowerAddressByte = Address;//Send Rest of Address
	M_I2C_SendByte(LowerAddressByte);

	M_I2C_SendStart();
	M_I2C_SendByte(0b10100001);//Address
	M_I2C_ReceiveByte_NoACK(Byte);
	M_I2C_SendStop();
}

#if READ_WRITE_BUFFER == 1
void H_ExEEPROM_ReadBuffer(u16 Address, u8* Buffer, u16 Count)
{
	u8 DeviceAddress = ((Address & 0x30000)>>7) | 0b10100000;
	M_I2C_SendStart();
	M_I2C_SendByte(DeviceAddress);//Send Address
	u8 LowerAddressByte = Address;//Send Rest of Address
	M_I2C_SendByte(LowerAddressByte);

	M_I2C_SendStart();
	M_I2C_SendByte(0b10100001);//Address

	for(int i=0; i<Count-1;i++)
    {
	  M_I2C_ReceiveByte_ACK(Buffer+i);
    }
	M_I2C_ReceiveByte_NoACK(Buffer + Count - 1);
	M_I2C_SendStop();
}
#endif
