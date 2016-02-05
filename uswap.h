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

// SWAP device classes
#include "devtemp.h"
#include "devtemphum.h"
#include "binouts.h"
#include "rgbdriver.h"
#include "co2meter.h"
#include "currentmeter.h"

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

  public:
    /**
     * Gateway address
     */
    uint8_t address;

    /**
     * valueUpdate
     *
     * Endpoint value changed. Callback function
     *
     * @param addr Device address
     * @param name Endpoint name
     * @param val value in string format
     */
    void (*valueUpdate)(uint8_t addr, const char *name, char *val);

    /**
     * Class constructor
     */
    inline SWAP(void)
    {
      valueUpdate = NULL;
    }

    /**
     * attachInterrupt
     * 
     * Declare custom ISR, to be called whenever an endpoint value changes
     * 
     * @param funct pointer to the custom function
     */
     inline void attachInterrupt(void (*funct)(uint8_t addr, const char *name, char *val))
     {
       valueUpdate = funct;
     }

    /**
     * begin
     *
     * Start SWAP stack
     *
     * @param channel RF chanel
     * @param netidH  Network ID, high byte
     * @param netidL  Network ID, low byte
     * @param addr modem's device address
     */
    inline void begin(uint8_t channel=DEFAULT_RF_CHANNEL, uint8_t netidH=DEFAULT_NETID_H, uint8_t netidL=DEFAULT_NETID_L, uint8_t addr=DEFAULT_DEV_ADDRESS)
    {
      LEDS::config();
      address = addr;
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

    /**
     * push
     *
     * Push value update towards user application
     *
     * @param addr Device address
     * @param name Endpoint name
     * @param val value in string format
     */
    inline void push(uint8_t addr, const char *name, char *val)
    {
      if (valueUpdate != NULL)
        valueUpdate(addr, name, val);
    }

    /**
     * push
     *
     * Push value update towards user application
     *
     * @param addr Device address
     * @param name Endpoint name
     * @param val value in integer format
     */
    inline void push(uint8_t addr, const char *name, int val)
    {
      char buf[24];
      sprintf(buf, "%d", val);
      push(addr, name, buf);
    }

    /**
     * push
     *
     * Push value update towards user application
     *
     * @param addr Device address
     * @param name Endpoint name
     * @param val value in float format
     * @param nbDec number of decimals to keep for hte transmitted value
     */
    inline void push(uint8_t addr, const char *name, float val, uint8_t nbDec)
    {
      char buf[24];
      int integer = (int)val;
      float decimal = val - integer;
      decimal *= pow(10, nbDec);
      sprintf(buf, "%d.%d", integer, (int)decimal);
      push(addr, name, buf);
    }
};

/**
 * Global SWAP object
 */
extern SWAP swap;

#endif

