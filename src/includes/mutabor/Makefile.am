CLEANFILES =
AM_CFLAGS =
check_MIDIFILES =

SUBDIRS=tests
include $(top_srcdir)/common-rules.mk

SUFFIXES += .def .h .hh

CLASSES=object identifier interval intervalSum intervalDiff idlist \
	intervalPlaceholder intervalStretch intervalInv ptrlist \
	mutfile

BUILT_SOURCES += $(CLASSES:%=%.h) $(CLASSES:%=%.hh)
#	object.h object.hh identifier.h identifier.hh interval.h interval.hh \
#	intervalSum.h intervalSum.hh intervalDiff.h intervalDiff.hh idlist.h idlist.hh \
#	intervalPlaceholder.h intervalPlaceholder.hh intervalStretch.h intervalStretch.hh \
#	intervalInv.h intervalInv.hh ptrlist.h ptrlist.hh \
#	mutfile.h mutfile.hh

EXTRA_DIST += makeclass.pl $(CLASSES:%=%.def) $(BUILT_SOURCES)


$(BUILT_SOURCES):makeclass.pl

@COND_PERL_TRUE@.def.hh:
@COND_PERL_TRUE@	$(PERL)  $(srcdir)/makeclass.pl -D$(DEPDIR)/$*.Po -I$(srcdir) -d $*.hh  <$<  >$*.h
@COND_PERL_TRUE@.def.h:	
@COND_PERL_TRUE@	$(PERL) $(srcdir)/makeclass.pl -D$(DEPDIR)/$*.Po -I$(srcdir) -d $*.hh <$<  >$*.h

@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/object.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/identifier.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/interval.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/intervalPlaceholder.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/intervalSum.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/intervalDiff.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/intervalStretch.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/intervalInv.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/idlist.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/ptrlist.Po@am__quote@
@COND_PERL_TRUE@@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/mutfile.Po@am__quote@


DISTCLEANFILES+= ./$(DEPDIR)/*.Po
