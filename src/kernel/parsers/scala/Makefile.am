include %D%/tests/Makefile.am

CLEANFILES += %D%/*.class \
	fix_scale_parser.stamp


%D%/scale_parser.$(OBJEXT): $(srcdir)/%D%/location.hh \
			    $(srcdir)/%D%/position.hh \
			    $(srcdir)/%D%/stack.hh \
			    fix_scale_parser.stamp
$(srcdir)/%D%/location.hh: location.hh
	if test -f "$<" ; then (cmp "$<" "$@" || cp $< $@) ; fi

$(srcdir)/%D%/position.hh: position.hh
	if test -f "$<" ; then (cmp "$<" "$@" || cp $< $@) ; fi

$(srcdir)/%D%/stack.hh: stack.hh
	if test -f "$<" ; then (cmp "$<" "$@" || cp $< $@) ; fi

location.hh stack.hh position.hh: %D%/scale_parser.hh

fix_scale_parser.stamp: $(srcdir)/%D%/scale_parser.cc
	sed -e 's,$(srcdir)/%D%/scale_parser.hh,scale_parser.hh,g' "$<" >"$@"
	cmp "$@" "$<" || cp "$@" "$<"
	touch "$@"

# lex and yacc rules seem not to be very clear about parallel builds
# since we rely on flex and beson, we can use their more "portable" features
# to generate the desired files

CLEANFILES += \
	%D%/scale_parser.cc.stamp \
	%D%/keymap_parser.cc.stamp \
	%D%/scale_lexer.cc.stamp


if OFF_TREE
$(top_srcdir)/%D%/scale_parser.cc: %D%/scale_parser.cc.stamp
$(top_srcdir)/%D%/keymap_parser.cc: %D%/keymap_parser.cc.stamp
$(top_srcdir)/%D%/scale_lexer.cc: %D%/scale_lexer.cc.stamp
endif


%D%/scale_parser.cc: %D%/scale_parser.cc.stamp
%D%/scale_parser.cc.stamp: %D%/scale_parser.yy
	rm -f "$@"
	$(MKDIR_P) `dirname %D%/scale_parser.cc`
	rm -f "%D%/scale_parser.cc"
	$(YACCCOMPILE) -o %D%/scale_parser.cc -b %D%/ $<
	cmp $(top_srcdir)/%D%/scale_parser.cc %D%/scale_parser.cc 2>/dev/null || \
		cp %D%/scale_parser.cc $(top_srcdir)/%D%/scale_parser.cc
	touch "$@"

%D%/keymap_parser.cc: %D%/keymap_parser.cc.stamp
%D%/keymap_parser.cc.stamp: %D%/keymap_parser.yy
	rm -f "$@"
	$(MKDIR_P) `dirname %D%/keymap_parser.cc`
	rm -f "%D%/keymap_parser.cc"
	$(YACCCOMPILE) -o %D%/keymap_parser.cc -b %D%/ $<
	cmp $(top_srcdir)/%D%/keymap_parser.cc %D%/keymap_parser.cc 2>/dev/null || \
		cp %D%/keymap_parser.cc $(top_srcdir)/%D%/keymap_parser.cc
	touch "$@"

%D%/scale_lexer.cc: %D%/scale_lexer.cc.stamp
%D%/scale_lexer.cc.stamp: %D%/scale_lexer.ll
	rm -f "$@"
	$(MKDIR_P) `dirname %D%/scale_lexer.cc`
	rm -f "%D%/scale_lexer.cc"
	$(LEXCOMPILE) -o %D%/scale_lexer.cc $<
	cmp $(top_srcdir)/%D%/scale_lexer.cc %D%/scale_lexer.cc 2>/dev/null || \
		cp %D%/scale_lexer.cc $(top_srcdir)/%D%/scale_lexer.cc
	touch "$@"

# if OFF_TREE
# $(top_srcdir)/%D%/scale_parser.cc: %D%/scale_parser.cc
# 		cp %D%/scale_parser.cc $(top_srcdir)/%D%/scale_parser.cc
# $(top_srcdir)/%D%/scale_parser.hh: %D%/scale_parser.hh
# 		cp %D%/scale_parser.hh $(top_srcdir)/%D%/scale_parser.hh
# $(top_srcdir)/%D%/keymap_parser.cc: %D%/keymap_parser.cc
# 		cp %D%/keymap_parser.cc $(top_srcdir)/%D%/keymap_parser.cc
# $(top_srcdir)/%D%/scale_lexer.cc: %D%/scale_lexer.cc
# 		cp %D%/scale_lexer.cc $(top_srcdir)/%D%/scale_lexer.cc
# endif

