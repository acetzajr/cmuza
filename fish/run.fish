#!/bin/fish
fish/build.fish $argv
if not test $status -eq 0
    exit $status
end
./build/muza
