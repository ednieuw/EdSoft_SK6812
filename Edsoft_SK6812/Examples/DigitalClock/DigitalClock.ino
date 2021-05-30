//------------------------------------------------------------------------------
//  Digital time in 12x12 LED matrix
//------------------------------------------------------------------------------




#include <EdSoft_SK6812.h>
#include <TimeLib.h>                               // Arduino standard library Time or  https://github.com/PaulStoffregen/Time 
#include <Wire.h>                                  // Arduino standard library
#include "RTClib.h"                                // Arduino standard library or https://github.com/adafruit/RTClib 

//#define MOD_DS3231                               // If a DS3231 module is installed, if not the Arduino internal clock is used

const byte LED_PIN       = 5;                      // Pin where the LED strip is attached to
const byte NUM_LEDS      = 144;                    // How many leds in  strip?
const byte MATRIX_WIDTH  = 12;                     // Width in pixels of the LED strips
const byte MATRIX_HEIGHT = 12;                     // Height in pixels of the LED strips
const byte BRIGHTNESS    = 32;                     // BRIGHTNESS 0 - 255
const uint32_t white     = 0xFF000000;
EdSoft_SK6812 LED(NUM_LEDS, LED_PIN);  

        #ifdef MOD_DS3231
RTC_DS3231 RTCklok;
        #else
RTC_Millis RTCklok;   
        #endif 
DateTime Inow;
tmElements_t I;                                                                        // Initialyse a time struct I for internal times used to display the time in the clock
uint32_t lastminute;
uint32_t msTick;                                                                       // Static to remmember the msTick in this function
 

// Definition of the digits 0 - 9, 3 wide, 5 high. 
const byte PROGMEM Getal[10][3][5]  = { 
                     { {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1} },  //0
                     { {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1} },  //1
                     { {1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 0, 1} },  //2
                     { {1, 0, 1, 0, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 1, 1} },  //3
                     { {1, 1, 1, 0, 0}, {0, 0, 1, 0, 0}, {1, 1, 1, 1, 1} },  //4
                     { {1, 1, 1, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1} },  //5
//                   { {1, 1, 1, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 1, 1} },  //5 An other 5
                     { {1, 1, 1, 1, 1}, {0, 0, 1, 0, 1}, {0, 0, 1, 1, 1} },  //6
                     { {1, 1, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1} },  //7
                     { {1, 1, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 1, 1} },  //8
                     { {1, 1, 1, 0, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 1, 1} }   //9
                     }; 
//------------------------------------------------------------------------------
// ARDUINO Setup
//------------------------------------------------------------------------------
void setup() 
{
 Serial.begin(9600);                                                                          // Setup the serial port to 9600 baud       
 RTCklok.begin(DateTime(F(__DATE__), F(__TIME__)));                                           // If no RTC module is installed use the ATMEGAchip clock
 LED.setBrightness(128);    
 LedsOff();                                                                                   // Turn all LEDs off
 LED.show();                                                                                  // and do not forget LED.show(); to send the data in the LEDstrip
 msTick = millis();
}
//------------------------------------------------------------------------------
// ARDUINO Loop
//------------------------------------------------------------------------------
void loop() 
{
 EverySecondCheck();                                                                          // Keep the loop simple
}
//------------------------------------------------------------------------------
// CLOCK Update routine done every second
//------------------------------------------------------------------------------
void EverySecondCheck(void)
{
 if (millis() - msTick > 999)                                                                 // Enter the loop every second
    {
     GetTijd(0);                                                                              // Update I.Second, I.Minute, I.Hour, I.Day, I.Month, I.Year
     msTick = millis();
     if (I.Minute != lastminute)   EveryMinuteUpdate();                                       // Enter the every minute routine after one minute
    }
}
//------------------------------------------------------------------------------
// CLOCK Update routine done every minute
//------------------------------------------------------------------------------
void EveryMinuteUpdate(void)
 {
  lastminute = I.Minute;  
  LedsOff();                                                                                  // Start by clearing the display to a known state   
  TimePlaceDigit(I.Hour,I.Minute);
  LED.show();
  Print_RTC_tijd();
 }
 
//------------------------------------------------------------------------------
//  LED Place digits 0 - 9 in Matrix display
// First row and column = 0, PosX,PosY is left top position of 3x5 digit
// Calculate position LED #define MATRIX_WIDTH 12 #define MATRIX_HEIGHT 12
//------------------------------------------------------------------------------
void Zet_Pixel(byte Cijfer,byte Pos_X, byte Pos_Y) 
{ 
 uint32_t LEDnum;
 for(int i=0;i<3;i++)
  {  
   for(int j=0;j<5;j++)
   {
    int c = pgm_read_byte_near ( &Getal[Cijfer][i][j]); 
    if ( c )                                                                                  // if Digit == 1 then turn that light on
     {                                                                                        // Serial.print(strip.getPixelColor(LEDnum) & 0X00FFFFFF,HEX); Serial.print(" ");
      if((Pos_Y+j)%2) LEDnum = ((MATRIX_WIDTH -1) - (Pos_X + i) + (Pos_Y + j) * (MATRIX_HEIGHT));
      else            LEDnum =                      (Pos_X + i) + (Pos_Y + j) * (MATRIX_HEIGHT); 
      LED.setPixelColor(LEDnum, white);
     }
   }
 }
}
//------------------------------------------------------------------------------
//  LED Time in four digits in display
//------------------------------------------------------------------------------
void TimePlaceDigit(byte uur, byte minuut)
{   
 Zet_Pixel(    uur / 10, 2, 1);  Zet_Pixel(    uur % 10, 7, 1);
 Zet_Pixel( minuut / 10, 2, 7);  Zet_Pixel( minuut % 10, 7, 7);
}
//------------------------------------------------------------------------------
//  LED Clear display settings of the LED's
//------------------------------------------------------------------------------
void LedsOff(void) 
{ 
 LED.fill(0, 0, NUM_LEDS );
}

//------------------------------------------------------------------------------
// DS3231 Get time from DS3231
//------------------------------------------------------------------------------
void GetTijd(byte printit)
{
 Inow    = RTCklok.now();
 I.Hour   = min(Inow.hour()  , 24);
 I.Minute = min(Inow.minute(), 59);
 I.Second = min(Inow.second(), 59);
 I.Day    = Inow.day();
 I.Month  = Inow.month();
 I.Year   = Inow.year()-2000;
 I.Wday   = Inow.dayOfTheWeek();
// if (I.Hour > 24) { I.Hour = random(12)+1; I.Minute = random(60)+1; I.Second = 30;}          // Set a time if time module is absent or defect
 if (printit)  Print_RTC_tijd(); 
}
//------------------------------------------------------------------------------
// DS3231 utility function prints time to serial
//------------------------------------------------------------------------------
void Print_RTC_tijd(void)
{
 char sptext[40];
 sprintf(sptext,"%02d:%02d:%02d %02d-%02d-%04d",                                              
     Inow.hour(),Inow.minute(),Inow.second(),Inow.day(),Inow.month(),Inow.year());
 Serial.println(sptext);
}
