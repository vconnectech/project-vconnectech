#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define MM2S_DMACR 0x0
#define MM2S_DMASR 0x4
#define MM2S_SA 0x18
#define MM2S_SA_MSB 0x1C
#define MM2S_LENGTH 0x28
#define S2MM_DMACR 0x30
#define S2MM_DMASR 0x34
#define S2MM_DA 0x48
#define S2MM_DA_MSB 0x4C
#define S2MM_LENGTH 0x58
#define ADDR 0x00000000a0010000
void setting_of_s2mm(void * baseaddress,char *);
void setting_of_mm2s(void * baseaddress,char *);
int main() 
{
	int uioFd0,uioFd1,uioFd2,uioFd3;
	unsigned int uioSize;
	FILE *sizeFd0,*sizeFd1,*sizeFd2,*sizeFd3;
	void * baseAddress[4];
	static const int moveSize = 10;
	char *outBuff;
	char *inBuff;
	int irq = 0;
	int irqClr = 1;
	int mm2sStat;
	int s2mmStat;
	int i;

	// Access AXIDMA space

	printf("===========\n");

	uioFd0 = open("/dev/uio7", O_RDWR | O_SYNC);

	if (uioFd0 < 0) 
	{
		printf("UIO driver open ERROR\n" );
		perror("uio open:");
		return errno;
	}


	uioSize = 0x1000;
	void *base1 = mmap(NULL, uioSize, PROT_READ|PROT_WRITE, MAP_SHARED, uioFd0, 0);
	printf("=========== %u\n", __LINE__);
	printf("baseAddress[i]: %x\n",*(u_int32_t *)base1);

	*base1  = *base1+1;
	printf("baseAddress changed : %x\n",*(u_int32_t *)base1);
	printf("=========== %u\n", __LINE__);
	//return ;
}  
// Prepare data
/*
   outBuff = malloc(moveSize * sizeof(char));
   for (i = 0; i < moveSize; i++)
   {
   outBuff[i] = i;
   }

   inBuff = malloc(moveSize * sizeof(char));

   for(int i=0;i<4;i++) {
   setting_of_s2mm(baseaddress[i],inBuff);
   setting_of_mm2s(baseaddress[i],outBuff);
   return;
   }

   }

   void setting_of_s2mm(void * baseaddress,char *inBuff){


// Configure AXIDMA - S2MM
////     First base address 
 *((volatile unsigned long *) (baseAddress + S2MM_DMACR)) = 0x4;
 s2mmStat = *((volatile unsigned long *) (baseAddress + S2MM_DMASR));
 printf("S2MM: %d\n", s2mmStat);

 *((volatile unsigned long *) (baseAddress + S2MM_DMACR)) = 0x1000;
 s2mmStat = *((volatile unsigned long *) (baseAddress + S2MM_DMASR));
 printf("S2MM: %d\n", s2mmStat);

 *((volatile unsigned long *) (baseAddress + S2MM_DA)) = inBuff;
 *((volatile unsigned long *) (baseAddress + S2MM_DA_MSB)) = 0;
 *((volatile unsigned long *) (baseAddress + S2MM_LENGTH)) = moveSize;
 *((volatile unsigned long *) (baseAddress + S2MM_DMACR)) = 0x1001;

 s2mmStat = *((volatile unsigned long *) (baseAddress + S2MM_DMASR));
 printf("S2MM: %d\n", s2mmStat);
 return;
 }*/
// Configure AXIDMA - MM2S
/*
   void setting_of_mm2s(void * baseaddress,char *outBuff){


 *((volatile unsigned long *) (baseAddress + MM2S_DMACR)) = 0x4;  
 mm2sStat = *((volatile unsigned long *) (baseAddress + MM2S_DMASR));
 printf("MM2S: %d\n", mm2sStat);
 *((volatile unsigned long *) (baseAddress + MM2S_DMACR)) = 0x1000;  
 mm2sStat = *((volatile unsigned long *) (baseAddress + MM2S_DMASR));
 printf("MM2S: %d\n", mm2sStat);

 *((volatile unsigned long *) (baseAddress + MM2S_SA)) = outBuff;
 *((volatile unsigned long *) (baseAddress + MM2S_SA_MSB)) = 0;
 *((volatile unsigned long *) (baseAddress + MM2S_LENGTH)) = moveSize;
 *((volatile unsigned long *) (baseAddress + MM2S_DMACR)) = 0x1001;  

 mm2sStat = *((volatile unsigned long *) (baseAddress + MM2S_DMASR));
 printf("MM2S: %d\n", mm2sStat);
 return;
 }
// Wait for interrupt

read(uioFd, (void *)&irq, sizeof(int));

write(uioFd, (void *)&irqClr, sizeof(int));

// Check received data

s2mmStat = *((volatile unsigned long *) (baseAddress + S2MM_DMASR));
printf("S2MM: %d\n", s2mmStat);
mm2sStat = *((volatile unsigned long *) (baseAddress + MM2S_DMASR));
printf("MM2S: %d\n", mm2sStat);

for (i = 0; i < moveSize; i++)
{
printf("expected: %d, received: %d\n", outBuff[i], inBuff[i]);
}

// Close

munmap(baseAddress, uioSize);

return errno;
}*/
