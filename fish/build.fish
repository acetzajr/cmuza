#!/bin/fish
fish/init.fish $argv
if not test $status -eq 0
    exit $status
end
set jobs 16
cmake --build build --target muza --config $argv --parallel $jobs --
