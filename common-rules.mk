DLLCOPYPATTERN = \(wx\|mingw\)
DLLEXEDIR = Mutabor

installdll:
	@echo 'solving references for $(DLLLINKFILE)'
	DLLSEARCHPATH="$(DLLSEARCHPATH)" ; \
	for d in `LANG=C $(OBJDUMP) -p  $(DLLEXEDIR)/$(DLLLINKFILE) |sed '/^\s*DLL Name:.*\(wx\|mingw\|gcc\|stdc++\)/ { s/^\s*DLL Name:\s*//; p } ; d '` ; \
	do \
		echo -n checking "$$d" ; \
		if [ ! -f $(DLLEXEDIR)/$$d ] ; then \
			echo -n search ; \
			f=`( find $$DLLSEARCHPATH -name "$$d" || \
			find $$DLLSEARCHPATH -name "$$d.*")|head -n 1` ; \
			echo -n install " $$f " ; \
			test -f "$$f" && $(INSTALL_PROGRAM_ENV) $(INSTALL_DATA) "$$f" "`pwd`/$(DLLEXEDIR)" ; \
			case "$$f" in \
			*.gz)  GZIP=$(GZIP_ENV) gzip -dc $(DLLEXEDIR)/`basename "$$f"` >$(DLLEXEDIR)/"$$d" ;; \
			esac ; \
			echo -n check " $$d " ; \
			$(MAKE) DLLLINKFILE="$$d" DLLEXEDIR="$(DLLEXEDIR)" installdll ; \
		fi ; \
		echo " done." ;\
	done ; \
	ls
