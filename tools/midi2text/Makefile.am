#SUBDIRS=gmut includes kernel wxintl tests wxGUI xrc
#include $(top_srcdir)/common-rules.mk

CLEANFILES=symbols.map

all: midi2text
midi2text: mf2txt$(EXEEXT) txt2mf$(EXEEXT)

noinst_PROGRAMS = mf2txt txt2mf

AM_CFLAGS = -Isrc

mf2txt_SOURCES = \
	src/crack.c \
	src/mf2t.c \
	src/mf2tfuncts.h \
	src/midifile.c \
	src/midifile.h

txt2mf_SOURCES = \
	src/crack.c \
	src/mf2tfuncts.h \
	src/midifile.c \
	src/midifile.h \
	src/t2mf.c \
	src/t2mf.h \
	src/t2mflex.c \
	src/yyread.c
