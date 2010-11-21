#!/bin/bash

languages=""
localefiles=""
for dir in `wx-config --prefix` /usr /usr/local /opt /opt/local ; 
do 
    echo "testing $dir"/share/locale/*/LC_MESSAGES/wxstd.mo

    if [ -d "$dir"/share/locale ] ; then
	found=""
	for dirx in "$dir"/share/locale/* ; do 
	    test -f "$dirx"/LC_MESSAGES/wxstd.mo && found="yes"
	done

	if test "$found" = yes ; then
	    wxlocaledir="$wxlocaledir $dir/share/locale"
	fi

	echo $wxlocaledir
    fi
done

echo $wxlocaledir