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

set +e
./midifilemutabor${EXEEXT} "$file" "${stemfile}-result.mid" "$srcscript" "$startkeys"
returned=$?
if test "$returned" -ne "$retval"
then
    echo "Got wrong return value ${returned} (expected: ${retval})"
    exit $returned
fi
set -e


./mf2txt${EXEEXT} "${stemfile}-result.mid" | \
    sed 's/\r$//' | \
    diff -u "${srcscript%.mut}-output.txt" -

exit 0
