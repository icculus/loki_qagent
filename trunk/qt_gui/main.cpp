#include "host_def.h"
#include "qagent_globals.h"
#include "x_utils.h"
#include "utils.h"

#include "qt_gui.h"
#include "console_gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *argv0;
char *work_dir;

char *product_name;
char *product_version;
char *product_desc;
char *product_path;
char *product_prefs;
char *product_cdrom;
char *stack_trace_path;

char *support_path;
char *dump_path;
char *header_path;
char *encrypt_path;


char *home;

char *user_name = NULL;
char *user_email = NULL;
char *user_regno = NULL;
char *user_comment = NULL;
char *user_file_path = NULL;

int useGPG = FALSE;

int mode = QAGENT_STANDARD_MODE;

int main (int argc, char *argv[])
{

	parse_args(argc,argv);
	prepare_for_launch();
	run_QT_GUI(argc,argv);

}
