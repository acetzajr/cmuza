#!/bin/fish
echo "> Formatting c++ files..."
function format
    for file in (find $argv[1] -type f -name "*.$argv[2]")
        clang-format --Werror --dry-run $file &>/dev/null
        if not test $status -eq 0
            clang-format -i $file &>/dev/null
            echo "  $file formatted"
            set count (math $math + 1)
        end
    end
end    
set count 0
format include hpp
format source cpp
if test $count -eq 0
    echo "  no files formatted"
end
