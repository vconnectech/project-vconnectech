/******************************************************************************
* Copyright (c) 2014 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xil_io.h
*
* @addtogroup common_io_interfacing_apis Register IO interfacing APIs
*
* The xil_io.h file contains the interface for the general I/O component, which
* encapsulates the Input/Output functions for the processors that do not
* require any special I/O handling.
*
* @{
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------- -------- -----------------------------------------------
* 5.00 	pkp  	 05/29/14 First release
* 6.00  mus      08/19/16 Remove checking of __LITTLE_ENDIAN__ flag for
*                         ARM processors
* 7.20  har      01/03/20 Added Xil_SecureOut32 for avoiding blindwrite for
*                         CR-1049218
* </pre>
******************************************************************************/


/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xstatus.h"

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 Data);
u32 Xil_EndianSwap32(u32 Data);
#ifdef ENABLE_SAFETY
extern u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#endif

#define  INLINE inline

/***************** Macros (Inline Functions) Definitions *********************/
#if defined __GNUC__
#if defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define DATA_SYNC		mbar(1)
# else
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define DATA_SYNC		dsb()
# endif
#else
# define SYNCHRONIZE_IO
# define INST_SYNC
# define DATA_SYNC
# define INST_SYNC
# define DATA_SYNC
#endif

#if defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#define INLINE inline
#else
#define INLINE __inline
#endif

extern u32 Xil_ReadReg32(UINTPTR vir_regaddr, u32 offset);
extern void Xil_WriteReg32(UINTPTR vir_regaddr, u32 offset, u32 data);

