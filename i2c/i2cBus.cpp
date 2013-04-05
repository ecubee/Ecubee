//
//  i2cBus.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#include "i2cBus.h"

i2cBus::i2cBus(const char * busname) {
	// open a pointer to the device, and make it able to read and write to it
	file = open(busname, O_RDWR ); // the used beagle board expansion header allocates to i2c-2
	if(!file){
		fprintf(stderr, "Error while trying to open \"%s\"",bus);
		exit(-1); 
	}
} 
i2cBus::~i2cBus () {
    close(file);
}

bool i2cBus::setSlaveAddress(short address){
	// set the slave address, so we can read of that client: (perhaps create a lastConnected var?)
	if(address != lastAccessed){
		if( ioctl( deviceDescriptor, I2C_SLAVE, address ) < 0 )
		{
            fprintf( stderr, "Failed to set i2c slave address: %m\n" );
            return false;
		}
		lastAccessed = address;
		return true;
	}else{
		// already set to this address!
		return true;
	}
}