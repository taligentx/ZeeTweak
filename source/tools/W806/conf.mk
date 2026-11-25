sinclude $(TOP_DIR)/tools/W806/.config
CONFIG_W800_TARGET_NAME ?= W806
CONFIG_W800_IMAGE_TYPE ?= 1
CONFIG_W800_USE_LIB ?= n
CONFIG_W800_FIRMWARE_DEBUG ?= n
CONFIG_ARCH_TYPE ?= W806
CONFIG_W800_TOOLCHAIN_PREFIX ?= csky-abiv2-elf

TARGET ?= $(subst ",,$(CONFIG_W800_TARGET_NAME))

ODIR := $(TOP_DIR)/firmware/build
OBJODIR := $(ODIR)/$(TARGET)/obj
UP_EXTRACT_DIR := ../../lib
LIBODIR := $(ODIR)/$(TARGET)/lib
IMAGEODIR := $(ODIR)/$(TARGET)/image
BINODIR := $(ODIR)/$(TARGET)/bin
FIRMWAREDIR := $(TOP_DIR)/firmware

FIRMWARE_NAME ?= ZeeTweak
FIRMWARE_VERSION ?= 5.0
FIRMWARE_BASENAME := $(FIRMWARE_NAME)_v$(FIRMWARE_VERSION)
FIRMWARE_OUT := $(IMAGEODIR)/$(FIRMWARE_BASENAME)
FIRMWARE_FLS := $(FIRMWAREDIR)/$(FIRMWARE_BASENAME).fls
FIRMWARE_BIN := $(FIRMWARE_OUT).bin
FIRMWARE_IMG := $(FIRMWARE_OUT).img
FIRMWARE_ELF := $(FIRMWARE_OUT).elf
FIRMWARE_ELF_MAP := $(FIRMWARE_OUT).map
FIRMWARE_VERSION_STR ?= $(FIRMWARE_NAME) v$(FIRMWARE_VERSION)
SDK_TOOLS := $(TOP_DIR)/tools/$(CONFIG_ARCH_TYPE)
WM_TOOL ?= $(SDK_TOOLS)/wm_tool
PYTHON ?= python3

SECBOOT_HEADER_POS=8002000
SECBOOT_ADDRESS_POS=8002400
SEC_BOOT_BIN := $(SDK_TOOLS)/W806_secboot.bin
SEC_BOOT_IMG := $(SDK_TOOLS)/W806_secboot
SEC_BOOT := $(SDK_TOOLS)/W806_secboot.img

ifeq ($(CONFIG_W800_USE_LIB),y)
USE_LIB = 1
else
USE_LIB = 0
endif

DL_PORT ?= $(subst ",,$(CONFIG_W800_DOWNLOAD_PORT))
DL_BAUD ?= $(CONFIG_W800_DOWNLOAD_RATE)

IMG_TYPE := $(CONFIG_W800_IMAGE_TYPE)
IMG_HEADER := $(CONFIG_W800_IMAGE_HEADER)
RUN_ADDRESS := $(CONFIG_W800_RUN_ADDRESS)
UPD_ADDRESS := $(CONFIG_W800_UPDATE_ADDRESS)

BLOB_TEXT_BASE   ?= 0x08010500
BLOB_RODATA_BASE ?= 0x0802E760
SDK_TEXT_BASE    ?= 0x0807E3D8

optimization ?= -O2

ifeq ($(CONFIG_W800_FIRMWARE_DEBUG),y)
optimization += -g -DWM_SWD_ENABLE=1
endif

# C-SKY toolchain
cputype = ck804ef
extra_lib =
extra_flag =
ld_map_opt = -ckmap

VERBOSE ?= NO

TOOL_CHAIN_PREFIX = $(CONFIG_W800_TOOLCHAIN_PREFIX)
TOOL_CHAIN_PATH = $(subst ",,$(CONFIG_W800_TOOLCHAIN_PATH))

ifeq ($(VERBOSE),YES)
    AR = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-ar
    ASM = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-gcc
    CC = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-gcc
    CXX = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-g++
    LINK = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-gcc
    OBJCOPY = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-objcopy
    OBJDUMP = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-objdump
else
    AR      = @echo "AR       $(notdir $@)" 2>/dev/null; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-ar
    ASM     = @echo "ASM      $<"; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-gcc
    CC      = @echo "CC       $<"; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-gcc
    CXX     = @echo "CXX      $<"; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-g++
    LINK    = @echo "LINK     $(notdir $(FIRMWARE_ELF))"; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-gcc
    OBJCOPY = @echo "OBJCOPY  $(notdir $(FIRMWARE_BIN))"; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-objcopy
    OBJDUMP = @echo "OBJDUMP  $<"; $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-objdump
endif

LDDIR = $(TOP_DIR)/ld/$(CONFIG_ARCH_TYPE)
LD_FILE = $(LDDIR)/gcc_csky.ld

LIB_EXT = .a

CCFLAGS := -Wall \
    -DTLS_CONFIG_CPU_XT804=1 \
    -DGCC_COMPILE=1 \
    -mcpu=$(cputype) \
    $(optimization) \
    -std=gnu99 \
    -c  \
    -mhard-float  \
    $(extra_flag)  \
    -fdata-sections  \
    -ffunction-sections

CCXXFLAGS := -Wall \
    -DTLS_CONFIG_CPU_XT804=1 \
    -DGCC_COMPILE=1 \
    -mcpu=$(cputype) \
    $(optimization) \
    -std=gnu++11 \
    -c  \
    -mhard-float  \
    $(extra_flag)  \
    -fdata-sections  \
    -ffunction-sections

ASMFLAGS := -Wall \
    -DTLS_CONFIG_CPU_XT804=1 \
    -DGCC_COMPILE=1 \
    -mcpu=$(cputype) \
    $(optimization) \
    -std=gnu99 \
    -c  \
    -mhard-float \
    -Wa,--gdwarf2 \
    $(extra_flag)  \
    -fdata-sections  \
    -ffunction-sections

ARFLAGS := ru

ARFLAGS_2 = xo

LINKFLAGS := -mcpu=$(cputype) \
    -nostartfiles \
    -mhard-float \
    $(extra_flag)  \
    -lm $(extra_lib) \
    -Wl,-T$(LD_FILE)

MAP := -Wl,$(ld_map_opt)=$(FIRMWARE_ELF_MAP)

sinclude $(TOP_DIR)/tools/W806/inc.mk
