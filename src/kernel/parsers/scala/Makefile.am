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
	%D%/scale_parser

#
# if OFF_TREE
# $(top_srcdir)/%D%/scale_parser.cc: %D%/scale_parser.cc.stamp
# $(top_srcdir)/%D%/keymap_parser.cc: %D%/keymap_parser.cc.stamp
# #$(top_srcdir)/%D%/scale_lexer.cc: %D%/scale_lexer.cc.stamp
# endif
#
#

if OFF_TREE
$(srcdir)/%D%/location.hh \
$(srcdir)/%D%/stack.hh \
$(srcdir)/%D%/position.hh \
$(srcdir)/%D%/scale_parser.hh \
$(srcdir)/%D%/scale_parser.cc: %D%/scale_parser
	@echo Rule 2
	cat '$(srcdir)/%D%/scale_parser.hh'
endif
#
scaleparsertargets = \
	%D%/location.hh \
	%D%/stack.hh \
	%D%/position.hh \
	%D%/scale_parser.hh \
	%D%/scale_parser.cc

$(scaleparsertargets): %D%/scale_parser
	@echo rule 1
	cat '$(srcdir)/%D%/scale_parser.hh'
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
	sed -i -e '/digraph/ s,$(PWD),.,g' '$@.dot'
	ls %D%/*
	for d in %D%/location.hh \
		%D%/position.hh \
		%D%/stack.hh   \
		'$@.cc' \
		'$@.hh'; \
	do  \
		sed -i -e '/\#[^"]*include/ s,$(srcdir)/%D%/\(scale_parser\|location\|position\|stack\),%D%/\1,g'  "$$d" || exit 1 ; \
		grep -v '#line' "$$d" >"$$d.tmp" ; \
		(grep -v '#line' "$(srcdir)/$$d" 2>/dev/null | cmp "$$d.tmp" "-" >/dev/null 2>/dev/null) && \
			rm -f "$$d" "$$d.tmp" || \
			(rm -f "$$d.tmp" ; mv "$$d" "$(srcdir)/$$d")  || exit 2 ; \
	done
	touch "$@"
	ls %D%/*
	ls $(srcdir)/%D%/*
	cat '$(srcdir)/%D%/scale_parser.hh'


