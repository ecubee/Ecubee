/*
 * Serial Port Class
 */
 
/*
	bool init(void)
	Must be called before any other function. This opens the serial port device file.
	Returns true if successful.
	
	bool deinit(void)
	Called when serial port communication is no longer needed.
	This closes the device file and restores the port's old settings.
	Returns true if successful.
	
	int send(char *buf, int len)
	Used to send data over the serial port.
	Input:	buf		buffer with data to send
			len		amount of bytes to send
	Returns the number of written bytes on success. On error, -1 is returned, and errno is set appropriately.
	
	int receive(char *buf, int len)
	Used to receive data from the serial port.
	Input:	buf		buffer to store the received data
			len		amount of bytes to receive
	On success, the number of bytes read is returned. On error, -1 is returned, and errno is set appropriately.
*/	

#ifndef __RS232_H__
#define __RS232_H__

#include <termios.h>

#define UART_DEVICE	"/dev/ttyS1"

class SerialPort {
public:
	// SerialPort(int baudrate = 115200);
	// ~SerialPort(void);
	bool init(void);
	bool deinit(void);
	int send(char *buf, int len);
	int receive(char *buf, int len);
private:
	int port;
	struct termios old_port_settings;
	struct termios new_port_settings;
};

#endif