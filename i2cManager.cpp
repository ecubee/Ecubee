#include "i2cManager.h"
#include <stdio.h>   /* Standard input/output definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <stdlib.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <sys/ioctl.h>
#include "i2c-dev.h" /* for the I2C_SLAVE constant and write/read functions*/

/******************************************
 * The constructor starts communication via the i2c device
 ******************************************/
i2cManager::i2cManager(const char * bus) {
	// open a pointer to the device, and make it able to read and write to it
	deviceDescriptor = open( bus, O_RDWR ); // the used beagle board expansion header allocates to i2c-2
	if(!deviceDescriptor){
		fprintf(stderr, "Error while trying to open \"%s\"",bus);
		exit(-1);
	}
}

/******************************************
 * The constructor stops communication via the i2c device
 ******************************************/

i2cManager::~i2cManager() {
	// TODO Auto-generated destructor stub
	close(deviceDescriptor);
}

/**************************************************************
 * Read a byte from the given address and register
 **************************************************************/
char i2cManager::readByte(short slaveAddress, char reg){
	// set the slave address, so we can read of that client
	setSlaveAddress(slaveAddress);	
	// now actually read the value from the register:
	return i2c_smbus_read_word_data(deviceDescriptor,reg);
}

/**************************************************************
 * write a byte to the given address and register
 **************************************************************/
bool i2cManager::writeByte(short slaveAddress, char reg, char value){
	// set the slave address, so we can read of that client
	setSlaveAddress(slaveAddress);	
	
	// and actually try to write to the specified register:
	if( i2c_smbus_write_byte_data( deviceDescriptor, reg, value ) < 0 ){
	        fprintf( stderr, "Failed to write value to I2C device: %m\n" );
		return false;
	}
	return true;
}

/**************************************************************
 * write a byte from the given address and register
 **************************************************************/
bool i2cManager::setSlaveAddress(short address){
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
