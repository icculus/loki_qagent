#!/bin/sh
#
# netdump.sh -- dump various networking things to the QAgent file.
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

echo "<netdump.sh>" >> "$dump_path"

echo "<ifconfig>" >> "$dump_path"

if [ -f /sbin/ifconfig ]; then
	/sbin/ifconfig >> "$dump_path"
else
	echo "netdump.sh:: couldn't find /sbin/ifconfig" >> "$dump_path"
fi

echo "</ifconfig>" >> "$dump_path"

echo "<r>"

echo "<route>" >> "$dump_path"

if [ -f /sbin/route ]; then
	/sbin/route >> "$dump_path"
else
	echo "netdump.sh:: couldn't find /sbin/route" >> "$dump_path"
fi

echo "</route>" >> "$dump_path"

echo "<r>"

echo "</netdump.sh>" >> "$dump_path"
