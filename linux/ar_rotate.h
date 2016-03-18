#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/extensions/Xrandr.h>

typedef struct randr_data
{
	Display *dpy;
	Window w;
	XRRScreenConfiguration *config;
	Time *config_timestamp;
	Time server_time;
} Randr_data;

Randr_data *init_xrandr_vars();
void reload_xrandr_vars(Randr_data *vars);
void rotate_screen(int orientation, Randr_data *vars);
void die(const char *msg);

Randr_data* init_xrandr_vars()
{
	Randr_data *vars = malloc(sizeof(Randr_data));
	if (!(vars->dpy = XOpenDisplay(NULL)))
		die("Couldn't open display.\n");
	vars->w = XRootWindow(vars->dpy, 0);
	vars->config = XRRGetScreenInfo(vars->dpy, vars->w);
	vars->config_timestamp = malloc(sizeof(Time));
	vars->server_time = XRRTimes(vars->dpy, 0, vars->config_timestamp);

	return vars;
}

/*
 * If stored config is out of date, Xrandr will reject rotation call
 * In this case config could be reloaded
*/
void reload_xrandr_vars(Randr_data *vars)
{
	vars->config = XRRGetScreenInfo(vars->dpy, vars->w);
	vars->server_time = XRRTimes(vars->dpy, 0, vars->config_timestamp);
}

/*
 * Attempts to rotate the screen according to the given orientation
 * Will attempt to reload the config and re-attempt rotation once upon failure
 * TODO may need to reload config every time
 * TODO will most likely need a mutex if I thread rotate calls
*/
void rotate_screen(int orientation, Randr_data *vars)
{
	int res;
	if (res = XRRSetScreenConfig(vars->dpy, vars->config, vars->w, 0, orientation, vars->server_time))
	{
		printf("SetScreenConfig failed, attempting to reload conf.");
		reload_xrandr_vars(vars);
		if (res = XRRSetScreenConfig(vars->dpy, vars->config, vars->w, 0, orientation, vars->server_time))
			die("Failed to rotate screen after reloading config");
	}
}

void die(const char *msg)
{
	perror(msg);
	exit(-1);
}
