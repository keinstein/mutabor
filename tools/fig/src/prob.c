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
#include <stdlib.h>
#include "prob.h"
#include "log.h"
#include "control.h"
#include <sys/time.h>

static int initialized = 0;
struct _callwrap {
  call* call;
  int numcalls;
};
typedef struct _callwrap callwrap;
static callwrap calls [MAX_CALLS];

/*
 * This function is run once for each process running under FIG. It is
 * triggered when the program first calls a library function that has been
 * instrumented by FIG. The function opens the control file specified by
 * the LIBFIG_CONTROL environment variable, parses its contents and generates
 * a structure that keeps track of the number of calls that have been made
 * to each instrumented function. The structure also contains the rules
 * as to when and what types of errors should be injected into various
 * instrumented library calls.
 *
 * NOT MT-SAFE
 */
static void init()
{
  struct timeval te;
  struct timezone tz;
  char * controlFile = getenv("LIBFIG_CONTROL");
  callset * cs;
  rule * tmp;
  int i, j, callno, numRules;
  static int initializing = 0;

  if (initializing == 1) {
    return;
  }
  initializing = 1;
  
  memset (&tz, 0, sizeof tz);
  memset (&calls, 0, (sizeof (callwrap)) * MAX_CALLS);

  gettimeofday (&te, &tz);
  srand (te.tv_usec);
  if (!controlFile) {
    log (NONE, "prob::init() control file not specified. Defaulting to null"
         " file.\n");
  } else {
    log (NONE, "prob::init() Using control file name: %s\n", controlFile);
    cs = getCallSet (controlFile);
    if (!cs->numCalls) {
      log (NONE, "prob::init() Using an empty control file.\n");
    }
    for (i = 0 ; i < cs->numCalls ; i++) {
      callno = cs->calls[i]->callNumber;
      calls[callno].call = cs->calls[i];
      numRules = calls[callno].call->rules->numRules;
      for (j = 0; j < numRules / 2 ; j++) {
        tmp = calls[callno].call->rules->rules[j];
        calls[callno].call->rules->rules[j] =
          calls[callno].call->rules->rules[numRules-j-1];
        calls[callno].call->rules->rules[numRules-j-1] = tmp;        
      }
//      printCall (calls[callno].call);
    }
    free (cs);
    log (NONE, "Sorted call set.\n");
  }
  initialized = 1;
  initializing = 0;
} 

/* Returns 1 or 0, depending on the given probability of getting a 1 */
static int event (double prob)
{
  int i = rand() < prob * RAND_MAX;
  return (i);
}

/*
 * returns whether the rule matches the given call or not.
 *
 * rule - the rule that we're checking
 * callno - instance of the call, i.e, how many calls to this particular call
 *          type have been made in the past.
 */
static int match (rule * r, int callno)
{
  return (r->i.left <= callno && (r->i.right == -1 ||
                                  r->i.right >= callno));
}

/*
 * Returns nonzero if an error (defined by the act structure) should be returned
 * for a particular call to an instrumented FIG library function.
 * Returns 0 if the call should be allowed to complete normally.
 *
 * May produce errors in MT-cases [we perform an increment op. that should be
 * protected by a lock.]
 */
int fig_error (int call, action * act)
{
  int i;

  if (initialized == 0) {
    init();
  }

  // Return 0 (no error) if the callset hasn't finished being built yet.
  // This only happens if an instrumented call is invoked DURING the init().
  if (!calls[call].call) {
    return 0;
  }
  calls[call].numcalls ++;
  for (i = 0; i < calls[call].call->rules->numRules; i++) {
    if (match (calls[call].call->rules->rules[i], calls[call].numcalls-1) &&
        event(calls[call].call->rules->rules[i]->prob)) {
      act->ret = calls[call].call->rules->rules[i]->retval;
      act->err = calls[call].call->rules->rules[i]->errno;
      return 1 + i;
    }
  }
  return 0;    
}
