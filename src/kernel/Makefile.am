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
		%D%/error.h \
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
		%D%/error.cpp \
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

CLEANFILES += \
	%D%/mutlex.cc.stamp \
	%D%/mut.cc.stamp


EXTRA_DIST += \
	%D%/mutlex.h \
	%D%/mutlex.cc \
	%D%/mut.hh \
	%D%/mut.cc

%D%/scala.$(OBJEXT) \
%D%/mutlex.$(OBJEXT) \
%D%/mut.$(OBJEXT): \
	$(srcdir)/%D%/mut.cc \
	$(srcdir)/%D%/mut.hh \
	$(srcdir)/%D%/mutlex.h \
	$(srcdir)/%D%/mutlex.cc



# lex and yacc rules seem not to be very clear about parallel builds
# since we rely on flex and beson, we can use their more "portable" features
# to generate the desired files

CLEANFILES += \
	%D%/mut.cc.stamp \
	%D%/keymap_parser.cc.stamp \
	%D%/mutlex.cc.stamp \
	%D%/mut.dot \
	%D%/mut.xml \
	%D%/mut.output \
	%D%/mut \
	%D%/mut.dot.bak \
	%D%/location.hh.bak \
	%D%/position.hh.bak \
	%D%/stack.hh.bak \
	%D%/mut.cc.bak \
	%D%/mut.hh.bak

#
muttargets = \
	%D%/location.hh \
	%D%/stack.hh \
	%D%/position.hh \
	%D%/mut.cc
# mut.hh is not mentioned here, as there is a different rule from Automake somewhere else

if OFF_TREE
# this rule is distinct from the rule without $(srcdir) above. Both are needed for VPATH builds
muttargets += \
	$(srcdir)/%D%/mut.hh \
	$(srcdir)/%D%/mut.cc
CLEANFILES += \
	%D%/mut.hh \
	%D%/mut.cc
endif


# this rule must contain commands.
# otherwise automake will generate a different rule for mut.yy
$(muttargets):
	@rm -f %D%/mut
	@$(MAKE) $(AM_MAKEFLAGS) %D%/mut


# sed -i expects a backup argument on Mac OS X
%D%/mut: $(srcdir)/%D%/mut.yy
	rm -f $@
	$(AM_V_YACC)$(am__skipyacc) \
		$(SHELL) \
		$(YLWRAP) \
		'$<' \
		y.tab.c '$@.cc' \
		y.tab.h '$@.hh' \
		y.output '$@.output' \
		y.dot '$@.dot' \
		y.xml '$@.xml' \
		-- \
		$(YACCCOMPILE)
	sed -i.bak -e '/digraph/ s,$(PWD),.,g' '$@.dot'
	for d in \
		'$@.cc' \
		'$@.hh'; \
	do  \
		test -e "$$d" || continue ; \
		sed -i.bak \
			-e '/\#[^"]*\(include\|line\)/ s,$(srcdir)/%D%/\(mut\|location\|position\|stack\),%D%/\1,g' \
			-e '/\#[^"]*\(include\|line\)/ s,"\(mut\|location\|position\|stack\),"%D%/\1,g' \
			"$$d" || exit 1 ; \
		grep -v '#line' "$$d" >"$$d.tmp" ; \
		if diff -u "$(srcdir)/$$d" "$$d"; \
		then \
			echo $(RM_OFFTREE) "$$d" "$$d.tmp"; \
			$(RM_OFFTREE) "$$d" "$$d.tmp" ; \
		else \
			echo "rm -f \"$$d.tmp\" ; $(MV_OFFTREE) \"$$d\" \"$(srcdir)/$$d\"" ; \
			( rm -f "$$d.tmp" ; $(MV_OFFTREE) "$$d" "$(srcdir)/$$d")  || exit 2 ; \
		fi ; \
	done
	touch "$@"

# #if OFF_TREE
#$(top_srcdir)/%D%/mutlex.cc: %D%/mutlex.cc.stamp
#$(top_srcdir)/%D%/mut.cc: %D%/mut.cc.stamp
# #endif
# $(top_srcdir)/%D%/mut.cc:$(top_srcdir)/%D%/mut.yy
# 		$(AM_V_YACC)$(am__skipyacc) \
# 			$(SHELL) \
# 			$(YLWRAP) "$<" \
# 				"bison.cc" "$@" \
# 				"bison.hh" `echo $@ | $(am__yacc_c2h)` \
# 				bison.output $*.output \
# 				bison.dot $*.dot \
# 				bison.xml $*.xml \
# 			-- \
# 			$(YACCCOMPILE) -o "bison.cc" -b "."
#

# %D%/mut.cc: %D%/mut.cc.stamp
# %D%/mut.cc.stamp: $(top_srcdir)/%D%/mut.yy
# 	rm -f "$@"
# 	$(MKDIR_P) "`dirname '%D%/mut.cc'`"
# 	rm -f "%D%/mut.cc"
# 	cmp "%D%/`basename '$<'`" '$<' || cp '$<' '%D%/'
# 	$(YACCCOMPILE) -o '%D%/mut.cc' -b '$(top_srcdir)/%D%/' "%D%/`basename '$<'`"
# 	cmp $(top_srcdir)/%D%/mut.cc %D%/mut.cc 2>/dev/null || \
# 		cp %D%/mut.cc $(top_srcdir)/%D%/mut.cc
# 	touch "$@"
#

# %D%/mutlex.cc: %D%/mutlex.cc.stamp
# %D%/mutlex.cc.stamp: $(top_srcdir)/%D%/mutlex.ll
# 	rm -f "$@"
# 	$(MKDIR_P) `dirname %D%/mutlex.cc`
# 	rm -f "%D%/mutlex.cc"
# 	$(LEXCOMPILE) -o %D%/mutlex.cc $<
# 	cmp $(top_srcdir)/%D%/mutlex.cc %D%/mutlex.cc 2>/dev/null || \
# 		cp %D%/mutlex.cc $(top_srcdir)/%D%/mutlex.cc
# 	touch "$@"
#

#if OFF_TREE
#$(top_srcdir)/%D%/mut.cc: %D%/mut.cc
#	cmp $< $@ || cp $< $@
#$(top_srcdir)/%D%/mutlex.cc: %D%/mutlex.cc
#	cmp $< $@ || cp $< $@
#endif
