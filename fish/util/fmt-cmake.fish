#!/bin/fish
echo "> Formatting cmake files..."
function format
    for file in (find . -type f -name "CMakeLists.txt")
        cmake-format --check $file &>/dev/null
        if not test $status -eq 0
            cmake-format -i $file &>/dev/null
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
