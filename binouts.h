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
 * Creation date: 01/27/2016
 */

#ifndef _BINOUTS_H
#define _BINOUTS_H

#include "device.h"

/**
 * Class: BINOUTS
 * 
 * Description:
 * SWAP device providing 8-binary outputs and 4 PWM outputs
 */
class BINOUTS : public DEVICE
{
  private:
    /**
     * Current value of the binary output register
     */
    uint8_t currentStates;

  public:
    /**
     * Regular register id's
     */
     enum REGID
     {
        BINOUTS_REGID = 0x0B,
        PWMOUTS_REGID
     };

    /**
     * Binary (ON/OFF) outputs. Each bit represents the state of a binary output.
     * Lower output (BINOUT0) is the less significant bit
     */
    uint8_t binOutputs[8];

    /**
     * PWM (0-255) outputs. Each byte represents the level of a PWM output.
     * Lower output (PWMOUT0) is the less significant byte.
     */
    uint8_t pwmOutputs[4];

    /**
     * Class constructor
     *
     * @param addr Device address
     */
    BINOUTS(uint8_t addr) : DEVICE(addr) {currentStates=0;}

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

