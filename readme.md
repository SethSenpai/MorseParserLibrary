# Character Reference:
![Character codes](https://i.pinimg.com/originals/1c/70/2e/1c702e4de14c05968c6707190e0d2cd0.jpg)

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
