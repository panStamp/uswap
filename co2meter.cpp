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
 * Creation date: 02/03/2016
 */

#include "uswap.h"

/**
 * Endpoint names
 */
const char VOLTAGE_NAME[] = "VOLTAGE";
const char CO2_NAME[] = "CO2";
const char TEMPERATURE_NAME[] = "TEMPERATURE";
const char HUMIDITY_NAME[] = "HUMIDITY";

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
uint8_t CO2METER::updateRegister(uint8_t regId, SWDATA *value)
{
  uint16_t tmp;

  switch(regId)
  {
    // Voltage
    case VOLTAGE_REGID:
      if (value->length != 2)
        break;
      tmp = value->data[0] << 8;
      co2 = tmp | value->data[1];
      // Send update to user application
      swap.push(address, CO2_NAME, co2);
      return true;
    // CO2 level
    case CO2_REGID:
      if (value->length != 2)
        break;
      tmp = value->data[0] << 8;
      voltage = tmp | value->data[1];
      // Send update to user application
      swap.push(address, VOLTAGE_NAME, voltage);
      return true;
    // Temperature and humidity
    case TEMPHUM_REGID:
      if (value->length != 4)
        break;
      tmp = value->data[0] << 8;
      tmp |= value->data[1];
      temperature = tmp * 0.1 - 50;
      tmp = value->data[2] << 8;
      tmp |= value->data[3];
      humidity = tmp * 0.1;
      // Send update to user application
      swap.push(address, TEMPERATURE_NAME, temperature, 1);
      swap.push(address, HUMIDITY_NAME, humidity, 1);
      return true;
    default:
      break;
  }

  return false;
}


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
uint8_t CO2METER::getValue(char *val, char *name)
{
  if (!strcmp(name, VOLTAGE_NAME))
  {
    sprintf(val, "%d", voltage);
    return true;
  }
  else if (!strcmp(name, CO2_NAME))
  {
    sprintf(val, "%d", co2);
    return true;
  }
  else if (!strcmp(name, TEMPERATURE_NAME))
  {
    char buf[24];
    int integer = (int)temperature;
    float decimal = temperature - integer;
    decimal *= 10;
    sprintf(val, "%d.%d", integer, (int)decimal);
    return true;
  }
  else if (!strcmp(name, HUMIDITY_NAME))
  {
    char buf[24];
    int integer = (int)humidity;
    float decimal = humidity - integer;
    decimal *= 10;
    sprintf(val, "%d.%d", integer, (int)decimal);
    return true;
  }

  return false;
}

