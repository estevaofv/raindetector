//*****************************************************************************
//  Copyright 2016 Paul Chote
//  This file is part of raindetector, which is free software. It is made available
//  to you under version 3 (or later) of the GNU General Public License, as
//  published by the Free Software Foundation and included in the LICENSE file.
//*****************************************************************************

#include <avr/interrupt.h>
#include <stdint.h>

static uint8_t output_buffer[256];
static volatile uint8_t output_read = 0;
static volatile uint8_t output_write = 0;

void usb_initialize()
{
#define BAUD 9600
#include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A = _BV(U2X0);
#endif

    // Enable transmit only
    UCSR0B = _BV(TXEN0);

    output_read = output_write = 0;
}

// Add a byte to the send buffer.
// Will block if the buffer is full
void usb_write(uint8_t b)
{
    // Don't overwrite data that hasn't been sent yet
    while (output_write == (uint8_t)(output_read - 1));

    output_buffer[output_write++] = b;

    // Enable transmit if necessary
    UCSR0B |= _BV(UDRIE0);
}

ISR(USART_UDRE_vect)
{
    if (output_write != output_read)
        UDR0 = output_buffer[output_read++];

    // Ran out of data to send - disable the interrupt
    if (output_write == output_read)
        UCSR0B &= ~_BV(UDRIE0);
}
