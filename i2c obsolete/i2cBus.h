//
//  i2cBus.h
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#ifndef __Ecubee__i2cBus__
#define __Ecubee__i2cBus__

class i2cBus {
public:
	i2cBus(const char * bus);
	virtual ~i2cBus();
    friend class i2cSlave;
private:
	int file;
	short lastAccessed;
	bool setSlaveAddress(short address);
  //  bool releaseSlave(short address); Could be used with setSlaveAddress to let i2cSlave claim and release the bus, to be used when i2cSlaves run in different treads.
};

#endif /* defined(__Ecubee__i2cBus__) */
