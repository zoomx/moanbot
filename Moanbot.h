/* Arduino Moanbot Library
 * by Peter Knight
 * Copyright (C) 2010 TinkerLondon.com
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with the Arduino Moanbot Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef Moanbot_h
#define Moanbot_h

#include <stdint.h>
#define LEDMAP_LEN 12

class MoanbotClass{
public:
    void begin();
    void mouthHappy();
    void mouthSad();
    void mouthFlat();
    void mouthRipple();
    void mouthCustom(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t e,uint8_t f,uint8_t g,uint8_t h);
    void nose(uint8_t a);
    void hat(uint8_t a);
    uint8_t play(uint16_t a);
    uint16_t tempReadLeft();
    uint16_t tempReadRight();
    uint16_t lightReadLeft();
    uint16_t lightReadRight();
    uint8_t tilt();
};

extern MoanbotClass Moanbot;

#endif
