#ifndef EdSoft_SK6812_H_
#define EdSoft_SK6812_H_

#include <Arduino.h>

#ifndef F_CPU
#define  F_CPU 16000000UL
#endif

struct RGBW {  // Store of the original values           
	uint8_t g; // Green 
	uint8_t r; // Red
	uint8_t b; // Blue
	uint8_t w; // White
};

class EdSoft_SK6812 
{ 
 public: 
	EdSoft_SK6812(uint16_t num_leds,uint8_t pin);
	~EdSoft_SK6812();
	
	void     fill(RGBW RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs);	
	void     fill(uint32_t RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs);
	void     setBrightness(uint16_t Bright);
    void     setPixelColor(uint16_t i, RGBW RGBWColor);	
    void     setPixelColor(uint16_t i, uint32_t RGBWColor);
	void     show(void);
    uint8_t  getWhite(uint32_t c);
    uint8_t  getRed(  uint32_t c);
    uint8_t  getGreen(uint32_t c);
    uint8_t  getBlue( uint32_t c);	
    uint32_t getPixelColor(uint16_t index);
    uint32_t makeRGBWcolor( uint32_t Red, uint32_t Green, uint32_t Blue, uint32_t White);	
	
 private:

	uint8_t  _pin_mask;
	uint16_t _count_led;
	uint16_t  Brightness     = 128;
	uint16_t  PreviousBright = 128;
	RGBW     *_pixels;
	RGBW     *_Orgpixels;		
	const volatile uint8_t *_port;
	volatile uint8_t       *_port_reg;

	void sendarray_mask(uint8_t *data,uint16_t datlen,uint8_t maskhi,uint8_t *port);

};

#endif /* EdSoft_SK6812_H_ */
