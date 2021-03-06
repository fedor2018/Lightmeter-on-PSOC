//*****************************************************************************
//*****************************************************************************
//  FILENAME: `$INSTANCE_NAME`_FS.h
//  Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
//
//
//  DESCRIPTION: SDCard User Module C Language header file for the
//               PSoC family of devices.  This header file contains the low
//               level file function calls not intended to be used by the
//               programmer.  See the `$INSTANCE_NAME`.h file for a list of
//               user APIs.
//
//-----------------------------------------------------------------------------
//  The original source for this user module was purchased from
//  Efficient Computer Systems, LLC.
//-----------------------------------------------------------------------------
//
//  Copyright 2003-2006   Efficient Computer Systems, LLC
//  Licensed only for use on any Cypress PSOC Mixed-Signal Controllers.
//  All rights reserved
//
//-----------------------------------------------------------------------------
//
//         Created 12-04-03   By: Lee W. Morin and Herb Winters
//  1.00   Release 04-24-06   By: Lee Morin, Herb Winters, Eric Curtis
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2013-14. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************

#ifndef `$INSTANCE_NAME`_FS_HEADER
#define `$INSTANCE_NAME`_FS_HEADER

#include "`$INSTANCE_NAME`_SD_CS.h"
#include "`$INSTANCE_NAME`_SD_PWR.h"

#include "cytypes.h"
#include "CyLib.h"

// ============================================================================
// = Optional card Socket functions
// =  NOTE: selected by Module Parameters "`$INSTANCE_NAME`_PRESENT" and
// =        "`$INSTANCE_NAME`_WPROT" being set to any PSOC Pin. Disabled if
// =          Parameter set to NONE
//--------------------------------------------------------------
#define     `$INSTANCE_NAME`_ENABLE_PRESENT    0
#define     `$INSTANCE_NAME`_ENABLE_WPROTECT   0

#if (`$INSTANCE_NAME`_ENABLE_PRESENT == 1)
#define `$INSTANCE_NAME`_CPPort    `$INSTANCE_NAME`_SD_CD_Read()
#define `$INSTANCE_NAME`_CPMask    1
#endif

#if (`$INSTANCE_NAME`_ENABLE_WPROTECT == 1)
#define `$INSTANCE_NAME`_WPPort    `$INSTANCE_NAME`_SD_WP_Read()
#define `$INSTANCE_NAME`_WPMask    1
#endif

#define `$INSTANCE_NAME`_ENABLE  1
#define `$INSTANCE_NAME`_DISABLE 0

// ============================================================================
// = Define Resource usage configuration option
// = Only one of these options should be use at a time
// ============================================================================
#define `$INSTANCE_NAME`_Build_Config_Level   `@BUILD_CONFIG`
#define ENABLE_FULL_FILE_SYSTEM         0
#define ENABLE_STANDARD_FILE_SYSTEM     1
#define ENABLE_BASIC_FILE_SYSTEM        2
#define ENABLE_READONLY_FILE_SYSTEM     3
#define ENABLE_BASIC_READWRITE          4
#define ENABLE_CUSTOM_CONFIGURATION     5

// ============================================================================
// = This section works with the "Resource usage configuration"
// = parameter to enable the correct options.
// ============================================================================
#if  ( ENABLE_CUSTOM_CONFIGURATION == `$INSTANCE_NAME`_Build_Config_Level )
// Not used. Will not work.
// #include "`$INSTANCE_NAME`_Config.h"
#else
// Maximum number of files that can be open at one time
#define `$INSTANCE_NAME`_MAXFILES   `@MAXFILES`
#endif

//==============================================================
// The following list of #defines can be use to create Custom
// configurations Just set the "Resource usage configuration"
// parameter to "CUSTOM" then add a header file named `$INSTANCE_NAME`_Config.h
// then place any of the #defines below to create you configuration
//==============================================================
//--------------------------------------------------------------
// File systems to support if ENABLE_FILESYSTEM defined
// Note: If file systems enabled - FAT16 is enabled
//--------------------------------------------------------------
//#define ENABLE_FILESYSTEM
//#define ENABLE_FAT32
//--------------------------------------------------------------
// Write supported
//#define ENABLE_WRITE
//--------------------------------------------------------------
// Enable subdirectory feautures (Not yet developed)
//#define ENABLE_SUBDIR
//--------------------------------------------------------------
// High level File commands
//#define ENABLE_FILECOPY
//#define ENABLE_FILERENAME
//#define ENABLE_FILEREMOVE
//--------------------------------------------------------------
// DEBUG FUNCTIONS
//#define ENABLE_DEBUGFUNCT
//==============================================================

