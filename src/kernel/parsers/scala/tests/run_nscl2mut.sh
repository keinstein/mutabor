#!/bin/sh

env

file="$1"

$top_builddir/scl2mut $file ${file%.nscl}.mut && exit 1
grep -q -f ${file%.nscl}.err ${file%.nscl}.log || exit 2
exit 0
