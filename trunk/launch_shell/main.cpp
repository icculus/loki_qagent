#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE (!FALSE)

int check_for_X ( void )
{
	int result;
	char *display_name = NULL;
	Display *display;

	if ((display = XOpenDisplay(display_name)) == NULL)
	{
		result = FALSE;
#ifdef QAGENT_VERBOSE
		fprintf(stderr,"No X Server Found\n");
#endif
	}
	else
	{
		result = TRUE;
#ifdef QAGENT_VERBOSE
		fprintf(stderr,"X Server Found\n");
#endif
		XCloseDisplay(display);
	}

	return result;

}

int main ( int argc, char *argv[] )
{
	if (check_for_X())
	{
		execv("./qagent_x11",argv);
	}
	else
	{
		execv("./qagent_curses",argv);	
	}
}
