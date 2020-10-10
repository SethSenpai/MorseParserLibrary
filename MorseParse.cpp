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
      m_returnLetter = ' ';
      // parse old letter
    } else if(p_buttonOnTime < (p_buttonOnTime + p_buttonOffTime) * dashThreshold) {
      // dot
      m_returnLetter = '.';

    } else {
      // dash
      m_returnLetter = '-';
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
