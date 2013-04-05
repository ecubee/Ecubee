/*
 * LIS3LV02DLWrapper.h
 *
 *  Created on: 1 sep 2010
 *      Author: s050401
 */

// Device wrapper for the linear accelerometer LIS3LV02DL
#include "i2cManager.h"
#ifndef LIS3LV02DLWRAPPER_H_
#define LIS3LV02DLWRAPPER_H_
#define LIS3LV02DL_ADDRESS 0x1d
// PD0 and PD1 in the datasheet
#define LIS3LV02DL_POWERDOWNCONTROL ((1 << 7) | (1 << 6))
// CR1 and CR2 in the datasheet
#define LIS3LV02DL_CONTROL_REGISTER_1 0x20
#define LIS3LV02DL_CONTROL_REGISTER_2 0x21
// bits 5 and 6 of CR1, 00 = 40Hz; 01 = 160Hz; 10 = 640Hz; 11 = 2560Hz
#define LIS3LV02DL_DECIMATE_FACTOR (0 << 5 | 1 << 4)
#define LIS3LV02DL_ENABLE_MEASUREMENT (1 << 2 | 1 << 1 | 1 )

class LIS3LV02DLWrapper {
public:
	LIS3LV02DLWrapper(i2cManager * man);
	LIS3LV02DLWrapper(i2cManager * man, char configuration);
	virtual ~LIS3LV02DLWrapper();
	bool getData(float* vx, float* vy, float* vz);
private:
	char controlRegister1;
	char controlRegister2;
	i2cManager* manager;
	int readRegister(char reg);
	bool writeRegister(char reg, char value);

};

#endif /* LIS3LV02DLWRAPPER_H_ */

