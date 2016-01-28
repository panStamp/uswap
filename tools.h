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

#ifndef _TOOLS_H
#define _TOOLS_H

#include "Arduino.h"

/**
 * Class: CCPACKET
 * 
 * Description:
 * Generic tools
 */
class TOOLS
{
  public:
    /**
     * strToHex
     *
     * @param buf Hex byte as a char array
     *
     * @return Hex byte
     */
    static inline uint8_t charToHex(char *buf)
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
};

#endif

