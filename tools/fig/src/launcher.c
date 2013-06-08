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

/* When compiled, this produces the fig wrapper program. When a program */
/* is invoked with this wrapper, it is run with LD_PRELOAD set to the   */
/* the libfig.so library. Thus, any calls to the library functions      */
/* given in the control file and described in func.desc or a user-      */
/* defined stub go through this library and may be subject to the error */
/* injection code provided.                                             */
/*                                                                      */
/* The wrapper also sets up a shared memory logging buffer by default   */
/* and spawns a logging daemon process. The job of this process is to   */
/* scan the logging buffer for messages written there by the error      */
/* injection code from the library stubs, and periodically write this   */
/* data to the log file.                                                */
/* The wrapper may take a variety of arguments to describe the degree   */
/* and frequency of logging, and also displays usage, version and       */
/* timing info. */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/times.h>
#include "loglevel.h"
#include "spinlock.h"

#define ERR_BAD_CMDLINE      -1
#define ERR_FORK             -2
#define ERR_EXEC             -3
#define ERR_SHM              -4
#define ERR_FILE             -5
#define ERR_WAIT             -6
#define ERR_SIG              -7

#define SHM_SIZE           1048576

int parse_cmdline(int argc, char *argv[]);
void usage(void);
char **set_argv(int prog_index, int argc, char *argv[]);
void setup_environ(int shm_id, int shm_size);
int monitor_child(pid_t pid, int logfile);
void sig_handler(int);
void setup_signals(void);
void tv_difference(struct timeval *a, struct timeval *b, struct timeval *c);

static enum e_log_level logging_level = ALL;
static char *ld_preload = "libfig.so";
static char *control_filename = "control.out";
static char *log_filename = "fig.log";

static int shm_size = SHM_SIZE;
static int *shm_pos;
static spinlock_t *shm_lock;
static char *shm_data;
static int shm_data_size;

static int nice_level = 2;
static int timeout_usec = 50000;

static pid_t pid = 0; 

static int verbose = 0;

static int do_timing = 1;
static int no_fig = 0;
static int do_locking = 0;

