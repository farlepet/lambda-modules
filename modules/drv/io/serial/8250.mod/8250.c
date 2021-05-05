#include <intr/intr.h>

#include <arch/io/ioport.h>

void serial_8250_init(uint16_t port, uint32_t baud) {
    uint16_t divisor = (115200 / baud);

	outb(port + 1, 0x00);
	outb(port + 3, 0x80);
	outb(port + 0, (uint8_t)divisor);
	outb(port + 1, (uint8_t)(divisor >> 8));
	outb(port + 3, 0x03);
	outb(port + 2, 0xC7);
	outb(port + 4, 0x0B);
	outb(port + 1, 0x01);

	/*set_interrupt(INT_SERIALA, &serial_interrupt);
	set_interrupt(INT_SERIALB, &serial_interrupt);
	enable_irq(4);
	enable_irq(3);*/

	/*add_input_dev(&serial_dev, IDRIVER_SERIAL, "ser", 1, 0);
	serial_dev.iev_buff = &_serial_buff;*/
}
