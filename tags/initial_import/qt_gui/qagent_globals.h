#ifndef __QAGENT_GLOBALS_H
#define __QAGENT_GLOBALS_H

#ifndef FALSE
#define FALSE (0)
#define TRUE (!FALSE)
#endif

#define QAGENT_VERSION "0.1"

#define QAGENT_STANDARD_MODE 0
#define QAGENT_ADVANCED_MODE 1

extern char *argv0;

extern char *work_dir;

extern char *home;
extern char *product_path;
extern char *product_name;
extern char *product_cdrom;
extern char *product_version;
extern char *product_desc;
extern char *product_prefs;
extern char *stack_trace_path;

extern char *support_path;
extern char *dump_path;
extern char *header_path;
extern char *encrypt_path;

extern char *user_file_path;
extern char *user_name;
extern char *user_email;
extern char *user_regno;
extern char *user_comment;

extern int useGPG;

#ifdef ENABLE_SETUPDB

extern int useSetupDB;

#endif

extern int mode;

#endif