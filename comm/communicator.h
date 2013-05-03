#ifndef __COMMUNICATOR_H__
#define __COMMUNICATOR_H__

#include <osgGA/EventQueue>
#include <OpenThreads/Thread>
#include "CustomCamera.h"

#ifndef SIMULATION
	#include "rs232.h"

  #ifdef BART
	#include "MPU9150Wrapper.h"
  #endif
#endif

#define MAX_DATA_SIZE	255

enum eHeader {
    Dummy,
    FusedValues,
    GyroValues,
	MagnetoValues,
	AcceleroValues
};

struct sMessage {
	unsigned char header;
	unsigned char size;
    unsigned char dummy[2];
	unsigned char data[MAX_DATA_SIZE];
};

class CommunicatorThread : public OpenThreads::Thread
{
public:
	CommunicatorThread(CustomCamera *cam) : _done(false), _cameraManip(cam) {}
	virtual void run(void);
	void stop(void);
	void handle(struct sMessage *msg);

protected:
	bool _done;
	CustomCamera *_cameraManip;
#ifndef SIMULATION
	SerialPort *serialPort;
  #ifdef BART
    MPU9150Wrapper * sensor;
  #endif
#endif
};

#endif
