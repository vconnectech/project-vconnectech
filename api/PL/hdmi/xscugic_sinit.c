/******************************************************************************
*
* Copyright (C) 2010 - 2015 Xilinx, Inc.  All rights reserved.
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
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
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
*
* @file xscugic_sinit.c
* @addtogroup scugic_v3_8
* @{
*
* Contains static init functions for the XScuGic driver for the Interrupt
* Controller. See xscugic.h for a detailed description of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- --------------------------------------------------------
* 1.00a drg  01/19/10 First release
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_assert.h"
#include "xparameters.h"
#include "xscugic.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/
#define XPAR_SCUGIC_NUM_INSTANCES   1U
extern XScuGic_Config XScuGic_ConfigTable[XPAR_SCUGIC_NUM_INSTANCES];
extern XScuGic_Config *XScuGic_LookupConfig(u16 DeviceId);

/************************** Function Prototypes ******************************/

/*
int XIicPs_MasterSendPolled_ours(XIicPs *InstancePtr, u8 *MsgPtr,
		 int ByteCount, u16 SlaveAddr)
{
	u32 IntrStatusReg;
	u32 StatusReg;
	u32 BaseAddr;
	u32 Intrs;

*/	/*
	 * Assert validates the input arguments.
	 */
/*	Xil_AssertNonvoid(InstancePtr != NULL);
	Xil_AssertNonvoid(MsgPtr != NULL);
	Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
	Xil_AssertNonvoid(XIICPS_ADDR_MASK >= SlaveAddr);

	BaseAddr = InstancePtr->Config.BaseAddress;
	InstancePtr->SendBufferPtr = MsgPtr;
	InstancePtr->SendByteCount = ByteCount;

	XIicPs_SetupMaster(InstancePtr, SENDING_ROLE);

	XIicPs_WriteReg(BaseAddr, XIICPS_ADDR_OFFSET, SlaveAddr);

	Intrs = XIICPS_IXR_ARB_LOST_MASK | XIICPS_IXR_TX_OVR_MASK |
			XIICPS_IXR_TO_MASK | XIICPS_IXR_NACK_MASK;

	IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
	XIicPs_WriteReg(BaseAddr, XIICPS_ISR_OFFSET, IntrStatusReg);

	TransmitFifoFill(InstancePtr);

	IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);

	while ((InstancePtr->SendByteCount > 0) &&
		((IntrStatusReg & Intrs) == 0)) {
		StatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_SR_OFFSET);

		if ((StatusReg & XIICPS_SR_TXDV_MASK) != 0) {
			IntrStatusReg = XIicPs_ReadReg(BaseAddr,
					XIICPS_ISR_OFFSET);
			continue;
		}

		TransmitFifoFill(InstancePtr);
	}

	// NOTE for MicroCART: Corrected function. Original left for reference.
//	while ((XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET) &
//		XIICPS_IXR_COMP_MASK) != XIICPS_IXR_COMP_MASK);
	while (!(IntrStatusReg & (Intrs | XIICPS_IXR_COMP_MASK))) {
		IntrStatusReg = XIicPs_ReadReg(BaseAddr, XIICPS_ISR_OFFSET);
	}

	if (IntrStatusReg & Intrs) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

*/







/*****************************************************************************/
/**
*
* Looks up the device configuration based on the unique device ID. A table
* contains the configuration info for each device in the system.
*
* @param	DeviceId is the unique identifier for a device.
*
* @return	A pointer to the XScuGic configuration structure for the
*		specified device, or NULL if the device was not found.
*
* @note		None.
*
******************************************************************************/
XScuGic_Config *XScuGic_LookupConfig(u16 DeviceId)
{
	XScuGic_Config *CfgPtr = NULL;
	u32 Index;

	for (Index=0U; Index < (u32)XPAR_SCUGIC_NUM_INSTANCES; Index++) {
		if (XScuGic_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XScuGic_ConfigTable[Index];
			break;
		}
	}

	return (XScuGic_Config *)CfgPtr;
}
/** @} */
