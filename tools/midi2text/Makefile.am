#SUBDIRS=gmut includes kernel wxintl tests wxGUI xrc
#include $(top_srcdir)/common-rules.mk

all: midi2text
midi2text: mf2txt$(EXEEXT) txt2mf$(EXEEXT)

noinst_PROGRAMS = mf2txt txt2mf

mf2txt_SOURCES = \
	mf2t/crack.c \
	mf2t/mf2t.c \
	mf2t/mf2tfuncts.h \
	mf2t/midifile.c \
	mf2t/midifile.h

mf2txt_CFLAGS = $(CFLAGS) "-I$(top_srcdir)/tools/midi2text/mf2t"

txt2mf_SOURCES = \
	t2mf/crack.c \
	t2mf/mf2tfuncts.h \
	t2mf/midifile.c \
	t2mf/midifile.h \
	t2mf/t2mf.c \
	t2mf/t2mf.h \
	t2mf/t2mflex.c \
	t2mf/yyread.c

txt2mf_CFLAGS = $(CFLAGS) "-I$(top_srcdir)/tools/midi2text/mf2t"
