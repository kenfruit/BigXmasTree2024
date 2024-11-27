// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

// Current Board is ESP-WROOM-DA


#include <FastLED.h>

#define DATA_PIN_0 13
#define DATA_PIN_1 12
#define DATA_PIN_2 14
#define DATA_PIN_3 27
#define DATA_PIN_4 26
#define DATA_PIN_5 25
#define DATA_PIN_6 33
#define DATA_PIN_7 32


enum {
  GRB_Black = 0x000000,   GRB_Navy = 0x000080,   GRB_DarkBlue = 0x00008B,   GRB_MediumBlue = 0x0000CD,   GRB_Blue = 0x0000FF,   GRB_DarkGreen = 0x640000,   GRB_Green = 0x800000,
  GRB_Teal = 0x800080,   GRB_DarkCyan = 0x8B008B,   GRB_DeepSkyBlue = 0xBF00FF,   GRB_DarkTurquoise = 0xCE00D1,   GRB_MediumSpringGreen = 0xFA009A,   GRB_Lime = 0xFF0000,   GRB_SpringGreen = 0xFF007F,
  GRB_Aqua = 0xFF00FF,   GRB_Cyan = 0xFF00FF,   GRB_MidnightBlue = 0x191970,   GRB_DodgerBlue = 0x901EFF,   GRB_LightSeaGreen = 0xB220AA,   GRB_ForestGreen = 0x8B2222,
  GRB_SeaGreen = 0x8B2E57,   GRB_DarkSlateGray = 0x4F2F4F,   GRB_DarkSlateGrey = 0x4F2F4F,   GRB_LimeGreen = 0xCD3232,   GRB_MediumSeaGreen = 0xB33C71,   GRB_Turquoise = 0xE040D0,
  GRB_RoyalBlue = 0x6941E1,   GRB_SteelBlue = 0x8246B4,   GRB_DarkSlateBlue = 0x3D488B,   GRB_MediumTurquoise = 0xD148CC,   GRB_Indigo = 0x004B82,   GRB_DarkOliveGreen = 0x6B552F,
  GRB_CadetBlue = 0x9E5FA0,   GRB_CornflowerBlue = 0x9564ED,   GRB_MediumAquamarine = 0xCD66AA,   GRB_DimGray = 0x696969,   GRB_DimGrey = 0x696969,   GRB_SlateBlue = 0x5A6ACD,
  GRB_OliveDrab = 0x8E6B23,   GRB_SlateGray = 0x807090,   GRB_SlateGrey = 0x807090,   GRB_LightSlateGray = 0x887799,   GRB_LightSlateGrey = 0x887799,   GRB_MediumSlateBlue = 0x687BEE,
  GRB_LawnGreen = 0xFC7C00,   GRB_Chartreuse = 0xFF7F00,   GRB_Aquamarine = 0xFF7FD4,   GRB_Maroon = 0x008000,   GRB_Purple = 0x008080,   GRB_Olive = 0x808000,
  GRB_Gray = 0x808080,   GRB_Grey = 0x808080,   GRB_SkyBlue = 0xCE87EB,   GRB_LightSkyBlue = 0xCE87FA,   GRB_BlueViolet = 0x2B8AE2,   GRB_DarkRed = 0x008B00, GRB_KRFDarkDarkRed = 0x000B00,
  GRB_DarkMagenta = 0x008B8B,   GRB_SaddleBrown = 0x458B13,   GRB_DarkSeaGreen = 0xBC8F8F,   GRB_LightGreen = 0xEE9090,   GRB_MediumPurple = 0x7093DB,   GRB_DarkViolet = 0x0094D3,
  GRB_PaleGreen = 0xFB9898,   GRB_DarkOrchid = 0x3299CC,   GRB_Amethyst = 0x6699CC,   GRB_YellowGreen = 0xCD9A32,   GRB_Sienna = 0x52A02D,   GRB_Brown = 0x2AA52A,
  GRB_DarkGray = 0xA9A9A9,   GRB_DarkGrey = 0xA9A9A9,   GRB_LightBlue = 0xD8ADE6,   GRB_GreenYellow = 0xFFAD2F,   GRB_PaleTurquoise = 0xEEAFEE,   GRB_LightSteelBlue = 0xC4B0DE,
  GRB_PowderBlue = 0xE0B0E6,   GRB_FireBrick = 0x22B222,   GRB_DarkGoldenrod = 0x86B80B,   GRB_MediumOrchid = 0x55BAD3,   GRB_RosyBrown = 0x8FBC8F,   GRB_DarkKhaki = 0xB7BD6B,
  GRB_Silver = 0xC0C0C0,   GRB_MediumVioletRed = 0x15C785,   GRB_Plaid = 0x55CC33,   GRB_IndianRed = 0x5CCD5C,   GRB_Peru = 0x85CD3F,   GRB_Chocolate = 0x69D21E,
  GRB_Tan = 0xB4D28C,   GRB_LightGrey = 0xD3D3D3,   GRB_Thistle = 0xBFD8D8,   GRB_Orchid = 0x70DAD6,   GRB_Goldenrod = 0xA5DA20,   GRB_PaleVioletRed = 0x70DB93,
  GRB_Crimson = 0x14DC3C,   GRB_Gainsboro = 0xDCDCDC,   GRB_Plum = 0xA0DDDD,   GRB_BurlyWood = 0xB8DE87,   GRB_LightCyan = 0xFFE0FF,   GRB_Lavender = 0xE6E6FA,
  GRB_DarkSalmon = 0x96E97A,   GRB_Violet = 0x82EEEE,   GRB_PaleGoldenrod = 0xE8EEAA,   GRB_LightCoral = 0x80F080,   GRB_Khaki = 0xE6F08C,   GRB_AliceBlue = 0xF8F0FF,
  GRB_Honeydew = 0xFFF0F0,   GRB_Azure = 0xFFF0FF,   GRB_SandyBrown = 0xA4F460,   GRB_Wheat = 0xDEF5B3,   GRB_Beige = 0xF5F5DC,   GRB_WhiteSmoke = 0xF5F5F5,
  GRB_MintCream = 0xFFF5FA,   GRB_GhostWhite = 0xF8F8FF,   GRB_Salmon = 0x80FA72,   GRB_AntiqueWhite = 0xEBFAD7,   GRB_Linen = 0xF0FAE6,   GRB_LightGoldenrodYellow = 0xFAFAD2,
  GRB_OldLace = 0xF5FDE6,   GRB_Red = 0x00FF00,   GRB_Fuchsia = 0x00FFFF,   GRB_Magenta = 0x00FFFF,   GRB_DeepPink = 0x14FF93,   GRB_OrangeRed = 0x45FF00,
  GRB_Tomato = 0x63FF47,   GRB_HotPink = 0x69FFB4,   GRB_Coral = 0x7FFF50,   GRB_DarkOrange = 0x8CFF00,   GRB_LightSalmon = 0xA0FF7A,   GRB_Orange = 0xA5FF00,
  GRB_LightPink = 0xB6FFC1,   GRB_Pink = 0xC0FFCB,   GRB_Gold = 0xD7FF00,   GRB_PeachPuff = 0xDAFFB9,   GRB_NavajoWhite = 0xDEFFAD,   GRB_Moccasin = 0xE4FFB5,
  GRB_Bisque = 0xE4FFC4,   GRB_MistyRose = 0xE4FFE1,   GRB_BlanchedAlmond = 0xEBFFCD,   GRB_PapayaWhip = 0xEFFFD5,   GRB_LavenderBlush = 0xF0FFF5,   GRB_Seashell = 0xF5FFEE,
  GRB_Cornsilk = 0xF8FFDC,   GRB_LemonChiffon = 0xFAFFCD,   GRB_FloralWhite = 0xFAFFF0,   GRB_Snow = 0xFAFFFA,   GRB_Yellow = 0xFFFF00,   GRB_LightYellow = 0xFFFFE0,
  GRB_Ivory = 0xFFFFF0,   GRB_White = 0xFFFFFF,   GRB_KRFWhite = 0xFF60FF,   GRB_KRFDarkGreen = 0x400000,   GRB_KRFDarkPurple = 0x004040,   GRB_KRFDarkDarkPurple = 0x000810
};

