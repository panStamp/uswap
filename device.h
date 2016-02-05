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
//#include "swpacket.h"
#include "swcommand.h"

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
     * @return true if a valid register was updated. Return false otherwise
     */
    virtual uint8_t updateRegister(uint8_t regId, SWDATA *value) {}

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
    virtual uint8_t getValue(char *val, char *name) {}

    /**
     * controlRegister
     *
     * Set new register value in remote device
     *
     * @param regId register id
     * @param value register value
     *
     * @return >0 in case of command successfully transmitted. Return 0 otherwise
     */
    inline uint8_t controlRegister(uint8_t regId, SWDATA *value)
    {
      SWCOMMAND command(address, regId, value);
      return command.send();
    }

    /**
     * controlOutput
     *
     * Control output value
     *
     * @param name endpoint name
     * @param value output value in string format
     *
     * @return true in case of command successfully transmitted. Return false otherwise
     */
    virtual uint8_t controlOutput(char *name, uint8_t *buf) {return false;};
};

#endif

