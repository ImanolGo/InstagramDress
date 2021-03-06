///////////////////////////////////////////////////////////////////
// Class controlling the leds and its effects
//
//
// This code is under A Creative Commons Attribution/Share-Alike License
// http://creativecommons.org/licenses/by-sa/4.0/
// 2018, Imanol Gomez
///////////////////////////////////////////////////////////////////

#pragma once
#include "Arduino.h"
#include <WS2812FX.h>
#include "LedsManager.h"


//#define NUM_LEDS    40
#define NUM_LEDS    162
#define BRIGHTNESS  90
//#define DATA_PIN_1    12
#define DATA_PIN_1    15
#define DATA_PIN_2    2


typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

} Color;
        
enum LED_PATTERNS {
  DEFAULT_,
  FADE,
  SPARKLE,
  FLASH,
  MOVE,
  RAINBOW
};


enum LED_COLORS{
  RED_,
  GREEN_,
  BLUE_,
  CYAN_,
  PINK_,
  PURPLE_,
  WHITE_,
  LAVENDER_
};


class LedsManager{

  public:
    
    LedsManager() {}
    
    void setup();
    void update();

    void setColorIndex(uint8_t i);
    void setColorHex(uint32_t c);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setPattern(uint8_t patternNumber);
    
  private:

    void setupLeds();

    void setDefault();
    void setRainbow();
    void setFade();
    void setSparkle();
    void setFlash();
    void setMove();
    void setBlack();
    void setMode(uint8_t m, uint16_t s);
    
    WS2812FX* ws2812fx1;
    WS2812FX* ws2812fx2;

    Color   m_currentColor;
  
    uint8_t currentPatternNumber; // Index number of which pattern is current
    uint8_t currentColorNumber; // Index number of which color is current
  
    
};

void LedsManager::setup()
{
    this->setupLeds();
    this->setDefault();  
}


void LedsManager::setupLeds()
{
    ws2812fx1 = new WS2812FX(NUM_LEDS, DATA_PIN_1, NEO_RGB + NEO_KHZ800);
    ws2812fx2 = new WS2812FX(NUM_LEDS, DATA_PIN_2, NEO_RGB + NEO_KHZ800); 

    ws2812fx1->init();
    ws2812fx1->setBrightness(BRIGHTNESS);
   
    ws2812fx2->init();
    ws2812fx2->setBrightness(BRIGHTNESS);   
}

void LedsManager::update()
{
    ws2812fx1->service();
    ws2812fx2->service();
}


void LedsManager::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    ws2812fx1->setColor(g,r,b);
    ws2812fx2->setColor(g,r,b);

    m_currentColor.r = r;
    m_currentColor.g = g;
    m_currentColor.b = b;
}

void LedsManager::setColorHex(uint32_t c)
{
    ws2812fx1->setColor(c);
    ws2812fx2->setColor(c);
}

void LedsManager::setColorIndex(uint8_t i)
{
    currentColorNumber = i;
    switch (currentColorNumber) 
    {
       case RED_:
         this->setColor(255,0,0);
         Serial.println("Set Color: Red");
         break;
       case GREEN_:
         this->setColor(0,255,40);
         Serial.println("Set Color: Green");
         break;
       case BLUE_:
         this->setColor(24,8,171);
         Serial.println("Set Color: Blue");
         break;
       case CYAN_:
         this->setColor(0,147,94);
         Serial.println("Set Color: Cyan");
         break;
       case PINK_:
         this->setColor(255,30,37);
         Serial.println("Set Color: Pink");
         break;
       case PURPLE_:
         this->setColor(255,70,167);
         Serial.println("Set Color: Purple");
         break;
       case WHITE_:
         this->setColor(255,255,184);
         Serial.println("Set Color: White");
         break;
       case LAVENDER_:
         this->setColor(251, 161, 252);
         Serial.println("Set Color: Lavender");
        default: 
          // if nothing else matches, do the default
          // default is optional
        break;
    }
}



void LedsManager::setPattern(uint8_t patternNumber )
{
    currentPatternNumber = patternNumber;

     switch (currentPatternNumber) 
    {
        case RAINBOW:
          this->setRainbow();
          Serial.println("Set Pattern: Rainbow");
          break;
        case DEFAULT_:
          this->setDefault();
          Serial.println("Set Pattern: Default");
          break;
        case FADE:
          this->setFade();
          Serial.println("Set Pattern: Fade");
          break;
        case SPARKLE:
          this->setSparkle();
          Serial.println("Set Pattern: Sparkle");
          break;
        case FLASH:
          this->setFlash();
          Serial.println("Set Pattern: Flash");
          break;
        case MOVE:
          this->setMove();
          Serial.println("Set Pattern: Move");
          break;        
        default: 
          // if nothing else matches, do the default
          // default is optional
        break;
    }
}

void LedsManager::setMode(uint8_t m, uint16_t s)
{
    this->setBlack();
    
    ws2812fx1->setSpeed(s);  
    ws2812fx1->setMode(m);
    ws2812fx1->start();
    ws2812fx2->setSpeed(s);
    ws2812fx2->setMode(m);
    ws2812fx2->start();
}

void LedsManager::setDefault()
{

   uint8_t mode_ = FX_MODE_RUNNING_LIGHTS;
   uint16_t speed_ = 9000;
   this->setMode(mode_,speed_);
   this->setColor(255,255,255);
}

void LedsManager::setRainbow()
{
   uint8_t mode_ = FX_MODE_RAINBOW_CYCLE;
   uint16_t speed_ = 10000;
   this->setMode(mode_,speed_);

}
void LedsManager::setFade()
{
   uint8_t mode_ = FX_MODE_FADE;
   uint16_t speed_ = 2000;
   this->setMode(mode_,speed_);
}

void LedsManager::setSparkle()
{  
   uint8_t mode_ = FX_MODE_FIREWORKS;
   uint16_t speed_ = 10000;
   this->setMode(mode_,speed_);
}


void LedsManager::setMove()
{
   uint8_t mode_ = FX_MODE_COLOR_WIPE;
   uint16_t speed_ = 30000;
   this->setMode(mode_,speed_);
}

void LedsManager::setFlash()
{
    uint8_t mode_ = FX_MODE_STROBE;
    uint16_t speed_ = 500;
    this->setMode(mode_,speed_);
}

void LedsManager::setBlack()
{ 
    
    ws2812fx1->setColor(0,0,0);
    ws2812fx2->setColor(0,0,0);
    
    ws2812fx1->setMode(FX_MODE_STATIC);
    ws2812fx1->init();
    ws2812fx1->service();

    ws2812fx2->setMode(FX_MODE_STATIC);
    ws2812fx2->init();
    ws2812fx2->service();

    this->setColor(m_currentColor.r,m_currentColor.g,m_currentColor.b);
   
}
  
    

