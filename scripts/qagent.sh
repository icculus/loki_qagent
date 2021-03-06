#!/bin/sh -v
#
# qagent.sh -- execute all Loki QAgent Shell Scripts, and do sanity checks
#
# (C) 2000 Loki Software, Inc.
#
# Authors: Nicholas Vining (mordred@lokigames.com)
#	   Sam Lantinga (hercules@lokigames.com)

# Function to find the real directory a program resides in.
# Feb. 17, 2000 - Sam Lantinga, Loki Entertainment Software
FindPath()
{
    fullpath="`echo $1 | grep /`"
    if [ "$fullpath" = "" ]; then
        oIFS="$IFS"
        IFS=:
        for path in $PATH
        do if [ -x "$path/$1" ]; then
               if [ "$path" = "" ]; then
                   path="."
               fi
               fullpath="$path/$1"
               break
           fi
        done
        IFS="$oIFS"
    fi
    if [ "$fullpath" = "" ]; then
        fullpath="$1"
    fi
    # Is the awk/ls magic portable?
    if [ -L "$fullpath" ]; then
        fullpath="`ls -l "$fullpath" | awk '{print $11}'`"
    fi
    dirname $fullpath
}

# A few useful declarations....

qagent_version=0.1

# Main Entry Point is here.

# Jump to the install directory.

cd `FindPath $0`

# And see if we've got write permissions in the QAgent Directory
# (~/.loki/support)

#nv20000928 -- exported from QAgent now.
#support_path="$HOME/.loki/support"

while [ "$1" != "" ]; do
    case $1 in
        --product_name)
		 if [ "$2" = "" ]; then
                     echo "--product_name requires a parameter"
                     exit 1
                 fi
                 product_name=$2
		 export product_name
                 shift; shift;
                 ;;
        --product_cdrom)
		 if [ "$2" = "" ]; then
                     echo "--product_cdrom requires a parameter"
                     exit 1
                 fi
                 product_cdrom=$2
		 export product_cdrom
                 shift; shift;
                 ;;
        --product_version)
		 if [ "$2" = "" ]; then
                     echo "--product_version requires a parameter"
                     exit 1
                 fi
                 product_version=$2
		 export product_version
                 shift; shift;
                 ;;
        --product_path)
		 if [ "$2" = "" ]; then
                     echo "--product_path requires a parameter"
                     exit 1
                 fi
                 product_path=$2
		 export product_path
                 shift; shift;
                 ;;
        --product_desc)
		 if [ "$2" = "" ]; then
                     echo "--product_desc requires a parameter"
                     exit 1
                 fi
                 product_desc=$2
		 export product_desc
                 shift; shift;
                 ;;
        --product_prefs)
		 if [ "$2" = "" ]; then
                     echo "--product_prefs requires a parameter"
                     exit 1
                 fi
                 product_prefs=$2
		 export product_prefs
                 shift; shift;
                 ;;
        --support_path)
		 if [ "$2" = "" ]; then
                     echo "--support_path requires a parameter"
                     exit 1
                 fi
                 support_path=$2
		 export support_path
                 shift; shift;
                 ;;
        --dump_path)
		 if [ "$2" = "" ]; then
                     echo "--dump_path requires a parameter"
                     exit 1
                 fi
                 dump_path=$2
		 export dump_path
                 shift; shift;
                 ;;
        --product_stack)
		 if [ "$2" = "" ]; then
                     echo "--product_stack requires a parameter"
                     exit 1
                 fi
                 if [ ! -f $2 ]; then
                     echo "bad stack path"
                     exit 1
                 fi
                 stack_trace_path=$2
		 export stack_trace_path
		 shift; shift; 
                 ;;
        *)       echo "Unknown parameter $1"
                 echo ""
		 echo "Loki QAgent v$qagent_version, (C) 2000 Loki Software Inc."
		 echo ""
                 echo "Usage: $0 [--game game_name] [--stack stack_trace_path]"
                 echo ""
		 exit 2
		 ;;
    esac
done

# nv20001009 -- shuffle this stuff downwards to make sure that we DO have
# a support path... we need to modify this to hack around a KProcess bug.

if [ "$support_path" == "" ]; then
	echo "Please run this script from the Loki QAgent tool."
	exit 2
fi

if [ ! -d "$support_path" ]; then
	mkdir -p "$support_path"
fi

if [ ! -w "$support_path" ]; then
	echo "No write permissions on $support_path"
 	exit 2
fi

# Export parameters for use by other scripts

if [ $game_name ]; then
	export game_name
fi

# Make sure we can create a file (just another paranoia check...)

# Clean up after ourselves..

if [ -f "$support_path/qagent_dump" ]; then
	rm "$support_path/qagent_dump"
fi

echo "--- this file was automatically generated by Loki QAgent v$qagent_version" > "$support_path/qagent_dump"

if [ ! -f "$support_path/qagent_dump" ]; then
	echo "Couldn't create $support_path/qagent_dump"
	exit 1
fi

# and a useful export.
#dump_file="$support_path/qagent_dump"

export dump_path

# Some handy text to stop the user panicking!

# Now we start calling scripts.

if [ -f ./rpmdump.sh ]; then
	sh ./rpmdump.sh
fi


if [ -f ./md5sum.sh ]; then
	sh ./md5sum.sh
fi

if [ -f ./procdump.sh ]; then
	sh ./procdump.sh
fi

if [ -f ./xinfo.sh ]; then
	sh ./xinfo.sh
fi

if [ -f ./netdump.sh ]; then
	sh ./netdump.sh
fi

if [ -f ./hwdump.sh ]; then
	sh ./hwdump.sh
fi

if [ -f ./gldump.sh ]; then
	sh ./gldump.sh
fi

if [ "$product_path" ]; then

if [ -f $product_path/.qagent.sh ]; then
echo "--- user script starts now ---" >> "$dump_path"

	 sh $product_path/.qagent.sh

echo "--- user script ends now ---" >> "$dump_path"

fi
fi

# token for the user script..

echo "<r>"

# make sure that we actually have a stack path...
if [ $stack_trace_path ]; then

# and that we actually can use the script...

	if [ -f ./stackdump.sh ]; then
		. ./stackdump.sh
	fi
fi

# this is the token for the stack dump but we can't put it there in case
# we don't actually have a stack path.

echo "<r>"


