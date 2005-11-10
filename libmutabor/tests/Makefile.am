buildincludedir=$(top_builddir)/includes
INCLUDES = -I$(buildincludedir)  -I$(top_srcdir)/includes
AM_LDFLAGS = -static
check_PROGRAMS = testmutfile
bin_PROGRAMS = testobject testidentifier testinterval testchkobject testidlist \
	testplaceholder testptrlist

#testparser_SOURCES = testparser.c
#testparser_LDADD = ../libmutabor.la

testobject_SOURCES = testobject.c
testobject_LDADD = -lmcheck ../libmutabor.la

testidentifier_SOURCES = testidentifier.c
testidentifier_LDADD = -lmcheck ../libmutabor.la

testinterval_SOURCES = testinterval.c
testinterval_LDADD = -lmcheck ../libmutabor.la

testchkobject_SOURCES = testchkobject.c
testchkobject_LDADD = -lmcheck ../libmutabor.la

testidlist_SOURCES = testidlist.c
testidlist_LDADD = -lmcheck ../libmutabor.la

testptrlist_SOURCES = testptrlist.c
testptrlist_LDADD = -lmcheck ../libmutabor.la

testplaceholder_SOURCES = testplaceholder.c
testplaceholder_LDADD = -lmcheck ../libmutabor.la

testmutfile_SOURCES = testmutfile.c
testmutfile_LDADD = -lmcheck ../libmutabor.la
testmutfile_LDFLAGS = -static


TESTS=testobject testidentifier testinterval testidlist testplaceholder testmutfile testptrlist
