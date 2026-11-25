TOP_DIR := .
.DEFAULT_GOAL := all
sinclude $(TOP_DIR)/tools/W806/conf.mk

ifndef PDIR # {
GEN_IMAGES =
GEN_BINS = $(FIRMWARE_BASENAME).bin
SUBDIRS = \
    $(TOP_DIR)/src_zw \
    $(TOP_DIR)/app
endif # } PDIR

ifndef PDIR # {
ifeq ($(USE_LIB), 0)
SUBDIRS += \
    $(TOP_DIR)/platform/arch        \
    $(TOP_DIR)/platform/drivers
endif
endif

VOBJ          = $(OBJODIR)/src_zw
BSPOBJ        = $(OBJODIR)/platform/arch/xt804/bsp
BSP_OBJS      = $(BSPOBJ)/startup.o $(BSPOBJ)/system.o $(BSPOBJ)/vectors.o
ZEEWEEII_OBJS = $(VOBJ)/app_boot.o $(VOBJ)/zw_app.o \
                $(VOBJ)/zw_rodata.o $(VOBJ)/zw_symbols.o

APP_SRCS      = $(wildcard $(TOP_DIR)/app/src/*.c)
APP_OBJS      = $(patsubst $(TOP_DIR)/app/src/%.c,$(OBJODIR)/app/src/%.o,$(APP_SRCS))

LD_BIN      = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-ld

LD_BASE_ARGS = --defsym __text_base_arg=$(BLOB_TEXT_BASE) \
               --defsym __rodata_base_arg=$(BLOB_RODATA_BASE) \
               --defsym __sdk_text_base_arg=$(SDK_TEXT_BASE)

IMAGE_OBJS  = $(BSP_OBJS) $(ZEEWEEII_OBJS) $(APP_OBJS)
IMAGE_LIBS  = --start-group -L$(LIBODIR) -ldrivers -lwmlibc -lwmarch \
                  -L$(TOP_DIR)/lib/W806 -ldsp --end-group

$(FIRMWARE_ELF): $(TOP_DIR)/ld/W806/app_sdk.ld | .subdirs
	@mkdir -p $(IMAGEODIR)
	@echo "LINK     $(notdir $@)"
	$(LD_BIN) -T $(TOP_DIR)/ld/W806/app_sdk.ld $(LD_BASE_ARGS) \
	    -Map $(FIRMWARE_ELF_MAP) -o $@ \
	    $(IMAGE_OBJS) $(IMAGE_LIBS)

INCLUDES := $(INCLUDES) -I$(PDIR)include
INCLUDES += -I ./

sinclude $(TOP_DIR)/tools/$(CONFIG_ARCH_TYPE)/rules.mk

PYTHON ?= python3
FIRMWARE ?=
GENERATED_DIR := $(ODIR)/generated
VENDOR_SOURCE_ARGS = $(if $(strip $(FIRMWARE)),--firmware "$(FIRMWARE)",)
VENDOR_OBJDUMP = $(subst ",,$(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX))-objdump

.PHONY: source
source:
	$(PYTHON) $(TOP_DIR)/gen/generate_vendor_source.py \
	    $(VENDOR_SOURCE_ARGS) \
	    --work-dir "$(GENERATED_DIR)" \
	    --out-dir "$(TOP_DIR)/src_zw" \
	    --objdump "$(VENDOR_OBJDUMP)"

.subdirs: source

STOCK_IMAGE := $(GENERATED_DIR)/image/image1.img

.PHONY: verify
verify: $(OBINS)
	@$(PYTHON) $(TOP_DIR)/tools/W806/verify_identity.py \
	    --stock "$(STOCK_IMAGE)" \
	    --built "$(FIRMWARE_BIN)" \
	    --sdk-base "$(SDK_TEXT_BASE)"

# Printed from the last step of the default goal, so it stays below every
# check the build runs rather than splitting them.
all: verify
	@echo
	@echo "Build complete: $(FIRMWARE_FLS)"
