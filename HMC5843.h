/*
 * HMC5843Wrapper.h
 *
 *  Created on: 1 sep 2010
 *      Author: s050401
 */

// Device wrapper for the linear accelerometer HMC5843
#include "i2cManager.h"
#ifndef HMC5843WRAPPER_H_
#define HMC5843WRAPPER_H_
#define HMC5843_ADDRESS 0x1e
#define HMC5843_CONTROL_REGISTER_A 0x00
#define HMC5843_CONTROL_REGISTER_B 0x01
#define HMC5843_MODE_REGISTER 0x02
#define HMC5843_STATUS_REGISTER 0x09
// DO2 to DO0 / CRA4 to CRA2 # set to 50 Hz (1 1 0)
#define HMC5843_DATA_RATE ((1 << 4) | (1 << 3) | (0 << 2))
// MD1 and MD0 in MR1 and MR0
#define HMC5843_SINGLE_CONVERSION_MODE ((0 << 1) | ( 1 ))
#define HMC5843_CONTINUOUS_CONVERSION_MODE ((0 << 1) | ( 0 ))


class HMC5843Wrapper {
public:
	HMC5843Wrapper(i2cManager * man);
	HMC5843Wrapper(i2cManager * man, char configuration);
	virtual ~HMC5843Wrapper();
	bool getData(float* vx, float* vy, float* vz);
private:
	char modeRegister;
	char configurationRegisterA;
	char configurationRegisterB;
	i2cManager* manager;
	int readRegister(char reg);
	bool writeRegister(char reg, char value);
	bool isDataReady();
	bool isUnlocked();

};

#endif /* HMC5843WRAPPER_H_ */

