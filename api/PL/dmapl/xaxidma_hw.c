/******************************************************************************
*
* Copyright (C) 2010 - 2019 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
 *  @file xaxidma_hw.h
* @addtogroup axidma_v9_9
* @{
 *
 * Hardware definition file. It defines the register interface and Buffer
 * Descriptor (BD) definitions.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00a jz   05/18/10 First release
 * 2.00a jz   08/10/10 Second release, added in xaxidma_g.c, xaxidma_sinit.c,
 *                     updated tcl file, added xaxidma_porting_guide.h
 * 3.00a jz   11/22/10 Support IP core parameters change
 * 4.00a rkv  02/22/11 Added support for simple DMA mode
 * 6.00a srt  01/24/12 Added support for Multi-Channel DMA mode
 * 8.0   srt  01/29/14 Added support for Micro DMA Mode and Cyclic mode of
 *		       operations.
 * 9.7   rsp  04/24/18 Added support for 64MB data transfer.Instead of #define
 *                     read max buffer width from IP config.
 *
 * </pre>
 *
 *****************************************************************************/
#include <sys/types.h>

#ifndef XAXIDMA_HW_H_    /* prevent circular inclusions */
#define XAXIDMA_HW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xil_types.h"
#include "xaxidma_hw.h"
//#include "xil_io.h"

/*****************************************************************************/
/**
*
* Read the given register.
*
* @param	BaseAddress is the base address of the device
* @param	RegOffset is the register offset to be read
*
* @return	The 32-bit value of the register
*
* @note
*		C-style signature:
*		u32 XAxiDma_ReadReg(u32 BaseAddress, u32 RegOffset)
*
******************************************************************************/
/*
#define XAxiDma_ReadReg(BaseAddress, RegOffset)             \
    XAxiDma_In32((BaseAddress) + (RegOffset))
*/
u_int32_t XAxiDma_ReadReg(UINTPTR vir_regaddr, u_int32_t offset)
{
	u_int32_t *ptr = (u_int32_t *) vir_regaddr;
	return *(ptr + (offset/4));
}


/*****************************************************************************/
/**
*
* Write the given register.
*
* @param	BaseAddress is the base address of the device
* @param	RegOffset is the register offset to be written
* @param	Data is the 32-bit value to write to the register
*
* @return	None.
*
* @note
*		C-style signature:
*		void XAxiDma_WriteReg(u32 BaseAddress, u32 RegOffset, u32 Data)
*
******************************************************************************/
/*#define XAxiDma_WriteReg(BaseAddress, RegOffset, Data)          \
    WriteReg32(BaseAddress, RegOffset, Data)
*/

//    XAxiDma_Out32((BaseAddress) + (RegOffset), (Data))
void XAxiDma_WriteReg(UINTPTR vir_regaddr, u_int32_t offset, u_int32_t data)
{
	u_int32_t *ptr = (u_int32_t *) vir_regaddr;

 	*(ptr + (offset/4)) = data;
}



#ifdef __cplusplus
}
#endif

#endif
/** @} */
