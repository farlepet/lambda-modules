# Required variables:
#   MODDIR: Directory of module
#   MODOUT: Module output file

MAINDIR     = $(CURDIR)

# TODO: Multiple architecture-support
ARCH        = x86
KERNEL      = $(MAINDIR)/../lambda-kern
KERNEL_INC  = $(KERNEL)/kernel/inc
KERNEL_ARCH = $(KERNEL)/kernel/arch/x86/inc

SRCS        = $(wildcard $(MODDIR)/*.c)
OBJS        = $(patsubst %.c,%.o,$(SRCS))

CFLAGS     += -m32 -nostdlib -nostdinc -ffreestanding \
              -Wall -Wextra -Werror -fno-stack-protector \
			  -I$(KERNEL_INC) -I$(KERNEL_ARCH) -D ARCH_X86
LDFLAGS     = -melf_i386 -l:lambda.shared --no-dynamic-linker -pic -L$(KERNEL) -e0x0

ifeq ($(CC), clang)
CFLAGS    += -Wno-incompatible-library-redeclaration 
else
CFLAGS    += -Wno-builtin-declaration-mismatch
endif

$(MODOUT): $(OBJS)
	@echo -e "\033[32m  \033[1mLD\033[21m    \033[34m$@\033[0m"
	@$(LD) $(LDFLAGS) -o $(MODOUT) $(OBJS)
	

%.o: %.c
	@echo -e "\033[32m  \033[1mCC\033[21m    \033[34m$<\033[0m"
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@rm -f $(OBJS) $(MODOUT)