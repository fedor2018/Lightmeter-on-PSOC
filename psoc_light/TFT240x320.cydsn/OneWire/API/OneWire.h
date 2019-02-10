/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#if !defined(`$INSTANCE_NAME`_H) 
#define `$INSTANCE_NAME`_H


#include "cytypes.h"        //Обеспечивает macros и еще что-то
//#include "cylib.h"
//#include "cyfitter.h"     //Файл определяет адреса при компиляции.


#define Tinact  20          //in us. (Inactive before next signal)
#define TMtr0   50          //Data bit 0 read,write 15-60us
#define TMtr1   10          //Data bit 1 read,write 1-15us
#define RST_MAX 480         //in us.(минимум 480)

#define true 1
#define false 0

#define MAXDEVICES 10	

#define OW_CMD_SEARCHROM	0xF0
#define OW_CMD_READROM		0x33
#define OW_CMD_MATCHROM		0x55
#define OW_CMD_SKIPROM		0xCC

#define	OW_SEARCH_FIRST	0xFF		// start new search
#define	OW_PRESENCE_ERR	0xFF
#define	OW_DATA_ERR	    0xFE
#define OW_LAST_DEVICE	0x00		// last device found
//			0x01 ... 0x40: continue searching

#define OW_DS1990_FAMILY_CODE	1
#define OW_DS2405_FAMILY_CODE	5
#define OW_DS2413_FAMILY_CODE	0x3A
#define OW_DS1822_FAMILY_CODE	0x22
#define OW_DS2430_FAMILY_CODE	0x14
#define OW_DS1990_FAMILY_CODE	1
#define OW_DS2431_FAMILY_CODE	0x2d
#define OW_DS18S20_FAMILY_CODE	0x10
#define OW_DS18B20_FAMILY_CODE	0x28
#define OW_DS2433_FAMILY_CODE	0x23
	
	// rom-code size including CRC
#define OW_ROMCODE_SIZE	8	
	
	
	
	
/***************************************
*        Function Prototypes 
***************************************/

uint8 `$INSTANCE_NAME`_R_Bit();                 //******   ReadBit ************

void `$INSTANCE_NAME`_W_Bit(uint8 payload);     //******   WriteBit ***********

uint8 `$INSTANCE_NAME`_BusReset();              //******** Bus Reset **********

void `$INSTANCE_NAME`_Write8(uint8 payload);    //******* Write a byte *********

uint8 `$INSTANCE_NAME`_Read8();              // чтение байта  


//++++++++++++    added from  GitHub    onewire.h    https://github.com/qidstudio/pyutc   +++++++++++++++ 

uint8 `$INSTANCE_NAME`_SearchROM( unsigned char diff, unsigned char *id );

void `$INSTANCE_NAME`_FindROM(unsigned char *diff, unsigned char id[]);

unsigned char `$INSTANCE_NAME`_ReadROM(unsigned char *buffer);

unsigned char `$INSTANCE_NAME`_MatchROM(unsigned char *rom);

#endif












//[] END OF FILE
