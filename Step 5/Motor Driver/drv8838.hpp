// drv8838.h
// Basic Raspberry library for the TI DRV8838 motor driver
// Based on Christopher Green - Modified for raspberry by Rafael Carbonell

#ifndef drv8838_h
#define drv8838_h

#define FORWARD 0
#define BACKWARD 1

#include <stdint.h>

class drv8838{
public:
	drv8838(uint8_t, uint8_t); //constructor that sets pins for board - enable, phase - enable should be PWM
	void setDirection(bool); //set motor direction
	void setSpeed(uint8_t); //set motor speeds
private:
	int _EN_pin, _PH_pin; //enable and phase pins
};

#endif
