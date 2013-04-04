#ifndef I2CMANAGER_H_
#define I2CMANAGER_H_

class i2cManager {
public:
	i2cManager(const char * bus);
	virtual ~i2cManager();
	char readByte(short slaveAddress, char reg);
	bool writeByte(short slaveAddress, char reg, char value);
private:
	int deviceDescriptor;
	int lastAccessed;
	bool setSlaveAddress(short address);
};

#endif /* I2CMANAGER_H_ */

