#include <lambda/mod/module.h>
/* TODO: This should be moved somewhere under lambda/ */
#include <err/error.h>

static int mod_func(uint32_t func, void *data __unused) {
    switch(func) {
        case LAMBDA_MODFUNC_START:
            kerror(ERR_BOOTINFO, "BIG TEST\n");
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
        .ident        = "test.test1",
        .name         = "Test Module",
        .description  = "Module for testing Lambda module loading",
        .license      = "MIT",
        .authors      = (char *[]){
            "Peter Farley <far.peter1@gmail.com>",
            NULL
        },
        .requirements = NULL
    },

};
