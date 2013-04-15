//
//  MPU9150Wrapper.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//  TODO: Integrated interupt support using GPIO pin
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MPU9150Wrapper.h"
#include "mpu9150.h"
#include "vector3d.h"


MPU9150Wrapper::MPU9150Wrapper(int bus, char add) {
    i2c_bus = bus;
    add = add;
}

MPU9150Wrapper::~MPU9150Wrapper() {
	// Stop the DMP
    stop();
}

int MPU9150Wrapper::init() {
    
    
	if (mpu9150_init(i2c_bus, MPU9150_SAMPLE_RATE, MPU9150_YAW_MIX_FACTOR)) {
        fprintf( stderr, "Failed set up MPU9150\n" );
        return -1;
    }
    
	setCalibration(false); // Accel Calibration;
    setCalibration(true);  // Magneto Calibration
    
    memset(&mpu, 0, sizeof(mpudata_t));
    
    
	return 0;
}

int MPU9150Wrapper::getEuler(vector3d_t vector) {
    // Get Euler angles
    //  In: pointer to float[3] vector
    //  Return: 0 on succes, 1 on data not ready, -1 on read error
    
    int result;
    
    if ((result = read()) != 0) {
        return result;
    }
    
    for (int i=0; i < 3; i++) {
        vector[i] = mpu.fusedEuler[i];
    }
    return 0;
}

int MPU9150Wrapper::stop() {
    return mpu9150_exit();
}

int MPU9150Wrapper::read() {
    return mpu9150_read(&mpu);
}

void MPU9150Wrapper::debug(int dbg) {
    mpu9150_set_debug(dbg);
}

int MPU9150Wrapper::setCalibration(bool mag) {
    int i;
	FILE *f;
    char filename[32];
	char buff[32];
	long readout[6];
    long magdefaults[6] = {MPU9150_MAGNETO_DEFAULT_CALIBRATION};
    long acceldefaults[6] = {MPU9150_ACCEL_DEFAULT_CALIBRATION};
    long * val;
    bool error = false;
	caldata_t cal;
    
    if (mag) {
        strcpy(filename, "/etc/ecubee/magcal.txt");
        val = magdefaults;
    } else {
        strcpy(filename, "/etc/ecubee/accelcal.txt");
        val = acceldefaults;
    }
    
    f = fopen(filename, "r");
    
    if (f) {
        memset(buff, 0, sizeof(buff));
        
        for (i = 0; i < 6; i++) {
            if (!fgets(buff, 20, f)) {
                fprintf(stderr, "Warning: Not enough lines in calibration file, switching to hardcoded values\n");
                error = true;
                break;
            }
            
            readout[i] = atoi(buff);
            
            if (readout[i] == 0) {
                fprintf(stderr, "Warning: Invalid cal value: %s, switching to hardcoded values\n", buff);
                error = true;
                break;
            }
        }
        
        fclose(f);

    } else {
        fprintf(stderr, "Warning: %s not found, switching to hardcoded values\n", filename);
        error = true;
    }
    
    if (!error)
        val = readout;

    
	cal.offset[0] = (short)((val[0] + val[1]) / 2);
	cal.offset[1] = (short)((val[2] + val[3]) / 2);
	cal.offset[2] = (short)((val[4] + val[5]) / 2);
    
	cal.range[0] = (short)(val[1] - cal.offset[0]);
	cal.range[1] = (short)(val[3] - cal.offset[1]);
	cal.range[2] = (short)(val[5] - cal.offset[2]);
	
	if (mag)
		mpu9150_set_mag_cal(&cal);
	else
		mpu9150_set_accel_cal(&cal);
    
	return 0;
}

