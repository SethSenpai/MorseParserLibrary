#include "Arduino.h"
#include "MorseParse.h"

MorseParse::MorseParse(int button_pin, int led_pin){
  pinMode(button_pin,INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);

  digitalWrite(led_pin,LOW);

  p_buttonPin = button_pin;
  p_ledPin = led_pin;
  p_clockTime = 0;
  p_newClockTime = 0;
  p_buttonOnTime = 0;
  p_buttonOffTime = 0;
  p_newLEDCycle = false;
  symbolIndex = 0;
}

char MorseParse::Update(){
  char m_returnLetter = 0x00;
  if(digitalRead(p_buttonPin) == LOW) {
    p_buttonOnTime++;
  } else {
    p_buttonOffTime++;
  }

  // check every LED period to see what character we've gotten 
  if(p_newLEDCycle) {
    if(p_buttonOnTime == LOW) {
      m_returnLetter = parseMorseCharacter(symbols, symbolIndex);
      symbolIndex = 0;
    } else if(p_buttonOnTime < (p_buttonOnTime + p_buttonOffTime) * dashThreshold) {
      // dot
      // m_returnLetter = '.';
      symbols[symbolIndex] = DOT;
      symbolIndex++;

    } else {
      // dash
      // m_returnLetter = '-';
      symbols[symbolIndex] = DASH;
      symbolIndex++;
    }
    
    p_buttonOnTime = 0;
    p_buttonOffTime = 0;
  }
  
  p_newClockTime = millis() % clockPeriod;
  p_newLEDCycle = (p_newClockTime < p_clockTime);
  p_clockTime = p_newClockTime;  
  digitalWrite(p_ledPin, ((p_clockTime > clockPeriod/10) && p_clockTime < ((clockPeriod/10) + clockPeriod * .1) ));
  return m_returnLetter;
}

void MorseParse::SetClockPeriod(int period){
  clockPeriod = period;
}

void MorseParse::SetDashThreshold(float threshold){
  dashThreshold = threshold;
}

char MorseParse::parseMorseCharacter(symbol p_symbols[], int p_symbolIndex) {
  // create properly sized array from parameter (no trailing symbols)
  symbol character[symbolIndex];
  for(int i = 0;i < symbolIndex;i++) {
    character[i] = p_symbols[i];
  }

  symbol a[] = {DOT, DASH};
  symbol b[] = {DASH, DOT, DOT, DOT};
  symbol c[] = {DASH, DOT, DASH, DOT};
  symbol d[] = {DASH, DOT, DOT};
  symbol e[] = {DOT};
  symbol f[] = {DOT, DOT, DASH, DOT};
  symbol g[] = {DASH, DASH, DOT};
  symbol h[] = {DOT, DOT, DOT, DOT};
  symbol i[] = {DOT, DOT};
  symbol j[] = {DOT, DASH, DASH, DASH};
  symbol k[] = {DASH, DOT, DASH};
  symbol l[] = {DOT, DASH, DOT, DOT};
  symbol m[] = {DASH, DASH};
  symbol n[] = {DASH, DOT};
  symbol o[] = {DASH, DASH, DASH};
  symbol p[] = {DOT, DASH, DASH, DOT};
  symbol q[] = {DASH, DASH, DOT, DASH};
  symbol r[] = {DOT, DASH, DOT};
  symbol s[] = {DOT, DOT, DOT};
  symbol t[] = {DASH};
  symbol u[] = {DOT, DOT, DASH};
  symbol v[] = {DOT, DOT, DOT, DASH};
  symbol w[] = {DOT, DASH, DASH};
  symbol x[] = {DASH, DOT, DOT, DASH};
  symbol y[] = {DASH, DOT, DASH, DASH};
  symbol z[] = {DASH, DASH, DOT, DOT};
  
  if(compareSymbolArray(character, a, symbolIndex, sizeof(a)/sizeof(a[0]))) return 'a';
  if(compareSymbolArray(character, b, symbolIndex, sizeof(b)/sizeof(a[0]))) return 'b';
  if(compareSymbolArray(character, c, symbolIndex, sizeof(c)/sizeof(a[0]))) return 'c';
  if(compareSymbolArray(character, d, symbolIndex, sizeof(d)/sizeof(a[0]))) return 'd';
  if(compareSymbolArray(character, e, symbolIndex, sizeof(e)/sizeof(a[0]))) return 'e';
  if(compareSymbolArray(character, f, symbolIndex, sizeof(f)/sizeof(a[0]))) return 'f';
  if(compareSymbolArray(character, g, symbolIndex, sizeof(g)/sizeof(a[0]))) return 'g';
  if(compareSymbolArray(character, h, symbolIndex, sizeof(h)/sizeof(a[0]))) return 'h';
  if(compareSymbolArray(character, i, symbolIndex, sizeof(i)/sizeof(a[0]))) return 'i';
  if(compareSymbolArray(character, j, symbolIndex, sizeof(j)/sizeof(a[0]))) return 'j';
  if(compareSymbolArray(character, k, symbolIndex, sizeof(k)/sizeof(a[0]))) return 'k';
  if(compareSymbolArray(character, l, symbolIndex, sizeof(l)/sizeof(a[0]))) return 'l';
  if(compareSymbolArray(character, m, symbolIndex, sizeof(m)/sizeof(a[0]))) return 'm';
  if(compareSymbolArray(character, n, symbolIndex, sizeof(n)/sizeof(a[0]))) return 'n';
  if(compareSymbolArray(character, o, symbolIndex, sizeof(o)/sizeof(a[0]))) return 'o';
  if(compareSymbolArray(character, p, symbolIndex, sizeof(p)/sizeof(a[0]))) return 'p';
  if(compareSymbolArray(character, q, symbolIndex, sizeof(q)/sizeof(a[0]))) return 'q';
  if(compareSymbolArray(character, r, symbolIndex, sizeof(r)/sizeof(a[0]))) return 'r';
  if(compareSymbolArray(character, s, symbolIndex, sizeof(s)/sizeof(a[0]))) return 's';
  if(compareSymbolArray(character, t, symbolIndex, sizeof(t)/sizeof(a[0]))) return 't';
  if(compareSymbolArray(character, u, symbolIndex, sizeof(u)/sizeof(a[0]))) return 'u';
  if(compareSymbolArray(character, v, symbolIndex, sizeof(v)/sizeof(a[0]))) return 'v';
  if(compareSymbolArray(character, w, symbolIndex, sizeof(w)/sizeof(a[0]))) return 'w';
  if(compareSymbolArray(character, x, symbolIndex, sizeof(x)/sizeof(a[0]))) return 'x';
  if(compareSymbolArray(character, y, symbolIndex, sizeof(y)/sizeof(a[0]))) return 'y';
  if(compareSymbolArray(character, z, symbolIndex, sizeof(z)/sizeof(a[0]))) return 'z';

  return 0x00;
}

bool MorseParse::compareSymbolArray(symbol p_a[], symbol p_b[], int sizeA, int sizeB) {
  // compare size 
  if(sizeA != sizeB) {
    return false;
  }
  
  // compare contents 
  for(int i = 0; i < sizeA;i++) {
    if(p_a[i] != p_b[i]) {
      return false;
    }
  }

  return true;
}
