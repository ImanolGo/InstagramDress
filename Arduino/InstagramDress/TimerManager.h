///////////////////////////////////////////////////////////////////
// Class in charge of the timing
//
//
// This code is under A Creative Commons Attribution/Share-Alike License
// http://creativecommons.org/licenses/by-sa/4.0/
// 2018, Imanol Gomez
///////////////////////////////////////////////////////////////////

#pragma once
#include "Arduino.h"

#define INTERVAL  120000 // 2 Minute interval

class TimerManager{

  public:
    
    TimerManager(LedsManager* ledsManager);
    
    void setup();
    void update();

    void reset();

  private:

    LedsManager* ledsManager;  ///< it sets the defaut state
    unsigned long startTime;
};

TimerManager::TimerManager(LedsManager* ledsManager)
{
  this->ledsManager=ledsManager;
  startTime = millis();
};


void TimerManager::setup()
{
      
}

void TimerManager::reset()
{
     startTime = millis();
}


void TimerManager::update()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;

    
    if (elapsedTime > INTERVAL) 
    {   
        Serial.println("Reset to default");
        this->reset();
        this->ledsManager->setDefaultState();
    }
}



