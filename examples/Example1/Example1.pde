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
    Moanbot.play(3);
    delay(3000);
  } else {
    Moanbot.mouthHappy();
    Moanbot.nose(0);
  }
}
