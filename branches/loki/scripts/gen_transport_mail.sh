#!/bin/sh
#
# gen_transport_mail.sh -- builds script to send mail to the support e-mail
# address with the right data.
#
# Author: Nicholas Vining (mordred@lokigames.com)
#
# Note: This script is automatically generated at build time.

. ../host.def

target="./transport_mail.sh"

echo "source_file_path=\$1" > "$target"
echo "source_email_address=\$2" >> "$target"
echo "" >> "$target"
echo "if [ \"\$source_file_path\" == \"\" ]; then" >> "$target"
echo "	echo \"Bad source file path.\"" >> "$target"
echo "	exit 2" >> "$target"
echo "fi" >> "$target"
echo "" >> "$target"
echo "if [ \"\$source_email_address\" == \"\" ]; then" >> "$target"
echo "	echo \"Bad dest. e-mail path.\"" >> "$target"
echo "	exit 2" >> "$target"
echo "fi" >> "$target"
echo "" >> "$target"
echo "echo \".\" >> \"\$source_file_path\"" >> "$target"
echo "" >> "$target"
echo "if [ -f /usr/bin/sendmail ]; then" >> "$target"
echo "# This information is automatically retrieved from host.def" >> "$target"
echo "/usr/bin/sendmail -f\$source_email_address $target_email < \"\$source_file_path\"" >> "$target"
echo "" >> "$target"
echo "fi" >> "$target"
