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

#ifndef _LEDS_H
#define _LEDS_H

#include "Arduino.h"

/**
 * LED pins
 */
#define LED1    5
#define LED2    4

/**
 * Class: LEDS
 * 
 * Description:
 * On-board LED control
 */
class LEDS
{
  public:
    /**
     * Class constructor
     *
     * @param ledPin LED pin
     */
    static inline void config(void)
    {
      pinMode(LED1, OUTPUT);
      pinMode(LED2, OUTPUT);
    }

    /**
     * led1
     *
     * Control LED1
     *
     * @param state LED state (HIGH or LOW)
     */
    static inline void led1(const uint8_t state)
    {
      digitalWrite(LED1, state);
    }

    /**
     * led2
     *
     * Control LED2
     *
     * @param state LED state (HIGH or LOW)
     */
    static inline void led2(const uint8_t state)
    {
      digitalWrite(LED2, state);
    }
};

#endif

