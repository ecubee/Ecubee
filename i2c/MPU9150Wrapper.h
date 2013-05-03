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
#define MPU9150_YAW_MIX_FACTOR 10    // The bigger, the less dominant magnetometer
#define MPU9150_MAGNETO_DEFAULT_CALIBRATION -146,234,-101,241,-296,232
#define MPU9150_ACCEL_DEFAULT_CALIBRATION -16946,16572,-18726,16748,-17946,16724
#define MPU9150_REG_FIFO_COUNT 0x72

#if (defined I2C_DEBUG || defined SERIAL_DEBUG)
#define MPU9150_SAMPLE_RATE 2   // Output rate of DMP
#else
#define MPU9150_SAMPLE_RATE 50   // Output rate of DMP
#endif

class MPU9150Wrapper {
public:
    MPU9150Wrapper(int bus = MPU9150_BUS, unsigned char add = MPU9150_ADDRESS);
    ~MPU9150Wrapper();
    int init();
    void debug(int dbg = 1);
    int stop();
    int flush();
	int getEuler(vector3d_t vector);
    int runSelfTest();
    int printRegDump();

private:
    int i2c_bus;
    unsigned char address;
    mpudata_t mpu;
    int setCalibration(bool mag);
    int read();
    int getEulerFromAccel(vector3d_t vector);
    int getEulerFromRawQuat(vector3d_t vector);
    int getEulerFromNineAxisFusion(vector3d_t vector);
};

#endif /* defined(__Ecubee__MPU9150Wrapper__) */
