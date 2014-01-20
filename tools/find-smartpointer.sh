#!/bin/bash

pointers=`sed -e "/New value.*$1/ { "'s/.*\(0x[^ 	]*\)[ 	]*->[ 	]*\(0x[^ 	]*\).*/\1/ ;  p}; d' "$2"|sort -u`

undestroyed=
for p in $pointers
do
    echo -n "$p "
    if grep -q "Destroying $p ->" "$2"
    then
	echo "... destroyed"
    else
	echo "???"
	undestroyed="$p $undestroyed"
    fi
done
echo "undestroyed: $undestroyed"

pointers=
for p in $undestroyed
do
    pointers="$pointers `sed -e "/$p.*\@/ {"'s/.*\@ \([^)]*\).*/\1/;p};d' "$2"`"
done
echo "addresses: $pointers"
for p in $pointers
do
    addr2line -e "$3" "$p"
done
