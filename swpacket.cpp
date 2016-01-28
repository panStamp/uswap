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

#include "swpacket.h"
#include "uswap.h"

/**
 * SWPACKET
 * 
 * Class constructor
 * 
 * @param packet Pointer to the raw CC1101 packet
 */
SWPACKET::SWPACKET(CCPACKET *packet) 
{
  uint8_t i;
   
  // Save raw data and length
  length = packet->length;
  for(i=0 ; i<length ; i++)
    data[i] = packet->data[i];
  
  // Fill SWPACKET fields
  hop = (data[2] >> 4) & 0x0F;
  security = data[2] & 0x0F;
   
  nonce = data[3];
  function = data[4] & ~SWAP_EXTENDED_ADDRESS_BIT;
  destAddr = data[0];
  srcAddr = data[1];
  regAddr = data[5];
  regId = data[6];

  value.data = data + SWAP_DATA_HEAD_LEN + 1;
  value.length = length - SWAP_DATA_HEAD_LEN - 1;
}

/**
 * SWPACKET
 * 
 * Class constructor
 */
SWPACKET::SWPACKET(void) 
{
}

/**
 * send
 * 
 * Send SWAP packet. Do up to 5 retries if necessary
 *
 * @return amount of bytes transmitted
 */
uint8_t SWPACKET::send(void)
{
  byte i;
  boolean res;

  length = value.length + SWAP_DATA_HEAD_LEN + 1;

  data[0] = destAddr;
  data[1] = srcAddr;
  data[2] = (hop << 4) & 0xF0;
  data[2] |= security & 0x0F;
  data[3] = nonce;
  data[4] = function;
  data[5] = regAddr;
  data[6] = regId;

  for(i=0 ; i<value.length ; i++)
    data[i+SWAP_DATA_HEAD_LEN + 1] = value.data[i];

  return swap.write(this);
}

