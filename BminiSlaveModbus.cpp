#include "BminiSlaveModbus.h"
#include "SimpleModbusSlave.h"

/*Bmini shield pins mapping
with Arduino Mini board
Biemme Italia 2013
*/

//digital input pins
#define DIGIN1 2
#define DIGIN2 3
#define DIGIN3 4
#define DIGIN4 5

//digital output pins (relay)
#define RELAY1 7
#define RELAY2 6
#define RELAY3 9
#define RELAY4 8

//pwm pins
#define PWM1 10
#define PWM2 11

//modbus status led and MAX485/1487 enable pin
#define MODBUSLED 12
#define MODBUSPIN 13

//analog pins

#define ANALOG1 0
#define ANALOG2 1
#define ANALOG3 2
#define ANALOG4 3
#define ANALOG5 4
#define ANALOG6 5
#define ANALOG7 6
#define ANALOG8 7

// function definitions
int analogReadPin(int pin_number);


//modbus registers update
unsigned int modbus_update_regs(unsigned int *holdingRegs){
	unsigned int ret = modbus_update(holdingRegs);
	return ret;
}

// Bmini pins initialization
void bmini_init(unsigned int slaveid, unsigned int baudrate, unsigned int TOTAL_REGS_SIZE)
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
	modbus_configure(baudrate, slaveid, MODBUSPIN, TOTAL_REGS_SIZE);

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

/* Get digital inputs status
 Biemme Italia 2013
*/
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

	int reading = analogReadPin(an_number);
	
	if (reading > -999){

		float voltage = reading * 5.0;
		voltage /= 1024.0; 
	 
		 //converting from 10 mv per degree wit 500 mV offset
		//to degrees ((volatge - 500mV) times 100)
	 	float temperatureC = (voltage - 0.5) * 100 ; 
	 
		return temperatureC;
 	}else{
		return -999;
	}


}

/* Read temperature from TMP36 like sensor
 Biemme Italia 2013
*/
float readTemperatureF(int an_number){

	int reading = analogReadPin(an_number);

	if (reading > -999){
		float voltage = reading * 5.0;
		voltage /= 1024.0; 
	 
		 //converting from 10 mv per degree wit 500 mV offset
		//to degrees ((volatge - 500mV) times 100)
	 	float temperatureC = (voltage - 0.5) * 100 ; 

	 	// now convert to Fahrenheight
		float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
		return temperatureF;
	}else{
		return -999;
	}
}

/* Read analog pins
* Biemme Italia
*/
int analogReadPin(int pin_number){
        int pin_toread;
        switch(pin_number){
                case 1:
                        pin_toread = ANALOG1;
                        break;
                case 2:
                        pin_toread = ANALOG2;
                        break;
                case 3:
                        pin_toread = ANALOG3;
                        break;
                case 4:
                        pin_toread = ANALOG4;
                        break;
		case 5:
                        pin_toread = ANALOG5;
			break;
		case 6:
			pin_toread = ANALOG6;
			break;
		case 7:
			pin_toread = ANALOG7;
			break;
		case 8:
			pin_toread = ANALOG8;
			break;
                default:
                        // no more than 4 analog input are allowed
                        return -999;
        }
        int value = analogRead(pin_toread);

        return value;

}