int main(int argc, char *argv[], char *envp[]) {
  int progname;
  char **new_argv;
  int  child_status;
  key_t shm_key;
  int   shm_id;
  void *shm_addr;
  int log_file;
  char *errname;

  struct timeval tv_start, tv_child_start, tv_end;
  struct timezone tz_start, tz_child_start, tz_end;

  gettimeofday(&tv_start, &tz_start);

  progname = parse_cmdline(argc, argv);

  if (progname < 0 || progname >= argc) {
    usage();
    return ERR_BAD_CMDLINE;
  }

  /* Create and attach the shared memory segment */

  if ((shm_id = shmget(IPC_PRIVATE, shm_size, 0600)) == -1) {
    fprintf(stderr, "Could not create shared memory segment.\n");
    return ERR_SHM;
  }

  if ((int)(shm_addr = shmat(shm_id, NULL, 0)) == -1) {
    fprintf(stderr, "Could not attach shared memory segment.\n");
    return ERR_SHM;
  }

  if ((log_file = open(log_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
    fprintf(stderr, "Could not open logging file.\n");
    return ERR_FILE;
  }

  /* Set up the shared memory structures. */

  shm_pos = (int *) shm_addr;
  shm_lock = shm_addr + sizeof(int);
  spin_lock_init(shm_lock);
  shm_data = (char *) shm_addr + sizeof(int) + sizeof(spinlock_t);
  shm_data_size = shm_size - sizeof(int) - sizeof(spinlock_t);
  *shm_pos = 0;
      
  /* Create the child process's argv and environment */
  new_argv = set_argv(progname, argc, argv);
  if (!no_fig) {
    setup_environ(shm_id, shm_size);
  }

  setup_signals();

  gettimeofday(&tv_child_start, &tz_child_start);

  if ((pid = fork()) < 0) {
    fprintf(stderr, "Could not fork.\n");
    return ERR_FORK;
  } else if (pid == 0) {
    /* Processing for parent (foreground) */
    if (execvp(argv[progname], new_argv) == -1) {
      fprintf(stderr, "Could not execv program %s\n", argv[progname]);
      return ERR_EXEC;
    }
  } else {
    /* Processing for logging daemon */
    struct tms time;
    clock_t total_utime;
    clock_t total_stime;
    struct timeval wall_time;
    struct timeval child_wall_time;
    long clk_tck;

    /* Reduce our priority so that we don't swamp the child */

    nice(nice_level);
    
    child_status = monitor_child(pid, log_file);

    times(&time);
    gettimeofday(&tv_end, &tz_end);
    clk_tck = sysconf(_SC_CLK_TCK);

    tv_difference(&tv_end, &tv_start, &wall_time);
    tv_difference(&tv_end, &tv_child_start, &child_wall_time);

    total_utime = time.tms_utime + time.tms_cutime;
    total_stime = time.tms_stime + time.tms_cstime;

    printf("Timing                   User        System         Real\n");
    printf("%-15s %6dm%05.3fs %6dm%05.3fs %6dm%05.3fs\n",
	   argv[progname],
	   time.tms_cutime / (clk_tck * 60),
	   ((float)(time.tms_cutime % (clk_tck * 60)) / (float)clk_tck),
	   time.tms_cstime / (clk_tck * 60),
	   ((float)(time.tms_cstime % (clk_tck * 60)) / (float)clk_tck),
	   child_wall_time.tv_sec / 60,
	   (float)(child_wall_time.tv_sec % 60) + 
	   ((float)child_wall_time.tv_usec / 1000000.0));
    printf("%-15s %6dm%05.3fs %6dm%05.3fs %6dm%05.3fs\n",
	   "fig",
	   time.tms_utime / (clk_tck * 60),
	   ((float)(time.tms_utime % (clk_tck * 60)) / (float)clk_tck),
	   time.tms_stime / (clk_tck * 60),
	   ((float)(time.tms_stime % (clk_tck * 60)) / (float)clk_tck),
	   wall_time.tv_sec / 60,
	   (float)(wall_time.tv_sec % 60) + 
	   ((float)wall_time.tv_usec / 1000000.0));
    printf("%-15s %6dm%05.3fs %6dm%05.3fs %6dm%05.3fs\n",
	   "total",
	   total_utime / (clk_tck * 60),
	   ((float)(total_utime % (clk_tck * 60)) / (float)clk_tck),
	   total_stime / (clk_tck * 60),
	   ((float)(total_stime % (clk_tck * 60)) / (float)clk_tck),
	   wall_time.tv_sec / 60,
	   (float)(wall_time.tv_sec % 60) + 
	   ((float)wall_time.tv_usec / 1000000.0));

    shmdt(shm_addr);
    close(log_file);

    return child_status;
  }

  return 0;
}

void tv_difference(struct timeval *a, struct timeval *b, struct timeval *c) {
  c->tv_sec = a->tv_sec - b->tv_sec;
  c->tv_usec = a->tv_usec - b->tv_usec;

  if (c->tv_usec < 0) {
    c->tv_sec--;
    c->tv_usec += 1000000;
  }
}

void setup_signals(void) {
  sigset_t sigset;
  struct sigaction sigact;

  if (sigemptyset(&sigset) == -1) {
    fprintf(stderr, "Error setting up signal handler\n");
    exit(ERR_SIG);
  }

  if (sigaddset(&sigset, SIGINT) == -1) {
    fprintf(stderr, "Error setting up signal handler\n");
    exit(ERR_SIG);
  }

  sigact.sa_handler = sig_handler;
  sigact.sa_mask = sigset;
  sigact.sa_flags = SA_RESETHAND;

  if (sigaction(SIGINT, &sigact, NULL) == -1) {
    fprintf(stderr, "Error setting up signal handler\n");
    exit(ERR_SIG);
  }
}

void sig_handler(int signum) {
  kill(pid, signum);
}
  

#if 0
void flush_shm(int start, int end, int logfile) {
  char buffer[4096];
  int size;

  while (start < end) {
    size = (end - start) > 4096 ? 4096 : (end - start);

    memcpy(buffer, shm_data + start, size);
    write(logfile, buffer, size);

    start += size;
  }
}
#endif

void flush_shm(int start, int end, int logfile) {
  write(logfile, shm_data + start, end - start);
}
 
int monitor_child(pid_t pid, int logfile) {
  static int old_pos = 0; 
  int new_pos;
  pid_t child_pid;
  int   child_status;
  int  done = 0;

  while (1) {
    new_pos = *shm_pos;

    if (new_pos > old_pos) {
      /* "normal" case: the new position is further along in the buffer */

      if (verbose) {
	printf("fig: flushing %d bytes from the log.\n", new_pos - old_pos);
      }

      flush_shm(old_pos, new_pos, logfile);
    } else if (new_pos == old_pos) {
      /* Nothing new has been added to the buffer since the last time
	 we checked. Do nothing. */
      ;
    } else {
      /* The circular buffer has wrapped on us */

      if (verbose) {
	printf("fig: flushing %d bytes from the log.\n", 
	       (shm_data_size - old_pos) + new_pos);
      }

      flush_shm(old_pos, shm_data_size, logfile);
      flush_shm(0, new_pos, logfile);
    }

    old_pos = new_pos;

    /* Check to see if the child has completed */

    if (done) {
      return WEXITSTATUS(child_status);
    }

    child_pid = waitpid(-1, &child_status, WNOHANG);
    if (child_pid == -1) {
      fprintf(stderr, "An error occurred in waitpid()\n");
      return ERR_WAIT;
    } else if (child_pid == 0) {
      usleep(timeout_usec);
    } else {
      done = 1;
    } 
  }
  
  return 0;
}

void setup_environ(int shm_id, int shm_size) {
  char shm_id_str[64];
  char shm_size_str[64];
  char log_lvl_str[64];
  FILE *config;
  char *pwd;
  char *control_file_path;
  char *ld_preload_path;
  char *log_file_path;

  snprintf(shm_id_str, 64, "%d", shm_id);
  snprintf(shm_size_str, 64, "%d", shm_size);
  snprintf(log_lvl_str, 64, "%d", logging_level);

  /* Set the FIG environment variables and write their values */
  /* to the config file.                                      */

  pwd = getenv("PWD");

  if (control_filename != NULL) {
    control_file_path = (char *)malloc(sizeof(char) * (strlen(pwd) + strlen(control_filename) + 2));
    sprintf(control_file_path, "%s/%s\0", pwd, control_filename);
    setenv("LIBFIG_CONTROL", control_file_path, 1);
  }
  setenv("LIBFIG_SHMID", shm_id_str, 1);
  setenv("LIBFIG_SHMSIZE", shm_size_str, 1);
  log_file_path = (char *)malloc(sizeof(char) * (strlen(pwd) + strlen(log_filename) + 2));
  sprintf(log_file_path, "%s/%s\0", pwd, log_filename);
  setenv("LIBFIG_OUTPUT", log_file_path, 1);
  setenv("LIBFIG_LOG_LEVEL", log_lvl_str, 1);
  if (do_timing) {
    setenv("LIBFIG_TIMING", "1", 1);
  } else {
    setenv("LIBFIG_TIMING", "0", 1);
  }
  if (do_locking) {
    setenv("LIBFIG_SYNC", "1", 1);
  } else {
    setenv("LIBFIG_SYNC", "0", 1);
  }
  ld_preload_path = (char *)malloc(sizeof(char) * (strlen(pwd) + strlen(ld_preload) + 2));
  sprintf(ld_preload_path, "%s/%s\0", pwd, ld_preload);
  setenv("LD_PRELOAD", ld_preload_path, 1);

  config = fopen("/tmp/fig.conf", "w");
  fprintf(config, "LD_PRELOAD=\n");
  fprintf(config, "%s\n", ld_preload_path);
  fprintf(config, "LIBFIG_CONTROL=\n");
  fprintf(config, "%s\n", control_file_path);
  fprintf(config, "LIBFIG_SHMID=\n");
  fprintf(config, "%s\n", shm_id_str);
  fprintf(config, "LIBFIG_SHMSIZE=\n");
  fprintf(config, "%s\n", shm_size_str);
  fprintf(config, "LIBFIG_OUTPUT=\n");
  fprintf(config, "%s\n", log_file_path);
  fprintf(config, "LIBFIG_LOG_LEVEL=\n");
  fprintf(config, "%s\n", log_lvl_str);
  if (do_timing) {
    fprintf(config, "LIBFIG_TIMING=\n");
    fprintf(config, "1\n");
  } else {
    fprintf(config, "LIBFIG_TIMING=\n");
    fprintf(config, "0\n");
  }
  if (do_locking) {
    fprintf(config, "LIBFIG_SYNC=\n");
    fprintf(config, "1\n");
  } else {
    fprintf(config, "LIBFIG_SYNC=\n");
    fprintf(config, "0\n");
  }
  fclose(config);

}

char **set_argv(int prog_index, int argc, char *argv[]) {
  char **rv;
  int i, j;

  rv = (char **) malloc(sizeof(char *) * (argc - prog_index));
  for (i = prog_index, j = 0; i < argc; ++i, ++j) {
    rv[j] = argv[i];
  }

  return rv;
}

void usage(void) {
  fprintf(stderr, "fig [-c control_file] [-o logfile] [-l all|injected|errors|none] [-m size] prog [arg1 arg2 ...]\n");
  fprintf(stderr, "\nDescription:\n");
  fprintf(stderr, "    Launches the specified program with the FIG instrumentation library.\n");
  fprintf(stderr, "\nOptions:\n");
  fprintf(stderr, "    -c file     Specifies the control file name.\n");
  fprintf(stderr, "    -o file     Specifies the log file name.\n");
  fprintf(stderr, "    -l level    Sets the logging level. The level must be either none,\n");
  fprintf(stderr, "                errors, injected, or all.\n");
  fprintf(stderr, "    -m size     Sets the size of the shared log buffer (in bytes).\n");
  fprintf(stderr, "    -n nice     Sets the nice level of the launcher.\n");
  fprintf(stderr, "    -t usec     Sets the interval the wrapper waits before checking\n");
  fprintf(stderr, "                for new log entries.\n");
  fprintf(stderr, "    -v          Print logging statistics.\n");
  fprintf(stderr, "    -q          Suppress logging timestamps.\n");
  fprintf(stderr, "    -nofig      Do not install the FIG library (useless).\n");
  fprintf(stderr, "    -sync       Synchronize access to the log buffer with spinlocks. Useful\n");
  fprintf(stderr, "                if running multi-process applications.\n");
  fprintf(stderr, "    -h, --help  Displays this usage information.\n");
  fprintf(stderr, "    --version   Displays the FIG version info.\n");
  fprintf(stderr, "\nDefaults:\n");
  fprintf(stderr, "    -c %s\n", control_filename);
  fprintf(stderr, "    -o %s\n", log_filename);
  switch (logging_level) {
  case NONE:
    fprintf(stderr, "    -l none\n");
    break;
  case INJECTED:
    fprintf(stderr, "    -l injected\n");
    break;
  case ERROR:
    fprintf(stderr, "    -l errors\n");
    break;
  case ALL:
    fprintf(stderr, "    -l all\n");
    break;
  }
  fprintf(stderr, "    -m %d\n", shm_size);
  fprintf(stderr, "    -n %d\n", nice_level);
  fprintf(stderr, "    -t %d\n", timeout_usec);
}

int parse_cmdline(int argc, char *argv[]) {
  int i;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-l") == 0) {
      if (++i < argc) {
	if (strcmp(argv[i], "all") == 0) {
	  logging_level = ALL;
	} else if (strcmp(argv[i], "injected") == 0) {
	  logging_level = INJECTED;
	} else if (strcmp(argv[i], "errors") == 0) {
	  logging_level = ERROR;
	} else if (strcmp(argv[i], "none") == 0) {
	  logging_level = NONE;
	} else {
	  return ERR_BAD_CMDLINE;
	}
      } else {
	return ERR_BAD_CMDLINE;
      }
    } else if (strcmp(argv[i], "-c") == 0) {
      if (++i < argc) {
	control_filename = argv[i];
      } else {
	return ERR_BAD_CMDLINE;
      }
    } else if (strcmp(argv[i], "-o") == 0) {
      if (++i < argc) {
	log_filename = argv[i];
      } else {
	return ERR_BAD_CMDLINE;
      }
    } else if (strcmp(argv[i], "-m") == 0) {
      if (++i < argc) {
	shm_size = atoi(argv[i]);
      } else {
	return ERR_BAD_CMDLINE;
      }
    } else if (strcmp(argv[i], "-t") == 0) {
      if (++i < argc) {
	timeout_usec = atoi(argv[i]);
      } else {
	return ERR_BAD_CMDLINE;
      }
    } else if (strcmp(argv[i], "-v") == 0) {
      verbose = 1;
    } else if (strcmp(argv[i], "-q") == 0) {
      do_timing = 0;
    } else if (strcmp(argv[i], "-nofig") == 0) {
      no_fig = 1;
    } else if (strcmp(argv[i], "-sync") == 0) {
      do_locking = 1;
    } else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))  {
      usage();
      exit(0);
    } else if (strcmp(argv[i], "--version") == 0) { 
      fprintf(stderr, "FIG: a library-level error injection tool.\n");
      fprintf(stderr, "Version 0.3 BETA\n");
      fprintf(stderr, "Broadwell, Sastry and Traupman. UCB 2002.\n");
      exit(0);
    } else {
      return i;
    }
  }

  return i;
}
