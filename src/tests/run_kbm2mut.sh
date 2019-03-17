#!/bin/sh
. src/tests/run_variables.sh


outputfile="${scriptdir}/${scriptbase%.kbm}.mut2"
comparefile="${srcscript%.kbm}.muto"
"./scl2mut${EXEEXT}" -k "${srcscript}" "${top_srcdir}/src/tests/12tet.scl" "${outputfile}" || exit
sed "s/\$//" "${outputfile}" | diff -u "${comparefile}" - || exit
exit 0
