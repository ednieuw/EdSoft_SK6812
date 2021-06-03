# EdSoft_SK6812
Arduino library for SK6812 based 4-channel RGBW LEDs.<br>
The NeoPixel library from Adafruit can also be used to drive these LEDs but is larger in size and for my projects only a few of its functionalities are needed.<br>
The functions are comparable with Neopixel.<br>
The assembler source that drives WS2812 LEDs made by Tim (cpldcpu@gmail.com) was used with a few modifications.<br>

void     fill(RGBW RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs);<br>	
void     fill(uint32_t RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs);<br>
void     setBrightness(uint16_t Bright);<br>
void     setPixelColor(uint16_t i, RGBW RGBWColor);	<br>
void     setPixelColor(uint16_t i, uint32_t RGBWColor);<br>
void     show(void);<br>
uint8_t  getwhite(uint32_t c);<br>
uint8_t  getred(  uint32_t c);<br>
uint8_t  getgreen(uint32_t c);<br>
uint8_t  getblue( uint32_t c);	<br>
uint32_t getPixelColor(uint16_t index);<br>
uint32_t makeRGBWcolor( uint32_t Red, uint32_t Green, uint32_t Blue, uint32_t White);	<br>


## Usage
1. Download zip file<br>
2. In Arduino IDE: Sketch -> Include Library -> Add .ZIP Library<br>
3. Include the library in your project using "#include <EdSoft_SK6812.h>" directive<br>


## Example

#include <EdSoft_SK6812.h><br>
EdSoft_SK6812 LED(4, 5);                  // EdSoft_SK6812LED(NUM_LEDS, LED_PIN);<br>
uint32_t color1 = 0X000000FF;             // 0xWWRRGGBB  <br>
<br>
void setup() <br>
{                                         // LED.fill(RGBWColor, FirstLed, NoofLEDs );<br>
  LED.fill(color1, 1, 5 );                // Fill LEDs 2,3 and 4 with color1 <br>
}<br>
<br>
void loop() <br>
{  <br>
 LED.setPixelColor(0, {0, 0, 0, 255});    // Set second LED to white (using only W channel)<br>
 LED.show();                              // Send the values to the LEDs<br>
 delay(500);<br>
  <br>
 LED.setPixelColor(0, 0X00FF00FF);        // Set second LED to white (using only RGB channels)<br>
 LED.show();<br>
 delay(500);<br>
}<br>

