/**
 * Copyright (c) 2016 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 01/09/2016
 */

#ifndef _CCPACKET_H
#define _CCPACKET_H

#include "Arduino.h"

/**
 * Buffer and data lengths
 */
#define CCPACKET_BUFFER_LEN        64
#define CCPACKET_DATA_LEN          CCPACKET_BUFFER_LEN - 3

/**
 * Class: CCPACKET
 * 
 * Description:
 * CC1101 data packet class
 */
struct CCPACKET
{
  public:
    /**
     * Data length
     */
    uint8_t length;

    /**
     * Data buffer
     */
    uint8_t data[CCPACKET_DATA_LEN];

    /**
     * Received Strength Signal Indication
     */
    uint8_t rssi;

    /**
     * Link Quality Index
     */
    uint8_t lqi;
};

#endif