#if (ENABLE_FULL_FILE_SYSTEM == `$INSTANCE_NAME`_Build_Config_Level)
#define ENABLE_FILESYSTEM
#define ENABLE_FAT32
#define ENABLE_WRITE
// = #define ENABLE_SUBDIR          // Not yet developed
#define ENABLE_FILECOPY
#define ENABLE_FILERENAME
#define ENABLE_FILEREMOVE
#define ENABLE_DEBUGFUNCT           // Only NEED for debug
#endif

#if (ENABLE_STANDARD_FILE_SYSTEM == `$INSTANCE_NAME`_Build_Config_Level)
#define ENABLE_FILESYSTEM
//#define ENABLE_FAT32
#define ENABLE_WRITE
//#define ENABLE_SUBDIR             // Not yet developed
#define ENABLE_FILECOPY
#define ENABLE_FILERENAME
#define ENABLE_FILEREMOVE
//#define ENABLE_DEBUGFUNCT         // Only NEED for debug
#endif

#if (ENABLE_BASIC_FILE_SYSTEM == `$INSTANCE_NAME`_Build_Config_Level)
#define ENABLE_FILESYSTEM
//#define ENABLE_FAT32
#define ENABLE_WRITE
//#define ENABLE_SUBDIR             // Not yet developed
//#define ENABLE_FILECOPY
//#define ENABLE_FILERENAME
#define ENABLE_FILEREMOVE
//#define ENABLE_DEBUGFUNCT         // Only NEED for debug
#endif

#if (ENABLE_READONLY_FILE_SYSTEM == `$INSTANCE_NAME`_Build_Config_Level)
#define ENABLE_FILESYSTEM
//#define ENABLE_FAT32
//#define ENABLE_WRITE
//#define ENABLE_SUBDIR             // Not yet developed
//#define ENABLE_FILECOPY
//#define ENABLE_FILERENAME
//#define ENABLE_FILEREMOVE
//#define ENABLE_DEBUGFUNCT         // Only NEED for debug
#endif

#if (ENABLE_BASIC_READWRITE == `$INSTANCE_NAME`_Build_Config_Level)
//#define ENABLE_FILESYSTEM
//#define ENABLE_FAT32
#define ENABLE_WRITE
//#define ENABLE_SUBDIR             // Not yet developed
//#define ENABLE_FILECOPY
//#define ENABLE_FILERENAME
//#define ENABLE_FILEREMOVE
//#define ENABLE_DEBUGFUNCT         // Only NEED for debug
#endif

// ============================================================================
#define     `$INSTANCE_NAME`_ON      1
#define     `$INSTANCE_NAME`_OFF     0

// = R1 mask defines
#define     `$INSTANCE_NAME`_IDLE              0x01
#define     `$INSTANCE_NAME`_ERASE_CMD         0x02
#define     `$INSTANCE_NAME`_ILLEGAL_CMD       0x04
#define     `$INSTANCE_NAME`_CRC_ERROR         0x08
#define     `$INSTANCE_NAME`_ERASE_SEQ_ERROR   0x10
#define     `$INSTANCE_NAME`_ADDR_ERROR        0x20
#define     `$INSTANCE_NAME`_PARAM_ERROR       0x40

//----------------------------
// `$INSTANCE_NAME`_Status defines (SD card)
//----------------------------
// IFN   Invalid File Name
// FNF   File Not Found
// PRE   Parameter Range Error
// CE    Card Error
// FFE   File Format Error
// WRE   Write Error (Unused)
// FPE   File Pointer Error
// EOF   End Of File
//----------------------------
#define     `$INSTANCE_NAME`_IFN          0x01
#define     `$INSTANCE_NAME`_FNF          0x02
#define     `$INSTANCE_NAME`_PRE          0x04
#define     `$INSTANCE_NAME`_CE           0x08
#define     `$INSTANCE_NAME`_FFE          0x10
#define     `$INSTANCE_NAME`_FPE          0x20
#define     `$INSTANCE_NAME`_WRE          0x40
#define     `$INSTANCE_NAME`_EOF          0x80

