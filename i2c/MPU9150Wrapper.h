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

#define MPU9150_REG_SAMPLE_RATE_DEVIDER 0x19
#define MPU9150_REG_CONFIG_SYNC_DLPF 0x1A // External sync and DLPF config
#define MPU9150_REG_GYRO_CONFIG 0x1B
#define MPU9150_REG_ACCEL_CONFIG 0x1C
#define MPU9150_REG_FIFO_ENABLE 0x23 // Enable fifo buffer
#define MPU9150_REG_I2C_MASTER_CONTROL 0x24
#define MPU9150_REG_USER_CTRL 0x6A
#define MPU9150_REG_POWER_MANAGEMENT 0x6B

#define MPU9150_VALUE_DLPF_BANDWIDTH_5HZ 0x06
#define MPU9150_VALUE_DLPF_BANDWIDTH_10HZ 0x05
#define MPU9150_VALUE_DLPF_BANDWIDTH_20HZ 0x04
#define MPU9150_VALUE_DLPF_BANDWIDTH_44HZ 0x03
#define MPU9150_VALUE_DLPF_BANDWIDTH_94HZ 0x02
#define MPU9150_VALUE_DLPF_BANDWIDTH_184HZ 0x01
#define MPU9150_VALUE_DLPF_BANDWIDTH_260HZ 0x00 // Additionally sets FS_gyro = 8kHz
#define MPU9150_VALUE_GYRO_RANGE_250 0x00
#define MPU9150_VALUE_GYRO_RANGE_500 0x08
#define MPU9150_VALUE_GYRO_RANGE_1000 0x10
#define MPU9150_VALUE_GYRO_RANGE_2000 0x18
#define MPU9150_VALUE_ACCEL_RANGE_2G 0x00
#define MPU9150_VALUE_ACCEL_RANGE_4G 0x08
#define MPU9150_VALUE_ACCEL_RANGE_8G 0x10
#define MPU9150_VALUE_ACCEL_RANGE_16G 0x18
#define MPU9150_VALUE_FIFO_ENABLE_GYRO 0x70
#define MPU9150_VALUE_FIFO_ENABLE_ACCEL 0x08
#define MPU9150_VALUE_FIFO_ENABLE_MAGNETO 0x01 // Verify slave number of Magnetometer
#define MPU9150_VALUE_WAIT_FOR_ES 0x40
#define MPU9150_VALUE_I2C_MST_CLK_400KHZ 0x13
#define MPU9150_VALUE_FIFO_ENABLE_GLOBAL 0x40
#define MPU9150_VALUE_USER_CTRL_RESET 0x07
#define MPU9150_VALUE_I2C_MST_EN 0x20
#define MPU9150_VALUE_RESET_DEVICE 0x80 // Reset all register values to default
#define MPU9150_VALUE_CLOCK_PLL_X 0x01

class MPU9150 : public i2cSlave {
public:
	MPU9150(i2cBus * bus) : MPU9150(bus, MPU9150_ADDRESS);
	MPU9150(i2cBus * man, char address) : i2cSlave(bus, address);
	~MPU9150();
    bool init();
    bool reset();
//	bool getData(float* vx, float* vy, float* vz);

private:
    bool fifoEnabled;
    unsigned short getFifoCount();
    void readFifo();
    
};

#endif /* defined(__Ecubee__MPU9150__) */
