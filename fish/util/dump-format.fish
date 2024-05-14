#!/bin/fish
set style LLVM
clang-format -style=$style -dump-config >.clang-format
