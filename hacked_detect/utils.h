/*
 * Detect a Library for hardware detection
 *
 * Copyright (C) 1998-2000 MandrakeSoft
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#ifndef UTILS_H
#define UTILS_H

# define _GNU_SOURCE 1
# define __USE_GNU 1

#include <features.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <config.h>
#include <string.h>

#ifdef HAVE_LIBISAPNP
#  include <isapnp/pnp-access.h>
#  include <isapnp/res-access.h>
#endif

/*gettext stuff*/
#ifdef ENABLE_NLS
#  include <locale.h>
#  include <libintl.h>
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
/* Stubs that do something close enough.  */
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)  
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif

/* IMPORTANT: The following comments are needet, otherwise we won't   */
/* get the strings i18n'ed :-\  (they have to stay AFTER the defines) */

#define MALLOC_ERROR            _("Can't allocate memory!\n")
// _("Can't allocate memory!\n")
#define FOPEN_READ_ERROR        _("Can't open file `%s' for reading!\n")
// _("Can't open file `%s' for reading!\n")
#define FOPEN_WRITE_ERROR       _("Can't open file `%s' for writing!\n")
// _("Can't open file `%s' for writing!\n")
#define KERNEL_ERROR            _("Can't get kernel version\n")
// _("Can't get kernel version\n")
#define KERNEL_VERSION_ERROR    _("You must have a kernel version superior at 2.1.120\n")
// _("You must have a kernel version superior at 2.1.120\n")
#define IOCTL_ERROR             _("Error in ioctl request!\n")
// _("Error in ioctl request!\n")

#define hex_val(c)	({ \
				char _c = (c); \
				isdigit(_c) ? _c - '0' : \
				tolower(_c) + 10 - 'a'; \
			})


/*
 * utils.c
 * Strings handling
 */
extern char *cut_word(char *string, int start, int end);
extern char *extract_word(char *string, int pos, char *delim);
extern char *find_word(char *word, char *file);
extern char *trim(char *string);
extern char *ToLower(char *str);
extern char *ToUpper(char *str);
/*
 * utils.c
 * Memory handling
 */
extern void *my_malloc(size_t size);
extern void *my_calloc(size_t nmemb, size_t size);

/*
 * utils.c
 * Misc functions
 */
extern int kernel_verif();
void __attribute__((noreturn)) die(char *msg, ...);

/*
 * options.c
 * Misc functions
 */
extern int parseCommandLine(int argc, char *argv[]);
extern void usage();
extern void version();
extern void print_serial_modem();

#endif
