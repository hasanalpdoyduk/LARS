#include <Arduino.h>
#include "rf_module.h"
#include <U8glib.h>

// 
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI


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

