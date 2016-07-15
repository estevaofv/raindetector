//*****************************************************************************
//  Copyright 2016 Paul Chote
//  This file is part of raindetector, which is free software. It is made available
//  to you under version 3 (or later) of the GNU General Public License, as
//  published by the Free Software Foundation and included in the LICENSE file.
//*****************************************************************************

#include <stdint.h>

#ifndef RAINDETECTOR_USB_H
#define RAINDETECTOR_USB_H

void usb_initialize();
void usb_write(uint8_t b);

#endif