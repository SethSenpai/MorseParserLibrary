#include "Arduino.h"
#include "ClockSync.h"

ClockSync::ClockSync(int p_clockPin, int p_clockPeriod) {
  clockPin = p_clockPin;
  clockPeriod = p_clockPeriod;
  isMasterDevice = true;
}

void ClockSync::NegotiateMaster() {
  pinMode(clockPin, INPUT);
  int waitStart = millis();
  
  while(millis() < waitStart + clockPeriod * 2) {
    if(digitalRead(clockPin)) {
      isMasterDevice = false;
      break;
    }
  }
  // Serial.print("Master: ");
  // Serial.println(master ? "true" : "false");

  if(isMasterDevice) {
    pinMode(clockPin, OUTPUT);
  }
}

// returns true on a boink
bool ClockSync::ClockUpdate() {
  if(isMasterDevice) {
    newClockTime = millis() % clockPeriod;
    risingEdge = newClockTime < clockTime;
    clockTime = newClockTime;
    
    digitalWrite(clockPin, (millis() % clockPeriod) > clockPeriod/2);
  } else {
    newClockState = digitalRead(clockPin);
    risingEdge = (newClockState == true && clockState == false); // rising edge of clock
    clockState = newClockState;
  }

  return risingEdge;
}
