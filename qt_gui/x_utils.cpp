#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>

#include "host_def.h"
#include "qagent_globals.h"
#include "x_utils.h"

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
