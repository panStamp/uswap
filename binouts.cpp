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

#include "uswap.h"

/**
 * Endpoint names
 */
const char BINOUTS_NAME[][8] = {"BINOUT0", "BINOUT1", "BINOUT2", "BINOUT3", "BINOUT4", "BINOUT5", "BINOUT6", "BINOUT7"};
const char PWMOUTS_NAME[][8] = {"PWMOUT0", "PWMOUT1", "PWMOUT2", "PWMOUT3"};

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
uint8_t BINOUTS::updateRegister(uint8_t regId, SWDATA *value)
{
  uint16_t tmp;

  switch(regId)
  {
    // Binary outputs
    case BINOUTS_REGID:
      if (value->length != 1)
        break;
      currentStates = value->data[0];
      for(int i=0 ; i<8 ; i++)
      {
        if ((currentStates & (1 << i)) > 0)
          binOutputs[i] = 1;
        else
          binOutputs[i] = 0;

        // Send update to user application
        swap.push(address, BINOUTS_NAME[i], binOutputs[i]);
      }
      return true;
    // PWM outputs
    case PWMOUTS_REGID:
      if (value->length != 4)
        break;
      for(int i=0 ; i<4 ; i++)
      {
        pwmOutputs[i] = value->data[i];
        // Send update to user application
        swap.push(address, PWMOUTS_NAME[i], pwmOutputs[i]);
      }
      return true;
    default:
      break;
  }

  return false;
}

/**
 * controlOutput
 *
 * Control output value
 *
 * @param name endpoint name
 * @param buf output value in byte array format
 *
 * @return true in case of command successfully transmitted. Return false otherwise
 */
uint8_t BINOUTS::controlOutput(char *name, uint8_t *buf)
{
  SWDATA value;
  int regId = -1;
  uint8_t levels[4], state;

  // Binary output?
  for(int i=0 ; i<sizeof(binOutputs) ; i++)
  {
    if (!strcmp(BINOUTS_NAME[i], name))
    {
      if (!strcmp((char*)buf, "1") || !strcmp((char*)buf, "high") || !strcmp((char*)buf, "HIGH") ||
          !strcmp((char*)buf, "on") || !strcmp((char*)buf, "ON"))
        state = currentStates | (1 << i);
      else
        state = currentStates & ~(1 << i);

      regId = BINOUTS_REGID;
      value.length = 1;
      value.data = &state;
      break;
    }
  }

  if (regId != BINOUTS_REGID)
  {
    memcpy(levels, pwmOutputs, sizeof(pwmOutputs));

    // PWM output?
    for(int i=0 ; i<sizeof(pwmOutputs) ; i++)
    {
      if (!strcmp(PWMOUTS_NAME[i], name))
      {
        regId = PWMOUTS_REGID;
        levels[i] = atoi((char*)buf);
        break;
      }
    }

    if (regId == PWMOUTS_REGID)
    {
      value.length = 4;
      value.data = levels;
    }
    else
      return false;
  }

  if (controlRegister((uint8_t)regId, &value))
    return true;

  return false;
}

