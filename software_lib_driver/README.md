本仓库使用两个工程
core0的工程software_lib_driver_core0
core1的工程software_lib_driver_core1

注意事项
1.驱动文件放在目录qx_c2000/device/
2.测试文件放在目录qx_c2000/test/
3.每个工程有独立的启动文件asm_core.s
4.每个工程有独立的中断描述文件qx_isr.c,qx_isr.h

中断描述：