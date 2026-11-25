TOP_DIR = ..
sinclude $(TOP_DIR)/tools/W806/conf.mk

ifndef PDIR
GEN_LIBS =
GEN_IMAGES =
GEN_BINS =
endif

sinclude $(TOP_DIR)/tools/W806/rules.mk

ifeq ($(filter clean clobber,$(MAKECMDGOALS)),)
ifeq ($(wildcard zw_app.s),)
$(error Firmware sources not generated: run 'make source' from the repository root)
endif
endif

AS_BIN = $(TOOL_CHAIN_PATH)$(TOOL_CHAIN_PREFIX)-as
VOBJ   = $(OBJODIR)/$(subdir_path)

$(VOBJ):
	@mkdir -p $@

$(VOBJ)/zw_app.o: zw_app.s | $(VOBJ)
	@echo "AS       $<"; $(AS_BIN) -mcpu=$(cputype) -o $@ $<

$(VOBJ)/zw_rodata.o: zw_rodata.s zw_rodata.bin | $(VOBJ)
	@echo "AS       $<"; $(AS_BIN) -mcpu=$(cputype) -o $@ $<

$(VOBJ)/zw_symbols.o: zw_symbols.s | $(VOBJ)
	@echo "AS       $<"; $(AS_BIN) -mcpu=$(cputype) -o $@ $<

all: $(VOBJ)/zw_app.o $(VOBJ)/zw_rodata.o $(VOBJ)/zw_symbols.o
