# Example Code:
```cpp
#include "MorseParse/MorseParse.h"

//create the parser object, first number is the button pin that gets pulled low. Second number is the LED that goes HIGH;
MorseParse parser(8,13);

void setup() {
  Serial.begin(115200);
}

void loop() {
   char out = parser.Update();
   if(out != 0x00){
    Serial.println(out);
   }
}
```