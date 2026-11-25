.DEFAULT_GOAL := all

subdir_path := $(subst $(abspath $(TOP_DIR))/,,$(shell pwd))

# Force a full relink on a build goal so the .fls is regenerated even when the
# ELF is up to date.  Only the top-level make may do this: the recursive makes
# run from .subdirs have no goals of their own, so without the subdir_path guard
# they match the empty-goal case and delete the ELF out from under the link.
ifeq ($(subdir_path),)
ifeq ($(FIRMWARE_ELF),$(wildcard $(FIRMWARE_ELF)))
ifeq ($(MAKECMDGOALS),)
$(shell $(RM) -rf $(FIRMWARE_ELF))
else ifeq ($(MAKECMDGOALS),all)
$(shell $(RM) -rf $(FIRMWARE_ELF))
else ifeq ($(MAKECMDGOALS),image)
$(shell $(RM) -rf $(FIRMWARE_ELF))
else ifeq ($(MAKECMDGOALS),flash)
$(shell $(RM) -rf $(FIRMWARE_ELF))
else ifeq ($(MAKECMDGOALS),run)
$(shell $(RM) -rf $(FIRMWARE_ELF))
endif
endif
endif

CSRCS ?= $(wildcard *.c)
CPPSRCS ?= $(wildcard *.cpp)
ASRCS ?= $(wildcard *.S)

SUBDIRS ?= $(patsubst %/,%,$(dir $(wildcard */Makefile)))

OBJS := $(CSRCS:%.c=$(OBJODIR)/$(subdir_path)/%.o) \
        $(CPPSRCS:%.cpp=$(OBJODIR)/$(subdir_path)/%.o) \
        $(ASRCS:%.S=$(OBJODIR)/$(subdir_path)/%.o)

OBJS-DEPS := $(patsubst %.c, $(OBJODIR)/$(subdir_path)/%.o.d, $(CSRCS))

OLIBS := $(GEN_LIBS:%=$(LIBODIR)/%)

OIMAGES := $(GEN_IMAGES:%=$(IMAGEODIR)/%)

OBINS := $(GEN_BINS:%=$(BINODIR)/%)

CFLAGS = $(CCFLAGS) $(DEFINES) $(EXTRA_CCFLAGS) $(INCLUDES)

CXXFLAGS = $(CCXXFLAGS) $(DEFINES) $(EXTRA_CCXXFLAGS) $(INCLUDES)

define ShortcutRule
$(1): .subdirs $(2)/$(1)
endef

