#!/bin/sh
#
# procdump.sh -- Dumps an assortment of fascinating things to the QAgent
# file from the /proc directory. 
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

echo "<procdump.sh>" >> "$dump_path"

if [ ! -d "/proc" ]; then
	echo "procdump.sh: couldn't find /proc" >> "$dump_path"
fi

if [ -f "/proc/cpuinfo" ]; then
	cat /proc/cpuinfo >> "$dump_path"
else
	echo "procdump.sh: couldn't find /proc/cpuinfo" >> "$dump_path"
fi

echo "<r>"

echo "<meminfo>" >> "$dump_path"

if [ -f "/proc/meminfo" ]; then

	cat /proc/meminfo >> "$dump_path"

else
	echo "procdump.sh: couldn't find /proc/meminfo" >> "$dump_path"
fi

echo "</meminfo>" >> "$dump_path"

echo "<r>"

echo "<modules>" >> "$dump_path"

if [ -f "/proc/modules" ]; then
	cat /proc/modules >> "$dump_path"
else
	echo "procdump.sh: couldn't find /proc/modules" >> "$dump_path"
fi

echo "</modules>" >> "$dump_path"

echo "<r>"

echo "<version>" >> "$dump_path"

if [ -f "/proc/version" ]; then
	cat /proc/version >> "$dump_path"
else
	echo "procdump.sh: couldn't find /proc/version" >> "$dump_path"
fi

echo "</version>" >> "$dump_path"

echo "<r>"

echo "</procdump.sh>" >> "$dump_path"
