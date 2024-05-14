#!/bin/fish
if test -d $argv
    echo "Removing $argv directory..."
    rm -r "$argv"
end
