//
//  MPU9150.h
//  Ecubee
//
//  Created by Marcel Laurijsse on 4/4/13.
//
//

#ifndef Ecubee_MPU9150_h
#define Ecubee_MPU9150_h

#define MPU9150_ADDRESS 0x68
#define HMC5843_CONTROL_REGISTER_A 0x00
#define HMC5843_CONTROL_REGISTER_B 0x01
#define HMC5843_MODE_REGISTER 0x02
#define HMC5843_STATUS_REGISTER 0x09
// DO2 to DO0 / CRA4 to CRA2 # set to 50 Hz (1 1 0)
#define HMC5843_DATA_RATE ((1 << 4) | (1 << 3) | (0 << 2))
// MD1 and MD0 in MR1 and MR0
#define HMC5843_SINGLE_CONVERSION_MODE ((0 << 1) | ( 1 ))
#define HMC5843_CONTINUOUS_CONVERSION_MODE ((0 << 1) | ( 0 ))

#define LIS3LV02DL_ADDRESS 0x1d
// PD0 and PD1 in the datasheet
#define LIS3LV02DL_POWERDOWNCONTROL ((1 << 7) | (1 << 6))
// CR1 and CR2 in the datasheet
#define LIS3LV02DL_CONTROL_REGISTER_1 0x20
#define LIS3LV02DL_CONTROL_REGISTER_2 0x21
// bits 5 and 6 of CR1, 00 = 40Hz; 01 = 160Hz; 10 = 640Hz; 11 = 2560Hz
#define LIS3LV02DL_DECIMATE_FACTOR (0 << 5 | 1 << 4)
#define LIS3LV02DL_ENABLE_MEASUREMENT (1 << 2 | 1 << 1 | 1 )


class MPU9150Wrapper {
public:
	MPU9150Wrapper(i2cManager * man);
	MPU9150Wrapper(i2cManager * man, char configuration);
	virtual ~MPU9150Wrapper();
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



#endif
