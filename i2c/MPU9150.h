//
//  MPU9150.h
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#ifndef __Ecubee__MPU9150__
#define __Ecubee__MPU9150__

#define MPU9150_ADDRESS 0x68

class MPU9150 : private i2cSlave {
public:
	MPU9150(i2cBus * bus) : MPU9150(bus, MPU9150_ADDRESS);
	MPU9150(i2cBus * man, char address) : i2cSlave(bus, address);
	~MPU9150();
//	bool getData(float* vx, float* vy, float* vz);


    
};

#endif /* defined(__Ecubee__MPU9150__) */
