SUFFIXES=.def .h .hh

CLASSES=object identifier interval intervalSum intervalDiff idlist \
	intervalPlaceholder intervalStretch intervalInv ptrlist \
	mutfile

BUILT_SOURCES=$(CLASSES:%=%.h) $(CLASSES:%=%.hh)
#	object.h object.hh identifier.h identifier.hh interval.h interval.hh \
#	intervalSum.h intervalSum.hh intervalDiff.h intervalDiff.hh idlist.h idlist.hh \
#	intervalPlaceholder.h intervalPlaceholder.hh intervalStretch.h intervalStretch.hh \
#	intervalInv.h intervalInv.hh ptrlist.h ptrlist.hh \
#	mutfile.h mutfile.hh

EXTRA_DIST=makeclass.pl $(CLASSES:%=%.def)

$(BUILT_SOURCES):makeclass.pl

.def.hh:
	$(srcdir)/makeclass.pl <$< >$*.h
.def.h:	
	$(srcdir)/makeclass.pl <$< >$*.h