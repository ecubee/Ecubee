//
//  MPU9150Wrapper.h
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#ifndef __Ecubee__MPU9150Wrapper__
#define __Ecubee__MPU9150Wrapper__

#include "mpu9150.h"

#define MPU9150_BUS 3           // 1 for raspberry, 3 for beagleboard
#define MPU9150_ADDRESS 0x68
#define MPU9150_SAMPLE_RATE 50   // Output rate of DMP
#define MPU9150_YAW_MIX_FACTOR 10    // The bigger, the less dominant magnetometer
#define MPU9150_ACCEL_CAL "accelcal.txt"
#define MPU9150_MAG_CAL "magcal.txt"


class MPU9150Wrapper {
public:
    MPU9150Wrapper(int bus = MPU9150_BUS, char add = MPU9150_ADDRESS);
	~MPU9150();
    int init();
    int reset();
    int stop();
//	bool getData(float* vx, float* vy, float* vz);

private:
    const int i2c_bus;
    const char address;
    mpudata_t mpu;
    
    int setCalibration(bool mag);
    int read();
};

#endif /* defined(__Ecubee__MPU9150Wrapper__) */
