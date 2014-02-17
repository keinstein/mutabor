#ifndef MISSFUNC_STPCPY_H
#define MISSFUNC_STPCPY_H

#if ! (HAVE_STPCPY)

#if HAVE_INLINE || MUTABOR_BUILD_MISSFUNC

static inline char * mutabor_stpcpy(char *restrict TO, const char *restrict FROM){
	while ( ( (*(TO++)) = (*(FROM++)) ) ) ;
	return TO;
}

#else 
char * mutabor_stpcpy(char *restrict TO, const char *restrict FROM);
#endif /* inline */

#define stpcpy mutabor_stpcpy

#endif /* HAVE_STPCPY */
#endif /* MISSFUNC_STPCPY_H */
