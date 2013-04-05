//
//  MPU9150.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#include "MPU9150.h"



MPU9150::MPU9150(i2cBus * bus) : i2cSlave(bus, MPU9150_ADDRESS) {
    //some other important stuff
}

MPU9150::MPU9150(i2cBus * man, char address) : i2cSlave(bus, address) {
    
}

MPU9150::~MPU9150() {
    //do some shutdown?
}
