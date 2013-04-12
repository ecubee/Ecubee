//
//  MPU9150.cpp
//  Ecubee
//
//  Created by Marcel Laurijsse on 5/4/13.
//
//  TODO: Integrated interupt support using GPIO pin
//

#include "MPU9150Wrapper.h"




MPU9150Wrapper::MPU9150Wrapper(i2cBus * man, char address) : i2cSlave(bus, address) {
    
}

MPU9150Wrapper::~MPU9150Wrapper() {
    //do some shutdown?
}

MPU9150Wrapper::init() {
    
}

//MPU9150::init(bool useFifo = false) {
//    // Configuration and initialization procedures
//    
//    // Reset all registers
//    writeRegByte(MPU9150_REG_POWER_MANAGEMENT, MPU9150_VALUE_RESET_DEVICE);
//    
//    // Set LPF
//    writeRegByte(MPU9150_REG_CONFIG_SYNC_DLPF, MPU9150_VALUE_DLPF_BANDWIDTH_5HZ);
//    
//    // Set Sensor Range
//    writeRegByte(MPU9150_REG_GYRO_CONFIG, MPU9150_VALUE_GYRO_RANGE_250);
//    writeRegByte(MPU9150_REG_ACCEL_CONFIG, MPU9150_VALUE_ACCEL_RANGE_2G);
//
//    // Use the FIFO buffer?
//    fifoEnabled = useFifo;
//    if useFifo 
//        writeRegByte(MPU9150_REG_FIFO_ENABLE, (MPU9150_VALUE_FIFO_ENABLE_GYRO | MPU9150_VALUE_FIFO_ENABLE_ACCEL | MPU9150_VALUE_FIFO_ENABLE_MAGNETO));
//    else
//        writeRegByte(MPU9150_REG_FIFO_ENABLE, 0x00);
//        
//    
//    // Configure external sensor (magnetometer)
//    writeRegByte(MPU9150_REG_I2C_MASTER_CONTROL, (MPU9150_VALUE_WAIT_FOR_ES | MPU9150_VALUE_I2C_MST_CLK_400KHZ));
//    
//    // Switch to Gyro clock
//    writeRegByte(MPU9150_REG_POWER_MANAGEMENT, MPU9150_VALUE_CLOCK_PLL_X);
//    
//    // Reset all measurements
//    reset();
//    
//}

MPU9150::reset() {
    // this clears the sensors of all analog an digital traces left by previous measurements
    
    char command
    
    if fifoEnabled
        command = MPU9150_VALUE_FIFO_ENABLE_GLOBAL | MPU9150_VALUE_USER_CTRL_RESET | MPU9150_VALUE_I2C_MST_EN;
    else
        command = MPU9150_VALUE_USER_CTRL_RESET | MPU9150_VALUE_I2C_MST_EN;

    writeRegByte(MPU9150_REG_USER_CTRL, command);
        
}