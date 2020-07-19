#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include "xaxidma.h"
#include "xstatus.h"
#include "xparameters.h"
#include "xdebug.h"
/******************** Constant Definitions **********************************/

/*
 * Device hardware build related constants.
 */

#define DMA_DEV_ID 	XPAR_AXIDMA_0_DEVICE_ID

#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR		XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif defined (XPAR_MIG7SERIES_0_BASEADDR)
#define DDR_BASE_ADDR	        XPAR_MIG7SERIES_0_BASEADDR
#elif defined (XPAR_MIG_0_BASEADDR)
#define DDR_BASE_ADDR	        XPAR_MIG_0_BASEADDR
#elif defined (XPAR_PSU_DDR_0_S_AXI_BASEADDR)
#define DDR_BASE_ADDR    	XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

#define MEM_BASE_ADDR		0x10000000

#define TX_BUFFER0_BASE		(MEM_BASE_ADDR + 0x01000000)
#define RX_BUFFER0_BASE		(MEM_BASE_ADDR + 0x02000000)
#define TX_BUFFER1_BASE		(MEM_BASE_ADDR + 0x03000000)
#define RX_BUFFER1_BASE		(MEM_BASE_ADDR + 0x04000000)
#define TX_BUFFER2_BASE		(MEM_BASE_ADDR + 0x05000000)
#define RX_BUFFER2_BASE		(MEM_BASE_ADDR + 0x06000000)
#define TX_BUFFER3_BASE		(MEM_BASE_ADDR + 0x07000000)
#define RX_BUFFER3_BASE		(MEM_BASE_ADDR + 0x08000000)

#define DEVID_0 0
#define DEVID_1 1
#define DEVID_2 2
#define DEVID_3 3


#define SIZE_500K       500*1024
#define SIZE_50K        50*1024

#define TEST_START_VALUE	0xC

#define NUMBER_OF_TRANSFERS	10

#define xil_printf printf
/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

static int CheckData(void);

/************************** Variable Definitions *****************************/
/*
 * Device instance definitions
 */
XAxiDma AxiDma0;
XAxiDma AxiDma1;
XAxiDma AxiDma2;
XAxiDma AxiDma3;

u32 InitCfgxPtr(int DeviceId, int *uioFd, XAxiDma_Config *CfgPtr, XAxiDma *AxiDma)
{
	int Status;
	/* Initialize the XAxiDma device 0.
	 */
	CfgPtr = XAxiDma_LookupConfig(DeviceId);
	if (!CfgPtr) {
		xil_printf("No config found for %d\r\n", DeviceId);
		return XST_FAILURE;
	}

    switch(DeviceId)
	{
		case 0: *uioFd = open("/dev/uio4", O_RDWR | O_SYNC); break;

		case 1: *uioFd = open("/dev/uio5", O_RDWR | O_SYNC); break;

		case 2: *uioFd = open("/dev/uio6", O_RDWR | O_SYNC); break;

		case 3: *uioFd = open("/dev/uio7", O_RDWR | O_SYNC); break;
	}

    if (uioFd < 0) 
    {
	      xil_printf("UIO driver open ERROR\n" );
      	      return 0;
    }
	
        CfgPtr->BaseAddr = (UINTPTR)mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, *uioFd, 0);

	if(CfgPtr->BaseAddr < 0)
	{
		xil_printf("Error in mapping HW\n");
		return 0;
	}

 	Status = XAxiDma_CfgInitialize(AxiDma, CfgPtr);

	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}

	/* Disable interrupts, we use polling mode
	 */
	XAxiDma_IntrDisable(AxiDma, XAXIDMA_IRQ_ALL_MASK,
						XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(AxiDma, XAXIDMA_IRQ_ALL_MASK,
						XAXIDMA_DMA_TO_DEVICE);


    xil_printf("Mapping HW Successfully %x\n", CfgPtr->BaseAddr );
}

