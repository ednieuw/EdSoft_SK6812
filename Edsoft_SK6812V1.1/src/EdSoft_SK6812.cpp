#include "EdSoft_SK6812.h"
//--------------------------------------------
//  Initialyse 
//--------------------------------------------
EdSoft_SK6812::EdSoft_SK6812(uint16_t num_leds,uint8_t pin)
{
	_count_led = num_leds;
	_pixels    = new RGBW[_count_led];   
	_Orgpixels = new RGBW[_count_led];

	_pin_mask  = digitalPinToBitMask(pin);
	_port      = portOutputRegister(digitalPinToPort(pin));
	_port_reg  = portModeRegister(digitalPinToPort(pin));
}
//--------------------------------------------
//  Exit
//--------------------------------------------
EdSoft_SK6812::~EdSoft_SK6812()
{
	delete [] _pixels;
	delete [] _Orgpixels;
}

//--------------------------------------------
//  Set Brightness (0 - 255)of a pixel to be written 
//  with show(); to the LED strip
//--------------------------------------------
void EdSoft_SK6812::setBrightness(uint16_t Bright)
{
 Brightness = Bright;
 return;
}
//--------------------------------------------
//  Write the _pixels array to the strip
//  that will be multiplied with the Brightness factor
//--------------------------------------------
void EdSoft_SK6812::show()
{
 memcpy(_Orgpixels, _pixels,_count_led * sizeof(RGBW) );
 for (uint16_t i = 0; i< _count_led; i++)  // Prepare the string with dimmed values
	{
     _pixels[i].r = (uint8_t)(_pixels[i].r * Brightness / 255);
 	 _pixels[i].g = (uint8_t)(_pixels[i].g * Brightness / 255);
	 _pixels[i].b = (uint8_t)(_pixels[i].b * Brightness / 255);
	 _pixels[i].w = (uint8_t)(_pixels[i].w * Brightness / 255);
	}	
 *_port_reg |= _pin_mask;
 sendarray_mask((uint8_t *)_pixels, _count_led * sizeof(RGBW), _pin_mask, (uint8_t *)_port);

 memcpy(_pixels,_Orgpixels, _count_led * sizeof(RGBW) );
}

//--------------------------------------------
// Get Pixel Color 
//--------------------------------------------
uint32_t EdSoft_SK6812::getPixelColor(uint16_t i)
{
 uint32_t Retvalue = 0;	
 if (i < _count_led) 
	Retvalue = makeRGBWcolor(_pixels[i].r,_pixels[i].g,_pixels[i].b,_pixels[i].w);
return(Retvalue);
}
//--------------------------------------------
//  Write an RGBW struct in strip array _pixels
//--------------------------------------------
void EdSoft_SK6812::setPixelColor(uint16_t i, RGBW RGBWColor)
{
	if (i < _count_led) 
	{
	 _pixels[i].r = RGBWColor.r;
 	 _pixels[i].g = RGBWColor.g;
	 _pixels[i].b = RGBWColor.b;
	 _pixels[i].w = RGBWColor.w;

	}
 return;
}
//--------------------------------------------
//  Write an uint32_t in strip array _pixels
//--------------------------------------------
void EdSoft_SK6812::setPixelColor(uint16_t i, uint32_t RGBWColor)
{
	if (i < _count_led) 
	{
    _pixels[i].r = getRed(RGBWColor)  ;
    _pixels[i].g = getGreen(RGBWColor);
    _pixels[i].b = getBlue(RGBWColor) ;
    _pixels[i].w = getWhite(RGBWColor);
	}
 return;
}
//------------------------------------------------------------------------------
// Function to make RGBW color
//------------------------------------------------------------------------------ 
uint32_t EdSoft_SK6812::makeRGBWcolor( uint32_t Red, uint32_t Green, uint32_t Blue, uint32_t White)
{ 
 return ( (White<<24) + (Red << 16) + (Green << 8) + Blue );
}

//--------------------------------------------
// Fill part of the LED Strip with an RGBW color 
//--------------------------------------------
void EdSoft_SK6812::fill(RGBW RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs)
{
 uint16_t LastLED = FirstLed + NoofLEDs;
 if (LastLED > _count_led) LastLED = _count_led;
 for(uint16_t i = FirstLed; i < LastLED; i++)
   {
	 _pixels[i].r = RGBWColor.r;
 	 _pixels[i].g = RGBWColor.g;
	 _pixels[i].b = RGBWColor.b;
	 _pixels[i].w = RGBWColor.w;
//	Serial.print(i); Serial.print (":"); Serial.println(_pixels[i].r);
  }
}
//--------------------------------------------
// Fill part of the LED Strip with an RGBW color 
//--------------------------------------------
void EdSoft_SK6812::fill(uint32_t RGBWColor, uint16_t FirstLed, uint16_t NoofLEDs)
{
 uint16_t LastLED = FirstLed + NoofLEDs;
 if (LastLED > _count_led) LastLED = _count_led;
 for(uint16_t i = FirstLed; i < LastLED; i++)
   {
    _pixels[i].r = getRed(RGBWColor)  ;
    _pixels[i].g = getGreen(RGBWColor);
    _pixels[i].b = getBlue(RGBWColor) ;
    _pixels[i].w = getWhite(RGBWColor);
//	Serial.print(i); Serial.print (":"); Serial.println(_pixels[i].r);
  }
}
//------------------------------------------------------------------------------
//  Functions to extract RGBW colors
//------------------------------------------------------------------------------ 
 uint8_t EdSoft_SK6812::getWhite(uint32_t c) { return (c >> 24);}
 uint8_t EdSoft_SK6812::getRed(  uint32_t c) { return (c >> 16);}
 uint8_t EdSoft_SK6812::getGreen(uint32_t c) { return (c >> 8); }
 uint8_t EdSoft_SK6812::getBlue( uint32_t c) { return (c);      }