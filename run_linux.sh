#!/bin/bash
echo ' Welcome'
read -p  "command to run : " name

if [ "$name"  =  "linux" ]; then
	echo " Your running the  Linux "
	cd ../Kernel/linux-xlnx/
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j10

elif [ "$name" = "uboot" ]; then
	echo " Your running the  uboot "
	cd ../Kernel/u-boot-xlnx/
	export CROSS_COMPILE=aarch64-linux-gnu-
	export ARCH=aarch64
	make -j10


elif [ "$name" = "genbins" ]; then
	echo " Your running the  uboot "
	cd ../Bitfiles/UIO/
	./genbins

else 
	echo "choose properly"

fi 
