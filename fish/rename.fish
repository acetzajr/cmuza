#!/bin/fish
function format
    for file in (find  $argv[1] -type f -name "*.$argv[2]")
        set rename (path change-extension $argv[3] $file)
        echo "  $file renamed to $rename"
        mv $file $rename
    end
end
echo "> Renaming files in '$argv[1]' with extension '$argv[2]' to extension '$argv[3]'"
format $argv
