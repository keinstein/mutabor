#!/bin/sh
. src/tests/run_variables.sh


outputfile="${scriptdir}/${scriptbase%.scl}.mut2"
comparefile="${srcscript%.scl}.muto"
"./scl2mut${EXEEXT}" "${srcscript}" "${outputfile}" || exit
sed "s/
exit 0