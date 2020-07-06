1) Folder Structure -- Done

2) Compile options  -- make inner make has to do.

Note: To compile the kernel we need to set up the crosscompiler
    eg: make -C kernel/linux-xlnx/ ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j10


3) Boot mode
  a) SD
  b) QSPI 
  c) JTAG

Sample example LIke ::PL -dma , PS - iic

4) Git hub submission


Dt:   7-07

5) Document the procedure to change the following 
   a) Bitfile 
   b) Dts 
      i) adding IRQ's 
      ii) new controler 
   c) Kernel -- 
      i) Display enable or disable
   d) U-boot (optional)
   e) Api
   f) App


   
   
6)Examples
  a) Video bist example
  b) Video  Pass through
  
  
