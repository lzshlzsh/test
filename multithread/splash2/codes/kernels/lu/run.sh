#!/bin/bash

cd "contiguous_blocks"
echo "contiguous_blocks"
if [ -f run.sh ]; then
	export PATH="$PWD:$PATH"
	sh run.sh
fi
cd "-" >/dev/null

cd "non_contiguous_blocks"
echo "non_contiguous_blocks"
if [ -f run.sh ]; then
	export PATH="$PWD:$PATH"
	sh run.sh
fi
cd "-" >/dev/null
