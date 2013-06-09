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

#ifndef PROB_H
#define PROB_H

#define MAX_CALL_TYPES 512

/*
 * Struct describing what should be done -- to fault or not to fault, that is
 * the question.
 */
struct _action
{
  // if we are not to use the library, what return value do we use? 
  int ret;
  // if we are not to use the library, what to set errno:
  int err;
} ;
typedef struct _action action;

/*
 * On return, we fill in action with a struct describing what should be done.
 *
 * call - the numeric associated with the call.
 * action - describes what the caller should do -- whether they should use the
 *        glibc version or not; if not, it describes what should be returned
 *        and what errno should be.
 * returns whether to call the library version or not. 0 means call the lib
 * version normally (ie no error), non-zero means there is an error and follow
 * the directions given in action [ in fact, we return the rull number that
 * that caused the error, where 1 is the first rule].
 */
int fig_error (int call, action * act);


#endif
