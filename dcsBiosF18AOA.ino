
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

#include <FastLED.h>

// fastled setup
#define NUM_LEDS 8
#define DATA_PIN 8
#define AOA_GREEN_LED 0
#define AOA_YELLOW_LED 1
#define AOA_RED_LED 2
CRGB leds[NUM_LEDS];

#define CONSOLE_LED_START 3
#define CONSOLE_LED_END 7
#define BRIGHTNESS 128 // this is the overall brightness of all the leds

// global variable for individual pixel brightness 0 - 255
int ledBrightness = 0; // 128 is random start number for brightness

int divideBrightness(int simBrightness) // 0 - 65535
{
  ledBrightness = simBrightness / 256; // Converts 0-65535 to 0-255
  return ledBrightness;
}

void changeBrightness(int simBrightness)
{
  for (int i = CONSOLE_LED_START; i <= CONSOLE_LED_END; i++)
  {
    leds[i].setHSV(96, 255, divideBrightness(simBrightness));
  }
}

void onConsoleIntLtChange(unsigned int newValue)
{
  changeBrightness(newValue);
  FastLED.show();
}
DcsBios::IntegerBuffer consoleIntLtBuffer(0x7558, 0xffff, 0, onConsoleIntLtChange);

void onAOAIndexerHighChange(unsigned int newValue)
{
  if (newValue == 1)
  {
    turnOnAOAIndexerHigh();
  }
  else
  {
    turnOffAOAIndexerHigh();
  }
  FastLED.show();
}
DcsBios::IntegerBuffer aoaIndexerHighBuffer(0x7408, 0x0008, 3, onAOAIndexerHighChange);

void onAOAIndexerLowChange(unsigned int newValue)
{
  if (newValue == 1)
  {
    turnOnAOAIndexerLow();
  }
  else
  {
    turnOffAOAIndexerLow();
  }
  FastLED.show();
}
DcsBios::IntegerBuffer aoaIndexerLowBuffer(0x7408, 0x0020, 5, onAOAIndexerLowChange);

void onAOAIndexerNormalChange(unsigned int newValue)
{
  if (newValue == 1)
  {
    turnOnAOAIndexerNormal();
  }
  else
  {
    turnOffAOAIndexerNormal();
  }
  FastLED.show();
}
DcsBios::IntegerBuffer aoaIndexerNormalBuffer(0x7408, 0x0010, 4, onAOAIndexerNormalChange);

void turnOnAOAIndexerHigh()
{
  leds[AOA_GREEN_LED] = CRGB::Green;
}
void turnOffAOAIndexerHigh()
{
  leds[AOA_GREEN_LED] = CRGB::Black;
}

void turnOnAOAIndexerLow()
{
  leds[AOA_RED_LED] = CRGB::Red;
}
void turnOffAOAIndexerLow()
{
  leds[AOA_RED_LED] = CRGB::Black;
}

void turnOnAOAIndexerOff()
{
  leds[AOA_YELLOW_LED] = CRGB::Yellow;
}
void turnOffAOAIndexerOff()
{
  leds[AOA_YELLOW_LED] = CRGB::Black;
}

void turnOnAOAIndexerNormal()
{
  leds[AOA_YELLOW_LED] = CRGB::Yellow;
}
void turnOffAOAIndexerNormal()
{
  leds[AOA_YELLOW_LED] = CRGB::Black;
}

void setup()
{
  // fastled setup
  // set all leds to off
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  // dcsbios setup
  DcsBios::setup();
}
void loop()
{
  // put your main code here, to run repeatedly:
  DcsBios::loop();
}
