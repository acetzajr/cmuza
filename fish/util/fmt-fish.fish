#!/bin/fish
echo "> Formatting fish files..."
function format
    for file in (find fish -type f -name "*.fish")
        fish_indent --check $file &>/dev/null
        if not test $status -eq 0
            fish_indent --write $file &>/dev/null
            echo "  $file formatted"
            set count (math $math + 1)
        end
    end
end
set count 0
format
if test $count -eq 0
    echo "  no files formatted"
end
