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
#include "vector3d.h"

#define MPU9150_BUS 3           // 1 for raspberry, 3 for beagleboard
#define MPU9150_ADDRESS 0x68
#define MPU9150_SAMPLE_RATE 50   // Output rate of DMP
#define MPU9150_YAW_MIX_FACTOR 10    // The bigger, the less dominant magnetometer
#define MPU9150_MAGNETO_DEFAULT_CALIBRATION -163,77,-100,153,-231,34
#define MPU9150_ACCEL_DEFAULT_CALIBRATION -16566,16888,-16968,16996,-18186,16164 

class MPU9150Wrapper {
public:
    MPU9150Wrapper(int bus = MPU9150_BUS, char add = MPU9150_ADDRESS);
	virtual ~MPU9150Wrapper();
    int init();
    int reset();
    int stop();
    int flush();
	int getEuler(vector3d_t vector);
    void debug(int dbg = 1);

private:
    int i2c_bus;
    char address;
    mpudata_t mpu;
    
    int setCalibration(bool mag);
    int read();
};

#endif /* defined(__Ecubee__MPU9150Wrapper__) */
