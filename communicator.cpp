#include <osgGA/GUIEventAdapter>
#include <iostream>
#include <iomanip>
#include "communicator.h"
#include "acos.h"


void CommunicatorThread::run(void)
{
#ifndef SIMULATION
	// initialize serial port
	serialPort = new SerialPort();
	serialPort->init();
  #ifdef BART
	manager = new i2cManager("/dev/i2c-3");
	accelerometer = new LIS3LV02DLWrapper(manager);
	magnetometer = new HMC5843Wrapper(manager);
  #endif
#endif

#ifdef SIMULATION
	float dir = 0.001;
	float sensorVal[3];
	for (int i = 0; i < 3; ++i)
		sensorVal[i] = 0.0;
#endif

	while (!_done) {
		struct sMessage msg;
#ifdef SIMULATION
		msg.header = AcceleroValues & 0xff;
		msg.size = 3 * sizeof(float);
		float *ptr = (float *) msg.data;
		for (int i = 0; i < 3; ++i, ++ptr) {
			// turn random side
			unsigned int randVal = rand() & 1;
			sensorVal[i] = (randVal > 0) ? sensorVal[i] + dir : sensorVal[i];

			// clip sensor val to -0.5 < x < 0.5
			dir = (sensorVal[i] < -0.5) ? 0.001 : dir;
			dir = (sensorVal[i] > 0.5) ? -0.001 : dir;
			
			*ptr = sensorVal[i];
		}
#else
  #ifdef BART
		float sensorVal[3];
		if (accelerometer->getData(&sensorVal[0], &sensorVal[1], &sensorVal[2])) {
			// construct message
			msg.header = AcceleroValues & 0xff;
			msg.size = 3 * sizeof(float);
			float *ptr = (float *) msg.data;
			for (int i = 0; i < 3; ++i, ++ptr) {
				*ptr = sensorVal[i];
			}
			// send message via serial port
			serialPort->send((char *) &msg, msg.size + 2);
		}
  #else
		// read message from serial port
		serialPort->receive((char *) &msg.header, 1);
		serialPort->receive((char *) &msg.size, 1);
		serialPort->receive((char *) msg.data, msg.size);
  #endif
#endif	
		// handle message
		handle(&msg);
		
		// sleep for a while
#ifdef SIMULATION
		OpenThreads::Thread::microSleep(16000);
#else
		OpenThreads::Thread::microSleep(1000000);
#endif
	}

#ifndef SIMULATION
	// close port
	serialPort->deinit();
#endif
}

void CommunicatorThread::stop(void)
{
	_done = true;
}

void CommunicatorThread::handle(struct sMessage *msg)
{
	switch (msg->header) {
	case AcceleroValues:
		{
			float sensorVal[3];
			float xAngle, yAngle;
			float *ptr = (float *) msg->data;
			for (int i = 0; i < 3; ++i, ++ptr) {
				sensorVal[i] = *ptr;
			}
			// OSG_NOTICE << std::fixed << std::setprecision(3);
			// OSG_NOTICE <<"Accelerometer x: " << sensorVal[0] << ", ";
			// OSG_NOTICE <<"Accelerometer y: " << sensorVal[1] << ", ";
			// OSG_NOTICE <<"Accelerometer z: " << sensorVal[2] << std::endl;
			
			// calculate angles
			xAngle = fastAcos(sensorVal[0]) - (0.5 * osg::PI);
			yAngle = fastAcos(sensorVal[1]) - (0.5 * osg::PI);
			
			// update camera manipulator angles
			_cameraManip->setXAngle(xAngle);
			_cameraManip->setYAngle(yAngle);
		}
		break;
	default:
		break;
	}
}
