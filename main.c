//*****************************************************************************
//  Copyright 2016 Paul Chote
//  This file is part of raindetector, which is free software. It is made available
//  to you under version 3 (or later) of the GNU General Public License, as
//  published by the Free Software Foundation and included in the LICENSE file.
//*****************************************************************************

#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include "usb.h"

static volatile bool update_state = true;

void tick()
{
    if (!update_state)
        return;

    usb_write('$');

    // Sensor group 1 is PD2-7 (arduino digital pins 2-7)
    usb_write((PIND & 0xFC) >> 2);

    // Sensor group 2 is PC0-5 (arduino analog pins 0-5)
    usb_write(PINC & 0x3F);

    usb_write('\r');
    usb_write('\n');

    update_state = false;
}

int main()
{
    // Configure timer1 to interrupt every 1.00 seconds
    OCR1A = 15624;
    TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12);
    TIMSK1 |= _BV(OCIE1B);

    usb_initialize();

    // Inputs are on:
    //   PD2-7 (arduino digital pins 2-7)
    //   PC0-5 (arduino analog pins 0-5)
    // Pins default to inputs, so we only need to enable pull-ups
    PORTD = 0xFC;
    PORTC = 0x3F;

    sei();
    for (;;)
        tick();
}

ISR(TIMER1_COMPB_vect)
{
    update_state = true;
}