# Top-level Makefile for all FIG files

# "infrastructure" non-generated files:
# Headers
FIG_HDR = log.h prob.h util.h loglevel.h spinlock.h control.h
# Source files
FIG_SRC = log.c prob.c util.c control.c loglevel.c malloc.c execve.c
# The generated files are the first column of names from func.desc with .c
# tacked on
FIG_GEN := $(addsuffix .c, $(shell cut -f1 func.desc))
# The instrumented library that is the final results of "make all"
FIG_LIB = libfig.so
# Prefix of all parser-related files
FIG_GRM = control_parser
# Program that launches the wrapper version of FIG
FIG_LAUNCHER = launcher.c

GCC     = gcc -O2
CC      = $(GCC)
FIG_FLAGS = -shared -ldl

# Produces libfig.so and control.out, with standard in-line logging enabled
all: nologd control.out

# Produces libfig.so, control.out and the fig launcher program, which
# facilitates shared-memory logging via a separate daemon process
wrapper: logd fig control.out

# Produces the fig launcher program
fig: $(FIG_LAUNCHER)
	$(GCC) -o fig $(FIG_LAUNCHER)

# to generate the library stubs, we utilize awk. 
$(FIG_GEN): func.desc stubgen.awk 
	awk -f stubgen.awk < func.desc > /dev/null

nologd: $(FIG_HDR) $(FIG_SRC) $(FIG_GEN) $(addsuffix .c, $(FIG_GRM))
	$(GCC) -o $(FIG_LIB) $(FIG_FLAGS) \
		$(FIG_SRC) \
		$(FIG_GEN) \
		$(addsuffix .c, $(FIG_GRM))

logd: $(FIG_HDR) $(FIG_SRC) $(FIG_GEN) $(addsuffix .c, $(FIG_GRM))
	$(GCC) -o $(FIG_LIB) $(FIG_FLAGS) -DSHMEM_LOGGING \
		$(FIG_SRC) \
		$(FIG_GEN) \
		$(addsuffix .c, $(FIG_GRM))

# Invokes bison with the grammar file to produce a control file parser program
$(addsuffix .c, $(FIG_GRM)): $(addsuffix .grm, $(FIG_GRM))
	bison -p fig -o $(addsuffix .c, $(FIG_GRM)) $(addsuffix .grm, $(FIG_GRM))

# Generates the version of the control file that serves as input to the parser
control.out: control
	./make_control control

###
clean:
	rm -f *.o $(FIG_LIB) fig

#kills the generated files too
superclean: clean
	rm -f $(FIG_GEN) $(addsuffix .c, $(FIG_GRM)) fig.log* core
