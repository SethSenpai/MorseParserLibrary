# Character Reference:
![Character codes](https://i.pinimg.com/originals/1c/70/2e/1c702e4de14c05968c6707190e0d2cd0.jpg)

Note we don't do the character space/word space thing.

Space character is ``. . . . . .``
Backspace character is ``. . . . . -``

Note that backspace implementation is device specific. The library will only return the ascii backspace character (0x08). This may or may not be printed depending on the implementation of your display or monitor.

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