u32 Setup_Transfer(XAxiDma *AxiDma, u8* RxBufferPtr, u8 *TxBufferPtr, int Length)
{
	int Status = XAxiDma_SimpleTransfer(AxiDma,(UINTPTR) RxBufferPtr,
				Length, XAXIDMA_DEVICE_TO_DMA);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XAxiDma_SimpleTransfer(AxiDma,(UINTPTR) TxBufferPtr,
				Length, XAXIDMA_DMA_TO_DEVICE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
}

void WaitForTransfer(XAxiDma *AxiDma)
{
	while ((XAxiDma_Busy(AxiDma,XAXIDMA_DEVICE_TO_DMA)) ||
			(XAxiDma_Busy(AxiDma,XAXIDMA_DMA_TO_DEVICE))) {
				/* Wait */
		}
}

/*****************************************************************************/
/**
* The example to do the simple transfer through polling. The constant
* NUMBER_OF_TRANSFERS defines how many times a simple transfer is repeated.
*
* @param	DeviceId is the Device Id of the XAxiDma instance
*
* @return
*		- XST_SUCCESS if example finishes successfully
*		- XST_FAILURE if error occurs
*
* @note		None
*
*
******************************************************************************/

int main (void)
{
	XAxiDma_Config *CfgPtr0, *CfgPtr1, *CfgPtr2, *CfgPtr3;
	int Status;
	int Tries = NUMBER_OF_TRANSFERS;
	int Index;
	u8 *TxBufferPtr0, *TxBufferPtr1, *TxBufferPtr2, *TxBufferPtr3;
	u8 *RxBufferPtr0, *RxBufferPtr1, *RxBufferPtr2, *RxBufferPtr3;
	u8 Value;
        int uioFd0, uioFd1, uioFd2, uioFd3;
	int DeviceId;
        struct timeval tv;
	int Start_TS[100],End_TS[100], CurrTS, PrevTS = 0;

    xil_printf("UIO driver opened Successfully\n" );
	TxBufferPtr0 = (u8 *)TX_BUFFER0_BASE;
	RxBufferPtr0 = (u8 *)RX_BUFFER0_BASE;
	TxBufferPtr1 = (u8 *)TX_BUFFER1_BASE;
	RxBufferPtr1 = (u8 *)RX_BUFFER1_BASE;
	TxBufferPtr2 = (u8 *)TX_BUFFER2_BASE;
	RxBufferPtr2 = (u8 *)RX_BUFFER2_BASE;
	TxBufferPtr3 = (u8 *)TX_BUFFER3_BASE;
	RxBufferPtr3 = (u8 *)RX_BUFFER3_BASE;

	/* Initialize the XAxiDma device 0.
	 */

    InitCfgxPtr(DEVID_0, &uioFd0, CfgPtr0, &AxiDma0);
    InitCfgxPtr(DEVID_1, &uioFd1, CfgPtr1, &AxiDma1);
    InitCfgxPtr(DEVID_2, &uioFd2, CfgPtr2, &AxiDma2);
    InitCfgxPtr(DEVID_3, &uioFd3, CfgPtr3, &AxiDma3);

	xil_printf("Starting DMA transfers\n");

        gettimeofday(&tv,NULL);
	PrevTS = tv.tv_usec;
	
	for(Index = 0; Index < Tries; Index ++) {

		do {
			gettimeofday(&tv,NULL);
		}while((tv.tv_usec - PrevTS) <= 500);
		Start_TS[Index] = PrevTS = tv.tv_usec;

		Status = Setup_Transfer(&AxiDma0, RxBufferPtr0, TxBufferPtr0, SIZE_500K);
		//Status = Setup_Transfer(&AxiDma1, RxBufferPtr1, TxBufferPtr1, SIZE_50K);
		//Status = Setup_Transfer(&AxiDma2, RxBufferPtr2, TxBufferPtr2, SIZE_50K);
		//Status = Setup_Transfer(&AxiDma3, RxBufferPtr3, TxBufferPtr3, SIZE_50K);

	    WaitForTransfer(&AxiDma0);
	    //WaitForTransfer(&AxiDma1);
	    //WaitForTransfer(&AxiDma2);
	    //WaitForTransfer(&AxiDma3);

        gettimeofday(&tv,NULL);
		End_TS[Index] = tv.tv_usec;
	}
	xil_printf("Completed %d DMA Transfer\n", Index);
	for(Index = 0; Index < Tries; Index ++) {
        xil_printf("Transfer : %u, proc_time: %u\n", Index+1, End_TS[Index] - Start_TS[Index]); // microseconds
	}

	/* Test finishes successfully
	 */
	return XST_SUCCESS;
}


