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

#ifndef CONTROL_H
#define CONTROL_H

#define MAX_RULES 256
#define MAX_CALLS 256

/* The data structures that make up the callset structure, which is */
/* contains information about the calls being instrumented and the  */
/* probabilities and types of errors that they may return.          */

struct _interval
{
  int left;
  int right; // use -1 to indicate infinity, ie open right interval
};
typedef struct _interval interval;

struct _rule
{
  interval i;
  int      retval;
  int      errno;
  double   prob;
};
typedef struct _rule rule;

struct _ruleset {
  int numRules;
  rule * *rules;
};
typedef struct _ruleset ruleset;

struct _call {
  int callNumber;
  ruleset *rules;
};
typedef struct _call call;

struct _callset {
  int numCalls;
  call * * calls;
};
typedef struct _callset callset;

callset * getCallSet (char * file);

void printRule (rule * r);
void printCall (call* c);
void printCallSet (callset * cs);

#endif
