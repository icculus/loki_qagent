#!/bin/sh
#
# .qagent.sh -- this is a template file which you can use for user-defined
# product scripts. 
#
# Author: Nicholas Vining (mordred@lokigames.com)

# Sanity checks.

if [ "$support_path" != "" ]; then
	echo "Please run this script from the Loki QAgent tool."
	exit 2
fi

if [ "$dump_path" != "" ]; then
	echo "Please run this script from the Loki QAgent tool."
	exit 2
fi

# indicator indicating the name of the script. This hasn't been solidified
# yet.

echo "--- template.sh ---" >> "$dump_path"

# This is the right way to perform crash analysis.

if [ "$stack_trace_path" ]; then
	echo "performing crash analysis" >> "$dump_path"
fi

# And just to show the existance of the variables.

if [ "$product_name" ]; then
	echo "product name: $(product_name)" >> "$dump_path"
fi

if [ "$product_version" ]; then
	echo "product version: $(product_version)" >> "$dump_path"
fi

if [ "$product_path" ]; then
	echo "product path: $(product_path)" >> "$dump_path"
fi

if [ "$product_cdrom" ]; then
	echo "product cdrom: $(product_cdrom)" >> "$dump_path"
fi

if [ "$product_desc" ]; then
	echo "product desc: $(product_desc)" >> "$dump_path"
fi

if [ "$product_prefs" ]; then
	echo "product prefs: $(product_prefs)" >> "$dump_path"
fi
