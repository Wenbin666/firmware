#
#  定义ARM 编译工具


# 定义编译工具前缀
GCC_ARM_PATH ?= $(PROJECT_ROOT)/tools/toolchain-gccarmnoneeabi/bin/
GCC_PREFIX ?= arm-none-eabi-

include $(COMMON_BUILD)/common-tools.mk

#
# 默认参数
#
ifeq ("$(MODULE)","bootloader")
CDEFINES += -DBOOTLOADER_BUILD=1
endif

# C 编译参数
CFLAGS += -mcpu=$(MCU_CORE)
ifeq ("$(MCU_CORE)","cortex-m4")
CFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16
endif

# 如果程序没有按预期工作   尝试去掉-fdata-sections
CFLAGS += -g3 -gdwarf-2 -Os -mthumb -fno-strict-aliasing -w -Wall -Wfatal-errors -fno-common -ffunction-sections -fdata-sections -Wno-switch -Wno-error=deprecated-declarations -fmessage-length=0 -Wno-sign-compare

CONLYFLAGS += -Wno-pointer-sign -std=gnu99

# C++ 编译参数  -fpermissive 把代码的语法错误作为警告,并继续编译进程
CPPFLAGS += -fno-exceptions -fno-rtti -fcheck-new -std=gnu++11 -fpermissive

ASFLAGS += -mcpu=$(MCU_CORE) -g3 -gdwarf-2 -Os -mthumb -x assembler-with-cpp -fmessage-length=0

LDFLAGS += -mcpu=$(MCU_CORE) -Os -mthumb -nostartfiles -mlittle-endian -Xlinker --gc-sections


ifeq ($(COMPILE_LTO),y)
CFLAGS += -flto -fno-fat-lto-objects
CPPFLAGS += -flto -fno-devirtualize
LDFLAGS += -flto -fuse-linker-plugin
endif


INTOROBOT_SERIAL_DEV = /dev/cu.usbmodem1411
#INTOROBOT_SERIAL_DEV = /dev/cu.usbmodemFD1231
#INTOROBOT_SERIAL_DEV = /dev/ttyACM0



# 检查编译器版本是否符合要求
# Check if the compiler version is the minimum required
arm_gcc_version:=$(shell $(CC) --version | head -n 1)
arm_gcc_version:=$(strip $(subst arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors),,$(arm_gcc_version)))
expected_version:=4.8.4
quote="
lt=\<
dollar=$$
#$(info result $(shell test $(quote)$(arm_gcc_version)$(quote) $(lt) $(quote)$(expected_version)$(quote);echo $$?))
ifeq ($(shell test $(quote)$(arm_gcc_version)$(quote) $(lt) $(quote)$(expected_version)$(quote); echo $$?),0)
     $(error "ARM gcc version $(expected_version) or later required, but found $(arm_gcc_version)")
endif


ifeq ($(shell test $(quote)$(arm_gcc_version)$(quote) $(lt) $(quote)4.9.0$(quote); echo $$?),0)
     NANO_SUFFIX=_s
endif
