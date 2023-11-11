#!/bin/sh

qemu-system-riscv64 -M virt \
                    -kernel ../linux-5.19.16/arch/riscv/boot/Image \
                    -initrd ../rootfs.img \
                    -nographic \
                    -s -S
