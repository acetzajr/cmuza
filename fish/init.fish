#!/bin/fish
# Debug, Release, RelWithDebInfo
if test $argv = Debug
    echo "CMAKE_BUILD_TYPE -> $argv: Disable optimizations - include debug information"
else if test $argv = Release
    echo "CMAKE_BUILD_TYPE -> $argv: Optimize for speed - exclude debug information"
else if test $argv = RelWithDebInfo
    echo "CMAKE_BUILD_TYPE -> $argv: Optimize for speed - include debug information"
else if test $argv = MinSizeRel
    echo "CMAKE_BUILD_TYPE -> $argv: Optimize for smallest binary size - exclude debug information"
else
    echo "--Error: wrong build type '$argv'"
    exit 1
end
fish/util/mkdir.fish build
set c_compiler gcc
cmake -S=. -B=build -DCMAKE_BUILD_TYPE=$argv -DCMAKE_C_COMPILER=$c_compiler -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
