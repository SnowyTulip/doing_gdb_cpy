import binascii
import sys
import  subprocess as sp
import os
from pathlib import Path
import argparse
#gen_data_instr.py is used to generate dat file for c2000's hardware vcs(Hardware emulation software).
#It use objcopy.exe and objdump.exe to generate bin and disassembly file.

class tools:
    def addTextSection(self, srcLines, dstLines):
        TexLinesNum = 0
        temp2 = ''
        for line in srcLines:
            TexLinesNum = TexLinesNum + 8
            temp2 = line[0:8] + line[8:16] + '\n'
            dstLines.append(temp2)
        return TexLinesNum

    def getInfo(self, x1, x2):
        x = hex(x1)[2:]
        x3 = x.zfill(8)
        x = hex(x2)[2:]
        x4 = x.zfill(8)
        y = x3 + x4 + '\n'
        return y

    def addDataSection(self, srcList, dstList):
        dataLinesNum = 0
        for line in srcList:
            dataLinesNum = dataLinesNum + 8
            dstList.append(line)
        return dataLinesNum

    def addBootloader(self, srcList, dstList):
        lineNum = 0
        for line in srcList:
            lineNum = lineNum + 1
            dstList.append(line)
            #package.writelines(line)

        padLinesNum = 1024 - lineNum
        for i in range(0, padLinesNum):
            dstList.append('beefbeefbeefbeef\n')

    def addInfoPad(self,  dstList):
        for i in range(0, 128):
            dstList.append('deaddeaddeaddead\n')

    def fixInfo(self, dstList, info1, info2, pos):
        coreInfo = self.getInfo(info1, info2)
        dstList[pos] = coreInfo

    def addCode(self, dataList, txtList, dstList, which, pos):
        textLinesNum = self.addTextSection(txtList, dstList)
        infoStr = which + 'TxtFile:' + str(textLinesNum)
        print(infoStr)

        dataLinesNum = self.addDataSection(dataList, dstList)
        infoStr = which + 'DataFile:' + str(dataLinesNum)
        print(infoStr)
        #becauseof createAbigFile arrange 1122334455667788 to 4433221188776655
        self.fixInfo(dstList, dataLinesNum, textLinesNum, pos)

    def create(self):
        if len(sys.argv) == 1:
            bootfile = open('software_lib_bootloader\\Release\\outer_insn_mem.dat', 'r')
            core0DataFile = open('software_lib_driver_core0\\Release\\outer_data_mem_core0.dat', 'r')
            core0TextFile = open('software_lib_driver_core0\\Release\\outer_insn_mem_core0.dat', 'r')
            core1DataFile = open('software_lib_driver_core1\\Release\\outer_data_mem_core1.dat', 'a+')
            core1TextFile = open('software_lib_driver_core1\\Release\\outer_insn_mem_core1.dat', 'a+')
            core1DataFile.seek(0);
            core1TextFile.seek(0);
        else:
            bootfile = open('software_lib_bootloader\\Release\\outer_insn_mem.dat', 'r')
            core0DataFile = open('software_lib_driver_core0\\Build\\outer_data_mem_core0.dat', 'r')
            core0TextFile = open('software_lib_driver_core0\\Build\\outer_insn_mem_core0.dat', 'r')
            core1DataFile = open('software_lib_driver_core1\\Build\\outer_data_mem_core1.dat', 'a+')
            core1TextFile = open('software_lib_driver_core1\\Build\\outer_insn_mem_core1.dat', 'a+')
            core1DataFile.seek(0);
            core1TextFile.seek(0);

        package = open('package.dat', 'w')
        packageList = []
        bootLines = bootfile.readlines()
        core0DataFileLines = core0DataFile.readlines()
        core0TextFileLines = core0TextFile.readlines()
        core1DataFileLines = core1DataFile.readlines()
        core1TextFileLines = core1TextFile.readlines()

        self.addBootloader(bootLines, packageList)
        self.addInfoPad(packageList)
        self.addCode(core0DataFileLines, core0TextFileLines, packageList, 'core0', 1024)
        self.addCode(core1DataFileLines, core1TextFileLines, packageList, 'core1', 1025)

        for line in packageList:
            package.writelines(line)

        bootfile.close()
        core0DataFile.close()
        core0TextFile.close()
        core1DataFile.close()
        core1TextFile.close()
        package.close()

    def createAbigFile(self):
        package = open('package.dat', 'r')
        flashTest = open('init_mem.txt', 'w')
        packageLines = package.readlines()
        for line in packageLines:
            line1 = line[:-1]
            #line2 = line1[-2:] +  '\n' + line1[-4:-2] + '\n' + line1[-6:-4] +  '\n' + line1[-8:-6] + '\n' + line1[-10:-8] + '\n' + line1[-12:-10] + '\n' + line1[-14:-12] + '\n' + line1[-16:-14] + '\n'
            line2 = line1[-8:-6] + '\n' + line1[-6:-4] + '\n' + line1[-4:-2] + '\n' + line1[-2:] +  '\n' + line1[-16:-14] + '\n' + line1[-14:-12] + '\n' + line1[-12:-10] + '\n' + line1[-10:-8] + '\n'
            flashTest.writelines(line2)
        flashTest.close()


    def createFlash(self):
        myTest = open('init_mem.txt', 'w')
        for i in range(0, 0x2000):
            x = hex(i)[2:]
            y = x.zfill(8)
            z = y[-2:] +  '\n' + y[-4:-2] + '\n' + y[-6:-4] +  '\n' + y[-8:-6] + '\n'
            myTest.writelines(z)
        myTest.close()


if __name__=="__main__":
    mytool = tools()
    mytool.create()
    mytool.createAbigFile()
    #mytool.createFlash()

