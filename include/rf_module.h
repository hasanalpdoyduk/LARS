#pragma once
#include <Arduino.h>

void rf_init_rx(int rxPin);
void rf_init_tx(int txPin);
bool rf_available();
unsigned long rf_get_value();
unsigned int rf_get_bit_length();
unsigned int rf_get_delay();
unsigned int* rf_get_raw_data();
unsigned int rf_get_protocol();
void rf_reset();
void rf_set_pulse_length(unsigned int pulse_length);
void rf_set_protocol(int protocol);
void rf_send_decimal(unsigned long value, unsigned int bit_length);
void rf_send_binary(const char* binary);

// RF output debug function
void output(unsigned long decimal, unsigned int length, unsigned int delay, unsigned int* raw, unsigned int protocol);
