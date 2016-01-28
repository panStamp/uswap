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
 * Creation date: 01/12/2016
 */

#include "uswap.h"
#include "swpacket.h"

uint8_t SWAP::numDevices = 0;

/**
 * process
 *
 * Process incoming SWAP traffic
 */
void SWAP::process(void)
{
  if (modem.available())
  {
    SWPACKET swPacket(modem.getPacket());
    DEVICE *dev = getDevice(swPacket.regAddr);

    if (dev != NULL)
    {
      // Update value only in case of SWAP status packet received
      if (swPacket.function == SWAPFUNCT_STA)
      {
        LEDS::led1(HIGH);
        dev->updateRegister(swPacket.regId, &swPacket.value);
        LEDS::led1(LOW);
      }
    }
  }
}

/**
 * Pre-instantiate SWAP object
 */
SWAP swap;

