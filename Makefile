MAINDIR    = $(CURDIR)
MODULESDIR = $(MAINDIR)/modules

OUTDIR      = $(MAINDIR)/out
MODULES     = $(shell find $(MODULESDIR) -type d -iname "*.mod")
MODULE_OBJS = $(patsubst %,$(OUTDIR)/%,$(subst /,.,$(subst $(MODULESDIR)/,,$(MODULES))))

MODULE_SRCS = $(foreach mod, $(MODULES), $(wildcard $(mod)/*.c))
MODULE_COBJ = $(patsubst %.c,%.o,$(MODULE_SRCS))

all: $(OUTDIR) $(MODULE_OBJS)

.SECONDEXPANSION:
$(OUTDIR)/%.mod: $(MODULESDIR)/$$(subst .,/,%).mod
	@echo -e "\033[32m\033[1mMOD\033[21m   \033[34m$@\033[0m"
	@make -f module.mk MODDIR=$< MODOUT=$@

$(OUTDIR):
	@mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -f $(MODULE_OBJS)
	rm -f $(MODULE_COBJ)