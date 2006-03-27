#ifndef MISSFUNC_STPCPY_H
#define MISSFUNC_STPCPY_H

#if HAVE_INLINE
#include "stpcpy.c"
#else 
char * mutabor_stpcpy(char *restrict TO, const char *restrict FROM);
#endif

#define stpcpy mutabor_stpcpy

#endif
