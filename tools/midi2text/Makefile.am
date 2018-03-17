#SUBDIRS=gmut includes kernel wxintl tests wxGUI xrc
#include $(top_srcdir)/common-rules.mk

CLEANFILES += \
   %D%/symbols.map

check_PROGRAMS += mf2txt txt2mf

AM_CFLAGS += -I%D%/src

mf2txt_SOURCES = \
	%D%/src/crack.c \
	%D%/src/mf2t.c \
	%D%/src/mf2tfuncts.h \
	%D%/src/midifile.c \
	%D%/src/midifile.h

txt2mf_SOURCES = \
	%D%/src/crack.c \
	%D%/src/mf2tfuncts.h \
	%D%/src/midifile.c \
	%D%/src/midifile.h \
	%D%/src/t2mf.c \
	%D%/src/t2mf.h \
	%D%/src/t2mflex.c \
	%D%/src/yyread.c
