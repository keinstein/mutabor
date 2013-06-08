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
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "log.h"
#include "prob.h"
#include "util.h"
#include "func.h"

#define FIG_VARS 20

/* Certain programs such as Netscape and MySQL use mechanisms that unset */
/* LD_PRELOAD before running the main program, thus disabling FIG.       */
/* Running these progrms under FIG with this instrumented version of     */
/* execve() included in libfig.so circumvents these measures.            */
/* The code below reads the FIG environment variable settings from       */
/* /tmp/fig.conf and resets them in the environment string sent to       */
/* the exec()'d function, if they've been removed or changed.            */

int execve(const char *filename, char *const argv[], char *envp[]) {
  action a;
  int old_errno;
  int rv;
  char name_buf[256];
  char value_buf[256];
  char **new_envp;
  char *new_var;
  char *errname;
  FILE *config;
  int i, j;
  int found;
  int stop = 0;
  int var_removed = 0;

  typedef void *(*execve_t)(const char *filename, char *const argv[], char *envp[]);
  execve_t real_execve;

  if (fig_error(EXECVE_INDEX, &a)) {
    log(INJECTED, "execve() Induced error - going to return %d, errno = %d\n", a.ret, a.err);
    errno = a.err;
    return (int) a.ret;
  }
  else {

    /* Create a new envp[] array, in case some FIG variables have       */
    /* been removed entirely from envp[]. We can add the missing        */
    /* variables to the end of the new_envp[] array, and use it in the  */
    /* final invocation of execve.                                      */
    new_envp = (char **)__libc_malloc(sizeof(char *) + sizeof(envp) + FIG_VARS);
    i=0;
    while(envp[i] != 0) {
      new_envp[i] = envp[i];
      i++;
    }
    j = i;

    /* Get the original FIG environment variable settings from fig.conf */
    /* and set them in envp[] and new_envp[].                           */
    config = (FILE *)_IO_fopen("/tmp/fig.conf", "r"); 
      
    if (config == NULL) {
      log(ALL, "execve() was unable to open /tmp/fig.conf. Proper behavior of FIG cannot be guaranteed.\n");
    } else {

      while (stop == 0) {
        if (fgets(name_buf, 256, config) == NULL) {
          stop = 1;
        } else {
          name_buf[strlen(name_buf) - 1] = 0;
          if (fgets(value_buf, 256, config) == NULL) {
            stop = 1;
          } else {
            value_buf[strlen(value_buf) - 1] = 0;
	    i=0;
            if (envp) {
              found = 0;
              while ((found == 0) && (envp[i] != NULL)) {
                if (strncmp(name_buf, envp[i], strlen(name_buf)) == 0) {
                  found = 1;
                } else {
                  i++;
                }
              }
              new_var = (char *)__libc_malloc(sizeof(char) * (strlen(name_buf) + strlen(value_buf)));
              sprintf(new_var, "%s%s", name_buf, value_buf);
              if (found) {
		if(strcmp(envp[i], new_var) != 0) {
                  envp[i] = new_var;
	  	  new_envp[i] = new_var;
		}
              } else {
		var_removed = 1;
		new_envp[j] = new_var;
		j++;
              }
            }
          }
        }	
      }
    }

    _IO_fclose(config);

    real_execve = (execve_t)getLibraryFunction("execve");
    if (var_removed == 0) {
      /* Call the real execve with the updated envp */
      rv = (int) real_execve(filename, argv, envp);
    }
    else {
      /* Call the real execve with the new evp */
      rv = (int) real_execve(filename, argv, new_envp);
    }

    // If we get to here, something went horribly wrong.
    old_errno = errno;
    errname = strerror(old_errno);
    log(ALL, "execve() failed with errno = %s\n", errname);
    errno = old_errno;
    return rv;
  }

}
