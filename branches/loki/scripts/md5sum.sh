#!/bin/sh
#
# md5sum.sh -- Dumps an md5sum of the product directory into the QAgent 
# file.
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

echo "<md5sum.sh>" >> "$dump_path"

if [ ! -d "/proc" ]; then
	echo "procdump.sh: couldn't find /proc" >> "$dump_path"
fi

if [ "$md5sum" == "" ]; then
	echo "Qagent says not to regenerate the MD5 sum." >> "$dump_path"
else

if [ "$product_path" == "" ]; then
	echo "No product path sent by QAgent." >> "$dump_path"	
else
	./md5sum "$product_path" >> "$dump_path"
fi
fi

echo "<r>"

echo "</md5sum.sh>" >> "$dump_path"
