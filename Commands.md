# Initialisation #

Put `#include "Moanbot.h` at the start of any Moanbot sketch. This enables the Moanbot commands for use in your sketch.

In the setup() part of your sketch, include `Moanbot.begin();` This sets up the Moanbot hardware on power-up.

# Display functions #

**Moanbot.mouthHappy()**
> Sets the mouth to a happy smile.

**Moanbot.mouthSad()**
> Sets the mouth to a sad frown.

**Moanbot.mouthFlat()**
> Sets the mouth to a neutral expression.

**Moanbot.mouthRipple()**
> Sets the mouth to a ripply expression.

**Moanbot.mouthCustom(a,b,c,d,e,f,g,h)**
> Sets the mouth to a custom expression. a,b,c,d are the top LEDs from left to right. e,f,g,h are the bottom LEDs. A value of 0 sets the LED off. 1 and 2 are dim states, and 3 is the brightest.

**Moanbot.nose()**
> Sets the nose colour. The colours are Black (0), Blue (1), Green (2), Cyan (3), Red (4), Purple (5), Yellow (6) and White (7).

**Moanbot.hat()**
> Sets the hat brightness. Values 0 (off) to 15 (brightest) are available.

# Sound functions #

**Moanbot.play(a)**
> Play a sound file. a is a number between 0 and 9999. Moanbot.play(1234) will play the file 1234.WAV. All files have 4 digits, so Moanbot.play(1) will play file 0001.WAV.

# Sensor functions #

**Moanbot.tempReadLeft(a)**
> This returns a value 0 to 1023 that corresponds to the temperature on the left temperature sensor.

**Moanbot.tempReadRight()**
> This returns a value 0 to 1023 that corresponds to the temperature on the right temperature sensor.

**Moanbot.lightReadLeft()**
> This returns a value 0 to 1023 that corresponds to the light level on the left eye sensor.

**Moanbot.lightReadRight()**
> This returns a value 0 to 1023 that corresponds to the light level on the right eye sensor.

**Moanbot.tilt()**
> This returns 0 when standing, but 1 when leaning forwards.