#ifndef __UTILS_H
#define __UTILS_H

/* Commonly used routines for various frontend GUI pieces of code. */

#define DUMP_FILE "/qagent_dump"
#define HEADER_FILE "/qagent_header"
#define ENCRYPT_FILE "/qagent_encrypt"
#define TARGET_FILE "/qagent_target"

// parse command line, set up strings
void parse_args ( int argc, char *argv[] );

// prepare for launch - reset all variables
void prepare_for_launch ( void );

void clean_up ( void );

void gen_header ( void );

int check_for_GPG ( void );

#endif