// System defines
#define     `$INSTANCE_NAME`_FAIL         0xAA
#define     `$INSTANCE_NAME`_PASS         0x00
#define     `$INSTANCE_NAME`_XCARD        0x0F
#define     `$INSTANCE_NAME`_XFAT         0xF0
#define     `$INSTANCE_NAME`_UNUSED       0xFFFF

//----------------------------
// Card command defines
//----------------------------
#define     `$INSTANCE_NAME`_CMD0         0x40
#define     `$INSTANCE_NAME`_CMD1         0x41
#define     `$INSTANCE_NAME`_CMD9         0x49
#define     `$INSTANCE_NAME`_CMD10        0x4A
#define     `$INSTANCE_NAME`_CMD12        0x4C
#define     `$INSTANCE_NAME`_CMD13        0x4D
#define     `$INSTANCE_NAME`_CMD16        0x50
#define     `$INSTANCE_NAME`_CMD17        0x51
#define     `$INSTANCE_NAME`_CMD18        0x52
#define     `$INSTANCE_NAME`_CMD24        0x58
#define     `$INSTANCE_NAME`_CMD25        0x59
#define     `$INSTANCE_NAME`_CMD27        0x5B
#define     `$INSTANCE_NAME`_CMD28        0x5C
#define     `$INSTANCE_NAME`_CMD29        0x5D
#define     `$INSTANCE_NAME`_CMD30        0x5E
#define     `$INSTANCE_NAME`_CMD32        0x60
#define     `$INSTANCE_NAME`_CMD33        0x61
#define     `$INSTANCE_NAME`_CMD38        0x66
#define     `$INSTANCE_NAME`_CMD55        0x77
#define     `$INSTANCE_NAME`_CMD56        0x78
#define     `$INSTANCE_NAME`_CMD58        0x7A
#define     `$INSTANCE_NAME`_CMD59        0x7B

#define     `$INSTANCE_NAME`_ACMD13       0x4D
#define     `$INSTANCE_NAME`_ACMD18       0x52
#define     `$INSTANCE_NAME`_ACMD22       0x56
#define     `$INSTANCE_NAME`_ACMD23       0x57
#define     `$INSTANCE_NAME`_ACMD25       0x59
#define     `$INSTANCE_NAME`_ACMD26       0x5A
#define     `$INSTANCE_NAME`_ACMD38       0x66
#define     `$INSTANCE_NAME`_ACMD41       0x69
#define     `$INSTANCE_NAME`_ACMD42       0x6A
#define     `$INSTANCE_NAME`_ACMD51       0x73

#define     `$INSTANCE_NAME`_NOARGS       0x00000000

//--------------------------------
// Declare external variables
//--------------------------------
#ifdef ENABLE_FILESYSTEM
#ifdef ENABLE_FAT32
extern uint32   `$INSTANCE_NAME`_CurStart[`$INSTANCE_NAME`_MAXFILES+1];   // Starting FAT entry value for file
extern uint32   `$INSTANCE_NAME`_CurFat[`$INSTANCE_NAME`_MAXFILES+1];     // Current FAT entry value of cluster
#else
extern uint16   `$INSTANCE_NAME`_CurStart[`$INSTANCE_NAME`_MAXFILES+1];   // Starting FAT entry value for file
extern uint16   `$INSTANCE_NAME`_CurFat[`$INSTANCE_NAME`_MAXFILES+1];     // Current FAT entry value of cluster
#endif  // End ENABLE_FAT32

extern uint8    `$INSTANCE_NAME`_CurSect[`$INSTANCE_NAME`_MAXFILES+1];    // Current sector of the current cluster
extern uint8    `$INSTANCE_NAME`_CurAttr[`$INSTANCE_NAME`_MAXFILES];      // Current file attributes - Bits 6 and seven are unused
extern uint8    `$INSTANCE_NAME`_FileError[`$INSTANCE_NAME`_MAXFILES];    // Current error flags for file
extern uint8    `$INSTANCE_NAME`_FileMode[`$INSTANCE_NAME`_MAXFILES];     // Current Mode bits = "r"=0, "w"=1, "a"=2, "+"=3
#endif // End ENABLE_FILESYSTEM

