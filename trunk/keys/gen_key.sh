#!/bin/sh
#
# gen_key.sh -- sample automated script to generate batch keys.
#
# Author: Nicholas Vining (mordred@lokigames.com)
#
# Realistically, you should NEVER use this, on the grounds that this is
# ridiculously insecure. However, this is here as an example of a way to get
# GnuPG the information that it needs.

# Get the data.

. ../host.def

key_script="./key_style.txt"

echo "%echo WHY ARE YOU STILL USING THIS SCRIPT?!" > "$key_script"
echo "Key-Type: DSA" >> "$key_script"
echo "Key-Length: 1024" >> "$key_script"
echo "Subkey-Type: ELG-E" >> "$key_script"
echo "Subkey-Length: 1024" >> "$key_script"
echo "Name-Real: $publickeyname" >> "$key_script"
echo "Name-Comment: $default_title" >> "$key_script"
echo "Name-Email: $target_email" >> "$key_script"
echo "Expire-Date: 0" >> "$key_script"

# And if you want to know why this is REALLY insecure...

echo "Passphrase: $passphrase" >> "$key_script"
echo "%pubring $publickeyfile" >> "$key_script"
echo "%secring $secretkeyfile" >> "$key_script"
echo "%commit" >> "$key_script"
echo "%echo Finished generating key." >> "$key_script"

# Generate the key...

gpg --batch --gen-key $key_script

# And now kill the obnoxious key script.

rm $key_script

