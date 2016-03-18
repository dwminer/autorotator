#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BAUDRATE B9600
#define DEFAULT_DEVICE "/dev/ttyACM0"

int open_device(const char* name);
void setup_serial_params(int fd, struct termios *oldtio, struct termios *newtio);

int open_device(const char* name)
{
	if (!name)
		name = DEFAULT_DEVICE;
	return open(name, O_RDONLY | O_NOCTTY);
}

/*
 * Setup termios flags for non-canonical input processing from fd
 * Store existing flags in oldtio
 * Store new flags in newtio and use them to tcsetattr
*/
void setup_serial_params(int fd, struct termios *oldtio, struct termios *newtio)
{
	bzero(newtio, sizeof(*newtio));
	newtio->c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

	newtio->c_iflag = IGNPAR;

	newtio->c_oflag = CLOCAL;

	newtio->c_lflag = 0;

	newtio->c_lflag = 0;
	newtio->c_cc[VTIME] = 0;
	newtio->c_cc[VMIN] = 1;
	
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, newtio);
}