define MakeLibrary
DEP_LIBS_$(1) = $$(foreach lib,$$(filter %$(LIB_EXT),$$(COMPONENTS_$(1))),$$(LIBODIR)/$$(notdir $$(lib)))
DEP_OBJS_$(1) = $$(foreach obj,$$(filter %.o,$$(COMPONENTS_$(1))),$$(OBJODIR)/$$(notdir $$(obj)))
# Nested archives are created by the recursive .subdirs make, so they are
# order-only prerequisites: as normal prerequisites they have no rule here
# (and fail under -j before .subdirs runs).  Extraction therefore keys off
# DEP_LIBS instead of $?, which no longer contains them.
$$(LIBODIR)/$(1)$(LIB_EXT): $$(OBJS) $$(DEP_OBJS_$(1)) $$(DEPENDS_$(1)) | $$(if $$(DEP_LIBS_$(1)),.subdirs)
	@mkdir -p $$(LIBODIR)
	$$(if $$(DEP_LIBS_$(1)),@mkdir -p $$(OBJODIR)/_$(1); cd $$(OBJODIR)/_$(1); $$(foreach lib,$$(DEP_LIBS_$(1)),$$(AR) $(ARFLAGS_2) $$(UP_EXTRACT_DIR)/$$(notdir $$(lib));))
	$$(AR) $(ARFLAGS) $$@ $$(filter %.o,$$?) $$(if $$(DEP_LIBS_$(1)),$$(OBJODIR)/_$(1)/*.o)
	$$(if $$(DEP_LIBS_$(1)),@$$(RM) -r $$(OBJODIR)/_$(1))
endef

define MakeImage
DEP_LIBS_$(1) = $$(foreach lib,$$(filter %$(LIB_EXT),$$(COMPONENTS_$(1))),$$(LIBODIR)/$$(notdir $$(lib)))
DEP_OBJS_$(1) = $$(foreach obj,$$(filter %.o,$$(COMPONENTS_$(1))),$$(OBJODIR)/$$(notdir $$(obj)))
$$(IMAGEODIR)/$(1).elf: $$(OBJS) $$(DEP_OBJS_$(1)) $$(DEP_LIBS_$(1)) $$(DEPENDS_$(1))
	@mkdir -p $$(IMAGEODIR)
	$(LINK) -Wl,--gc-sections -Wl,-zmax-page-size=1024 -Wl,--whole-archive $$(OBJS) $$(DEP_OBJS_$(1)) $$(DEP_LIBS_$(1)) $$(if $$(LINKFLAGS_$(1)),$$(LINKFLAGS_$(1))) -Wl,--no-whole-archive $(LINKFLAGS) $(MAP) -o $$@
endef

HOSTCC ?= gcc
$(WM_TOOL): $(SDK_TOOLS)/wm_tool.c
	@echo "HOSTCC   $(notdir $@)"
	@$(HOSTCC) $< -lpthread -o $@

$(BINODIR)/%.bin: $(IMAGEODIR)/%.elf $(WM_TOOL)
	@mkdir -p $(FIRMWAREDIR)
	$(OBJCOPY) -O binary $(FIRMWARE_ELF) $(FIRMWARE_BIN)
	@$(WM_TOOL) -b $(FIRMWARE_BIN) -fc 0 -it $(IMG_TYPE) -ih $(IMG_HEADER) -ra $(RUN_ADDRESS) -ua $(UPD_ADDRESS) -nh 0 -un 0 -vs "$(FIRMWARE_VERSION_STR)" -o $(FIRMWARE_OUT)
	@$(WM_TOOL) -b  $(SEC_BOOT_BIN) -fc 0 -it 0 -ih $(SECBOOT_HEADER_POS) -ra $(SECBOOT_ADDRESS_POS) -ua $(UPD_ADDRESS) -nh $(IMG_HEADER) -un 0 -o $(SEC_BOOT_IMG)
	@$(PYTHON) $(SDK_TOOLS)/verify_image.py \
	    --secboot-bin $(SEC_BOOT_BIN) \
	    --secboot-img $(SEC_BOOT)
	@cat $(SEC_BOOT) $(FIRMWARE_IMG) > $(FIRMWARE_FLS)
	@$(PYTHON) $(SDK_TOOLS)/verify_image.py \
	    --secboot-bin $(SEC_BOOT_BIN) \
	    --secboot-img $(SEC_BOOT) \
	    --fls $(FIRMWARE_FLS) \
	    --app-bin $(FIRMWARE_BIN) \
	    --run-address $(RUN_ADDRESS) \
	    --version-string "$(FIRMWARE_VERSION_STR)"

all: .subdirs $(OBJS) $(OLIBS) $(OIMAGES) $(OBINS)

help:
	@echo  'Cleaning targets:'
	@echo  '  clean      - Remove most generated files'
	@echo  '  distclean  - Remove all generated files'
	@echo  ''
	@echo  'Compiling targets:'
	@echo  '  all        - Build firmware'
	@echo  ''
	@echo  'Programming targets:'
	@echo  '  image      - Build and flash the app image'
	@echo  '  flash      - Build and flash the full .fls image'
	@echo  '  down       - Flash the .fls image without building'
	@echo  ''
	@echo  'Other targets:'
	@echo  '  list       - List locally available serial ports'
	@echo  '  monitor    - Open a serial monitor'
	@echo  '  run        - Build, flash and open a serial monitor'

clean:
	$(RM) -r $(ODIR)

distclean:clean
	$(RM) -f $(FIRMWARE_FLS)

run monitor down image flash list: $(WM_TOOL)

run:all
	@$(WM_TOOL) -c $(DL_PORT) -rs at -ds $(DL_BAUD) -dl $(FIRMWARE_FLS) -sl str -ws 115200

monitor:
	@$(WM_TOOL) -c $(DL_PORT) -sl str -ws 115200

list:
	@$(WM_TOOL) -l

down:
	@$(WM_TOOL) -c $(DL_PORT) -rs at -ds $(DL_BAUD) -dl $(FIRMWARE_FLS)

image:all
	@$(WM_TOOL) -c $(DL_PORT) -rs at -ds $(DL_BAUD) -dl $(FIRMWARE_IMG)

flash:all
	@$(WM_TOOL) -c $(DL_PORT) -rs at -ds $(DL_BAUD) -dl $(FIRMWARE_FLS)

.subdirs:
	@set -e; $(foreach d, $(SUBDIRS), $(MAKE) -C $(d);)

sinclude $(OBJS-DEPS)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),clobber)
ifdef DEPS
sinclude $(DEPS)
endif
endif
endif

$(OBJODIR)/$(subdir_path)/%.o: %.c
	@mkdir -p $(OBJODIR)/$(subdir_path)
	$(CC) $(if $(findstring $<,$(DSRCS)),$(DFLAGS),$(CFLAGS)) $(COPTS_$(*F)) $(INCLUDES) $(CMACRO) -c "$<" -o "$@" -MMD -MD -MF "$(@:$(OBJODIR)/$(subdir_path)/%.o=$(OBJODIR)/$(subdir_path)/%.o.d)" -MT "$(@)"

$(OBJODIR)/$(subdir_path)/%.o: %.cpp
	@mkdir -p $(OBJODIR)/$(subdir_path)
	$(CXX) $(if $(findstring $<,$(DSRCS)),$(DFLAGS),$(CXXFLAGS)) $(COPTS_$(*F)) $(INCLUDES) $(CMACRO) -c "$<" -o "$@" -MMD -MD -MF "$(@:$(OBJODIR)/$(subdir_path)/%.o=$(OBJODIR)/$(subdir_path)/%.o.d)" -MT "$(@)"

$(OBJODIR)/$(subdir_path)/%.o: %.S
	@mkdir -p $(OBJODIR)/$(subdir_path)
	$(ASM) $(ASMFLAGS) $(INCLUDES) $(CMACRO) -c "$<" -o "$@"

$(foreach lib,$(GEN_LIBS),$(eval $(call ShortcutRule,$(lib),$(LIBODIR))))

$(foreach image,$(GEN_IMAGES),$(eval $(call ShortcutRule,$(image),$(IMAGEODIR))))

$(foreach bin,$(GEN_BINS),$(eval $(call ShortcutRule,$(bin),$(BINODIR))))

$(foreach lib,$(GEN_LIBS),$(eval $(call MakeLibrary,$(basename $(lib)))))

$(foreach image,$(GEN_IMAGES),$(eval $(call MakeImage,$(basename $(image)))))
