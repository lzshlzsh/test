#!/bin/bash

if [ "$(ps -elf | grep sigignore | grep -v grep)" != "" ]; then
    echo "sigignore is running"
    exit 0
fi
/home/lzs/programming/test/sigignore
