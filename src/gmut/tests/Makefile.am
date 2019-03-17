MUTEXAMPLETESTS = \
	%D%/english_demos.mutexample \
	%D%/english_demo.mutexample \
	%D%/english_cdur.mutexample \
	%D%/english_nix.mutexample \
	%D%/english_midi.mutexample \
	%D%/english_cohen.mutexample \
	%D%/english_tutorial.mutexample \
	%D%/english_instr.mutexample \
	%D%/english_extern.mutexample \
	%D%/german_Demo.mutexample \
	%D%/german_Extern.mutexample \
	%D%/german_Cohen.mutexample \
	%D%/german_Instr.mutexample \
	%D%/german_Demos.mutexample \
	%D%/german_Demo-utf8.mutexample \
	%D%/german_Cdur.mutexample \
	%D%/german_Midi.mutexample \
	%D%/german_Nix.mutexample 

MUTTESTS = \
	%D%/error1.mut \
	%D%/error2.mut \
	%D%/missing_tones.mut

EXTRA_DIST += \
	$(MUTEXAMPLETESTS:.mutexample=-output.txt) \
	%D%/error1-output.txt \
	%D%/error1.variables \
	%D%/error2-output.txt \
	%D%/error2.variables \
	%D%/missing_tones-output.txt \
	%D%/missing_tones.variables \
	$(MUTTESTS)

CLEANFILES += \
	$(MUTEXAMPLETESTS:.mutexample=-result.mid) \
	$(MUTTESTS:.mut=-result.mid)

TESTS += \
	$(MUTEXAMPLETESTS) \
	$(MUTTESTS)

.PHONY: $(MUTEXAMPLETESTS)
$(MUTEXAMPLETESTS):

#check_MIDIFILES += \
#	$(srcdir)/%D%/runmut.mid

#$(MUTTESTS:.mut=.log): \
#	%D%/run_mut.sh \
#	prepare_mut \
#	$(top_srcdir)/%D%/runmut.mid


