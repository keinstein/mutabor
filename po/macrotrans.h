/*
 *  macrotrans.h
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 15.10.07.
 *  Copyright 2007 TU Dresden. All rights reserved.
 *
 */

#include "config.h"
#define CONCAT(A,B) A # B

/* This function has the only purpose to be preprocessed in order to allow translation of macros */

inline void translate () {
	printf(_(PACKAGE_NAME" -- %s"));
}
