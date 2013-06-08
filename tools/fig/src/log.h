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

#ifndef LOG_H
#define LOG_H

#include "loglevel.h"

/*
 * Logs the following information at the given level.
 *
 * Uses printf style formatting [anything valid there is a-ok here]
 */
void log (enum e_log_level level, char * fmt, ...);


/*
 * Logs the following information at the given level but does not log any
 * timing information. Thus, does not make any calls to malloc.
 *
 * Uses printf style formatting [anything valid there is a-ok here]
 */
void logNT (enum e_log_level level, char * fmt, ...);

#endif
