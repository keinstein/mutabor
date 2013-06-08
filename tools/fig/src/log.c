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
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "log.h"
#include "loglevel.h"
#include "spinlock.h"

#ifdef SHMEM_LOGGING
/* Logging code for the wrapper version of FIG, which uses a shared memory */
/* buffer to communicate with a separate logging daemon.                   */

#define SHM_LOCK       if (do_locking) { spin_lock(shm_lock); }
#define SHM_UNLOCK     if (do_locking) { spin_unlock(shm_lock); }

/* Functions called by the instrumented FIG library stubs, which   */
/* write log messages to the shared memory segment. Once there,    */
/* messages later are picked up and written to the log file by the */
/* logging daemon (which was spawned by the fig wrapper program.   */

static int shm_attached = 0;
static int *shm_pos = NULL;
static spinlock_t *shm_lock = NULL;
static char *shm_data = NULL;
static int shm_size = 0;
static int shm_data_size = 0;

static pid_t my_pid;

enum e_log_level logging_level = ALL;
int do_timing = 0;
int do_locking = 0;

void attach_shm() {
  char *tmp;
  int  shm_id;
  void *shm_addr;

  tmp = getenv("LIBFIG_SHMID");
  if (tmp) {
    shm_id = atoi(tmp);
    
    tmp = getenv("LIBFIG_SHMSIZE");
    shm_size = atoi(tmp);

    tmp = getenv("LIBFIG_LOG_LEVEL");
    logging_level = atoi(tmp);

    tmp = getenv("LIBFIG_TIMING");
    do_timing = atoi(tmp);

    tmp = getenv("LIBFIG_SYNC");
    do_locking = atoi(tmp);
    
    if ((int)(shm_addr = shmat(shm_id, NULL, 0)) == -1) {
      fprintf(stderr, "Child could not attach shared memory segment.\n");
      exit(-1);
    }
    
    shm_pos = (int *) shm_addr;
    shm_lock = shm_addr + sizeof(int);
    shm_data = (char *) shm_addr + sizeof(int) + sizeof(spinlock_t);
    shm_data_size = shm_size - sizeof(int) - sizeof(spinlock_t);

    my_pid = getpid();
  }

  shm_attached = 1;
}

void write_logfile(char *buffer, int len) {
  int freespace;

  freespace = shm_data_size - *shm_pos;

  if (len > freespace) {

    SHM_LOCK;

    strncpy(shm_data + *shm_pos, buffer, freespace);
    strncpy(shm_data, buffer + freespace, len - freespace);
    *shm_pos = len - freespace;

    SHM_UNLOCK;

  } else {

    SHM_LOCK;

    strncpy(shm_data + *shm_pos, buffer, len);
    *shm_pos += len;

    SHM_UNLOCK;
  }
}

/* Function to write a log message at the given log level to the */
/* shared memory logging buffer, from which the logging daemon   */
/* will copy the message to the log file.                        */
void log (enum e_log_level level, char * fmt, ...) {
  struct timeval te;
  struct timezone tz;
  time_t t;
  char buffer[256];
  char tbuf[256];
  va_list list;
  int len;
  struct tm * tmNow;

  if (!shm_attached) {
    attach_shm();
  }

  if (level > logging_level) {
    return;
  }

  if (shm_data) {
    va_start(list, fmt);

    if (do_timing) {
      gettimeofday(&te, &tz);
      tmNow = (struct tm *)localtime ((time_t *) (&te.tv_sec));
      strftime (tbuf, 256, "%m/%d %H:%M:%S", tmNow);

      len = snprintf (buffer, 256, "[%s.%d] pid %d %s: ", tbuf , te.tv_usec, 
		     my_pid, levelstring(level));
      write_logfile(buffer, len);
    } else {
      len = snprintf(buffer, 256, "pid %d %s: ", my_pid, levelstring(level));
      write_logfile(buffer, len);
    }
    
    len = vsnprintf(buffer, 256, fmt, list);
    write_logfile(buffer, len);

    va_end(list);
  }
}

