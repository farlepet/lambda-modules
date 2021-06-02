#include <string.h>

#include <lambda/mod/module.h>

#include <err/error.h>
#include <fs/stream.h>
#include <mm/alloc.h>

#include "tty.h"

#define BUFFER_SZ 64

static int _dev_in(tty_handle_t *hand, uint8_t b) {
    fs_write(hand->buff_in, 0, 1, &b);
    return 0;
}

tty_handle_t *tty_create() {
    tty_handle_t *hand;

    hand = (tty_handle_t *)kmalloc(sizeof(tty_handle_t));
    if(!hand) {
        return NULL;
    }

    memset(hand, 0, sizeof(tty_handle_t));

    hand->buff_in = stream_create(BUFFER_SZ);
    if(!hand->buff_in) {
        kfree(hand);
        return NULL;
    }
    hand->buff_out = stream_create(BUFFER_SZ);
    if(!hand->buff_out) {
        /* TODO: Destroy stream */
        kfree(hand);
        return NULL;
    }

    /* Default device input handler function */
    hand->dev_in = _dev_in;

    return hand;
}

static int mod_func(uint32_t func, void *data __unused) {
    switch(func) {
        case LAMBDA_MODFUNC_START:
            kerror(ERR_BOOTINFO, "Initializing TTY driver\n");
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
        .ident        = "tty.tty",
        .name         = "TTY support module",
        .description  = "Implements base support for creating and managing TTYs",
        .license      = "MIT",
        .authors      = (char *[]){
            "Peter Farley <far.peter1@gmail.com>",
            NULL
        },
        .requirements = NULL
    },

};
