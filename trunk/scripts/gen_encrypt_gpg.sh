#!/bin/sh
#
# gen_encrypt_gpg.sh -- Generates encrypt_gpg.sh as part of the build
# process.
#
# Author: Nicholas Vining (mordred@lokigames.com)

# Since this will always have the same parameters, we can hack this out
# nastily. Really, we _shouldn't_, but...

. ../host.def

target="./encrypt_gpg.sh"

echo "source_file_path=\$1" > "$target"
echo "dest_file_path=\$2" >> "$target"
echo "used_keyring=\$3" >> "$target"
echo "" >> "$target"
echo "if [ \"\$source_file_path\" == \"\" ]; then" >> "$target"
echo "	echo \"bad source file path, or unspecified.\"" >> "$target"
echo "	exit 2" >> "$target"
echo "fi" >> "$target"
echo "" >> "$target"
echo "if [ ! -f \"\$source_file_path\" ]; then" >> "$target"
echo "	echo \"bad source file path.\"" >> "$target"
echo "	exit 2" >> "$target"
echo "fi" >> "$target"
echo "" >> "$target"
echo "if [ \"\$dest_file_path\" == \"\" ]; then" >> "$target"
echo "	echo \"bad dest file path, or unspecified.\"" >> "$target"
echo "	exit 2" >> "$target"
echo "fi" >> "$target"
echo "" >> "$target"
echo "" >> "$target"
echo "gpg --keyring \"\$used_keyring\" --no-default-keyring --yes --always-trust -e -r \"$publickeyname\" -o \"\$dest_file_path\" -a < \"\$source_file_path\"" >> "$target"

