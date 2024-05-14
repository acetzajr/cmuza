#!/bin/fish
if not test -d $argv
    echo "Making $argv directory..."
    mkdir "$argv"
end
