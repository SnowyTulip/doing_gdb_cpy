@echo off

python %1\gen_data_instr.py --toolsPath %1 --file %2 --coreType core1

cd ..\..\ && python gen_package.py && cd software_lib_driver_core1/Release

ftp -s:..\ftp_auto.txt
