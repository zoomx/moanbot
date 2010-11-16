/* Arduino Moanbot Library
 * Copyright (C) 2010 by TinkerLondon.com
 *  
 * This file is part of the Arduino Moanbot Library
 *
 * It patches William Greiman's WaveHC library to use the internal PWM instead of an
 * external DAC.
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
 *  
 * You should have received a copy of the GNU General Public License
 * along with the Arduino WaveHC Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 *  Macros and inline functions for MCP4921 DAC
 */   
#ifndef mcpDac_h
#define mcpDac_h

#include <avr/io.h>
#include <WavePinDefs.h>

#define mcpDacCsLow()
#define mcpDacCsHigh()
#define mcpDacSckLow()
#define mcpDacSckHigh()
#define mcpDacSckPulse()
#define mcpDacSdiLow()
#define mcpDacSdiHigh()
#define mcpDacSdiSet(v)
#define mcpDacSendBit(d, b)

inline void mcpDacInit(void) {}
inline void mcpDacSend(uint16_t data) { OCR2B = data>>8; }

#endif //mcpDac_h