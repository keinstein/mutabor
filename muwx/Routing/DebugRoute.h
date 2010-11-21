/*
 *  DebugRoute.h
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 13.04.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */


#ifdef DEBUG
void DebugCheckRoutes();
#else
#define DebugCheckRoutes()
#endif

