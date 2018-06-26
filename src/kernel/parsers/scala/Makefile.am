include %D%/tests/Makefile.am

CLEANFILES += %D%/*.class \
	fix_scale_parser.stamp \
	fix_scale_parser.tmp \
	remove_scaleparsertargets.stamp

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
DISTCLEANFILES += \
	%D%/scale_parser.sed
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
$(scaleparsertargets): remove_scaleparsertargets.stamp
	@echo 'created $@'

remove_scaleparsertargets.stamp: $(srcdir)/%D%/scale_parser.yy
	@rm -f %D%/scale_parser
	touch remove_scaleparsertargets.stamp
	$(MAKE) $(AM_MAKEFLAGS) %D%/scale_parser


%D%/scale_parser.sed: Makefile
	rm -f '$@.tmp'
	for cmd in include line ; do \
		echo "/\#[[:space:]]*$${cmd}/ s%$(PWD)/%%g" >> '$@.tmp'; \
		for file in scale_parser location position stack ; do \
			echo "/\#[[:space:]]*$${cmd}/ s%$(srcdir)/%D%/$${file}%%D%/$${file}%g" >> '$@.tmp' ; \
			echo "/\#[[:space:]]*$${cmd}/ s%\"$${file}%\"%D%/$${file}%g" >> '$@.tmp' ; \
		done; \
	done
	if cmp '$@.tmp' '$@' ; then rm $@.tmp ; else  mv '$@.tmp' '$@' ; fi

# sed -i expects a backup argument on Mac OS X
# the best way is to add a nonempty extension directly after -i
# We must use extended regular expressions as otherwise \| would not be recognised on Mac OS X
%D%/scale_parser: $(srcdir)/%D%/scale_parser.yy %D%/scale_parser.sed
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
		echo "" ; \
		echo --	$(SED) -i.bak \
			-E  -f '%D%/scale_parser.sed' \
			"$$d" || exit 1 ; \
		$(SED) -i.bak \
			-E  -f '%D%/scale_parser.sed' \
			"$$d" || exit 1 ; \
		diff "$${d}.bak" "$$d" ; \
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

