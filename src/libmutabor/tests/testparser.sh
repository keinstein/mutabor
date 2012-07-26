#!/bin/sh
export MALLOC_TRACE=testparser.trace
pwd
echo $srcdir/*.mut
echo ---
./testparser $srcdir/../mutlex_de.tab $srcdir/Demo.mut
exit $?
