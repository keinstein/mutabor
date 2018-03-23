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

#
# if OFF_TREE
# $(top_srcdir)/%D%/scale_parser.cc: %D%/scale_parser.cc.stamp
# $(top_srcdir)/%D%/keymap_parser.cc: %D%/keymap_parser.cc.stamp
# #$(top_srcdir)/%D%/scale_lexer.cc: %D%/scale_lexer.cc.stamp
# endif
#
#
$(top_srcdir)/%D%/scale_parser.cc: $(top_srcdir)/%D%/scale_parser.yy
	$(AM_V_YACC)$(am__skipyacc) \
		$(SHELL) \
		$(YLWRAP) \
		'$<' \
		y.tab.c '$@' \
		y.tab.h "`echo '$@' | $(am__yacc_c2h)`" \
		y.output '$*.output' \
		y.dot '$*.dot' \
		y.xml '$*.xml' \
		location.hh '$(top_srcdir)/%D%/location.hh' \
		position.hh '$(top_srcdir)/%D%/position.hh' \
		stack.hh  "$(top_srcdir)/%D%/stack.hh" \
		-- \
		$(YACCCOMPILE)


