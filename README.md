# README
## 前言
[MenuOS](https://github.com/mengning/menu/) 是《庖丁解牛Linux操作系统分析》的作者提供的一个实验平台。本项目通过修改汇编代码和Makefile使得 MenuOS 能够在RISC-V架构上进行运行。
## 依赖条件
- RISC-V 工具链
- qemu-7.1.0
- linux-5.19.16
- gdb-multiarch

安装方式可通过查阅 [《RISC-V Linux 内核分析实验手册》](https://github.com/Elonisme/RiSCV-Linux) 获得或者自己查阅相关资料。

## 使用方法
1. ./init-gdb.sh
   启动 qemu 模拟 RISC-V 的裸机并加载编译好的内核，同时开启 gdbserver
2. ./start-gdb.sh
   启动 gdb 准备开始调试
