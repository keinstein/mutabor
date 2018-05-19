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
	%D%/scale_parser.hh \
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
$(scaleparsertargets): %D%/scale_parser.stamp
	@echo "made $@"


# sed -i expects a backup argument on Mac OS X
%D%/scale_parser.stamp: $(srcdir)/%D%/scale_parser.yy
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
	sed -i.bak -e '/digraph/ s,$(PWD),.,g' '$@.dot'
	for d in %D%/location.hh \
		%D%/position.hh \
		%D%/stack.hh   \
		'$@.cc' \
		'$@.hh'; \
	do  \
		sed -i.bak \
			-e '/\#[^"]*include/ s,$(srcdir)/%D%/\(scale_parser\|location\|position\|stack\),%D%/\1,g' \
			-e '/\#[^"]*include/ s,"\(scale_parser\|location\|position\|stack\),"%D%/\1,g' \
			"$$d" || exit 1 ; \
		grep -v '#line' "$$d" >"$$d.tmp" ; \
		(grep -v '#line' "$(srcdir)/$$d" 2>/dev/null | diff -u "$$d.tmp" "-") && \
			$(RM_OFFTREE) "$$d" "$$d.tmp" || \
			(rm -f "$$d.tmp" ; $(MV_OFFTREE) "$$d" "$(srcdir)/$$d")  || exit 2 ; \
	done
	touch "$@"

