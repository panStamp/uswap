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

#include "devtemphum.h"

/**
 * updateRegister
 *
 * Update values in memory with new register information
 *
 * @param regId register id
 * @param value register value
 *
 * @return 
 */
uint8_t DEVTEMPHUM::updateRegister(uint8_t regId, SWDATA *value)
{
  uint16_t tmp;

  switch(regId)
  {
    // Voltage
    case VOLTAGE:
      if (value->length != 2)
        break;
      tmp = value->data[0] << 8;
      tmp |= value->data[1];
      voltage = tmp / 1000;
      break;
    // Temperature and humidity
    case TEMPHUM:
      if (value->length != 4)
        break;
      tmp = value->data[0] << 8;
      tmp |= value->data[1];
      temperature = tmp * 0.1 - 50;
      tmp = value->data[2] << 8;
      tmp |= value->data[3];
      humidity = tmp * 0.1;
    default:
      return -1;
      break;
  }

  return 0;
}

