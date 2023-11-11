#
# Makefile for Menu Program
#

CC_PTHREAD_FLAGS			 = -lpthread
CC_FLAGS                     = -c
CC_OUTPUT_FLAGS				 = -o
CC                           = riscv64-linux-gcc
RM                           = rm
RM_FLAGS                     = -f

TARGET  =   test
OBJS    =   linktable.o  menu.o test.o

all:	$(OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(TARGET) $(OBJS)
rootfs:
	riscv64-linux-gcc -o init linktable.c menu.c test.c  -static -lpthread
	riscv64-linux-gcc -o hello hello.c -static
	find init hello | cpio -o -Hnewc |gzip -9 > ../rootfs.img
	qemu-system-riscv64 -M virt \
			    -kernel ../linux-5.19.16/arch/riscv/boot/Image \
		            -initrd ../rootfs.img \
                            -nographic
.c.o:
	$(CC) $(CC_FLAGS) $<

clean:
	$(RM) $(RM_FLAGS)  $(OBJS) $(TARGET) *.bak
