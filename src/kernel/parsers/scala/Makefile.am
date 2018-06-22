include %D%/tests/Makefile.am

CLEANFILES += %D%/*.class \
	fix_scale_parser.stamp \
	fix_scale_parser.tmp

EXTRA_DIST += \
	%D%/location.hh \
	%D%/stack.hh \
	%D%/position.hh \
	%D%/scale_lexer.h \
	%D%/scale_lexer.cc \
	%D%/scale_parser.hh \
	%D%/scale_parser.cc

%D%/scala.$(OBJEXT) \
%D%/scale_lexer.$(OBJEXT) \
%D%/scale_parser.$(OBJEXT): $(srcdir)/%D%/location.hh \
			    $(srcdir)/%D%/position.hh \
			    $(srcdir)/%D%/stack.hh \
			    $(srcdir)/%D%/scale_parser.cc \
			    $(srcdir)/%D%/scale_parser.hh \
			    $(srcdir)/%D%/scale_lexer.h \
			    $(srcdir)/%D%/scale_lexer.cc



# lex and yacc rules seem not to be very clear about parallel builds
# since we rely on flex and beson, we can use their more "portable" features
# to generate the desired files

CLEANFILES += \
	%D%/scale_parser.cc.stamp \
	%D%/keymap_parser.cc.stamp \
	%D%/scale_lexer.cc.stamp \
	%D%/scale_parser.dot \
	%D%/scale_parser.xml \
	%D%/scale_parser.output \
	%D%/scale_parser \
	%D%/scale_parser.dot.bak \
	%D%/location.hh.bak \
	%D%/position.hh.bak \
	%D%/stack.hh.bak \
	%D%/scale_parser.cc.bak \
	%D%/scale_parser.hh.bak
#
# if OFF_TREE
# $(top_srcdir)/%D%/scale_parser.cc: %D%/scale_parser.cc.stamp
# $(top_srcdir)/%D%/keymap_parser.cc: %D%/keymap_parser.cc.stamp
# #$(top_srcdir)/%D%/scale_lexer.cc: %D%/scale_lexer.cc.stamp
# endif
#
#

#
scaleparsertargets = \
	%D%/location.hh \
	%D%/stack.hh \
	%D%/position.hh \
	%D%/scale_parser.cc

if OFF_TREE
# this rule is distingct from the rule without $(srcdir) below. Both are needed for VPATH builds
scaleparsertargets += \
	$(srcdir)/%D%/location.hh \
	$(srcdir)/%D%/stack.hh \
	$(srcdir)/%D%/position.hh \
	$(srcdir)/%D%/scale_parser.hh \
	$(srcdir)/%D%/scale_parser.cc
CLEANFILES += \
	%D%/location.hh \
	%D%/stack.hh \
	%D%/position.hh \
	%D%/scale_parser.hh \
	%D%/scale_parser.cc
endif


# this rule is distingct from the off-tree rule above. Both are needed for VPATH builds
$(scaleparsertargets):
	@rm -f %D%/scale_parser
	@$(MAKE) $(AM_MAKEFLAGS) %D%/scale_parser


# sed -i expects a backup argument on Mac OS X
%D%/scale_parser: $(srcdir)/%D%/scale_parser.yy
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
		location.hh '%D%/location.hh' \
		position.hh '%D%/position.hh' \
		stack.hh  "%D%/stack.hh" \
		-- \
		$(YACCCOMPILE)
	if test -e '$@.dot' ; then sed -i.bak -e '/digraph/ s,$(PWD),.,g' '$@.dot' ; fi
	for d in %D%/location.hh \
		%D%/position.hh \
		%D%/stack.hh   \
		'$@.cc' \
		'$@.hh'; \
	do  \
		test -e "$$d" || continue ; \
		sed -i.bak \
			-e '/\#[^"]*\(include\|line\)/ s,$(srcdir)/%D%/\(scale_parser\|location\|position\|stack\),%D%/\1,g' \
			-e '/\#[^"]*\(include\|line\)/ s,"\(scale_parser\|location\|position\|stack\),"%D%/\1,g' \
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

