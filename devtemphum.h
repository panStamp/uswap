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
 * Creation date: 01/20/2016
 */

#ifndef _DEVTEMPHUM_H
#define _DEVTDEVTEMPHUMEMP_H

#include "device.h"

/**
 * Class: DEVTEMPHUM
 * 
 * Description:
 * SWAP Temperature + Humidity sensor device
 */
class DEVTEMPHUM : public DEVICE
{
  public:
    /**
     * Regular register id's
     */
     enum REGID
     {
        VOLTAGE_REGID = 0x0B,
        TEMPHUM_REGID,
     };

    /**
     * Voltage supply
     */
    float voltage;

    /**
     * Temperature
     */
    float temperature;

    /**
     * Humidity
     */
    float humidity;

    /**
     * Class constructor
     *
     * @param addr Device address
     */
    DEVTEMPHUM(uint8_t addr) : DEVICE(addr) {}

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
     * getValue
     *
     * Get endpoint value
     *
     * @param val Current value returned in string format
     * @param name Endpoint name
     *
     * @return true if a valid endpoint was found. Return false otherwise
     */
    uint8_t getValue(char *val, char *name);
};

#endif

