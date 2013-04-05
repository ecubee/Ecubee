//
//  i2cSlave.h
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//

#ifndef __Ecubee__i2cSlave__
#define __Ecubee__i2cSlave__

class i2cSlave {
public:
    i2cSlave(i2cBus * busptr, short add);
    virtual ~i2cSlave();
    
protected:
    char readRegByte(char reg);             // Read byte from specified register
    char readByte();                        // Read byte from current register
    bool writeRegByte(char reg, char value);    // Write byte to specified register
    bool writeByte(char value);                 // Write byte to current register
    unsigned short readRegWord(char reg);               // Read out en create short from two adjecent registers
    int readRegBlock(char reg, char* data, int length); // Read out block of data with max length

private:
    short address;
    i2cBus * bus;
}


#endif /* defined(__Ecubee__i2cSlave__) */
