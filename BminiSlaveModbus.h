#ifndef BMINI_SLAVE_MODBUS_H
#define BMINI_SLAVE_MODBUS_H

/* Biemme Italia, 2013

 http://www.biemmeitalia.net/libraries
*/

#include "Arduino.h"

// function definitions
void bmini_init(unsigned int slaveid, unsigned int baudrate, unsigned int TOTAL_REGS_SIZE);
unsigned int modbus_update_regs(unsigned int *holdingRegs);


void relay(int relay_number, int value);
void pwm(int pwm_number, int value);
int get_inputs(int di_number);
float readTemperatureC(int an_number);
float readTemperatureF(int an_number);
int analogReadPin(int pin_number);

#endif
