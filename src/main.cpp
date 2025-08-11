#include <Arduino.h>
#include "rf_module.h"


// put function declarations here:
// int myFunction(int, int);


void setup() {
  Serial.begin(9600);
  rf_init_rx(2);
}


void loop() {
  if (rf_available()) {
    output(
      rf_get_value(),
      rf_get_bit_length(),
      rf_get_delay(),
      rf_get_raw_data(),
      rf_get_protocol()
    );
    rf_reset();
  }
}


// put function definitions here:
// int myFunction(int x, int y) {
//  return x + y;
// }
// }





/* 

MAIN MENU
> LISTEN & DECODE
> SAVED SIGNALS

DECODE MODE
> LISTENING 433.92MHz
<image>

DECODE MODE
> SIGNAL DETECTED
<image>

DECODE MODE


*/