extern uint32   `$INSTANCE_NAME`_CurSize[`$INSTANCE_NAME`_MAXFILES+1];    // Current file size (in bytes)
extern uint32   `$INSTANCE_NAME`_CurOffset[`$INSTANCE_NAME`_MAXFILES+1];  // Current offset into file

//extern uint8   Status;               // Temp value for returned status byte
extern uint8    `$INSTANCE_NAME`_CardType;                      // Card Type:    0=None,   1=MMC,    2=SD (lower nibble)
                                                                // FAT Type:     0=None,   10=FAT12, 20=FAT16, 30=FAT32 (upper nibble)
extern uint8 *  `$INSTANCE_NAME`_Buffer1;                       // Temporary buffer pointer for data reads and writes (part 1)
extern uint8 *  `$INSTANCE_NAME`_Buffer2;                       // Temporary buffer pointer for data reads and writes (part 2)

#ifdef ENABLE_FILESYSTEM
extern uint8    `$INSTANCE_NAME`_ClusterSize;                   // Cluster size in sectors
extern uint32   `$INSTANCE_NAME`_Fat1Start;                     // Start of 1st FAT Table (in bytes)
extern uint32   `$INSTANCE_NAME`_Fat2Start;                     // Start of 2nd FAT Table (in bytes)
extern uint32   `$INSTANCE_NAME`_DirStart;                      // Start of Root directory structure
#endif

extern uint32   `$INSTANCE_NAME`_DataStart;                     // Start of Data area

//---------------------------------------------------------------------------------------------
//                                   Function Prototypes
//---------------------------------------------------------------------------------------------

//---------------------------
// Low level card commands
//---------------------------
void        `$INSTANCE_NAME`_Cmd(uint8 CmdNum, uint32 Param);   // Sends out the command string including parameters
uint8       `$INSTANCE_NAME`_GetR1(void);                       // Returns R1 type command responsed
uint16      `$INSTANCE_NAME`_GetR2(void);                       // Returns R2 type command responsed
void        `$INSTANCE_NAME`_EndCmd(void);                      // Sends out the end of acommand string
void        `$INSTANCE_NAME`_Wait(void);                        // Wait a small amount of time  (Value not final)
void        `$INSTANCE_NAME`_Wait2(void);                       // Wait for approximately 50ms  (Value not final)
uint8       `$INSTANCE_NAME`_Cmd_00(void);                      // Resets Card to power up condition
uint8       `$INSTANCE_NAME`_Cmd_01(void);                      // Runs an MMC card's internal init routine
uint16      `$INSTANCE_NAME`_Cmd_13(void);                      // Returns the card status response
uint8       `$INSTANCE_NAME`_ACmd_41(void);                     // Runs an SD  card's internal init routine
uint8       `$INSTANCE_NAME`_Cmd_55(void);                      // Make the next command an App command
uint8       `$INSTANCE_NAME`_CheckReply(uint8 check);           // Compare check value to response
uint8       `$INSTANCE_NAME`_SetSize(uint32 size);              // Set sector size
uint32      `$INSTANCE_NAME`_GetTable(void);                    // Get Partition Table information and return boot sector start
void        `$INSTANCE_NAME`_XferWait(void);                    // Wait until transfer is complete
void        `$INSTANCE_NAME`_IncOffset(uint8 Fptr, uint8 mode); // Increment file position for CurOffset

//---------------------------
// Low level file commands
//---------------------------
#ifdef ENABLE_FILESYSTEM
uint8       `$INSTANCE_NAME`_GetBoot(uint32 BootStart);         // Get boot sector information and put it in Buffer
void        `$INSTANCE_NAME`_NextFat(uint8 Fptr);               // Loads CurFat[Fptr] with next FAT entry or FatEnd for end

