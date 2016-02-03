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
 * Creation date: 01/28/2016
 */

#include "uswap.h"
#include "tools.h"

/**
 * Endpoint names
 */
const char RGB_NAME[] = "RGB";
const char RED_NAME[] = "RED";
const char GREEN_NAME[] = "GREEN";
const char BLUE_NAME[] = "BLUE";

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
uint8_t RGBDRIVER::updateRegister(uint8_t regId, SWDATA *value)
{
  char buf[7], red[3], green[3], blue[3];

  switch(regId)
  {
    // RGB value
    case RGB_REGID:
      if (value->length != 3)
        break;

      // Update rgb value
      memcpy(rgb, value->data, sizeof(rgb));

      // Convert RGB array into string
      if (rgb[0] < 0x10)
        sprintf(red, "0%X", rgb[0]);
      else
        sprintf(red, "%X", rgb[0]);
      if (rgb[1] < 0x10)
        sprintf(green, "0%X", rgb[1]);
      else
        sprintf(green, "%X", rgb[1]);
      if (rgb[2] < 0x10)
        sprintf(blue, "0%X", rgb[2]);
      else
        sprintf(blue, "%X", rgb[2]);

      sprintf(buf, "%s%s%s", red, green, blue);

      // Send update to user application
      swap.push(address, RGB_NAME, buf);
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
uint8_t RGBDRIVER::getValue(char *val, char *name)
{
  char buf[7], red[3], green[3], blue[3];

  // Convert RGB array into string
  if (rgb[0] < 0x10)
    sprintf(red, "0%X", rgb[0]);
  else
    sprintf(red, "%X", rgb[0]);
  if (rgb[1] < 0x10)
    sprintf(green, "0%X", rgb[1]);
  else
    sprintf(green, "%X", rgb[1]);
  if (rgb[2] < 0x10)
    sprintf(blue, "0%X", rgb[2]);
  else
    sprintf(blue, "%X", rgb[2]);

  sprintf(buf, "%s%s%s", red, green, blue);

  if (!strcmp(name, RGB_NAME))
  {
    strcpy(val, red);
    return true;
  }
  else if (!strcmp(name, GREEN_NAME))
  {
    strcpy(val, green);
    return true;
  }
  else if (!strcmp(name, BLUE_NAME))
  {
    strcpy(val, blue);
    return true;
  }
  else if (!strcmp(name, RGB_NAME))
  {
    strcpy(val, buf);
    return true;
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
uint8_t RGBDRIVER::controlOutput(char *name, uint8_t *buf)
{
  SWDATA value;
  uint8_t tmpRGB[sizeof(rgb)], singleColor;
  char color[3];
  int regId = RGB_REGID;

  if (!strcmp(name, RGB_NAME))
  {
    if (strlen((char *)buf) != 6)
      return false;

    // RGB value is in RRGGBB (Hex) format    
    for (int i=0 ; i<sizeof(rgb) ; i++)
    {
      color[0] = buf[0];  
      color[1] = buf[1];
      color[2] = 0;
      tmpRGB[i] = TOOLS::charToHex(color);
      buf += 2;
    }
  }
  else if (!strcmp(name, RED_NAME))
  {
    if (strlen((char *)buf) != 2)
      return false;

    color[0] = buf[0];  
    color[1] = buf[1];
    color[2] = 0;

    memcpy(tmpRGB, rgb, sizeof(rgb));
    tmpRGB[0] = TOOLS::charToHex(color);
  }
  else if (!strcmp(name, GREEN_NAME))
  {
    if (strlen((char *)buf) != 2)
      return false;

    color[0] = buf[0];  
    color[1] = buf[1];
    color[2] = 0;

    memcpy(tmpRGB, rgb, sizeof(rgb));
    tmpRGB[1] = TOOLS::charToHex(color);
  }
  else if (!strcmp(name, BLUE_NAME))
  {
    if (strlen((char *)buf) != 2)
      return false;

    color[0] = buf[0];  
    color[1] = buf[1];
    color[2] = 0;

    memcpy(tmpRGB, rgb, sizeof(rgb));
    tmpRGB[2] = TOOLS::charToHex(color);
  }
  else
    return false;

  value.length = sizeof(rgb);
  value.data = tmpRGB;

  if (controlRegister((uint8_t)regId, &value))
    return true;

  return false;
}

