# Makefile for bison
#   Copyright (C) 1984, 1989 Bob Corbett and Free Software Foundation, Inc.
# 
# This file is part of Bison, the GNU Compiler Compiler.
# 
# Bison is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 1, or (at your option)
# any later version.
# 
# Bison is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Bison; see the file COPYING.  If not, write to
# the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

# For sysV, you must uncomment the following lines
#CFLAGS = -g -DUSG
#LIBS = -lPW
#and comment out the assignment of CFLAGS below.
#Also, if getopt.c gives any trouble, delete it from OBJECTS.
#so the system's getopt will be used.


DESTDIR=
# where the installed binary goes
# BINDIR = $(DESTDIR)/usr/local/bin
BINDIR = $(HOME)/CC/bin

# where the parsers go
# PARSERDIR = $(DESTDIR)/usr/local/lib
PARSERDIR = $(HOME)/CC/lib

# names of parser files
PFILE = bison.simple
PFILE1 = bison.hairy

# It is unwise ever to compile a program without symbols.
CFLAGS = -g

PFILES = -DXPFILE=\"$(PARSERDIR)/$(PFILE)\" \
	 -DXPFILE1=\"$(PARSERDIR)/$(PFILE1)\"

OBJECTS = LR0.o allocate.o closure.o conflicts.o derives.o files.o	\
	  getargs.o gram.o lalr.o lex.o					\
	  main.o nullable.o output.o print.o reader.o reduce.o symtab.o	\
	  warshall.o version.o						\
	  getopt.o

start: bison

clean:
	rm -f *.o core bison

install: bison
	install bison $(BINDIR)
	-cd $(PARSERDIR); rm -f $(PFILE) $(PFILE1)
	cp $(PFILE) $(PFILE1) $(PARSERDIR)

bison: $(OBJECTS)
	$(CC) $(LDFLAGS) -o bison $(OBJECTS) $(LIBS)

dist:	bison-dist.tar bison-dist.tar.Z

.PHONY: bison-dist.tar
bison-dist.tar:
	-rm -rf bison-dist
	mkdir bison-dist
	ln  COPYING ChangeLog Makefile REFERENCES bison.1 \
	    bison.simple bison.hairy \
	    LR0.c allocate.c closure.c conflicts.c derives.c \
	    files.c getargs.c gram.c lalr.c lex.c main.c nullable.c \
	    output.c print.c reader.c reduce.c symtab.c version.c \
	    warshall.c files.h gram.h lex.h machine.h new.h state.h \
	    symtab.h system.h types.h bison.cld build.com vmsgetargs.c \
	    vmshlp.mar README bison.texinfo bison.info* \
	  bison-dist
	cp ../lib/getopt.c bison-dist

	tar chvf bison-dist.tar bison-dist

bison-dist.tar.Z: bison-dist.tar
	compress < bison-dist.tar > bison-dist.tar.Z

TAGS: *.c *.h
	etags *.c *.h

# This file is different to pass the parser file names
# to the compiler.
files.o: files.c files.h new.h gram.h
	$(CC) -c $(CFLAGS) $(PFILES) files.c

LR0.o: machine.h new.h gram.h state.h
closure.o: machine.h new.h gram.h
conflicts.o: machine.h new.h files.h gram.h state.h
derives.o: new.h types.h gram.h
getargs.o: files.h
lalr.o: machine.h types.h state.h new.h gram.h
lex.o: files.h symtab.h lex.h
main.o: machine.h
nullable.o: types.h gram.h new.h
output.o: machine.h new.h files.h gram.h state.h
print.o: machine.h new.h files.h gram.h state.h
reader.o: files.h new.h symtab.h lex.h gram.h
reduce.o: files.h new.h machine.h gram.h
symtab.o: new.h symtab.h gram.h
warshall.o: machine.h
