//
//  fusion.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 15/4/13.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <float.h>
#include "i2c/MPU9150Wrapper.h"
#include "i2c/vector3d.h"
#include "i2c/linux_glue.h"

#ifdef RASPBERRYPI
#define I2C_BUS 1
#else
#define I2C_BUS 3
#endif

// globals
int done;

// forward declarations
void print_angles(vector3d_t angles);
void register_sig_handler();


int main(int argc, char **argv)
{
    vector3d_t angles;
    int result;
    MPU9150Wrapper * sensor;
    
    sensor = new MPU9150Wrapper(I2C_BUS);
    
    printf("Fusion Test Program. Use ^c to terminate\n\n");

    if (sensor->init()) 
        exit(1);
    
    sensor->debug();
    
    printf("\nInitialization successful. Entering read loop\n\n");
    
    while (!done) {
        if ((result = sensor->getEuler(angles)) < 0) {
            fprintf(stderr, "Sensor read error");
            break;
        }
        if (!result)
            print_angles(angles);
        
        linux_delay_ms(100);

    }
    
    sensor->stop();
}

void print_angles(vector3d_t angles)
{
    printf("\rX: %0.0f Y: %0.0f Z: %0.0f   ", angles[VEC3_X] * RAD_TO_DEGREE, angles[VEC3_Y] * RAD_TO_DEGREE, angles[VEC3_Z] * RAD_TO_DEGREE);
       fflush(stdout);
}

void sigint_handler(int sig)
{
	done = 1;
}

void register_sig_handler()
{
	struct sigaction sia;
    
	memset(&sia, 0, sizeof sia);
	sia.sa_handler = sigint_handler;
    
	if (sigaction(SIGINT, &sia, NULL) < 0) {
		perror("sigaction(SIGINT)");
		exit(1);
	}
}

