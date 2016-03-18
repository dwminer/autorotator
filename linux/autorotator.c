#include "ar_serial.h"
#include "ar_rotate.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int fd = open_device(NULL);
	struct termios oldtio, newtio;
	setup_serial_params(fd, &oldtio, &newtio);
	Randr_data *vars = init_xrandr_vars();
	
	char buf[255];
	char cont = 1;
	int res;
	while (cont)
	{
		res = read(fd, buf, 255);
		char rot = buf[0];
		buf[res] = 0;
		rotate_screen(rot, vars);
	}

	return 0;
}
