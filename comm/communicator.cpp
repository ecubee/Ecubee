#include <osgGA/GUIEventAdapter>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "communicator.h"
#include "acos.h"
#include "vector3d.h"
#include "MPU9150Wrapper.h"


void CommunicatorThread::run(void)
{
	// initialize serial port
	serialPort = new SerialPort();
	serialPort->init();
  #ifdef BART
    vector3d_t sensorVal;
	sensor = new MPU9150Wrapper();
    sensor->init();
    sensor->debug();
  #endif

	while (!_done) {
		struct sMessage msg;
  #ifdef BART
		if (!sensor->getEuler(sensorVal)) {
			// construct message
			msg.header = AcceleroValues & 0xff;
			msg.size = sizeof(vector3d_t);
			float *ptr = (float *) msg.data;
			for (int i = 0; i < 3; ++i, ++ptr) {
				*ptr = sensorVal[i];
			}
			// send message via serial port
			//serialPort->send((char *) &msg, msg.size + 2);
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
		
		// sleep for a while
		OpenThreads::Thread::microSleep(10000);
	}

    // We're done, so tidy up...
    
	// close port
	serialPort->deinit();
    delete serialPort;
 #ifdef BART
    delete sensor;
    exit(0);
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
