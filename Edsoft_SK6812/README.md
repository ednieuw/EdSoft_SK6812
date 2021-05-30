# EdSoft_SK6812 V1.0.0
Arduino library for SK6812 based 4-channel RGBW LEDs.
The NeoPixel library from Adafruit can also be used to drive these LEDs but is larger in size and 
for my projects a few of its functionalities are needed
The functions are comparable with Neopixel.
The assembler source that drives WS2812 LEDs made by Tim (cpldcpu@gmail.com) was used with a few modifications.

void     fill(RGBW RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs);	
void     fill(uint32_t RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs);
void     setBrightness(uint16_t Bright);
void     setPixelColor(uint16_t i, RGBW RGBWColor);	
void     setPixelColor(uint16_t i, uint32_t RGBWColor);
void     show(void);
uint8_t  getwhite(uint32_t c);
uint8_t  getred(  uint32_t c);
uint8_t  getgreen(uint32_t c);
uint8_t  getblue( uint32_t c);	
uint32_t getPixelColor(uint16_t index);
uint32_t makeRGBWcolor( uint32_t Red, uint32_t Green, uint32_t Blue, uint32_t White);	


## Usage
1. Download zip file
2. In Arduino IDE: Sketch -> Include Library -> Add .ZIP Library
3. Include the library in your project using "#include <EdSoft_SK6812.h>" directive


## Example

#include <EdSoft_SK6812.h>
EdSoft_SK6812 LED(4, 5);                  // EdSoft_SK6812LED(NUM_LEDS, LED_PIN);
uint32_t color1 = 0X000000FF;             // 0xWWRRGGBB  

void setup() 
{                                         // LED.fill(RGBWColor, FirstLed, NoofLEDs );
  LED.fill(color1, 1, 5 );                // Fill LEDs 2,3 and 4 with color1 
}

void loop() 
{  
 LED.setPixelColor(0, {0, 0, 0, 255});    // Set second LED to white (using only W channel)
 LED.show();                              // Send the values to the LEDs
 delay(500);
  
 LED.setPixelColor(0, 0X00FF00FF);        // Set second LED to white (using only RGB channels)
 LED.show();
 delay(500);
}




