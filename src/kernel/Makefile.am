include %D%/tests/Makefile.am
include %D%/routing/Makefile.am
include %D%/parsers/Makefile.am

CLEANFILES += %D%/*.class


TSBUILTSOURCES += \
	%D%/mut.hh \
	%D%/mut.cc \
	%D%/mutlex.cc \
	%D%/parsers/scala/scale_parser.hh \
	%D%/parsers/scala/scale_parser.cc \
	%D%/parsers/scala/location.hh \
	%D%/parsers/scala/position.hh \
	%D%/parsers/scala/stack.hh \
	%D%/parsers/scala/scale_lexer.cc 

EXTRA_DIST += \
	%D%/mut.yy \
	%D%/mutlex.ll \
	%D%/mut.hh \
	%D%/mut.cc \
	%D%/mutlex.cc \
	%D%/parsers/scala/scale_parser.hh \
	%D%/parsers/scala/scale_parser.cc \
	%D%/parsers/scala/location.hh \
	%D%/parsers/scala/position.hh \
	%D%/parsers/scala/stack.hh \
	%D%/parsers/scala/scale_lexer.cc 

noinst_LIBRARIES += \
	%D%/libmutaborkernel.a

#-------------------------------------------------------------
# libmutaborkernel.a
#-------------------------------------------------------------

%C%_libmutaborkernel_a_INLINEHEADERS = \
		%D%/mut.cc \
		%D%/mut.hh \
		%D%/mutlex.cc

%C%_libmutaborkernel_a_INDENTHEADERS = \
		%D%/Defs.h \
		%D%/box.h \
		%D%/Errors.h \
		%D%/Execute.h \
		%D%/Frac.h \
		%D%/Global.h \
		%D%/Hilfs.h \
		%D%/Interpre.h \
		%D%/Interval.h \
		%D%/Parser.h \
		%D%/MidiKern.h \
		%D%/Runtime.h \
		%D%/TabGen.h \
		%D%/treestorage.h \
		%D%/mutlex.h \
		%D%/debug.h \
		%D%/interface_deps.h \
		%D%/cow_container.h


%C%_libmutaborkernel_a_INDENTS = \
		%D%/box.cpp \
		%D%/Errors.cpp \
		%D%/Execute.cpp \
		%D%/Frac.cpp \
		%D%/Hilfs.cpp \
		%D%/Interval.c \
		%D%/Parser.cpp \
		%D%/Runtime.cpp \
		%D%/TabGen.cpp \
		%D%/debug.cpp 

noinst_HEADERS += $(%C%_libmutaborkernel_a_INLINEHEADERS) $(%C%_libmutaborkernel_a_INDENTHEADERS)

%C%_libmutaborkernel_a_POTSOURCES = $(%C%_libmutaborkernel_a_INLINEHEADERS) $(%C%_libmutaborkernel_a_INDENTHEADERS) $(libmutaborkernel_a_INDENTS)

%C%_libmutaborkernel_a_SOURCES = $(%C%_libmutaborkernel_a_INDENTS) \
			%D%/mut.yy \
			%D%/mutlex.ll \
			%D%/parsers/scala/scale_parser.yy \
			%D%/parsers/scala/scale_lexer.ll


%C%_libmutaborkernel_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS)

POTSOURCES += %C%_libmutaborkernel_a_POTSOURCES

if OFF_TREE
$(top_srcdir)/%D%/mut.cc:
	$(MAKE) %D%/mut.cc
endif
%D%/mut.cc: $(top_srcdir)/%D%/mut.yy
	$(MKDIR_P) `dirname $@`
	rm -f "$(top_srcdir)/%D%/mut.cc" "$@"
	$(YACCCOMPILE) -o $@ -b $(top_srcdir)/%D%/ $<
	cmp $(top_srcdir)/$@ $@ 2>/dev/null || \
		cp $@ $(top_srcdir)/$@

if OFF_TREE
$(top_srcdir)/%D%/mutlex.cc:
	$(MAKE) %D%/mutlex.cc
endif
$(MUTLEX_CC_TARGETS) \
%D%/mutlex.cc: $(top_srcdir)/%D%/mutlex.ll
	$(MKDIR_P) `dirname $@`
	rm -f "$(top_srcdir)/%D%/mutlex.cc" "$@"
	$(LEXCOMPILE) -o $@ $<
	cmp $(top_srcdir)/$@ $@ 2>/dev/null || \
		cp $@ $(top_srcdir)/$@


#if OFF_TREE
#$(top_srcdir)/%D%/mut.cc: %D%/mut.cc
#	cmp $< $@ || cp $< $@
#$(top_srcdir)/%D%/mutlex.cc: %D%/mutlex.cc
#	cmp $< $@ || cp $< $@
#endif
