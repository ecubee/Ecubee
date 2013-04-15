#include <osgGA/GUIEventAdapter>
#include <iostream>
#include <iomanip>
#include "communicator.h"
#include "acos.h"
#include "vector3d.h"
#include "MPU9150Wrapper.h"


void CommunicatorThread::run(void)
{
#ifndef SIMULATION
	// initialize serial port
	serialPort = new SerialPort();
	serialPort->init();
  #ifdef BART
	sensor = new MPU9150Wrapper();
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
		msg.header = FusedValues & 0xff;
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
		vector3d_t sensorVal;
		if (!sensor->getEuler(sensorVal)) {
			// construct message
			msg.header = AcceleroValues & 0xff;
			msg.size = sizeof(vector3d_t);
			float *ptr = (float *) msg.data;
			for (int i = 0; i < 3; ++i, ++ptr) {
				*ptr = sensorVal[i];
			}
			// send message via serial port
			serialPort->send((char *) &msg, msg.size + 2);
            _cameraManip->setXAngle(sensorVal[0]);
			_cameraManip->setYAngle(sensorVal[1]);
            _cameraManip->setZAngle(sensorVal[2]);
		}
  #else
		// read message from serial port
		serialPort->receive((char *) &msg.header, 1);
		serialPort->receive((char *) &msg.size, 1);
		serialPort->receive((char *) msg.data, msg.size);
        // handle message
		handle(&msg);

  #endif
#endif	
		
		// sleep for a while
#ifdef SIMULATION
		OpenThreads::Thread::microSleep(16000);
#else
		OpenThreads::Thread::microSleep(10000);
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
	case FusedValues:
		{
			float sensorVal[3];
			float *ptr = (float *) msg->data;
			for (int i = 0; i < 3; ++i, ++ptr) {
				sensorVal[i] = *ptr;
			}
			// OSG_NOTICE << std::fixed << std::setprecision(3);
			// OSG_NOTICE <<"Accelerometer x: " << sensorVal[0] << ", ";
			// OSG_NOTICE <<"Accelerometer y: " << sensorVal[1] << ", ";
			// OSG_NOTICE <<"Accelerometer z: " << sensorVal[2] << std::endl;
			
			// calculate angles
			//xAngle = fastAcos(sensorVal[0]) - (0.5 * osg::PI);
			//yAngle = fastAcos(sensorVal[1]) - (0.5 * osg::PI);
			
			// update camera manipulator angles
			_cameraManip->setXAngle(sensorVal[0]);
			_cameraManip->setYAngle(sensorVal[1]);
            _cameraManip->setZAngle(sensorVal[2]);
		}
		break;
	default:
		break;
	}
}
