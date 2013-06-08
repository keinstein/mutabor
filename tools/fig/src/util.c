/*
 * "Copyright (c) 2002 and The Regents of the University 
 * of California.  All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 *  Authors:   Peter Broadwell (pbwell@cs.berkeley.edu)
 *             Naveen Sastry (nks@cs.berkeley.edu)
 *             Jonathan Traupman (jont@cs.berkeley.edu)
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include "util.h"

/*
 * returns a pointer to the implementation of 'funcName' in
 * the libc library.  If not found, terminates the program.
 * This tool can be used (and is used, in a couple cases) to
 * describe the non-instrumented version of a libc library, if
 * a secondary definition (such as __libc_open for open) doesn't
 * exist.
 *
 * You can search for secondary definitions in the libc file by
 * running objdump -T /lib/libc.so.# | grep <library function you're
 * looking for>.
 *
 * Note that of the other software packages that use dlsym, many
 * cache the pointer to a function once it's been looked up to
 * avoid having to do the lookup multiple times.
 */
void *getLibraryFunction(const char *funcName)
{
    void *res;

    if ((res = dlsym(RTLD_NEXT, funcName)) == NULL) {
      perror();
      _exit(1);
    }
    return res; 
}
