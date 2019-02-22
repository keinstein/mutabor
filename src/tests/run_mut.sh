#!/bin/sh
set -e
. src/tests/run_variables.sh

stemfile="${script%.mut}"
file="${top_srcdir}/src/tests/runmut.mid"
startkeys=""

if test -f ${srcscript%.mut}.variables
then
    . ${srcscript%.mut}.variables
fi
if test -f ${script%.mut}.variables
then
    . ${script%.mut}.variables
fi

./midifilemutabor${EXEEXT} "$file" "${stemfile}-result.mid" "$srcscript" "$startkeys" || exit $?

./mf2txt${EXEEXT} "${stemfile}-result.mid" | \
    sed 's/\r$//' | \
    diff -u "${srcscript%.mut}-output.txt" -

exit 0
