################################以下项目需用户根据需要更改##########################
CORE_ID := 0

COMPILE_DIR := D:/work/dsp/toolchains/toolchain_3slot_320f

TARGET      := software_lib_driver_core$(CORE_ID)

BUILD_DIR   := Build

DEVICE_DIR  := ../qx_c2000/device
TESTS_DIR   := ../qx_c2000/tests

LDSCRIPT    := qx320f_link_core$(CORE_ID).x
START_FILE  := $(DEVICE_DIR)/src/core$(CORE_ID)/asm_core$(CORE_ID).s

# clang前端解析阶段参数
CFLAGS := -MMD # 加入.d自动头文件依赖解析文件生成, 必备参数
CFLAGS += -gdwarf-2 -emit-llvm -S -O0 -mcpu=qx320f -DQX_C2000_CORE$(CORE_ID) -D__ELF__ -D__dsp__ -target dsp # 该部分参数从QX_IDE获取
# CFLAGS += -Wall
# CFLAGS += -Wno-unused-variable
# CFLAGS += -Wno-varargs
# CFLAGS += -disable-tail-calls

# 这里添加头文件查找路径参数
CFLAGS += -I$(COMPILE_DIR)/include -I$(DEVICE_DIR)/inc -I$(DEVICE_DIR)/inc/hw_inc -I$(TESTS_DIR)

# llc阶段参数
LLCFLAGS := -O0 -march=dsp -mcpu=qx320f -relocation-model=static -filetype=obj

# 链接阶段参数
# 这里添加链接阶段-L库文件查找路径参数
LDFLAGS := -L $(COMPILE_DIR)/Lib
LDFLAGS += -T $(LDSCRIPT) -M=$(BUILD_DIR)/linkMapFile

# 这里添加链接阶段需要链接的各种库(DSP必须将这些库参数放置在.o之后才能正常使用)
LDFLAGS2 := -lc -lm -lrt -ldspsim


# 如果项目源码都在当前目录下且源码文件都需要参见编译则可以自动搜索所有源文件并制作所有的文件依赖
# C_SOURCES = $(shell find ./ -type f -iname "*.c")

# 如果项目源码好不在目录下或者存在多余不需要编译的文件, 则可以手动定义源码列表
C_SOURCES := main.c
C_SOURCES += $(TESTS_DIR)/common.c
C_SOURCES += $(TESTS_DIR)/device.c
C_SOURCES += $(DEVICE_DIR)/src/qx_startup.c
C_SOURCES += $(DEVICE_DIR)/src/qx_interrupt.c
C_SOURCES += $(DEVICE_DIR)/src/qx_gpio.c
C_SOURCES += $(DEVICE_DIR)/src/qx_sysctl.c
C_SOURCES += $(DEVICE_DIR)/src/qx_ipc.c
C_SOURCES += $(DEVICE_DIR)/src/qx_cputimer.c
# C_SOURCES += $(TESTS_DIR)/syscall.c

# 自动从common.h文件中获取 TEST_XXX 定义
TEST_NAME := $(shell awk '/TEST_/ {print $$2}' ../qx_c2000/tests/common.h)

ifeq ($(TEST_NAME), TEST_SCI)
C_SOURCES += $(DEVICE_DIR)/src/qx_sci.c
C_SOURCES += $(TESTS_DIR)/test_sci.c
endif

ifeq ($(TEST_NAME), TEST_FLASH)
C_SOURCES += $(DEVICE_DIR)/src/qx_flash.c
C_SOURCES += $(TESTS_DIR)/test_flash.c
endif

ifeq ($(TEST_NAME), TEST_DCC)
C_SOURCES += $(DEVICE_DIR)/src/qx_dcc.c
C_SOURCES += $(TESTS_DIR)/test_dcc.c
endif

ifeq ($(TEST_NAME), TEST_DMA)
C_SOURCES += $(DEVICE_DIR)/src/qx_dma.c
C_SOURCES += $(TESTS_DIR)/test_dma.c
C_SOURCES += $(TESTS_DIR)/test_spi.c
endif

ifeq ($(TEST_NAME), TEST_SPI)
C_SOURCES += $(DEVICE_DIR)/src/qx_spi.c
C_SOURCES += $(TESTS_DIR)/test_spi.c
endif

ifeq ($(TEST_NAME), TEST_CAN)
C_SOURCES += $(DEVICE_DIR)/src/qx_can.c
C_SOURCES += $(TESTS_DIR)/test_can.c
endif

ifeq ($(TEST_NAME), TEST_ECAP)
C_SOURCES += $(DEVICE_DIR)/src/qx_ecap.c
C_SOURCES += $(DEVICE_DIR)/src/qx_xbar.c
C_SOURCES += $(TESTS_DIR)/test_ecap.c
endif

ifeq ($(TEST_NAME), TEST_EPWM)
C_SOURCES += $(DEVICE_DIR)/src/qx_epwm.c
C_SOURCES += $(TESTS_DIR)/test_epwm.c
endif

