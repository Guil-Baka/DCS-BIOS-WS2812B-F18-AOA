/\*\*

- This little project was just an AOA indicator. the code interfaces with the DCS-BIOS protocol and reads the angle of attack (AOA) data from DCS. The AOA data is then used to control a LED AOA gauge using WS2812B LED strip and the FastLED library.

- It also can be used to dim cockpit lights based on the Console Brightness knob in the F-18.
  
- Had to use HSV instead of RGB. Its just easier to work with since in FASTLED you can just set the hue saturation and value(brightness) and be done whit it.
- Since DCS works whit 16bit values and brightness is 8bit i just divided it by 256 to get a value between 0 and 255. instead 0 and 65535.

- I used an Arduino Uno but it will work with any Arduino board.
  \*/
