/*
 * HMC5843Wrapper.cpp
 *
 *  Created on: 1 sep 2010
 *      Author: s050401
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "HMC5843.h"
#include "i2cManager.h"
/**
 * This object is used to abstract the i2c calls to the sensor. After
 * constructing it, it can feed back data via the getData() method
 */

/******************************************
 * The constructor enables the chip via the i2cbus 
 * it uses the coupled i2cManager to send and receive data bytes
 ******************************************/
HMC5843Wrapper::HMC5843Wrapper(i2cManager * man) {
	// set it to the automatic default configuration:
	manager = man;
	configurationRegisterA = HMC5843_DATA_RATE;

	writeRegister(HMC5843_CONTROL_REGISTER_A, configurationRegisterA);

	writeRegister(HMC5843_MODE_REGISTER, HMC5843_SINGLE_CONVERSION_MODE);
	usleep(100000);
}

HMC5843Wrapper::HMC5843Wrapper(i2cManager * man, char configuration) {
	// non-default configuration
	manager = man;
	configurationRegisterA = configuration;
	writeRegister(HMC5843_CONTROL_REGISTER_A, configurationRegisterA);
}

HMC5843Wrapper::~HMC5843Wrapper() {
	// on shutdown do, nothing?:
}

bool HMC5843Wrapper::getData(float* vX, float* vY, float* vZ) {
	if(!isDataReady()){
		//set up for single measurement
		writeRegister(HMC5843_MODE_REGISTER, HMC5843_SINGLE_CONVERSION_MODE);
		return false;
	}	
	// continue to read data
	int vx = (short) ((readRegister(0x03) << 8) | readRegister(0x04));
	int vy = (short) ((readRegister(0x05) << 8) | readRegister(0x06));
	int vz = (short) ((readRegister(0x07) << 8) | readRegister(0x08));

	// normalize:
	*vX = (float) vx*(2.0/4096);
	*vY = (float) vy*(2.0/4096);
	*vZ = (float) vz*(2.0/4096);

	// get new measurement
	writeRegister(HMC5843_MODE_REGISTER, HMC5843_SINGLE_CONVERSION_MODE);
       	return true;
}

int HMC5843Wrapper::readRegister(char reg){
//	usleep (10000); //sensor can't keep up
	return manager->readByte(HMC5843_ADDRESS, reg);
}

bool HMC5843Wrapper::writeRegister(char reg, char value){
	return manager->writeByte(HMC5843_ADDRESS, reg, value);
}

bool HMC5843Wrapper::isDataReady(){
	char status = manager->readByte(HMC5843_ADDRESS, HMC5843_STATUS_REGISTER);
	if(status & (1 << 0)) {
		return true;
	}else{
		return false;
	}
}
bool HMC5843Wrapper::isUnlocked(){
        char status = manager->readByte(HMC5843_ADDRESS, HMC5843_STATUS_REGISTER);
        if(status != 2) {
                return true;
        }else{
                return false;
        }
}

