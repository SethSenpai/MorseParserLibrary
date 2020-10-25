#ifndef MorseParse_h
#define MorseParse_h
#include "Arduino.h"

class MorseParse
{
  public:
    MorseParse(int button_pin_in, int button_pin_out, int led_pin);
    MorseParse(int rx_pin);
    char Update();

  private:
    int p_buttonPinOut;
    int p_buttonPinIn;
    int p_ledPin;

    int sampleCount;
    int silenceCount;
    bool wasPressing;
    long timeChecker;
    int sampleFrameTime;

    const static int SYMBOL_DEPTH = 5;
    typedef enum symbol {
      DOT,
      DASH
    };

    symbol symbols[SYMBOL_DEPTH];
    int symbolIndex;

    void initializeVariables();
    char parseMorseCharacter(symbol p_symbols[], int p_symbolIndex);
    bool compareSymbolArray(symbol p_a[], symbol p_b[], int p_sizeA, int p_sizeB);
};

#endif
