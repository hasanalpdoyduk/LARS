#include <Arduino.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void rf_init_rx(int rxPin) {
    mySwitch.enableReceive(digitalPinToInterrupt(rxPin));  // Receiver on interrupt
}

void rf_init_tx(int txPin) {
    mySwitch.enableTransmit(txPin);
}

bool rf_available() {
    return mySwitch.available();
}

unsigned long rf_get_value() {
    return mySwitch.getReceivedValue();
}

unsigned int rf_get_bit_length() {
    return mySwitch.getReceivedBitlength();
}

unsigned int rf_get_delay() {
    return mySwitch.getReceivedDelay();
}

unsigned int* rf_get_raw_data() {
    return mySwitch.getReceivedRawdata();
}

unsigned int rf_get_protocol() {
    return mySwitch.getReceivedProtocol();
}

void rf_reset() {
    mySwitch.resetAvailable();
}

void rf_set_pulse_length(unsigned int pulse_length) {
    mySwitch.setPulseLength(pulse_length);
}

void rf_set_protocol(int protocol) {
    mySwitch.setProtocol(protocol);
}

void rf_send_decimal(unsigned long value, unsigned int bit_length) {
    mySwitch.send(value, bit_length);
}

void rf_send_binary(const char* binary) {
    mySwitch.send(binary);
}




/*
    * This function is used to output the received RF data in a human-readable format.
    * It prints the decimal value, binary representation, tri-state representation,
    * pulse length, protocol, and raw data to the Serial monitor.
*/

static const char* bin2tristate(const char* bin);
static char* dec2binWzerofill(unsigned long Dec, unsigned int bit_length);

static const char* bin2tristate(const char* bin) {
  static char return_value[50];
  int pos = 0;
  int pos2 = 0;
  while (bin[pos] != '\0' && bin[pos + 1] != '\0') {
    if (bin[pos] == '0' && bin[pos + 1] == '0') {
      return_value[pos2] = '0';
    } else if (bin[pos] == '1' && bin[pos + 1] == '1') {
      return_value[pos2] = '1';
    } else if (bin[pos] == '0' && bin[pos + 1] == '1') {
      return_value[pos2] = 'F';
    } else {
      return "not applicable";
    }
    pos += 2;
    pos2++;
  }
  return_value[pos2] = '\0';
  return return_value;
}

static char* dec2binWzerofill(unsigned long Dec, unsigned int bit_length) {
  static char bin[64];
  unsigned int i = 0;

  while (Dec > 0) {
    bin[32 + i++] = ((Dec & 1) > 0) ? '1' : '0';
    Dec >>= 1;
  }

  for (unsigned int j = 0; j < bit_length; j++) {
    if (j >= bit_length - i) {
      bin[j] = bin[31 + i - (j - (bit_length - i))];
    } else {
      bin[j] = '0';
    }
  }
  bin[bit_length] = '\0';
  
  return bin;
}

void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol) {
  const char* b = dec2binWzerofill(decimal, length);
  Serial.print("Decimal: ");
  Serial.print(decimal);
  Serial.print(" (");
  Serial.print(length);
  Serial.print("Bit) Binary: ");
  Serial.print(b);
  Serial.print(" Tri-State: ");
  Serial.print(bin2tristate(b));
  Serial.print(" PulseLength: ");
  Serial.print(delay);
  Serial.print(" microseconds");
  Serial.print(" Protocol: ");
  Serial.println(protocol);
  
  Serial.print("Raw data: ");
  for (unsigned int i = 0; i <= length * 2; i++) {
    Serial.print(raw[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.println();
}