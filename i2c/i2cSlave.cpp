//
//  i2cSlave.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#include "i2cSlave.h"
#include <stdio.h>   /* Standard input/output definitions */
//#include <termios.h> /* POSIX terminal control definitions */
//#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <stdlib.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <sys/ioctl.h>
#include <linux/i2c-dev.h> /* for the I2C_SLAVE constant and write/read functions*/


i2cSlave::i2cSlave(i2cBus * busptr, short add) {
    // I should have a bus and address
    bus = busptr;
    address = add;
}
i2cSlave::~i2cSlave() {
    // On shutdown, do nothing?
}


char i2cSlave::readRegByte(char reg) {
    int result;
    
    // set bus to our address
    bus->setSlaveAddress(address);
    result = i2c_smbus_read_byte_data(bus->file, reg);
    if (result < 0) {
        fprintf( stderr, "Failed read i2c device: %m\n" );
        return NULL;
    }
    return result & 0x0ff

}

char readByte() {
    int result;
    
    // set bus to our address
    bus->setSlaveAddress(address);
    result = i2c_smbus_read_byte(bus->file);
    if (result < 0) {
        fprintf( stderr, "Failed read i2c device: %m\n" );
        return NULL;
    }
    return result & 0x0ff
}

bool writeRegByte(char reg, char value) {
    
    // set bus to our address
    bus->setSlaveAddress(address);
    if !i2c_smbus_write_byte_data(bus->file, reg, value)
        return true;
    return false;
}

bool writeByte(char value) {
    
    // set bus to our address
    bus->setSlaveAddress(address);
    if !i2c_smbus_write_byte(bus->file, value)
        return true;
    return false;
}

unsigned short readRegWord(char reg) {
    int result;
    
    // set bus to our address
    bus->setSlaveAddress(address);
    result = i2c_smbus_read_word_data(bus->file, reg);
    if (result < 0) {
        fprintf( stderr, "Failed read i2c device: %m\n" );
        return NULL;
    }
    return result & 0x0ffff
}

int readBlock(char reg, char* data, int maxlength){
    int result;
    char * values[32];
    
    // set bus to our address
    bus->setSlaveAddress(address);

    result = i2c_smbus_read_block_data(bus->file, reg, values);
    
    if result > 0 && result <= maxlength {
        memcopy(data, values, result);
        return result;
    else
        return 0;
}

