#!/bin/bash

# Must run script as: `source addDir.sh dir1 [dir2]`.
# Else script will run in new shell.
# When the script exits,
# the new shell will die along with the new path variable that was just created.

if [ -n $1 ]; then
    if [ -d $1 ]; then
        PATH=$PATH:$1
        export PATH
    else
        echo "DIRECTORY $1 DOES NOT EXIST."
    fi
fi

if [ -n $2 ]; then
    if [ -d $2 ]; then
        PATH=$PATH:$2
        export PATH
    else
        echo "DIRECTORY $2 DOES NOT EXIST."
    fi
fi