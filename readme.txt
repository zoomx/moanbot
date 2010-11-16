Moanbot library

  Moanbot.begin()
    Initialise the Moanbot hardware. This needs to be run in the setup() part of a sketch before Moanbot can be used.


  ***********************
  ** Display functions **
  ***********************

  Moanbot.mouthHappy()
    Show a happy mouth

  Moanbot.mouthSad()
    Show a sad mouth

  Moanbot.mouthFlat();
    Show a neutral / flat mouth

  Moanbot.mouthRipple()
    Show a ripply mouth

  Moanbot.mouthCustom(a,b,c,d,e,f,g,h)
    Show a custom mouth. Values are 0 (off), 1 (dim), 2 (brighter), 3 (brightest).
    a,b,c,d are the top row of LEDs, left to right.
    e,f,g,h are the bottom LEDs.
    eg. Moanbot.mouthCustom(3,0,0,3,0,3,3,0) is a smiley face.

  Moanbot.nose(a)
    Set the nose to a colour. The available colours are:
      0: Black  1: Blue   2: Green  3: Cyan
      4: Red    5: Purple 6: Yellow 7: White

  Moanbot.hat(a)
    Set the brightness of the hat LED, from 0 (off) to 15 (brightest).
    Note that the hat LED is quite dim - it is the best LED to use in a darkened room.


  *********************
  ** Sound functions **
  *********************

  Moanbot.play(a)
    a is a number between 0 and 9999. This will play a .WAV file from the SD card.
    Numbers are padded to four digits, so Moanbot.play(2) will play 0002.WAV.


  **********************
  ** Sensor functions **
  **********************
  
  Moanbot.tempReadLeft()
    This returns a value 0 to 1023 that corresponds to the temperature on the left temperature sensor.

  Moanbot.tempReadRight()
    This returns a value 0 to 1023 that corresponds to the temperature on the right temperature sensor.

  Moanbot.lightReadLeft()
    This returns a value 0 to 1023 that corresponds to the light level on the left eye sensor.

  Moanbot.lightReadRight()
    This returns a value 0 to 1023 that corresponds to the light level on the right eye sensor.

  Moanbot.tilt()
    This returns a 1 or a 0, corresponding to the tilt sensor state.

