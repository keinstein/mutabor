#!/bin/sh
. src/tests/run_variables.sh


outputfile="${scriptdir}/${scriptbase%.nscl}.mut2"
comparefile="${srcscript%.nscl}.err"
logfile="${scriptdir}/${scriptbase%.nscl}.log2"
if "./scl2mut${EXEEXT}" "${srcscript}" "${outputfile}" 2>&1 | tee "${logfile}"
then
    grep -Eo -f "${comparefile}" "${logfile}" || exit $?
    exit 0
else
    exit 1
fi
