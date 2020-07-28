// drv8838.cpp
// Basic Arduino library for the TI DRV8838 motor driver
// Christopher Green - Use this code at your own risk/peril

#include "drv8838.hpp"

#include <pigpio.h>


drv8838::drv8838(uint8_t ENABLE, uint8_t PHASE){ //Constructor that sets pins for board - enable should be PWM
	_EN_pin = ENABLE;
	_PH_pin = PHASE;
	gpioSetMode(_EN_pin, PI_OUTPUT);
	gpioSetMode(_PH_pin, PI_OUTPUT);
}

void drv8838::setDirection(bool direction){ //set motor direction
	gpioWrite(_PH_pin, direction);
}

void drv8838::setSpeed(uint8_t speed){ //set motor speed (0-255)
	gpioPWM(_EN_pin, speed);
}