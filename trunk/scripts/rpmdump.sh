#!/bin/sh
#
# rpmdump.sh -- check for the existance of RPM, and dump sorted data
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

echo "<rpmdump.sh>" >> "$dump_path"
if [ -f /bin/rpm ]; then
	/bin/rpm -qa | sort >> "$dump_path"
else
	echo "rpmdump.sh:: couldn't find /bin/rpm" >> "$dump_path"
fi

echo "</rpmdump.sh>" >> "$dump_path"

echo "<r>"
