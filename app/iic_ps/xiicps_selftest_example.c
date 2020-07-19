/******************************************************************************
*
* Copyright (C) 2010 - 2014 Xilinx, Inc.  All rights reserved.
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
 * @file xiicps_selftest_example.c
 *
 * This file contains a example for using the IIC hardware device and
 * XIicPs driver.
 *
 *
 * <pre> MODIFICATION HISTORY:
 *
 * Ver	 Who Date    	Changes
 * ----- --- -------- 	-----------------------------------------------
 * 1.00a sdm 05/30/11 	First release
 *
 * </pre>
 *
 ****************************************************************************/

/***************************** Include Files **********************************/
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include "xparameters.h"
#include "xiicps.h"
#include "xstatus.h"
#include <sys/time.h>
#define xil_printf printf

/************************** Constant Definitions ******************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define IIC_DEVICE_ID		XPAR_XIICPS_0_DEVICE_ID


/**************************** Type Definitions ********************************/

/************************** Function Prototypes *******************************/

int IicPsSelfTestExample(u16 DeviceId);

/************************** Variable Definitions ******************************/

XIicPs Iic;			/* Instance of the IIC Device */

/******************************************************************************/
/**
*
* Main function to call the Self Test example.
*
* @param	None.
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful.
*
* @note		None.
*
*******************************************************************************/
#ifndef TESTAPP_GEN
int main(void)
{
	int Status;

	printf("IIC Self Test Example \r\n");

	/*
	 * Run the Iic Self Test example, specify the Device ID that is
	 * generated in xparameters.h
	 */
	Status = IicPsSelfTestExample(IIC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		printf("IIC Self Test Failed\r\n");
		return XST_FAILURE;
	}

	printf("Successfully ran IIC Self Test Example Test\r\n");
	return XST_SUCCESS;
}
#endif

/*****************************************************************************/
/**
*
* This function does a minimal test on the Iic device and driver as a
* design example. The purpose of this function is to illustrate
* how to use the XIicPs component.
*
*
* @param	DeviceId is the Device ID of the IicPs Device and is the
*		XPAR_<IICPS_instance>_DEVICE_ID value from xparameters.h
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note		None.
*
*
*******************************************************************************/
int IicPsSelfTestExample(u16 DeviceId)
{
	int Status,*uioFd;
	XIicPs_Config *Config;

	/*
	 * Initialize the IIC driver so that it's ready to use
	 * Look up the configuration in the config table, then initialize it.
	 */

	Config = XIicPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	printf("Vij %s %d \n",__func__,__LINE__);

	*uioFd = open("/dev/uio4", O_RDWR | O_SYNC); 

	printf("%s %d \n",__func__,__LINE__);

	if (*uioFd < 0) {
		      xil_printf("UIO driver open ERROR\n" );
      		      return 0;
    	 }
	
	printf("%s %d \n",__func__,__LINE__);

        Config->BaseAddress = (UINTPTR)mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, *uioFd, 0);
	
	printf("%s %d \n",__func__,__LINE__);

	if(Config->BaseAddress < 0)
	{
		xil_printf("Error in mapping HW\n");
		return 0;
	}

	printf("%s %d \n",__func__,__LINE__);

	Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test.
	 */
	Status = XIicPs_SelfTest(&Iic);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}