/* Avoids writing the timing information to the log, since when logging */
/* certain calls like malloc, we may get a loop condition if the timing */
/* code (gettimeofday) itself calls malloc behind the scenes, etc.      */
void logNT (enum e_log_level level, char * fmt, ...) {
  char buffer[256];
  va_list list;
  int len;

  if (!shm_attached) {
    attach_shm();
  }

  if (level > logging_level) {
    return;
  }

  if (shm_data) {
    va_start(list, fmt);

    if (do_timing) {
      len = snprintf (buffer, 256, "[time unavailable] pid %d %s: ", 
		     my_pid, levelstring(level));
      write_logfile(buffer, len);
    }
    
    len = vsnprintf(buffer, 256, fmt, list);
    write_logfile(buffer, len);

    va_end(list);
  }
}

#endif

#ifndef SHMEM_LOGGING

/* Code for 2nd logging option, "in-line" logging: a call to an instrumented */
/* FIG library from within an application results in a call to log(), which  */
/* writes the pertinent logging information directly into the file           */
/* fig.log.<pid>.                                                            */

/* Function to open the current process's FIG log file, or else create a new */
/* one if it doesn't already exist.                                          */
FILE * getFile ()
{
  static int open_pending = 0;
  static FILE * destination = NULL;
  char * logFile;
  char * tmp;

  if (open_pending) {
    return destination;
  }
  if (destination != NULL) {
    return destination;
  }
  open_pending = 1;
  tmp = getenv ("LIBFIG_OUTPUT");

  if (!tmp) {
    do
      logFile = (char*)__libc_malloc(sizeof (char) * 256);
    while (!logFile);
    sprintf (logFile, "/tmp/libfig.out.%d", getpid());
  } else {
    do
      logFile = (char *)__libc_malloc(sizeof(char) * (strlen(tmp) + 8));
    while (!logFile);
    sprintf(logFile, "%s.%d", tmp, getpid());
  }

  while (destination == NULL) {
    destination = (FILE *)_IO_fopen (logFile, "a");
  }
  open_pending = 0;
  return destination;
}

/* Function to write the specified logging information to the log file, */
/* including timing information.                                        */
void log (enum e_log_level level, char * fmt, ...)
{
  struct timeval te;
  struct timezone tz;
  time_t t;
  char tbuf [256];
  char * levelstring;
  struct tm * tmNow;
  FILE * f = getFile();
  va_list list;
  static char prevbuf[256];
  static int buf_full = 0;

  va_start (list, fmt);
  if (f == NULL) {
    vsnprintf (prevbuf, 256, fmt, list);
    buf_full = 1;
    return;
  }

  if (buf_full == 1) {
    _IO_fprintf(f, "[delayed message]: UNKN: %s\n", prevbuf);
    buf_full = 0;
  }

  memset (&tz, 0, sizeof tz);
  memset (&te, 0, sizeof (te));
  
  assert (!gettimeofday (&te, &tz));
  tmNow = (struct tm *)localtime ((time_t *) (&te.tv_sec));
  strftime (tbuf, 256, "%m/%d %H:%M:%S", tmNow);

  /* Currently we ignore the log level for these functions. */
  switch (level) {
  case ALL:
    levelstring = "ALL";
    break;
  case INJECTED:
    levelstring = "INJECTED";
    break;
  case ERROR:
    levelstring = "ERROR";
    break;
  case NONE:
    levelstring = "NONE";
    break;
  default:
    levelstring = "UNKN";
  }
  _IO_fprintf (f, "[%s.%d] %s: ", tbuf , te.tv_usec, levelstring);
  _IO_vfprintf (f, fmt, list);
  fsync (f);
}

/* Function to write the specified logging information to the log file. */
/* Does not include timing information -- see above for an explanation. */
void logNT (enum e_log_level level, char * fmt, ...)
{
  char * levelstring;
  FILE * f = getFile();
  va_list list;
  static char prevbuf[256];
  static int buf_full = 0;

  va_start (list, fmt);
  if (f == NULL) {
    vsnprintf (prevbuf, 256, fmt, list);
    buf_full = 1;
    return;
  }

  if (buf_full == 1) {
    _IO_fprintf(f, "[delayed message]: UNKN: %s", prevbuf);
    buf_full = 0;
  }
  
  /* Currently we ignore the log level for these functions. */
  switch (level) {
  case ALL:
    levelstring = "ALL";
    break;
  case INJECTED:
    levelstring = "INJECTED";
    break;
  case ERROR:
    levelstring = "ERROR";
    break;
  case NONE:
    levelstring = "NONE";
    break;
  default:
    levelstring = "UNKN";
  }
  _IO_fprintf (f, "[time unavailable] %s: ", levelstring);
  _IO_vfprintf (f, fmt, list);
  fsync (f);
}
#endif
