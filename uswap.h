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

#ifndef _SWAP_H
#define _SWAP_H

#include "device.h"
#include "modem.h"
#include "leds.h"

#define null 0
#define MAX_DEVICES  50

/**
 * Default SWAP settings
 */
#define DEFAULT_RF_CHANNEL   0
#define DEFAULT_NETID_H      0xB5
#define DEFAULT_NETID_L      0x47
#define DEFAULT_DEV_ADDRESS  1

/**
 * Class: SWAP
 * 
 * Description:
 * SWAP protocol handler
 */
class SWAP
{
  private:
    /**
     * Wireless modem object
     */
    MODEM modem;

    /**
     * Array of devices
     */
    DEVICE *devices[MAX_DEVICES];

    /**
     * Number of registered devices
     */
    static uint8_t numDevices;

    /**
     * getDevice
     *
     * Get device object with address passed as argument
     *
     * @param addr SWAP address
     *
     * @return DEVICE object
     */
    inline DEVICE * getDevice(uint8_t addr)
    {
      for(int i=0 ; i<numDevices ; i++)
      {
        if (devices[i]->address == addr)
          return devices[i];
      }
      return null;
    }

  public:
    /**
     * begin
     *
     * Start SWAP stack
     *
     * @param channel RF chanel
     * @param netidH  Network ID, high byte
     * @param netidL  Network ID, low byte
     * @param address modem's device address
     */
    inline void begin(uint8_t channel=DEFAULT_RF_CHANNEL, uint8_t netidH=DEFAULT_NETID_H, uint8_t netidL=DEFAULT_NETID_L, uint8_t address=DEFAULT_DEV_ADDRESS)
    {
      LEDS::config();
      modem.begin();
      if (!modem.config(channel, netidH, netidL, address))
      {
        LEDS::led2(HIGH);
      }
    }

    /**
     * registerDevice
     *
     * Register device in array devices
     *
     * @param device Device to be registered
     */
    inline void registerDevice(DEVICE *device)
    {
      devices[numDevices++] = device;
    }

    /**
     * write
     *
     * Transmit packet
     *
     * @param ccPacket CCPACKET object to be transmitted to modem
     *
     * @return amount of bytes transmitted
     */
    inline uint8_t write(CCPACKET *ccPacket)
    {
      return modem.write(ccPacket);
    }

    /**
     * process
     *
     * Process incoming SWAP traffic
     */
    void process(void);
};

/**
 * Global SWAP object
 */
extern SWAP swap;

#endif

