#!/bin/sh
#
# hwdump.sh -- wrapper around a mangled version of Mandrake's "detect" tool
# which dumps info to the QAgent tool.
#
# Author: Nicholas Vining (mordred@lokigames.com)

# Sanity checks.

if [ "$support_path" == "" ]; then
	echo "Please run this script from the Loki QAgent tool."
	exit 2
fi

if [ "$dump_path" == "" ]; then
	echo "Please run this script from the Loki QAgent tool."
	exit 2
fi

echo "<hwdump.sh>" >> "$dump_path"
if [ -f ./detect ]; then
	./detect >> "$dump_path"
else
	echo "hwdump.sh:: couldn't find ./detect" >> "$dump_path"
fi

echo "<r>"

echo "</hwdump.sh>" >> "$dump_path"
