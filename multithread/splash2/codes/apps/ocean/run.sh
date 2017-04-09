#!/bin/bash

cd "contiguous_partitions"
echo "contiguous_partitions"
if [ -f run.sh ]; then
	export PATH="$PWD:$PATH"
	sh run.sh
fi
cd "-" >/dev/null

cd "non_contiguous_partitions"
echo "non_contiguous_partitions"
if [ -f run.sh ]; then
	export PATH="$PWD:$PATH"
	sh run.sh
fi
cd "-" >/dev/null
