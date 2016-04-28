#!/bin/sh

env

file="$1"

$top_builddir/scl2mut $file ${file%.scl}.mut 2>&1 >${file%.scl}.log || exit 1
diff -u ${file}.mut ${file%.scl}.mut || exit 2
exit 0
