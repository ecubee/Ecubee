//
//  fusion.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 15/4/13.
//
//

#include <stdio.h>
#include <signal.h>
#include "i2c/MPU9150Wrapper.h"

#ifdef RASPBERRY_PI
#define I2C_BUS 1;
#else
#define I2C_BUS 3;
#endif

// globals
int done;

// forward declarations
void print_angles(float * angles);
void register_sig_handler();


int main(int argc, char **argv)
{
    float angles[3];
    int result;
    sensor = new MPU9150Wrapper(I2C_BUS);
    
    printf("Fusion Test Program. Use ^c to terminate\n\n");

    sensor->init();
    sensor->debug();
    
    while (!done) {
        if ((result = sensor->getEuler(&angles)) < 0) {
            fprintf(stderr, "Sensor read error");
            break;
        }
        if (!result)
            print_angles(&angles);
        
    }
    
    sensor->stop();
}

void print_angles(float * angles)
{
    printf("\rX: %0.0f Y: %0.0f Z: %0.0f        ",
           angles[0] * RAD_TO_DEGREE,
           angles[1] * RAD_TO_DEGREE,
           angles[2] * RAD_TO_DEGREE);
    
    fflush(stdout);
}

void sigint_handler(int sig)
{
	done = 1;
}

void register_sig_handler()
{
	struct sigaction sia;
    
	bzero(&sia, sizeof sia);
	sia.sa_handler = sigint_handler;
    
	if (sigaction(SIGINT, &sia, NULL) < 0) {
		perror("sigaction(SIGINT)");
		exit(1);
	}
}

