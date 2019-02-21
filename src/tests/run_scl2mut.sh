#!/bin/sh
. src/tests/run_variables.sh


outputfile="${scriptdir}/${scriptbase%.scl}.mut2"
comparefile="${srcscript%.scl}.muto"
"./scl2mut${EXEEXT}" "${srcscript}" "${outputfile}" || exit
sed "s/\$//" "${outputfile}" | diff -u "${comparefile}" - || exit
exit 0
