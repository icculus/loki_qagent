#!/bin/sh
#
# stackdump.sh -- if QAgent is being run from a game with --detect following
# a crash, check for a stack trace, and dump that information to the file.
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

if [ ! $stack_trace_path ]; then
	echo "Please run this script from the Loki QAgent tool."
	exit 2
fi

echo "<stackdump.sh>" >> "$dump_path"

if [ -f "$stack_trace_path/stack-trace.txt" ]; then
	cat "$stack_trace_path/stack_trace.txt" >> "$dump_path"
else
	echo "No stack trace."
	echo "No stack trace." >> $"dump_path"
fi

echo "</stackdump.sh>" >> "$dump_path"
