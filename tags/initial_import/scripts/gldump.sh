#!/bin/sh
#
# gldump.sh -- looks for duplicate libGL libraries and dumps their locations
# to the QAgent file.
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

echo "<gldump.sh>" >> "$dump_path"

if [ -f /usr/bin/find ]; then
	backup_location="`/bin/pwd`"
	cd /usr
# todo: automatic weeding of flawed results
	/usr/bin/find -name libGL.so* >> "$dump_path"
	cd "$backup_location"
else
	echo "gldump.sh:: couldn't find /usr/bin/find" >> "$dump_path"
fi

echo "<r>"

echo "</gldump.sh>" >> "$dump_path"
