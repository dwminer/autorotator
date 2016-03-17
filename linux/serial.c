#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BAUDRATE B9600
#define SERIALDEVICE "/dev/ttyACM0"

void die(const char *msg);

int main(int argc, char *argv[])
{
	int fd, c, res;
	struct termios oldtio, newtio;
	char buf[255];

	fd = open(SERIALDEVICE, O_RDONLY | O_NOCTTY);

	//I really have no idea if any of this is even necessary anymore.
	//confirmed: these actually do things and it can fuck with how things work if you're not careful to change it back
	//does that mean that actually using this could be problematic? better off using libusb?
	//or is termios terminal-specific in that other running processes aren't effected? since tcsetattr is non-blocking that seems to the case, otherwise you'd have to wait to make sure the resource is available
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

	newtio.c_iflag = IGNPAR ;//| ICRNL;

	newtio.c_oflag = CLOCAL;

	newtio.c_lflag = 0; //ICANON;

	newtio.c_lflag = 0;
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 1;
	
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);
	
	while(1)
	{
		res = read(fd, buf, 255);
		char rot = buf[0];
		buf[res] = 0;
		printf(":%d:%d\n", rot, res);
	}

	tcsetattr(fd, TCSANOW, &oldtio);
	
}

void die(const char *msg)
{
	perror(msg);
	exit(-1);
}

