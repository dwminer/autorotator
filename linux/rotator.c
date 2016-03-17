#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
//#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>

Display *dpy;

void die(const char *msg);

int main(int argc, char *argv[])
{
	if (!(dpy = XOpenDisplay(NULL)))
		die("Couldn't open display.\n");
	Window w = XRootWindow(dpy, 0);
	XRRScreenConfiguration *config = XRRGetScreenInfo(dpy, w);
	Time *config_timestamp = malloc(sizeof(Time));
	Time servertime;
	servertime = XRRTimes(dpy, 0, config_timestamp);
	if (res = XRRSetScreenConfig(dpy, config, w, 0, RR_Rotate_90, servertime))
		//res is nonzero if config failed to apply. need to re-read config
		die("Failed\n");

	exit(0);
}

void die(const char *msg)
{
	perror(msg);
	exit(-1);
}
