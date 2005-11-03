SUFFIXES=.def .h .hh

BUILT_SOURCES=object.h object.hh identifier.h identifier.hh interval.h interval.hh \
	intervalSum.h intervalSum.hh intervalDiff.h intervalDiff.hh idlist.h idlist.hh \
	intervalPlaceholder.h intervalPlaceholder.hh intervalStretch.h intervalStretch.hh \
	intervalInv.h intervalInv.hh ptrlist.h ptrlist.hh \
	mutfile.h mutfile.hh

$(BUILT_SOURCES):makeclass.pl

.def.hh:
	./makeclass.pl <$< >$*.h
.def.h:	
	./makeclass.pl <$< >$*.h