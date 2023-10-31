set auto-load safe-path /
cd D:\doing_gdb_cpy\software_lib_driver\software_lib_driver_core0\Release
set target-async on 
target remote:3333
load software_lib_driver_core0.out
file software_lib_driver_core0.out
