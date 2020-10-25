# Character Reference:
![Character codes](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.pinterest.com%2Fpin%2F2040762304984546%2F&psig=AOvVaw2k64fhaiHAHujiAj0G8IkN&ust=1603718558000000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCID_2Knrz-wCFQAAAAAdAAAAABAu)
Note we don't do the character space/word space thing.
Also we've replaced the '@' symbol with a space.

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
