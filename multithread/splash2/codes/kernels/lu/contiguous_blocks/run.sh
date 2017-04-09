#!/bin/bash

declare -a inputs=
declare -r exe="LU"
declare -r opt="-p2"


if [ -n "${BTPLAY}" ]; then
	echo "record"
	time -p $PFMON_COMMAND -record ${exe} ${opt} ${inputs} | tee log.record
	echo "replay"
	time -p $PFMON_COMMAND -replay ${exe} ${opt} ${inputs} | tee log.replay

	if diff log.record log.replay 1>/dev/null 2>/dev/null; then 
		echo "MATCH"
	else
		echo "NOTMATCH"
	fi

	stat -c %s "${exe}.bp"
else
	echo "common"
	time -p $PFMON_COMMAND ${exe} ${opt} ${inputs} | tee log.common
fi
