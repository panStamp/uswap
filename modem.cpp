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

#include "modem.h"

#define OK_RECEIVED() (rxBuffer[0] == 'O' && rxBuffer[1] == 'K')

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
bool MODEM::config(uint8_t channel, uint8_t netidH, uint8_t netidL, uint8_t address)
{
  bool res = false;

  clearRxBuffer();

  // Enter command mode
  Serial.print("+++");
  while (!available());
  if (OK_RECEIVED())
  {
    delay(1000);
    clearRxBuffer();

    // Set RF channel
    Serial.print("ATCH=");
    Serial.println(channel, HEX);
    while (!available());
    if (OK_RECEIVED())
    {
      delay(1000);
      clearRxBuffer();

      // Set RF channel
      Serial.print("ATSW=");
      Serial.print(netidH, HEX);
      Serial.println(netidL, HEX);
      while (!available());
      if (OK_RECEIVED())
      {
        delay(1000);
        clearRxBuffer();

        // Set RF channel
        Serial.print("ATDA=");
        Serial.println(address, HEX);
        while (!available());
        if (OK_RECEIVED())
          res = true;
      }
    }
  }

  delay(1000);
  clearRxBuffer();

  // Leave command mode
  Serial.println("ATO");
  while (!available());
  if (!OK_RECEIVED())
    return false;

  return res;
}

/**
 * available
 *
 * Return true if a SWAP packet is waiting to be read from the buffer
 *
 * @return true if a paquet is waiting to be read. Return false otherwise
 */
bool MODEM::available(void)
{
  if (Serial.available() > 0)
  {
    uint8_t ch = Serial.read();

    if (rxLength >= sizeof(rxBuffer) - 1)
      clearRxBuffer();
    else if (ch == 0x0D) 
    {
      rxBuffer[rxLength] = 0;
      return true;
    }
    else if (ch != 0x0A)
    {
      rxBuffer[rxLength] = ch;
      rxLength++;
    }
  }

  return false;
}

/**
 * getPacket
 *
 * Return CCPACKET object containing the last packet received
 *
 * @return pointer to the CCPACKET object
 */
CCPACKET* MODEM::getPacket(void)
{
  if (rxBuffer[0] == '(' && rxBuffer[5] == ')')
  {
    char buf[3];
    uint8_t *ptr;

    ccPacket.length = (rxLength - 6) / 2;

    // RSSI
    buf[0] = rxBuffer[1];  
    buf[1] = rxBuffer[2];
    buf[2] = 0;
    ccPacket.rssi = charToHex(buf);

    // LQI
    buf[0] = rxBuffer[3];  
    buf[1] = rxBuffer[4];
    buf[2] = 0;
    ccPacket.lqi = charToHex(buf);

    // Data
    ptr = rxBuffer + 6;
    for (int i=0 ; i<ccPacket.length ; i++)
    {
      buf[0] = ptr[0];  
      buf[1] = ptr[1];
      buf[2] = 0;
      ccPacket.data[i] = charToHex(buf);
      ptr += 2;
    }
  }

  clearRxBuffer();
  return &ccPacket;
}

/**
 * write
 *
 * Send packet to serial modem
 *
 * @param ccPacket CCPACKET object to be transmitted to modem
 *
 * @return amount of bytes transmitted
 */
uint8_t MODEM::write(CCPACKET *ccPacket)
{
  int i;

  for(i=0 ; i<ccPacket->length ; i++)
    Serial.print(ccPacket->data[i]);

  Serial.println("");

  return i;
}

/**
 * strToHex
 *
 * @param buf Hex byte as a char array
 *
 * @return Hex byte
 */
uint8_t MODEM::charToHex(char *buf)
{
  uint8_t res = 0;
  
  for (int i=0 ; i<2 ; i++)
  {
    res <<= 4;
    if (buf[i] >= 'A' && buf[i] <= 'F')
      res |= buf[i] - 55;
    else if (buf[i] >= 'a' && buf[i] <= 'f')
      res |= buf[i] - 87;
    else if (buf[i] >= '0' && buf[i] <= '9')
      res |= buf[i] - 48;
    else
      return 0;
  }

  return res;
}

