#ifndef _getline_h_
#define _getline_h_ 1

#include <stdio.h>

#if defined (__GNUC__) || (defined (__STDC__) && __STDC__)
#define __PROTO(args) args
#else
#define __PROTO(args) ()
#endif  /* GCC.  */

#ifdef __cplusplus
extern "C"
{
#endif

int
  getline __PROTO ((char **_lineptr, size_t *_n, FILE *_stream));
int
  getstr __PROTO ((char **_lineptr, size_t *_n, FILE *_stream,
		   char _terminator, int _offset));
#ifdef __cplusplus
}
#endif

#endif /* _getline_h_ */
