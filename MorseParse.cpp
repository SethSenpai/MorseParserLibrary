#include "Arduino.h"
#include "MorseParse.h"

MorseParse::MorseParse(int button_pin_in, int button_pin_out, int led_pin){
  pinMode(button_pin_in,INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin_out,OUTPUT);

  digitalWrite(led_pin,LOW);

  p_buttonPinIn = button_pin_in;
  p_buttonPinOut = button_pin_out;
  p_ledPin = led_pin;

  initializeVariables();
}

MorseParse::MorseParse(int rx_pin){
  pinMode(rx_pin,INPUT_PULLUP);

  p_buttonPinIn = rx_pin;

  initializeVariables();
}

void MorseParse::initializeVariables() {
  symbolIndex = 0;
  sampleCount = 0;
  silenceCount = 0;
  wasPressing = false;
  timeChecker = 0;
  sampleFrameTime = 50;
  dotSamples = 4;
  waitSamples = 6;
}

char MorseParse::Update() {
  // Burn cpu cycles!
  char t_returnLetter = 0x00;
  if(millis() > timeChecker + sampleFrameTime) {
    digitalWrite(p_ledPin,HIGH);
    int mirror = digitalRead(p_buttonPinIn);
    digitalWrite(p_buttonPinOut,mirror);
    if(digitalRead(p_buttonPinIn) == LOW) {
      wasPressing = true;
      sampleCount ++;
      silenceCount = 0;
    }
    else
    {
      if(sampleCount > 0) {
        if(sampleCount > dotSamples) {
          Serial.print("-");
          digitalWrite(p_ledPin,LOW);
          symbols[symbolIndex] = DASH;
          symbolIndex++;
        }
        if(sampleCount <= dotSamples) {
          Serial.print(".");
          digitalWrite(p_ledPin,LOW);
          symbols[symbolIndex] = DOT;
          symbolIndex++;
        }
        sampleCount = 0;
      }
      if(silenceCount > waitSamples && wasPressing == true) {
        Serial.println(" ");

        t_returnLetter = parseMorseCharacter(symbols, symbolIndex);
        symbolIndex = 0;

        silenceCount = 0;
        wasPressing = false;
      }
      silenceCount ++;
    }
    timeChecker = millis();
  }
  return t_returnLetter;
}

void MorseParse::setDotSamples(int samples){
  dotSamples = samples;
  waitSamples = samples + 2;
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
  symbol one[] = {DOT, DASH, DASH, DASH, DASH};
  symbol two[] = {DOT, DOT, DASH, DASH, DASH};
  symbol three[] = {DOT, DOT, DOT, DASH, DASH};
  symbol four[] = {DOT, DOT, DOT, DOT, DASH};
  symbol five[] = {DOT, DOT, DOT, DOT, DOT};
  symbol six[] = {DASH, DOT, DOT, DOT, DOT};
  symbol seven[] = {DASH, DASH, DOT, DOT, DOT};
  symbol eight[] = {DASH, DASH, DASH, DOT, DOT};
  symbol nine[] = {DASH, DASH, DASH, DASH, DOT};
  symbol zero[] = {DASH, DASH, DASH, DASH, DASH};
  symbol dot[] = {DOT, DASH, DOT, DASH, DOT, DASH};
  symbol comma[] = {DASH, DASH, DOT, DOT, DASH, DASH};
  symbol question[] = {DOT, DOT, DASH, DASH, DOT, DOT};
  symbol slash[] = {DASH, DOT, DOT, DASH, DOT};
  symbol at[] = {DOT, DASH, DASH, DOT, DASH, DOT};
  symbol space[] = {DOT,DOT,DOT,DOT,DOT,DOT};
  symbol backspace[] = {DOT,DOT,DOT,DOT,DOT,DASH};
  
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
  if(compareSymbolArray(character, one, symbolIndex, sizeof(one)/sizeof(a[0]))) return '1';
  if(compareSymbolArray(character, two, symbolIndex, sizeof(two)/sizeof(a[0]))) return '2';
  if(compareSymbolArray(character, three, symbolIndex, sizeof(three)/sizeof(a[0]))) return '3';
  if(compareSymbolArray(character, four, symbolIndex, sizeof(four)/sizeof(a[0]))) return '4';
  if(compareSymbolArray(character, five, symbolIndex, sizeof(five)/sizeof(a[0]))) return '5';
  if(compareSymbolArray(character, six, symbolIndex, sizeof(six)/sizeof(a[0]))) return '6';
  if(compareSymbolArray(character, seven, symbolIndex, sizeof(seven)/sizeof(a[0]))) return '7';
  if(compareSymbolArray(character, eight, symbolIndex, sizeof(eight)/sizeof(a[0]))) return '8';
  if(compareSymbolArray(character, nine, symbolIndex, sizeof(nine)/sizeof(a[0]))) return '9';
  if(compareSymbolArray(character, zero, symbolIndex, sizeof(zero)/sizeof(a[0]))) return '0';
  if(compareSymbolArray(character, dot, symbolIndex, sizeof(dot)/sizeof(a[0]))) return '.';
  if(compareSymbolArray(character, comma, symbolIndex, sizeof(comma)/sizeof(a[0]))) return ',';
  if(compareSymbolArray(character, question, symbolIndex, sizeof(question)/sizeof(a[0]))) return '?';
  if(compareSymbolArray(character, slash, symbolIndex, sizeof(slash)/sizeof(a[0]))) return '/';
  if(compareSymbolArray(character, at, symbolIndex, sizeof(at)/sizeof(a[0]))) return '@';
  if(compareSymbolArray(character, space, symbolIndex, sizeof(space)/sizeof(a[0]))) return ' ';
  if(compareSymbolArray(character, backspace, symbolIndex, sizeof(backspace)/sizeof(a[0]))) return 0x08;
  
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
