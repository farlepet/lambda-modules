# Required variables:
#   MODDIR: Directory of module
#   MODOUT: Module output file
#   OUTDIR: Module output directory
# Optional variables:
#   MODREQ: Module pre-requisites

MAINDIR     = $(CURDIR)

# TODO: Multiple architecture-support
ARCH        = x86
KERNEL      = $(MAINDIR)/../lambda-kern
KERNEL_INC  = $(KERNEL)/kernel/inc
KERNEL_ARCH = $(KERNEL)/kernel/arch/x86/inc

MODREQ      = $(file < $(MODDIR)/module.deps)

MODSHARED   = $(subst .mod,.shared,$(MODOUT))

SRCS        = $(wildcard $(MODDIR)/*.c)
OBJS        = $(patsubst %.c,%.o,$(SRCS))

REQMODS     = $(addprefix $(OUTDIR)/,$(MODREQ))
REQFLAGS    = $(addprefix -L,$(REQMODS))

CFLAGS     += -m32 -nostdlib -nostdinc -ffreestanding \
              -Wall -Wextra -Werror -fno-stack-protector \
			  -D ARCH_X86 \
			  -I$(KERNEL_INC) -I$(KERNEL_ARCH)\
			  -iquote $(MODULESDIR)
LDFLAGS     = -melf_i386 -l:lambda.shared --no-dynamic-linker -pic -L$(KERNEL) -e0x0 -shared

ifeq ($(CC), clang)
CFLAGS    += -Wno-incompatible-library-redeclaration 
else
CFLAGS    += -Wno-builtin-declaration-mismatch
endif

$(MODOUT): $(OBJS) $(REQMODS)
	@echo -e "\033[32m  \033[1mLD\033[21m    \033[34m$@\033[0m"
	@$(LD) $(LDFLAGS) $(REQFLAGS) -o $@ $(OBJS)

.SECONDEXPANSION:
$(OUTDIR)/%.mod: $(MODULESDIR)/$$(subst .,/,%).mod
	@echo -e "\033[32m\033[1mMOD\033[21m   \033[34m$@\033[0m"
	@if [ -f "$</Makefile" ]; then                                    \
		make -s -f "$</Makefile" MODDIR=$< MODOUT=$@ OUTDIR=$(OUTDIR); \
	else                                                             \
		make -s -f module.mk MODDIR=$< MODOUT=$@ OUTDIR=$(OUTDIR);     \
	fi


%.o: %.c
	@echo -e "\033[32m  \033[1mCC\033[21m    \033[34m$<\033[0m"
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@rm -f $(OBJS) $(MODOUT)