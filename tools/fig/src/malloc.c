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

/* We provide malloc() as a user-defined (not auto-generated) library stub  */
/* file because it is necessary to use logNT, the version of the logging    */
/* code that does not include timing information, during instrumented calls */
/* to malloc(). The reason for this is because an infinite loop can result  */
/* with the timing portion of the default logging code, if a call to        */
/* gettimeofday() results in another call to malloc(), which recursively    */
/* invokes this library stub, which calls gettimeofday() again, etc.        */
/*                                                                          */
/* There are certainly other ways to get around this problem, but this was  */
/* the easiest to implement.                                                */

#define _GNU_SOURCE
#include <stdlib.h>
#include <errno.h>
#include "log.h"
#include "prob.h"
#include "util.h"
#include "func.h"

void *malloc(size_t size) {
  action a;
  int old_errno;
  void *rv;

  if (fig_error(MALLOC_INDEX, &a)) {
    logNT(INJECTED, "malloc(%d) Induced error - going to return %d, errno = %d\n", size, a.ret, a.err);
    errno = a.err;
    return (void *) a.ret;
  } else {
    rv = (void*)__libc_malloc(size);
    old_errno = errno;
    // Comment out this line to get rid of a LOT of logging overhead.
    logNT(ALL, "malloc(%d) library returning %p, errno %d\n", size, rv, errno);
    errno = old_errno;
    return rv;
  }
}
