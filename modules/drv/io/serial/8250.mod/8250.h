#ifndef MOD_DRV_IO_SERIAL_8250_8250_H
#define MOD_DRV_IO_SERIAL_8250_8250_H

#include <stdint.h>

#define SERIAL_COM1 0x3F8
#define SERIAL_COM2 0x2F8
#define SERIAL_COM3 0x3E8
#define SERIAL_COM4 0x2E8

/**
 * \brief Initialize the serial port.
 * 
 * @param port which port to initialize
 */
void serial_8250_init(uint16_t port, uint32_t baud);

#endif