//------------------------------------------------
// Low level commands affecting FAT16/32 switches
//------------------------------------------------
#ifdef ENABLE_FAT32
uint32      `$INSTANCE_NAME`_FatTrack(uint32 FatNum);           // Returns the next FAT entry in the chain.
uint32      `$INSTANCE_NAME`_LastFat(uint8 Fptr);               // Returns the last FAT entry used in a file chain
uint32      `$INSTANCE_NAME`_GetFatAddr(uint32 Fat);            // Return the sector address for the FAT entry
uint8 *     `$INSTANCE_NAME`_ReadFatSect(uint32 Fat);           // Read FAT entry sector into buffer and return buffer pointer
#else
uint16      `$INSTANCE_NAME`_FatTrack(uint16 FatNum);           // Returns the next FAT entry in the chain.
uint16      `$INSTANCE_NAME`_LastFat(uint8 Fptr);               // Returns the last FAT entry used in a file chain
uint32      `$INSTANCE_NAME`_GetFatAddr(uint16 Fat);            // Return the sector address for the FAT entry
uint8 *     `$INSTANCE_NAME`_ReadFatSect(uint16 Fat);           // Read FAT entry sector into buffer and return buffer pointer
#endif  // ENABLE_FAT32

uint8       `$INSTANCE_NAME`_NextSect(uint8 Fptr);              // Loads CurSect[Fptr] with next sector entry and sets FAT if needed
uint8       `$INSTANCE_NAME`_FindFile(uint8 Fptr, uint16 FileNum);// Find File in root directory for file pointer
uint8       `$INSTANCE_NAME`_ReadFileSect(uint8 Fptr);          // Read a sector of a file
void        `$INSTANCE_NAME`_GetAddress(uint8 Fptr, uint8 mode);// Calculate the address based on the current file/sub-directory position - mode 0=sector, 1=sect and offset
uint8 *     `$INSTANCE_NAME`_GetBuffPtr(uint16 Offset);         // Returns the pointer for read/write buffer offset
uint8 *     `$INSTANCE_NAME`_ReadDirSect(uint8 Fptr);           // Read directory entry sector into buffer and return buffer pointer
uint8       `$INSTANCE_NAME`_ParseFilename(uint8 * Filename);   // Parse the filename string and convert it into 8x3 dir format

//--------------------------------
// Low level file write commands
//--------------------------------

#ifdef ENABLE_WRITE
void        `$INSTANCE_NAME`_CopyDir(uint8 Fptr1, uint8 Fptr2); // Copy file directory information from file 1 to file 2
void        `$INSTANCE_NAME`_UpdateDir(uint8 Fptr);             // Update the directory entry from the current file info
void        `$INSTANCE_NAME`_WriteDirSect(uint8 Fptr);          // Write directory entry sector from the buffer
uint8       `$INSTANCE_NAME`_NewFile(uint8 Fptr, uint8 Filename[]);   // Create new file using filename
uint8       `$INSTANCE_NAME`_FileZero(uint8 Fptr, uint8 Del);   // Sets file size to zero and resets FAT entries or deletes file
uint8       `$INSTANCE_NAME`_WriteFileSect(uint8 Fptr);         // Write a sector to a file
uint8       `$INSTANCE_NAME`_AddFat(uint8 Fptr);                // Add a new FAT entry to the FAT chain, or create one

#ifdef ENABLE_FAT32
uint8       `$INSTANCE_NAME`_FatReclaim(uint32 FirstFat);       // Zero FAT chain starting at first FAT entry
void        `$INSTANCE_NAME`_WriteFatSect(uint32 Fat);          // Write FAT entry sector from the buffer
#else
uint8       `$INSTANCE_NAME`_FatReclaim(uint16 FirstFat);       // Zero FAT chain starting at first FAT entry
void        `$INSTANCE_NAME`_WriteFatSect(uint16 Fat);          // Write FAT entry sector from the buffer
#endif   // ENABLE_FAT32
#endif   // End ENABLE_WRITE
#endif   // End ENABLE_FILESYSTEM

// Debug functions
#ifdef ENABLE_DEBUGFUNCT
uint8       `$INSTANCE_NAME`_ACmd_13(void);                     // Get SD card status command
uint8       `$INSTANCE_NAME`_GetCID(void);                      // Send out command to read CID data into buffer
uint8       `$INSTANCE_NAME`_GetOCR(void);                      // Read card's OCR register routine
uint8       `$INSTANCE_NAME`_GetCSD(void);                      // Send out command to read CSD data into buffer
uint8       `$INSTANCE_NAME`_ReadByte(uint32 address);          // Return the byte pointed to by the absolute address
#endif

#endif

// ============================================================================

