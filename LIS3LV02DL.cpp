/*
 * LIS3LV02DLWrapper.cpp
 *
 *  Created on: 1 sep 2010
 *      Author: s050401
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "LIS3LV02DL.h"
#include "i2cManager.h"
/**
 * This object is used to abstract the i2c calls to the sensor. After
 * constructing it, it can feed back data via the getData() method
 */

/******************************************
 * The constructor enables the chip via the i2cbus 
 * it uses the coupled i2cManager to send and receive data bytes
 ******************************************/
LIS3LV02DLWrapper::LIS3LV02DLWrapper(i2cManager * man) {
	// set it to the automatic default configuration:
	manager = man;
	controlRegister1 = LIS3LV02DL_POWERDOWNCONTROL | LIS3LV02DL_DECIMATE_FACTOR | LIS3LV02DL_ENABLE_MEASUREMENT;
	writeRegister(LIS3LV02DL_CONTROL_REGISTER_1, controlRegister1);
}

LIS3LV02DLWrapper::LIS3LV02DLWrapper(i2cManager * man, char configuration) {
	// non-default configuration
	manager = man;
	controlRegister1 = configuration;
	writeRegister(LIS3LV02DL_CONTROL_REGISTER_1, configuration);
}

LIS3LV02DLWrapper::~LIS3LV02DLWrapper() {
	// on shutdown do, nothing?:
}

bool LIS3LV02DLWrapper::getData(float* forceX, float* forceY, float* forceZ) {
	int vx = (short) ((readRegister(0x29) << 8) | readRegister(0x28));
	int vy = (short) ((readRegister(0x2B) << 8) | readRegister(0x2A));
	int vz = (short) ((readRegister(0x2D) << 8) | readRegister(0x2C));

	//printf("\n 0x%08X,  0x%08X,  0x%08X\n",vx,vy,vz);
	//printf(" %8d,%8d,%8d\n",vx,vy,vz);

	// normalize:
	*forceX = (float) vx*(2.0/2048);
	*forceY = (float) vy*(2.0/2048);
	*forceZ = (float) vz*(2.0/2048);
	//printf("%8.2f,%8.2f,%8.2f\n",*forceX,*forceY,*forceZ);	
	//printf("|a| = %8.2f\n",sqrt((*forceX)*(*forceX)+(*forceY)*(*forceY)+(*forceZ)*(*forceZ)));

	return true;
}

int LIS3LV02DLWrapper::readRegister(char reg){
	return manager->readByte(LIS3LV02DL_ADDRESS, reg);
}

bool LIS3LV02DLWrapper::writeRegister(char reg, char value){
	return manager->writeByte(LIS3LV02DL_ADDRESS, reg, value);
}

