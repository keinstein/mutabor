#!/bin/sh
. src/tests/run_variables.sh

stemfile="${script%.mut}"
file="${top_srcdir}/src/tests/runmut.mid"
startkeys=""

if test -f ${script}.variables
then
    . ${script}.variables
fi

./midifilemutabor${EXEEXT} "$file" "${stemfile}-result.mid" "$srcscript" "$startkeys" 

./mf2txt${EXEEXT} "${stemfile}-result.mid" | \
    sed 's/\r$//' | \
    diff -u "${srcscript%.mut}-output.txt" -

exit 0
