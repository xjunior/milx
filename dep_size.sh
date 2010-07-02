#!/bin/bash

get_dep_tree() {
	for dep in `ldd $1 | awk '{ print $3 }' | grep "^/usr/lib"`
	do
		[ -h $dep ] && dep=`dirname "$dep"`/`readlink "$dep"`
		echo "$dep"
		get_dep_tree $dep
	done
}
get_total_size() {
	total=0
	for dep in $*; do
		size=`stat -c%s "$dep"`
		echo -e $(($size / 1024)) "KB\t$dep"
		total=$((total + size))
	done
	echo "Total:" $(( total / 1024 ))  "KB"
}

deps=`get_dep_tree "$1" | sort -u`
deps="$deps $1"

get_total_size $deps
