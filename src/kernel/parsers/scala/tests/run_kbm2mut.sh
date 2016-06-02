#!/bin/sh

env

file="$1"
dir=`dirname "$file"`
basefile=`basename "$file"`
$top_builddir/scl2mut -k $file "$dir/12tet.scl" ${basefile%.kbm}_kbm.mut2 || exit 1
diff -u ${file%.kbm}_kbm.mut ${basefile%.kbm}.mut2 || exit 2
exit 0
