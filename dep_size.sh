#!/bin/bash
#
# This file is part of Milx.
#
# Milx is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Milx is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
#

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
