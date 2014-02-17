/*
	(c) 2009 Tobias Schlemmer,
	This file can be redistributed under the terms of GPLv2


*/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if ! (HAVE_INLINE)
#ifndef inline
#define inline
#endif

#include "stpcpy.h"

#endif

static const char * version = VERSION;
const char * mutabor_missfunc_version () {
	return version;
}

