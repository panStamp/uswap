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
 * Creation date: 01/28/2016
 */

#ifndef _RGBDRIVER_H
#define _RGBDRIVER_H

#include "device.h"

/**
 * Class: RGBDRIVER
 * 
 * Description:
 * SWAP RGB driver
 */
class RGBDRIVER : public DEVICE
{
  public:
    /**
     * Regular register id's
     */
     enum REGID
     {
        RGB_REGID = 0x0B
     };

    /**
     * Binary (ON/OFF) outputs
     */
    uint8_t rgb[3];

    /**
     * Class constructor
     *
     * @param addr Device address
     */
    RGBDRIVER(uint8_t addr) : DEVICE(addr) {}

    /**
     * updateRegister
     *
     * Update values with new register information
     *
     * @param regId register id
     * @param value register value
     *
     * @return true if a valid register was updated. Return false otherwise
     */
    uint8_t updateRegister(uint8_t regId, SWDATA *value);

    /**
     * controlOutput
     *
     * Control output value
     *
     * @param name endpoint name
     * @param value output value in byte array format
     *
     * @return true in case of command successfully transmitted. Return false otherwise
     */
    uint8_t controlOutput(char *name, uint8_t *buf);
};

#endif

