/* Arduino Moanbot example 1
 * Copyright (C) 2010 TinkerLondon.com
 *
 * This file is distributed under the terms of the GPLv3 license.
 * See <http://www.gnu.org/licenses/>
 *
 * This example plays sound 0001.WAV when the left eye is covered,
 * and 0002.WAV when the right eye is covered.
 *
 */

#include <Moanbot.h>

void setup() {
  Moanbot.begin();
  Moanbot.mouthHappy();
}
void loop() {
  if (Moanbot.lightReadLeft() > 500) {
    Moanbot.mouthSad();
    Moanbot.nose(2);
    Moanbot.play(1);
    delay(3000);
  } else if (Moanbot.lightReadRight() > 500) {
    Moanbot.mouthRipple();
    Moanbot.nose(1);
    Moanbot.play(2);
    delay(3000);
  } else {
    Moanbot.mouthHappy();
    Moanbot.nose(0);
  }
}
