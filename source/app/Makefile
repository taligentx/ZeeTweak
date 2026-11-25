TOP_DIR = ..
sinclude $(TOP_DIR)/tools/W806/conf.mk

ifndef PDIR
GEN_LIBS =
GEN_IMAGES =
GEN_BINS =
endif

CSRCS := $(wildcard src/*.c)

sinclude $(TOP_DIR)/tools/W806/rules.mk

$(OBJS): | $(OBJODIR)/$(subdir_path)/src

$(OBJODIR)/$(subdir_path)/src:
	@mkdir -p $@