enum { setNone,
       setEven,
       setOdd,
       setBoth };

//#define DEBUG1 1
//#define DEBUG2 2
//#define DEBUG3 3

// For the array of lights 8 wide by 50 high
#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 50

#define NEXT_TO_LAST_ROW (NUM_LEDS_PER_STRIP - 1)

#define TWINKLE_NUM_LIGHTS_ON 150
#define RED_LED 30
#define RANDOM_LOC_MAX 200

#define CYCLE_TIME_LONG 7
#define CYCLE_TIME_SHORT 5

#define ANIMATION_DELAY 100

uint8_t randomRow[RANDOM_LOC_MAX];
uint8_t randomColumn[RANDOM_LOC_MAX];

uint8_t randomPoint1 = TWINKLE_NUM_LIGHTS_ON;
uint8_t randomPoint2 = 0;

bool heartBeat = true;
bool firstPass = true;

char stringDash[] = " - ";


CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CRGB scratchPad[NUM_LEDS_PER_STRIP];


unsigned long diagnosticCount = 1;
unsigned long subProgramIndex = 0; 
unsigned long loopCount = 0;

unsigned long lastTime = 0;


// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  //pinMode(16, OUTPUT);   //Built-in
  Serial.begin(9600);

  // Set-up the arrays of random rows and columns
  for (uint8_t i = 0; i < RANDOM_LOC_MAX; i++) {
    randomRow[i] = random(50);
    randomColumn[i] = random(8);
  }

  // tell FastLED there's 50 NEOPIXEL leds on each pin

  FastLED.addLeds<NEOPIXEL, DATA_PIN_0>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_4>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_5>(leds[5], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_6>(leds[6], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_7>(leds[7], NUM_LEDS_PER_STRIP);
    
}


void loop()
{
  //Serial.println(subProgramIndex);  

  if (firstPass)
  {
    //testPattern3();
    testPattern1();
    testPattern2();

    firstPass = false;
  }
  
   unsigned long time = micros();
   if(subProgramIndex == 0)
   {
    Serial.print("Time: ");
    Serial.println(time - lastTime); //prints time since program started
    lastTime = time;
   }    

  lightProgram(subProgramIndex);

  subProgramIndex++;
  subProgramIndex %= 60;
}

// Repeat this pattern forever
void lightProgram(int subProgramIndex) 
{
  if (subProgramIndex == 0) {
    FastLED.clear();
  }

  // Walk through the different displays in this order
  switch (subProgramIndex) {
    case 0:
      // Test code here so it runs first
      
      //goGreen();
      //swoosh(CYCLE_TIME_LONG, ANIMATION_DELAY);
      //rotateArrayLeft(CYCLE_TIME_LONG*2, ANIMATION_DELAY);

      goGreen();
      horzColorBandsDiag(GRB_KRFDarkGreen, 7, GRB_KRFWhite, 3, 2, CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 1:
      dazzle(GRB_KRFDarkGreen, GRB_KRFDarkDarkPurple, CYCLE_TIME_LONG);
      break;

    case 2:
      garlandWithSlide(GRB_KRFWhite, GRB_DarkRed, GRB_KRFWhite, GRB_DarkRed, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 3:
      rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 4:
      //twinkleLights(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      twinkleLights2(GRB_Blue, GRB_Purple, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      break;

    case 5:
      //Red Strobes
      RainbowSegueVert2(CYCLE_TIME_LONG,50);
      break;
      
    case 6:
      garlandWithSlide(GRB_Blue, GRB_Purple, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 7:
      rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 8:
      twinkleLights2(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      break;

    case 9:
      dazzle(GRB_KRFDarkGreen, GRB_Red, CYCLE_TIME_LONG);
      break;

    case 10:
      garlandWithSlide(GRB_KRFWhite, GRB_DarkRed, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 11:
      rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 12:
      goGreen();
      zigzag(GRB_KRFDarkGreen, GRB_KRFWhite, GRB_KRFDarkDarkPurple, CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      rotateArrayLeft(CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      break;

    case 13:
      goGreen();
      //twinkleLights(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple,CYCLE_TIME_LONG);
      twinkleLights2(GRB_Blue, GRB_KRFWhite, GRB_Blue, GRB_KRFWhite, CYCLE_TIME_LONG);
      break;

    case 14:
      //goGreen();
      horzColorBandsDiag(GRB_KRFDarkGreen, 8, GRB_KRFDarkPurple, 2, 2, CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 15:
      //goGreen();
      dazzle(GRB_KRFDarkGreen, GRB_Blue, CYCLE_TIME_LONG);
      break;

    case 16:
      garlandWithSlide(GRB_KRFWhite, GRB_Blue, GRB_KRFWhite, GRB_Blue, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 17:
      rotateVarySpeed();
      break;

    case 18:
      dazzle(GRB_KRFDarkDarkPurple, GRB_Blue, CYCLE_TIME_LONG);
      break;

    case 19:
      twinkleLights2(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      break;

    case 20:
      dazzle(GRB_KRFWhite, GRB_KRFDarkDarkPurple, CYCLE_TIME_LONG);
      break;

    case 21:
      garlandWithSlide(GRB_Blue, GRB_DarkRed, GRB_Blue, GRB_DarkRed, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 22:
      rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 23:

      marquee(GRB_KRFDarkGreen, GRB_KRFWhite, 70);
      marquee(GRB_KRFDarkGreen, GRB_DarkRed, 70);
      marquee(GRB_KRFDarkGreen, GRB_Purple, 70);
      break;

    case 24:
      goGreen();
      zigzag(GRB_KRFDarkGreen, GRB_KRFWhite, GRB_Blue, CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      rotateArrayLeft(CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      break;

    case 25:
      twinkleLights2(GRB_KRFWhite, GRB_KRFWhite, GRB_Blue, GRB_Blue, CYCLE_TIME_LONG);
      break;

    case 26:
      garlandWithSlide(GRB_KRFWhite, GRB_DarkRed, GRB_KRFWhite, GRB_DarkRed, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 27:
      dazzle(GRB_KRFDarkGreen, GRB_KRFWhite,CYCLE_TIME_LONG);
      break;

    case 28:
      garlandWithSlide(GRB_KRFWhite, GRB_Purple, GRB_KRFWhite, GRB_Purple, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;
      
    case 29:
      //        rotateVarySpeed();
      break;

    case 30:
      //        ////RainbowSegueHorz(CYCLE_TIME_LONG,ANIMATION_DELAY*2,2);
      break;

    case 31:
      twinkleLights2(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      break;

    case 32:
      horzColorBandsDiag(GRB_KRFDarkGreen, 4, GRB_LightSeaGreen, 4, 2, CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 33:
      //dazzle(GRB_Blue, GRB_KRFWhite, CYCLE_TIME_LONG);
      break;

    case 34:
      //goGreen();
      horzColorBandsDiag(GRB_KRFDarkGreen, 8, GRB_Yellow, 2, 2, CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 35:
      goGreen();
      zigzag(GRB_KRFDarkGreen, GRB_KRFWhite, GRB_Lime, CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      rotateArrayLeft(CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      break;

    case 36:
      garlandWithSlide(GRB_KRFWhite, GRB_Yellow, GRB_KRFWhite, GRB_Yellow, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 37:
      garlandWithSlide(GRB_KRFWhite, GRB_Yellow, GRB_KRFWhite, GRB_Yellow, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 38:
      garlandWithSlide(GRB_KRFWhite, GRB_Yellow, GRB_KRFWhite, GRB_Yellow, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 39:
      garlandWithSlide(GRB_KRFWhite, GRB_Yellow, GRB_KRFWhite, GRB_Yellow, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 40:
      //        rotateVarySpeed();
      break;

    case 41:
      goGreen();
      //twinkleLights(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      twinkleLights2(GRB_Red, GRB_Purple,GRB_Red, GRB_Purple, CYCLE_TIME_LONG);
      break;
      
    case 42:
      //goGreen();
      ///////dazzle(GRB_Blue, GRB_Red,CYCLE_TIME_LONG);
      break;

    case 43:
      garlandWithSlide(GRB_KRFWhite, GRB_Blue, GRB_KRFWhite, GRB_Blue, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 44:
      //goGreen();
      //dazzle(GRB_DarkRed, GRB_KRFWhite, CYCLE_TIME_LONG);
      break;


    case 45:
      //goGreen();
      //dazzle(GRB_DarkRed, GRB_Teal, CYCLE_TIME_LONG);
      break;

    case 46:
      //goGreen();
      twinkleLights2(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG);
      break;

    case 47:
      goGreen();
      zigzag(GRB_KRFDarkGreen, GRB_KRFWhite, GRB_DarkRed, CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      rotateArrayLeft(CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      break;

    case 48:
      //goGreen();
      garlandWithSlide(GRB_KRFWhite, GRB_Purple, GRB_KRFWhite, GRB_Purple, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 49:
      dazzle(GRB_DarkRed, GRB_Teal, CYCLE_TIME_LONG);
      break;

    case 50:
      //twinkleLights(GRB_Red, GRB_Yellow, GRB_Blue, GRB_Purple,CYCLE_TIME_LONG);
      twinkleLights2(GRB_KRFWhite,GRB_KRFWhite,GRB_KRFWhite,GRB_KRFWhite, CYCLE_TIME_LONG);
      break;

    case 51:
      garlandWithSlide(GRB_KRFWhite, GRB_Yellow, GRB_KRFWhite, GRB_Yellow, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 52:
      //        rotateVarySpeed();
      break;

    case 53:
      garlandWithSlide(GRB_KRFWhite, GRB_DarkRed, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 54:
      RainbowSegueVert(CYCLE_TIME_LONG,ANIMATION_DELAY*2);
      break;

    case 55:
      garlandWithSlide(GRB_Blue, GRB_Purple, GRB_Blue, GRB_Purple, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 56:
      rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 57:
      garland(GRB_Blue, GRB_Lime, GRB_Blue, GRB_Lime, true, true);
      garlandWithSlide(GRB_Blue, GRB_Lime, GRB_Blue, GRB_Lime, CYCLE_TIME_LONG, ANIMATION_DELAY*2);
      break;

    case 58:
      rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
      break;

    case 59:
      //spiral2(scratchPad, CYCLE_TIME_SHORT, 2);
      break;
   
    case 60:
      goGreen();
      zigzag(GRB_KRFDarkGreen, GRB_KRFWhite, GRB_Purple, CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      rotateArrayLeft(CYCLE_TIME_LONG*2, ANIMATION_DELAY);
      break;
    
    default:
      break;
  }
 
  return;
}


void marquee(int color0, int color1, unsigned long timeInSec)
{
  
  for (int col = 0; col < NUM_STRIPS; col++) {
      for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) 
      {
        // for columns 0 and 4, use "accent" color, otherwise background color
        if(col % 4 == 0)
          leds[col][row] = color1;
        else
          leds[col][row] = color0;
      }
  }

  rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
  
}

void marquee2(int color0, int color1, unsigned long timeInSec)
{
  
  for (int col = 0; col < NUM_STRIPS; col++) {
      for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) 
      {
        if(col % 4 == 0 && row % 2 == 0)
          leds[col][row] = color1;
        else
          leds[col][row] = color0;
      }
  }

  rotateArrayLeft(CYCLE_TIME_LONG, ANIMATION_DELAY);
  
}




void garlandWithSlide(CRGB color0, CRGB color1, CRGB color2, CRGB color3, unsigned long timeInSec, int msecDelay) {
  //Serial.println(101);
  garland(color0, color1, color2, color3, true, true);
  //garlandSlide(color0, color1, color2, color3, timeInSec, msecDelay);

  rotateArrayLeft(timeInSec, msecDelay);
}
void zigzag(CRGB color0, CRGB color1, CRGB color2, unsigned long timeInSec, int msecDelay)
{
  // 3 color Pattern 
  int zigzags[16][8] = 
    {
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,2,0,0,0},
    {0,0,0,1,2,1,0,0},
    {0,0,0,2,2,2,1,0},
    {0,0,1,2,2,2,2,0},
    {0,0,2,2,1,2,2,0},
    {0,1,2,2,0,2,2,1},
    {0,2,2,1,0,1,2,2},
    {1,2,2,0,0,0,1,2},
    {2,2,1,0,0,0,0,2},
    {2,2,0,0,0,0,0,2},
    {2,1,0,0,0,0,0,1},
    {2,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
    };

  int loopCount = 0;
  unsigned long exitTime = millis() + timeInSec * 1000L;

  
  for(int n = 0; n < 96; n++)
  {
    rotateDownOneRow();
    
	  for (int col = 0; col < NUM_STRIPS; col++)
    {
      
      if( 0 == zigzags[loopCount%16][col])
        leds[col][ NUM_LEDS_PER_STRIP-1] = color0;
      else if( 1 == zigzags[loopCount%16][col])
        leds[col][ NUM_LEDS_PER_STRIP-1] = color1;
      else if( 2 == zigzags[loopCount%16][col])
        leds[col][ NUM_LEDS_PER_STRIP-1] = color2;
 
    }
    
	//Serial.println("rotateDown - in");
    FastLED.show();
    //Serial.println("rotateDown - out");
    delay(msecDelay);

    loopCount++;
  }

  // Bounce the zigzabs
  /*
  for(int bounce = 0; bounce < 10; bounce++)
  {
      rotateDownOneRow();
      rotateDownOneRow();
      rotateDownOneRow();
      rotateDownOneRow();
        FastLED.show();
      delay(msecDelay);
      delay(msecDelay);
      delay(msecDelay);
      rotateUpOneRow();
      rotateUpOneRow();
      rotateUpOneRow();
      rotateUpOneRow();
        FastLED.show();
      delay(msecDelay);
      delay(msecDelay);
      delay(msecDelay);

  }
  */
  return;
}



void swoosh(unsigned long timeInSec, int msecDelay)
{
int swooshMap[25][8] =
{  {1,1,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,1,1,1,1,0,0,0},
  {1,1,1,1,1,1,0,0},
  {1,1,1,1,1,1,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,1,1},
  {0,0,0,1,1,1,1,1},
  {0,0,0,0,1,1,1,1},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,0,1,1},
  {0,0,0,0,0,0,1,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1}
};

  int loopCount = 0;
  unsigned long exitTime = millis() + timeInSec * 1000L;
  
  for(int n = 0; n < 50; n++)
  {
    rotateDownOneRow();
    
	  for (int col = 0; col < NUM_STRIPS; col++)
    {
      
      if( 0 == swooshMap[loopCount%25][col])
        leds[col][ NUM_LEDS_PER_STRIP-1] = GRB_KRFDarkGreen;
      else
        leds[col][ NUM_LEDS_PER_STRIP-1] = GRB_KRFWhite;

 
    }
    
	//Serial.println("rotateDown - in");
    FastLED.show();
    //Serial.println("rotateDown - out");
    delay(msecDelay);

    loopCount++;
  }

  return;
}




void icicles(CRGB color0, unsigned long timeInSec, int msecDelay) {
  //Serial.println(101);
  for (int col = 0; col < NUM_STRIPS; col++) {
      for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) 
      {
        if(col % 2 == 0)
          if(row % 10 < 6)
            leds[col][row] = GRB_KRFDarkGreen;
          else
            leds[col][row] = color0;
        else
          leds[col][row] = GRB_KRFDarkGreen;

      }
  }

  rotateDown(timeInSec, msecDelay);
}


void horzColorBandsDiag(CRGB color1, int rows1, CRGB color2, int rows2, int diagCount, unsigned long timeInSec, int msecDelay) {
  //Serial.println(102);
  setHorzColorBands(color1, rows1, color2, rows2);
  diagonalize(diagCount);
  rotateDown(timeInSec, msecDelay);
  return;
}

void toggleHeartBeat(void) {
  heartBeat = !heartBeat;
  digitalWrite(RED_LED, (heartBeat ? HIGH : LOW));
  return;
}


void rotateVarySpeed(void) {
  ////Serial.println("rotateVarySpeed");
  //  wdt_reset();

  rotateArrayLeft(CYCLE_TIME_SHORT, 100);
  //wdt_reset();

  rotateArrayLeft(CYCLE_TIME_SHORT, 50);
  //wdt_reset();

  rotateArrayLeft(CYCLE_TIME_SHORT, 100);
  //wdt_reset();

  rotateArrayLeft(CYCLE_TIME_SHORT, 50);
  //wdt_reset();

  return;
}



////
////
//// void rotateDown(int msecDelay)
////
//// Slide the colors down repeatedly
////
void rotateDown(unsigned long timeInSec, int msecDelay) {
  //Serial.println("rotateDown");
  int loopCount = 0;


  unsigned long exitTime = millis() + timeInSec * 1000L;

  while (millis() < exitTime) {
    rotateDownOneRow();
    //Serial.println("rotateDown - in");
    FastLED.show();
    //Serial.println("rotateDown - out");
    delay(msecDelay);

    loopCount++;
  }
  return;
}


////
////
//// void rotateDownOneRow()
////
//// Save the bottom row, slide the rows down, reset to top row from the saved bottom
////

void rotateDownOneRow() {
  //Serial.println("rotateDownOneRow");
  int col;

  // Save the current Bottom Row
  for (col = 0; col < NUM_STRIPS; col++) {
    scratchPad[col] = leds[col][0];
  }

  // Slide everything down, old bottom goes to the top
  shiftAllRowsDown();
  setTopColor(scratchPad, setBoth);

  return;
}

void rotateUpOneRow() {
  //Serial.println("rotateDownOneRow");
  int col;

  // Save the current Bottom Row
  for (col = 0; col < NUM_STRIPS; col++) {
    scratchPad[col] = leds[col][NEXT_TO_LAST_ROW];
  }

  // Slide everything down, old bottom goes to the top
  shiftAllRowsUp();
  setBottomColor(scratchPad, setBoth);

  return;
}




////
//// void rotateArrayLeft(int rotateCount, int msecDelay);
////
//// Rotate column into the next column with wrap
////

void rotateArrayLeft(unsigned long timeInSec, int msecDelay) {
  //Serial.println("rotateArrayLeft");

  unsigned long exitTime = millis() + timeInSec * 1000L;
  int loopCount = 0;

  // Now slide it up
  while (millis() < exitTime) {
    // Save existing column 0
    for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) {
      scratchPad[row] = leds[0][row];
      //Serial.println( scratchPad[row]);
    }

    slideColLeft();
    setColorLeft(scratchPad);

    //Serial.println("rotateArrayLeft - in");
    FastLED.show();
    //Serial.println("rotateArrayLeft - out");

    delay(msecDelay);
    loopCount++;
  }
  return;
}


////
////
//// void setHorzColorBands(CRGB color1, CRGB color2, int width1, int width2, int evenOdd)
////
////
////

void setHorzColorBands(CRGB color1, int width1, CRGB color2, int width2)
{
  ////Serial.println("setHorzColorBands");
  int col;
  int totalRowsSet = 0;
  int loopCount = 0;

  do {
    for (col = 0; col < width1; col++) {
      shiftAllRowsDown();
      setTopColor(color1, setBoth);
    }

    for (col = 0; col < width2; col++) {
      shiftAllRowsDown();
      setTopColor(color2, setBoth);
    }
    loopCount++;

  } while (totalRowsSet++ < NUM_LEDS_PER_STRIP);

  //Serial.println("SetHorzColorBands - in");
  FastLED.show();
  //Serial.println("SetHorzColorBands - out");


  delay(100);
  return;
}



////
////
//// void setVertColorBands(CRGB color[]);
////
////
////
void setVertColorBands(CRGB color[]) {
  ////Serial.println("setVertColorBands");
  for (int col = 0; col < NUM_STRIPS; col++) {
    for (int row = 0; row < 50; row++) {
      leds[col][row] = color[col];
    }
  }
  return;
}



void goWhite() {
  setHorzColorBands(GRB_KRFWhite, 5, GRB_KRFWhite, 5);
  return;
}

void goGreen() {
  setHorzColorBands(GRB_DarkGreen, 5, GRB_DarkGreen, 5);
  return;
}

void goBlue() {
  setHorzColorBands(GRB_DarkBlue, 5, GRB_DarkBlue, 5);
  return;
}

void goRed() {
  setHorzColorBands(GRB_DarkRed, 5, GRB_DarkRed, 5);
  return;
}

void goBlack() {
  setHorzColorBands(GRB_Black, 5, GRB_Black, 5);
  return;
}

void garland(CRGB color0, CRGB color1, CRGB color2, CRGB color3, bool clearToGreen, bool slideUp) {
  //Serial.println(103);
  // Do a zig-zag garland from top to bottom, then slide it up
  int col;

  CRGB color;

  // Do I want to repaint the tree all green before I start?
  if (clearToGreen) {
    //Serial.println(104);
    setHorzColorBands(GRB_Green, 5, GRB_DarkGreen, 5);
    //Serial.println(105);
  }

  // Turn on a string of lights from top to bottom
  for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) {
    switch (row % 4) {
      case 0:
        color = color0;
        break;
      case 1:
        color = color1;
        break;
      case 2:
        color = color2;
        break;
      case 3:
        color = color3;
        break;
      default:
        break;
    }

    col = row % 8;
    leds[col][NEXT_TO_LAST_ROW - row] = color;
  }
  return;
}


void garlandSlide(CRGB color0, CRGB color1, CRGB color2, CRGB color3, long int timeInSec, int msecDelay) {
  //Serial.println(106);
  int row;
  int col;
  int k;

  CRGB dummy;

  unsigned long exitTime = millis() + timeInSec * 1000L;
  int loopCount = 0;

  while (millis() < exitTime) {
    for (col = 0; col < NUM_STRIPS; col++) {
      for (row = 0; row < NUM_LEDS_PER_STRIP; row++) {
        //Serial.print(row); Serial.print(" "); Serial.println(col);

        if (leds[col][row] == color0)
          leds[col][row] = color1;
        else if (leds[col][row] == color1)
          leds[col][row] = color2;
        else if (leds[col][row] == color2)
          leds[col][row] = color3;
        else if (leds[col][row] == color3)
          leds[col][row] = color0;
      }
    }
    //Serial.println(107);

    //Serial.println("GarlandSlide - in");

    FastLED.show();
    //Serial.println("GarlandSlide - out");

    delay(msecDelay);
    //Serial.println(108);
    loopCount++;
  }
  //Serial.println(108);
  return;
}


void newGarland(int color1, int color0, unsigned long timeInSec, int msecDelay)
{
    unsigned long exitTime = millis() + timeInSec * 1000L;
    int loopCount = 0;

    while (millis() < exitTime) 
    {
        for (int col = 0; col < NUM_STRIPS; col++) {
            for (int row = 0; row < NUM_LEDS_PER_STRIP - 10; row++) 
            {
            }
        }
        FastLED.show();
        delay(msecDelay);
    }
}
  

//====================================

//void setColColorRight(int col, CRGB color[])
//{
//  for(int row = 0; row < NUM_LEDS_PER_STRIP; row++)
//  {
//     if(isOdd(row))
//     {
//       leds[col][row+1] = color[row];
//     }
//  }
//}

//void setColColorLeft(int col, CRGB color[])
//{
//  for(int row = 0; row < NUM_LEDS_PER_STRIP; row++)
//  {
//     if(isEven(row))
//     {
//       leds[col][row] = color[row];
//     }
//  }
//}

////
////
//// void setColColorRight(int col, CRGB color)
////
//// For the given column, set the odd numbered bulbs to the color
////
//void setColColorRight(int col, CRGB color)
//{
//  for(int row = 0; row < NUM_LEDS_PER_STRIP; row++)
//  {
//     if(isOdd(row))
//     {
//       leds[col][row] = color;
//     }
//  }
//}

////
////
//// void setColColorLeft(int col, CRGB color)
////
//// For the given column, set the even numbered bulbs to the color
////
//void setColColorLeft(int col, CRGB color)
//{
//  for(int row = 0; row < NUM_LEDS_PER_STRIP; row++)
//  {
//     if(isEven(row))
//     {
//       leds[col][row] = color;
//     }
//  }
//}
//






////
////
//// void shiftAllRowsDown()
////
////  Set the color in each cell in a row to the color of the cell above it.
////
void shiftAllRowsDown(void) {
  //Serial.println("shiftAllD");

  for (int row = 0; row < NEXT_TO_LAST_ROW; row++)  // Loop the rows
  {
    for (int col = 0; col < NUM_STRIPS; col++)  // Loop the columns
    {
      //Serial.print(row); Serial.print(" "),Serial.println(col);
      leds[col][row] = leds[col][row + 1];
    }
  }
  //Serial.println("shiftAllDone");
  return;
}
void shiftAllRowsUp(void) {
  //Serial.println("shiftAllD");

  for (int row = NEXT_TO_LAST_ROW; 0 < row; row--)  // Loop the rows
  {
    for (int col = 0; col < NUM_STRIPS; col++)  // Loop the columns
    {
      //Serial.print(row); Serial.print(" "),Serial.println(col);
      leds[col][row] = leds[col][row - 1];
    }
  }
  //Serial.println("shiftAllDone");
  return;
}


void setTopColor(CRGB color, int evenOdd) {

  //Serial.println("setTopC");
  for (int col = 0; col < NUM_STRIPS; col++) {
    //Serial.println(col);
    //   if( (isEven(col) && (evenOdd & setEven)) || (isOdd(col) && (evenOdd & setOdd)) )
    leds[col][NEXT_TO_LAST_ROW] = color;
  }
  //Serial.println("setTopCDone");
  return;
}

void setTopColor(CRGB color[], int evenOdd) {
  //Serial.println("setTopC[]");

  for (int col = 0; col < NUM_STRIPS; col++) {
    if ((isEven(col) && (evenOdd & setEven)) || (isOdd(col) && (evenOdd & setOdd)))
      leds[col][NEXT_TO_LAST_ROW] = color[col];
  }
  //Serial.println("setTopC[]Done");
  return;
}

void setBottomColor(CRGB color[], int evenOdd) {
  //Serial.println("setTopC[]");

  for (int col = 0; col < NUM_STRIPS; col++) {
    if ((isEven(col) && (evenOdd & setEven)) || (isOdd(col) && (evenOdd & setOdd)))
      leds[col][0] = color[col];
  }
  //Serial.println("setTopC[]Done");
  return;
}



////
////
////  void slideColLeft()
////
////  Move colors from column n+1 to column n
////

void slideColLeft() {
  // Loop the columns
  for (int col = 0; col < NUM_STRIPS - 1; col++) {
    //Loop the rows

    // This inner loop will go over each led in the current strip, one at a time
    for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) {
      leds[col][row] = leds[col + 1][row];
    }
  }
  return;
}


////
////
////  void setColorLeft(CRGB color)
////
////  Set the odd numberd bulbs on the high numbered column to the color
////
////


void setColorLeft(CRGB color) {

  for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) {
    leds[NUM_STRIPS - 1][row] = color;
  }
  return;
}

void setColorLeft(CRGB color[]) {
  for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) {
    leds[NUM_STRIPS - 1][row] = color[row];
  }
  return;
}



////
////
//// void twinkleLights(CRGB color0, CRGB color1, CRGB color2, CRGB color3, unsigned long timeInSec)
////
//// Paint the tree green, then randomly turn lights off and on.
////
void twinkleLights(CRGB color0, CRGB color1, CRGB color2, CRGB color3, unsigned long timeInSec) {
  ////Serial.println("twinkleLights");
  unsigned long exitTime = millis() + timeInSec * 1000L;

  uint8_t row;
  uint8_t col;

  CRGB currentColor;

  // First, set the tree all green
  setHorzColorBands(GRB_Green, 5, GRB_DarkGreen, 5);


  int loopCount = 0;
  while (millis() < exitTime) {
    // There are two pointers into the array of random numbers.
    // randomPoint1 is the next light to be turned on. Starts at TWINKLE_NUM_LIGHTS_ON
    // randomPoint2 trails randomPoint1 by TWINKLE_NUM_LIGHTS_ON. Starts at 0;

    // Next Light to turn off
    row = randomRow[randomPoint2];
    col = randomColumn[randomPoint2];

    leds[col][row] = GRB_Green;

    // Next Light to turn on
    int8_t row = randomRow[randomPoint1];
    int8_t column = randomColumn[randomPoint1];

    
    // Pick a color in rotation
    switch (loopCount % 4) {
      case 0:
        currentColor = color0;
        break;
      case 1:
        currentColor = color1;
        break;
      case 2:
        currentColor = color2;
        break;
      case 3:
        currentColor = color3;
        break;
      default:
        break;
    }

    leds[col][row] = currentColor;

    //advance and rollover
    randomPoint1++;
    randomPoint1 %= RANDOM_LOC_MAX;

    randomPoint2++;
    randomPoint2 %= RANDOM_LOC_MAX;

    // Set up all the light before displaying
    if (TWINKLE_NUM_LIGHTS_ON < loopCount) {
      //Serial.println("TwinkleLights - in");
      FastLED.show();
      //Serial.println("TwinkleLights - out");
      delay(5);
    }

    loopCount++;
  }

  return;
}


// Paint the tree green, then randomly turn lights off and on.
void twinkleLights2(CRGB color0, CRGB color1, CRGB color2, CRGB color3, unsigned long timeInSec) {
  //Serial.println("tL2");

  uint8_t row;
  uint8_t col;

  CRGB randomColor0;
  CRGB randomColor1;

  unsigned long exitTime = millis() + timeInSec * 1000L;

  // First, set the tree all green
  setHorzColorBands(GRB_Green, 5, GRB_DarkGreen, 5);
  //Serial.println("tL2PG");
  int loopCount = 0;
  while (millis() < exitTime) {
    //Serial.println(loopCount);

    // Set the colors
    switch (loopCount % 6) {
      case 0:
        randomColor0 = color0;
        randomColor1 = color1;
        break;
      case 1:
        randomColor0 = color2;
        randomColor1 = color3;
        break;
      case 2:
        randomColor0 = color0;
        randomColor1 = color2;
        break;
      case 3:
        randomColor0 = color1;
        randomColor1 = color3;
        break;
      case 4:
        randomColor0 = color0;
        randomColor1 = color3;
      case 5:
        randomColor0 = color1;
        randomColor1 = color2;
        break;
      default:
        break;
    }

    setTopColor(GRB_DarkGreen, setBoth);


    // Next Light to turn off
    col = random(8);
    leds[col][49] = randomColor0;

    col = random(8);
    leds[col][49] = randomColor1;

    rotateDownOneRow();

    //Serial.println("TwinkleLights2 - in");
    FastLED.show();
    //Serial.println("TwinkleLights2 - out");
    delay(50);

    loopCount++;

    //wdt_reset();

    if (loopCount % 20) {
      //Serial.println(loopCount);
    }
  }
  //Serial.println("tL2Done");
  return;
}



////
////
//// void testPattern1(void)
////
//// Turn on a single light running up each strip

void testPattern1(void) {
  int row;
  int col;

  long unsigned int colorPalate[] = { GRB_Green, GRB_Red, GRB_Blue, GRB_Purple, GRB_Yellow, GRB_KRFWhite, GRB_Cyan, GRB_Green };

  // Loop the columns, Loop the rows

  for (col = 0; col < NUM_STRIPS; col++) {
    for (row = 0; row < NUM_LEDS_PER_STRIP; row++) {
      leds[col][row] = colorPalate[col];  //GRB_Green;                     /// This is displaying Green
      FastLED.show();
      delay(10);
      leds[col][row] = GRB_Black;
    }
  }
  //Serial.println("TestPattern - in2");
  FastLED.show();  // Clear the last bulb
  //Serial.println("TestPattern - our2");
}

void testPattern2(void) {
  int row;
  int col;

  long unsigned int colorPalate[] = { GRB_Green, GRB_Red, GRB_Blue, GRB_Purple, GRB_Yellow, GRB_KRFWhite, GRB_Cyan, GRB_Green };

  // Loop the columns, Loop the rows

  for (row = 0; row < NUM_LEDS_PER_STRIP; row++) {
    for (col = 0; col < NUM_STRIPS; col++) {
      leds[col][row] = colorPalate[col];  //GRB_Green;                     /// This is displaying Green
      FastLED.show();
      delay(10);
    }
  }
  //Serial.println("TestPattern - in2");
  FastLED.show();  // Clear the last bulb
  //Serial.println("TestPattern - our2");
}

void testPattern3(void) {
  int reps;
  int reps2;
  int row;
  int col;
  int test;
  int test2;
  long unsigned int color1;
  long unsigned int color2;
  long unsigned int color;

  long unsigned int colorPalate[] = { GRB_Green, GRB_Red, GRB_Blue, GRB_Purple, GRB_Yellow, GRB_KRFWhite, GRB_Cyan, GRB_Green };

  // Loop the columns, Loop the rows
for (reps2 = 0; reps2 < 7; reps2++) 
{
  color1 = colorPalate[reps2];
  color2 = colorPalate[reps2+1];

  for (reps = 0; reps < 200; reps++) 
  {
    for (row = 0; row < NUM_LEDS_PER_STRIP; row++) 
    {
      for (col = 0; col < NUM_STRIPS; col++) 
      {
        test = (reps + row + col) % 8;
        if (test == 0 || test == 1 || test == 2)
          color = color1;
        else
          color = color2;  

        leds[col][row] = color;  //GRB_Green;                     /// This is displaying Green
      }
    }
    FastLED.show();
    delay(80);
  }
}
  //Serial.println("TestPattern - in2");
  //  FastLED.show();  // Clear the last bulb
  //Serial.println("TestPattern - our2");
}




bool isOdd(int testValue) {
  return (testValue % 2 == 1);
}
bool isEven(int testValue) {
  return !isOdd(testValue);
}

void diagonalize(int offset) {
  int workingOffset;

  for (int col = 0; col < NUM_STRIPS; col++) {
    workingOffset = (col * offset) % NUM_LEDS_PER_STRIP;
    slideColDown(col, workingOffset);
  }
}

void diagonalize2(int offset) {
  int workingOffset;

  for (int row = 0; row < NUM_LEDS_PER_STRIP; row++) {
    workingOffset = (row * offset) % NUM_STRIPS;
    slideRowLeft(row, workingOffset);
  }
}



////
////
//// void slideColDown(int col, int numRows)
////
//// Slice the given column down n Rows by calling SlideColDownOne() n times
////
void slideColDown(int col, int numRows) {
  for (int rowCount = 0; rowCount < numRows; rowCount++) {
    slideColDownOne(col);
  }
}


////
////
//// void slideColDownOne(int col)
////
//// Slice the given column down 1 Row
////
void slideColDownOne(int col) {
  CRGB temp;
  temp = leds[col][0];
  for (int row = 0; row < NUM_LEDS_PER_STRIP - 1; row++) {
    leds[col][row] = leds[col][row + 1];
  }
  leds[col][NUM_LEDS_PER_STRIP - 1] = temp;
}

////
////
//// void slideRowLeft(int row, int numCols)
////
//// Slice the given column down n Rows by calling SlideColDownOne() n times
////
void slideRowLeft(int row, int numCols) {
  for (int colCount = 0; colCount < numCols; colCount++) {
    slideRowLeftOne(row);
  }
}


////
////
//// void slideRowLeftOne(int row)
////
//// Slice the given column down 1 Row
////
void slideRowLeftOne(int row) {
  CRGB temp;
  temp = leds[0][row];
  for (int col = 0; col < NUM_STRIPS - 1; col++) {
    leds[col][row] = leds[col + 1][row];
  }
  leds[NUM_STRIPS - 1][row] = temp;
}



/////////////////////////////  Fromn small tree

void RainbowSegueVert(unsigned long timeInSec, int msecDelay)
{
 //////Serial.println("RainbowSegueVert");
 unsigned long exitTime = millis() + timeInSec * 1000L;

 int hue0 = 0;
 int hue1 = hue0 + 25;
 int hue2 = hue1 + 25;
 int hue3 = hue2 + 25;
 int hue4 = hue3 + 25;
 int hue5 = hue4 + 25;
 int hue6 = hue5 + 25;
 int hue7 = hue6 + 25;
 bool oddEven = true;

 int loopCount = 0;
 while( millis() < exitTime)
 {
   for(int row = 0; row < 50; row++)
   {
       leds[0][row] = CHSV( hue0, 255, 255);
       leds[1][row] = CHSV( hue1, 255, 255);
       leds[2][row] = CHSV( hue2, 255, 255);
       leds[3][row] = CHSV( hue3, 255, 255);
       leds[4][row] = CHSV( hue4, 255, 255);
       leds[5][row] = CHSV( hue5, 255, 255);
       leds[6][row] = CHSV( hue6, 255, 255);
       leds[7][row] = CHSV( hue7, 255, 255);

   }
   FastLED.show();
   delay(msecDelay);

   hue0 = hue1;
   hue1 = hue2;
   hue2 = hue3;
   hue3 = hue4;
   hue4 = hue5;
   hue5 = hue6;
   hue6 = hue7;
   hue7 = (hue7 + 10) % 255 ;

   loopCount++;
 }
 return;
}

void RainbowSegueVert2(unsigned long timeInSec, int msecDelay)
{
 //////Serial.println("RainbowSegueVert2");
 unsigned long exitTime = millis() + timeInSec * 1000L;

 int hue0 = 0;
 int hue1 = hue0 + 5;
 int hue2 = hue1 + 5;
 int hue3 = hue2 + 5;
 int hue4 = hue3 + 5;
 int hue5 = hue4 + 5;
 int hue6 = hue5 + 5;
 int hue7 = hue6 + 5;

 int loopCount = 0;
 while( millis() < exitTime)
 {
   for(int row = 0; row < 50; row++)
   {
       leds[0][row] = CHSV( hue0, 255, 255);
       leds[1][row] = CHSV( hue1, 255, 255);
       leds[2][row] = CHSV( hue2, 255, 255);
       leds[3][row] = CHSV( hue3, 255, 255);
       leds[4][row] = CHSV( hue4, 255, 255);
       leds[5][row] = CHSV( hue5, 255, 255);
       leds[6][row] = CHSV( hue6, 255, 255);
       leds[7][row] = CHSV( hue7, 255, 255);

   }
   FastLED.show();
   delay(msecDelay);

   hue0 = hue1;
   hue1 = hue2;
   hue2 = hue3;
   hue3 = hue4;
   hue4 = hue5;
   hue5 = hue6;
   hue6 = hue7;
   hue7 = (hue7 + 5) % 255 ;

   loopCount++;

 }
 return;

}





void RainbowSegueHorz(unsigned long timeInSec, int msecDelay, int diag)
{
 //////Serial.println("RainbowSegueHorz");
 unsigned long exitTime = millis() + timeInSec * 1000L;

 int hue0 = 0;  // base color for each rep
 int hue1 = 0;
 int loopCount = 0;
 while( millis() < exitTime)
 {
   for(int col =0; col < 8; col++)
   {
     hue1 = hue0;
     for(int row = 0; row < 50; row++)
     {
       leds[col][row] = CHSV( hue1, 255, 255);
       hue1 = (hue1 + 10)%255;
     }
   }
   hue0 =  (hue0 + 10)%255;

   diagonalize(diag);

   FastLED.show();
   delay(msecDelay);

   loopCount++;
 }
 return;
}


void dazzle(CRGB color0, CRGB color1, unsigned long timeInSec) {
  ////Serial.println("dazzle");
  horzColorBandsDiag(color0, 2, color1, 2, 2, timeInSec, 100);
  return;
}



// void CandyCane(uint16_t countMax) 
// {
//     int hue0 = 0;
//     int hue1 = hue0 + 5;
//     int hue2 = hue1 + 5;
//     int hue3 = hue2 + 5;
//     int hue4 = hue3 + 5;
//     int hue5 = hue4 + 5;
//     int hue6 = hue5 + 5;
//     int hue7 = hue6 + 5;


//    for(int loops = 0; loops < countMax; loops++)
//    {
//      for(int row = 0; row < 50; row++)
//      {
//        leds[0][row] = CHSV( hue0, 255, 255);
//        leds[1][row] = CHSV( hue1, 255, 255);
//        leds[2][row] = CHSV( hue2, 255, 255);
//        leds[3][row] = CHSV( hue3, 255, 255);
//        leds[4][row] = CHSV( hue4, 255, 255);
//        leds[5][row] = CHSV( hue5, 255, 255);
//        leds[6][row] = CHSV( hue6, 255, 255);
//        leds[7][row] = CHSV( hue7, 255, 255);
  
//        if(row < 6)
//        else if (row < 12)
//        else if (row < 18)
//        else if (row < 24)
//        else if (row < 30)
//        else if (row < 36)
//        else if (row < 42)
//        else
//          leds[0][row] = CHSV( hue0, 255, 255);
//          leds[1][row] = CHSV( hue1, 255, 255);
//          leds[2][row] = CHSV( hue2, 255, 255);
//          leds[3][row] = CHSV( hue3, 255, 255);
//          leds[4][row] = CHSV( hue4, 255, 255);
//          leds[5][row] = CHSV( hue5, 255, 255);
//          leds[6][row] = CHSV( hue6, 255, 255);
//          leds[7][row] = CHSV( hue7, 255, 255);
  
//      }
//      FastLED.show();
//      delay(ANIMATION_DELAY*2);
  
  
//    }
//   return;
// }


void spiral(CRGB color[], unsigned long timeInSec, int msecDelay)
{
 ////Serial.println("spiral[]");
 FastLED.clear();

     spiral(GRB_DarkGreen, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     spiral(GRB_Magenta, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     spiral(GRB_KRFWhite, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     spiral(GRB_Navy, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     spiral(GRB_Teal, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

}

void spiral2(CRGB color[], unsigned long timeInSec, int msecDelay)
{
 ////Serial.println("spiral2[]");
 FastLED.clear();

     mirrorSpiral(GRB_DarkGreen, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     mirrorSpiral(GRB_Magenta, timeInSec, msecDelay);
    // wdt_reset();                    // Reset the watchdog

     mirrorSpiral(GRB_KRFWhite, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     mirrorSpiral(GRB_Navy, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog

     mirrorSpiral(GRB_Teal, timeInSec, msecDelay);
     //wdt_reset();                    // Reset the watchdog


}


void spiral(CRGB color, unsigned long timeInSec, int msecDelay)
{
 ////Serial.println("spiral");
 int i;
 int col;
 unsigned long exitTime = millis() + timeInSec * 1000L;
//  while( millis() < exitTime)
//  {

   //wdt_reset();                    // Reset the watchdog
   FastLED.clear();


   //Loop 1  --- Col 0, Row 49, Col 7, Row 0
   for(i=0; i < 50; i++)
   {
     leds[0][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=1;col < 8; col++)
   {
     leds[col][49] = color;
     leds[col][48] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(i=48; -1 < i; i--)
   {
     leds[7][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=6; 0 < col; col--)
   {
     leds[col][0] = color;
     leds[col][1] = color;
     FastLED.show();
     delay(msecDelay);
   }




   //Loop 2  --- Col 1, Row 48, Col 6, Row 1
   for(i=2; i < 48; i++)
   {
     leds[1][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=2; col < 7; col++)
   {
     leds[col][47] = color;
     leds[col][46] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(i=48; 0 < i; i--)
   {
     leds[6][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=5; 1 < col; col--)
   {
     leds[col][2] = color;
     leds[col][3] = color;
     FastLED.show();
     delay(msecDelay);
   }



   //Loop 3  --- Col 2, Row 47, Col 5, Row 2
   for(i=4; i < 46; i++)
   {
     leds[2][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=3;col < 6; col++)
   {
     leds[col][45] = color;
     leds[col][44] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(i=48; -1 < i; i--)
   {
     leds[5][i] = color;
   FastLED.show();
   delay(msecDelay);
   }
   for(col=6; 0 < col; col--)
   {
     leds[col][4] = color;
     leds[col][5] = color;
   FastLED.show();
   delay(msecDelay);
   }



   //Loop 4  --- Col 3, Row 46, Col 4, Row 2
   for(i=6; i < 44; i++)
   {
     leds[3][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=4;col < 5; col++)
   {
     leds[col][47] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(i=48; -1 < i; i--)
   {
     leds[4][i] = color;
   FastLED.show();
   delay(msecDelay);
   }

//  }

}





void mirrorSpiral(CRGB color, unsigned long timeInSec, int msecDelay)
{
 //////Serial.println("mirrorSpiral");
 int i;
 int col;
 FastLED.clear();


   //Loop 1  --- Col 0, Row 49, Col 7, Row 0
   for(i=0; i < 50; i++)
   {
     leds[0][i] = color;
     leds[7][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=1;col < 8; col++)
   {
     leds[col][49] = color;
     leds[col][48] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(i=48; -1 < i; i--)
   {
     leds[3][i] = color;
     leds[4][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=6; 0 < col; col--)
   {
     leds[col][0] = color;
     leds[col][1] = color;
     FastLED.show();
     delay(msecDelay);
   }




   //Loop 2  --- Col 1, Row 48, Col 6, Row 1
   for(i=2; i < 48; i++)
   {
     leds[1][i] = color;
     leds[6][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=2; col < 7; col++)
   {
     leds[col][47] = color;
     leds[col][46] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(i=48; 0 < i; i--)
   {
     leds[2][i] = color;
     leds[5][i] = color;
     FastLED.show();
     delay(msecDelay);
   }
   for(col=5; 1 < col; col--)
   {
     leds[col][2] = color;
     leds[col][3] = color;
     FastLED.show();
     delay(msecDelay);
   }

}

void blip(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(16, HIGH);
    delay(ANIMATION_DELAY*2);
    digitalWrite(16, LOW);
    delay(ANIMATION_DELAY*2);
  }
}

