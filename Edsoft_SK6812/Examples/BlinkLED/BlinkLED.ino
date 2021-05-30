#include <EdSoft_SK6812.h>

EdSoft_SK6812 LED(4, 5);                  // EdSoft_SK6812LED(NUM_LEDS, LED_PIN);

uint32_t color1 = 0X000000FF;             // 0xWWRRGGBB  

void setup() {
  
  LED.fill(color1, 1, 5 );                // Fill LEDs 2,3 and 4 with color1 LED.fill(RGBWColor, FirstLed, NoofLEDs );
}

void loop() {
  
  LED.setPixelColor(0, {0, 0, 0, 255});   // Set second LED to white (using only W channel)
  LED.show();                             // Send the values to the LEDs
  delay(500);
  
  LED.setPixelColor(0, 0X00FF00FF);       // Set second LED to white (using only RGB channels)
  LED.show();
  delay(500);
}
