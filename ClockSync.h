#ifndef ClockSync_h
#define ClockSync_h
#include "Arduino.h"

class ClockSync
{
  public:
    ClockSync(int p_clockPin, int p_clockPeriod); // constructor
    void NegotiateMaster(); // 
    bool ClockUpdate(); // returns whether or not there has been a boink
  
  private:
    int clockPin;
    int clockPeriod;
    bool isMasterDevice;

    // for being master 
    int clockTime;
    int newClockTime;
    // for being slave
    bool clockState;
    bool newClockState;
    
    // aka 'boink' 
    bool risingEdge;
};

#endif
