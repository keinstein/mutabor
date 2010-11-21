buildincludedir=$(top_builddir)/includes
INCLUDES = -I$(buildincludedir)  -I$(top_srcdir)/includes \
	@NETINET_INC@ -I $(top_builddir)/intl
AM_LDFLAGS = -static
check_PROGRAMS = testmutfile
bin_PROGRAMS = testobject testidentifier testinterval testchkobject testidlist \
	testplaceholder testptrlist
LDADD = @LTLIBINTL@

#testparser_SOURCES = testparser.c
#testparser_LDADD = ../libmutabor.la

testobject_SOURCES = testobject.c
testobject_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la $(LDADD)

testidentifier_SOURCES = testidentifier.c
testidentifier_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la

testinterval_SOURCES = testinterval.c
testinterval_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la

testchkobject_SOURCES = testchkobject.c
testchkobject_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la

testidlist_SOURCES = testidlist.c
testidlist_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la

testptrlist_SOURCES = testptrlist.c
testptrlist_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la

testplaceholder_SOURCES = testplaceholder.c
testplaceholder_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la

testmutfile_SOURCES = testmutfile.c
testmutfile_LDADD = @MCHECK@ $(LDADD) ../libmutabor.la
testmutfile_LDFLAGS = -static


TESTS=testobject$(EXEEXT) testidentifier$(EXEEXT) testinterval$(EXEEXT) testidlist$(EXEEXT) testplaceholder$(EXEEXT) testmutfile$(EXEEXT) testptrlist$(EXEEXT)

