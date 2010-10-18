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
  REGEX="^\(/usr/\(.*/\)\?lib/\|`dirname $1`\)"
  [[ $2 = "--deep" ]] && REGEX="/"
  for dep in `ldd $1 | awk '{ print $3 }' | grep $REGEX`
  do
    dep=`readlink -f "$dep"`
    echo "$dep"
    get_dep_tree $dep
  done
}

join_all() {
  for a in $@; do
    FILE=`readlink -f $a`
    echo $FILE
    get_dep_tree "$FILE"
  done
}

# MAIN
{
  list=`join_all $* | sort -u`
  total=0
  for dep in $list; do
    size=`stat -c%s "$dep"`
    echo -e $(($size / 1024)) "KB\t$dep"
    total=$((total + size))
  done
  echo "Total:" $(( total / 1024 ))  "KB"
}

