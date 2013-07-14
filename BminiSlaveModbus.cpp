#include "BminiSlaveModbus.h"
#include "SimpleModbusSlave.h"

//board pins association

#define DIGIN1 2
#define DIGIN2 3
#define DIGIN3 4
#define DIGIN4 5

#define RELAY1 7
#define RELAY2 6
#define RELAY3 9
#define RELAY4 8

#define PWM1 10
#define PWM2 11

#define MODBUSLED 12
#define MODBUSPIN 13

//analog pins

#define ANALOG0 0
#define ANALOG1 1
#define ANALOG2 2
#define ANALOG3 3
#define ANALOG4 4
#define ANALOG5 5
#define ANALOG6 6
#define ANALOG7 7

// function definitions

//modbus registers update
unsigned int modbus_update_regs(unsigned int *holdingRegs){
	unsigned int ret = modbus_update(holdingRegs);
	return ret;
}

// Bmini pins initialization
void bmini_init(unsigned int slaveid, unsigned int baudrate)
{	
	//digital inputs init
	pinMode(DIGIN1, INPUT_PULLUP);
	pinMode(DIGIN2, INPUT_PULLUP);
	pinMode(DIGIN3, INPUT_PULLUP);
	pinMode(DIGIN4, INPUT_PULLUP);

	//digital outputs init
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);

	//pwm
	pinMode(PWM1, OUTPUT);
	pinMode(PWM2, OUTPUT);

	//modbus
	pinMode(MODBUSLED, OUTPUT);
	pinMode(MODBUSPIN, OUTPUT);
	
	//modbus_configure(baudrate, slaveid, MODBUSPIN, TOTAL_REGS_SIZE);
	modbus_configure(baudrate, slaveid, MODBUSPIN, 12);

}

//relays states
void relay(int relay_number, int value){
	int pin_relay;
	switch(relay_number){
		case 1:
			pin_relay = RELAY1;
			break;
		case 2:
			pin_relay = RELAY2;
			break;
		case 3:
			pin_relay = RELAY3;
			break;
		case 4:
			pin_relay = RELAY4;
			break;
		default:
			// no more than 4 relays are allowed
			return;
	}
	digitalWrite(pin_relay,value);
}

void pwm(int pwm_number, int value){				//max value allowed [0,255]
	int pwm_pin;
	switch(pwm_number){
		case 1:
			pwm_pin = PWM1; 
			break;
		case 2:
			pwm_pin = PWM2;
			break;
		default:
			// no more than 2 pwm are allowed
			return;
        }
	if (value >= 0 && value <= 255){
		analogWrite(pwm_pin, value);
	}
}

int get_inputs(int di_number){
	int dig_pin, ret;

	switch(di_number){
		case 1:
			dig_pin = DIGIN1;
			break;
		case 2:
			dig_pin = DIGIN2;
			break;
		case 3:
			dig_pin = DIGIN3;
			break;
		case 4:
			dig_pin = DIGIN4;
			break;
		default:
			return -1;
	}
	ret = 1-digitalRead(dig_pin);
	return ret;
}

float readTemperatureC(int an_number){
	int analog_pin, reading;
	switch(an_number){
		case 1:
			analog_pin = ANALOG1;
			break;
		case 2:
			analog_pin = ANALOG2;
			break;
		case 3:
			analog_pin = ANALOG3;
			break;
		case 4:
			analog_pin = ANALOG4;
			break;
		default:
			return -1;
	}
	
	reading = analogRead(analog_pin);

	float voltage = reading * 5.0;
	voltage /= 1024.0; 
 
	 //converting from 10 mv per degree wit 500 mV offset
        //to degrees ((volatge - 500mV) times 100)
 	float temperatureC = (voltage - 0.5) * 100 ; 
 
	return temperatureC;
 


}

float readTemperatureF(int an_number){

	int analog_pin, reading;
	switch(an_number){
		case 1:
			analog_pin = ANALOG1;
			break;
		case 2:
			analog_pin = ANALOG2;
			break;
		case 3:
			analog_pin = ANALOG3;
			break;
		case 4:
			analog_pin = ANALOG4;
			break;
		default:
			return -1;
	}
	
	reading = analogRead(analog_pin);

	float voltage = reading * 5.0;
	voltage /= 1024.0; 
 
	 //converting from 10 mv per degree wit 500 mV offset
        //to degrees ((volatge - 500mV) times 100)
 	float temperatureC = (voltage - 0.5) * 100 ; 



 	// now convert to Fahrenheight
	float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
	return temperatureF;
}

