#!/bin/sh
#
# xinfo.sh -- retrieve information on various things X.
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

echo "<xinfo.sh>" >> "$dump_path"
echo "<xdpyinfo>" >> "$dump_path"

# make sure we actually get a useful display for xdpyinfo, in case we're
# running in a console.

# And try to do a test...

if [ -f /usr/X11R6/bin/xdpyinfo ]; then
	/usr/X11R6/bin/xdpyinfo >> "$dump_path"
fi

echo "</xdpyinfo>" >> "$dump_path"

echo "<r>"

echo "<xf86config>" >> "$dump_path"

if [ -f /etc/X11/XF86Config ]; then
	echo " " >> "$dump_path"
	cat /etc/X11/XF86Config >> "$dump_path"
else if [ -f /etc/XF86Config ]; then
	echo " " >> "$dump_path"
	cat /etc/XF86Config >> "$dump_path"
fi
fi

echo "</xf86config>" >> "$dump_path"

echo "</xinfo.sh>" >> "$dump_path"

echo "<r>"


