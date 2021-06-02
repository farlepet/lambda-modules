#include <lambda/mod/module.h>
/* TODO: This should be moved somewhere under lambda/ */
#include <err/error.h>

#include "8250.h"

#define DEFAULT_BAUD 115200

static int mod_func(uint32_t func, void *data __unused) {
    switch(func) {
        case LAMBDA_MODFUNC_START:
            kerror(ERR_BOOTINFO, "Initializing 8250\n");
            serial_8250_init(SERIAL_COM1, DEFAULT_BAUD);
            break;
        case LAMBDA_MODFUNC_STOP:
            kerror(ERR_BOOTINFO, "BIG DETEST\n");
            break;
        default:
            return -1;
    }

    return 0;
}


MODULE_HEADER = {
    .head_magic   = LAMBDA_MODULE_HEAD_MAGIC,
    .head_version = LAMBDA_MODULE_HEAD_VERSION,
    .kernel       = LAMBDA_VERSION,
    .function     = &mod_func,

    .metadata     = {
        .ident        = "drv.io.serial.8250",
        .name         = "x86 8250 Serial Driver",
        .description  = "Implements support for the 8250 serial controller",
        .license      = "MIT",
        .authors      = (char *[]){
            "Peter Farley <far.peter1@gmail.com>",
            NULL
        },
        .requirements = (char *[]){
            "tty.tty",
            NULL
        }
    },

};