ifeq ($(TEST_NAME), TEST_EQEP)
C_SOURCES += $(DEVICE_DIR)/src/qx_eqep.c
C_SOURCES += $(TESTS_DIR)/test_eqep.c
endif

ifeq ($(TEST_NAME), TEST_SDFM)
C_SOURCES += $(DEVICE_DIR)/src/qx_sdfm.c
C_SOURCES += $(TESTS_DIR)/test_sdfm.c
endif

ifeq ($(TEST_NAME), TEST_ADC)
C_SOURCES += $(DEVICE_DIR)/src/qx_adc.c
C_SOURCES += $(TESTS_DIR)/test_adc.c
C_SOURCES += $(TESTS_DIR)/test_cputimer.c
endif

ifeq ($(TEST_NAME), TEST_DAC)
C_SOURCES += $(DEVICE_DIR)/src/qx_dac.c
C_SOURCES += $(TESTS_DIR)/test_dac.c
C_SOURCES += $(TESTS_DIR)/test_adc.c
endif

ifeq ($(TEST_NAME), TEST_FSI)
C_SOURCES += $(DEVICE_DIR)/src/qx_fsi.c
C_SOURCES += $(TESTS_DIR)/test_fsi.c
endif

ifeq ($(TEST_NAME), TEST_XBAR)
C_SOURCES += $(DEVICE_DIR)/src/qx_xbar.c
C_SOURCES += $(TESTS_DIR)/test_xbar.c
C_SOURCES += $(TESTS_DIR)/test_epwm.c
C_SOURCES += $(TESTS_DIR)/test_ecap.c
endif

ifeq ($(TEST_NAME), TEST_CMPSS)
C_SOURCES += $(DEVICE_DIR)/src/qx_cmpss.c
endif

ifeq ($(TEST_NAME), TEST_GLOBAL)
C_SOURCES += $(TESTS_DIR)/test_global.c
endif

ifeq ($(TEST_NAME), TEST_MEM)
C_SOURCES += $(TESTS_DIR)/test_mem.c
endif

ifeq ($(TEST_NAME), TEST_GPIO)
C_SOURCES += $(TESTS_DIR)/test_gpio.c
endif

ifeq ($(TEST_NAME), TEST_SYSCTL)
C_SOURCES += $(TESTS_DIR)/test_sysctl.c
endif

ifeq ($(TEST_NAME), TEST_TIMER)
C_SOURCES += $(TESTS_DIR)/test_timer.c
endif

ifeq ($(TEST_NAME), TEST_WDG)
C_SOURCES += $(TESTS_DIR)/test_wdg.c
endif

ifeq ($(TEST_NAME), TEST_I2C)
C_SOURCES += $(TESTS_DIR)/test_i2c.c
endif

ifeq ($(TEST_NAME), TEST_PLL)
C_SOURCES += $(TESTS_DIR)/test_pll.c
endif

ifeq ($(TEST_NAME), TEST_ISR)
C_SOURCES += $(TESTS_DIR)/test_isr.c
endif

ifeq ($(TEST_NAME), TEST_ASYS)
C_SOURCES += $(TESTS_DIR)/test_asys.c
endif

###################################用户修改结束###################################
CC      = $(COMPILE_DIR)/bin/clang
LLC     = $(COMPILE_DIR)/bin/llc
AS      = $(COMPILE_DIR)/bin/as
LD      = $(COMPILE_DIR)/bin/ld
GDB     = $(COMPILE_DIR)/bin/gdb
OBJCOPY = $(COMPILE_DIR)/bin/objcopy
OBJDUMP = $(COMPILE_DIR)/bin/objdump

START_FILE_OBJ = $(addsuffix .o, $(basename $(notdir $(START_FILE))))
OBJECTS        = $(addprefix $(BUILD_DIR)/, $(START_FILE_OBJ))
OBJECTS       += $(addprefix $(BUILD_DIR)/, $(notdir $(C_SOURCES:%.c=%.o)))
# $(info "$(OBJECTS)")

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.s $(dir $(START_FILE))

.PHONY:all clean

all: $(BUILD_DIR)/$(TARGET).out

$(BUILD_DIR)/$(TARGET).out: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDFLAGS2)
	cd $(BUILD_DIR) && python $(COMPILE_DIR)/bin/gen_data_instr.py --toolsPath $(COMPILE_DIR)/bin --file $(TARGET).out --coreType core$(CORE_ID)
	cd ../ && python gen_package.py 1
	cd $(BUILD_DIR) && ftp -s:../ftp_auto.txt

$(BUILD_DIR)/$(START_FILE_OBJ): $(START_FILE)
	$(AS) -g $< -o $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@.ll
	$(LLC) $(LLCFLAGS) $@.ll -o $@

clean:
	$(RM) -rf $(BUILD_DIR)/*

include $(wildcard $(BUILD_DIR)/*.d)
