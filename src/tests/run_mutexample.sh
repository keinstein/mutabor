#!/bin/sh
set -e -x
. src/tests/run_variables.sh

stemfile="${script%.mutexample}"
mut="${top_srcdir}Examples/`echo "${scriptbase%.mutexample}.mut" | ${SED} s,_,/,g`"
file="${top_srcdir}src/tests/runmut.mid"
startkeys=""

if test -f ${script}.variables
then
    . ${script}.variables
fi

./midifilemutabor${EXEEXT} "$file" "${stemfile}-result.mid" "$mut" "$startkeys" 

./mf2txt${EXEEXT} "${stemfile}-result.mid" | \
    sed 's/\r$//' | \
    diff -u "${top_srcdir}${stemfile}-output.txt" -
exit 0
