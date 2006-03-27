#if HAVE_CONFIG_H
#  include "config.h"
#endif

#if ! (HAVE_STPCPY)

inline char * mutabor_stpcpy(char *restrict TO, const char *restrict FROM){
	while ( ( (*(TO++)) = (*(FROM++)) ) ) ;
	return TO;
}

#endif
