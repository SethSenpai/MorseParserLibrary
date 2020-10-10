#ifndef MorseParse_h
#define MorseParse_h
#include "Arduino.h"

class MorseParse
{
  public:
    MorseParse(int button_pin_in, int button_pin_out, int led_pin);
    MorseParse(int rx_pin);

    void Update();
    char UpdateOnRisingEdge();

    // int clockPeriod = 1000;
    float dashThreshold = .3;

    // void SetClockPeriod(int period);
    void SetDashThreshold(float threshold);

    void updateLED();

  private:
    int p_buttonPinOut;
    int p_buttonPinIn;
    int p_ledPin;
    int p_clockTime;
    int p_newClockTime;
    int p_buttonOnTime;
    int p_buttonOffTime;
    bool p_newLEDCycle;

    bool newClockState; // high or low
    bool clockState;
    bool ledState;
    int clockPin;

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
