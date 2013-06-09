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
#include "control.h"
#include "log.h"

/* Contains functions to print to the log file portions of the callset */
/* data structure, for debugging purposes.                             */

void printRule (rule * r) {
  log(NONE, "::printRule - interval: [%d, %d] errno %d returns %d with prob %lf\n", 
          r->i.left, r->i.right, r->errno, r->retval, r->prob);
}

void printCall (call* c) {
  int i;
  ruleset * rs = c->rules;
  
  log (NONE, "::printCall - Call no: %d with %d rules\n", c->callNumber, rs->numRules);
  for (i = 0; i < rs->numRules; i++) {
    printRule (rs->rules[i]);
  }
}

void printCallSet (callset * cs) {
  int i;
  log (NONE, "::printCallSet - There are %d calls\n", cs->numCalls);
  for (i = 0; i < cs->numCalls; i++) {
    printCall (cs->calls[i]);
  }
}
