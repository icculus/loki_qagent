#!/bin/sh
#
# transport_file.sh -- sends file to the target location.
#
# Author: Nicholas Vining (mordred@lokigames.com)
#
# Note that we could do this in an executable, but it's being done as a
# batch file for reasons of consistency.

source_file_path=$1
dest_file_path=$2

if [ "$source_file_path" == "" ]; then
	echo "Bad source file path."
	exit 2
fi

if [ "$dest_file_path" == "" ]; then
	echo "Bad dest file path."
	exit 2
fi

cp $source_file_path $dest_file_path
