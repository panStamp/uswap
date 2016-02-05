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

#ifndef _MODEM_H
#define _MODEM_H

#include "ccpacket.h"

#define SERIAL_BUFFER_LEN  132

/**
 * Class: MODEM
 * 
 * Description:
 * SWAP serial interface
 */
class MODEM
{
  private:
    /**
     * Serial Rx buffer
     */
    uint8_t rxBuffer[SERIAL_BUFFER_LEN];

    /**
     * Current length of serial packet
     */
    uint8_t rxLength;

    /**
     * strToHex
     *
     * @param buf Hex byte as a char array
     *
     * @return Hex byte
     */
    uint8_t charToHex(char *buf);

  public:
    /**
     * Rx SWAP packet
     */
    CCPACKET ccPacket;

    /**
     * Class constructor
     */
    inline MODEM(void)
    {
      clearRxBuffer();
    }

    /**
     * Start modem
     *
     * @param speed Serial speed
     */
    inline void begin(uint16_t speed=38400)
    {
      Serial.begin(speed);
      Serial.setDebugOutput(0);
      Serial.println("");
      delay(2000);
    }

    /**
     * config
     *
     * Configure modem
     *
     * @param channel RF chanel
     * @param netidH  Network ID, high byte
     * @param netidL  Network ID, low byte
     * @param address modem's device address
     */
    bool config(uint8_t channel, uint8_t netidH, uint8_t netidL, uint8_t address);

    /**
     * clearRxBuffer
     *
     * Clear Rx buffer
     */
    inline void clearRxBuffer(void)
    {
      memset(rxBuffer, 0, sizeof(rxBuffer));
      rxLength = 0;
    }

    /**
     * available
     *
     * Return true if a SWAP packet is waiting to be read from the buffer
     *
     * @return true if a paquet is waiting to be read. Return false otherwise
     */
    bool available(void);

    /**
     * getPacket
     *
     * Return CCPACKET object containing the last packet received
     *
     * @return pointer to the CCPACKET object
     */
    CCPACKET* getPacket(void);

    /**
     * write
     *
     * Send packet to serial modem
     *
     * @param ccPacket CCPACKET object to be transmitted to modem
     *
     * @return amount of bytes transmitted
     */
    uint8_t write(CCPACKET *ccPacket);
};

#endif

