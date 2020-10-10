#ifndef MorseParse_h
#define MorseParse_h
#include "Arduino.h"

class MorseParse
{
  public:
    MorseParse(int button_pin, int led_pin);
    char Update();

    int clockPeriod = 1000;
    float dashThreshold = .3;

    void SetClockPeriod(int period);
    void SetDashThreshold(float threshold);


  private:
    int p_buttonPin;
    int p_ledPin;
    int p_clockTime;
    int p_newClockTime;
    int p_buttonOnTime;
    int p_buttonOffTime;
    bool p_newLEDCycle;

    const static int SYMBOL_DEPTH = 5;
    typedef enum symbol {
      DOT,
      DASH
    };

    symbol symbols[SYMBOL_DEPTH];
    int symbolIndex;

    char parseMorseCharacter(symbol p_symbols[], int p_symbolIndex);
    bool compareSymbolArray(symbol p_a[], symbol p_b[], int p_sizeA, int p_sizeB);
};

#endif
