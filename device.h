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
 * Creation date: 01/02/2016
 */

#ifndef _DEVICE_H
#define _DEVICE_H

#include "Arduino.h"
#include "swpacket.h"

/**
 * Class: DEVICE
 * 
 * Description:
 * SWAP device
 */
class DEVICE
{
  public:
    /**
     * Device address
     */
    uint8_t address;

    /**
     * Class constructor
     *
     * @param addr Device address
     */
    DEVICE(uint8_t addr);

    /**
     * updateRegister
     *
     * Update values in memory with new register information
     *
     * @param regId register id
     * @param value register value
     *
     * @return 0 in case of valid register and value successfully updated
     *        -1 in case of not a valid register
     */
    virtual uint8_t updateRegister(uint8_t regId, SWDATA *value) {}

    /**
     * controlRegister
     *
     * Set new register value in remote device
     *
     * @param regId register id
     * @param value register value
     *
     * @return 0 in case of valid register and value successfully updated
     *        -1 in case of not a valid register or lack of response from device
     */
    virtual uint8_t controlRegister(uint8_t regId, SWDATA *value) {};
};

#endif

