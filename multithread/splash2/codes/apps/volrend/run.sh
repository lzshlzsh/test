#!/bin/bash

declare -a inputs="inputs/*.den"
declare -r exe="VOLREND"
declare -r opt="8"


for i in ${inputs[*]}; do
	i=${i%.den}
#if [ ${i} != "inputs/head" ]; then
	echo "${i}"

	if [ -n "${BTPLAY}" ]; then	
		echo "record"
		time -p $PFMON_COMMAND -record ${exe} ${opt} ${i} | tee log.record
		echo "replay"
		time -p $PFMON_COMMAND -replay ${exe} ${opt} ${i} | tee log.replay

		if diff log.record log.replay 1>/dev/null 2>/dev/null; then 
			echo "MATCH"
		else
			echo "NOTMATCH"
		fi

		stat -c %s "${exe}.bp"

		i=${i##*/}
		cp ${exe}.bp ${exe}.bp.${i}
	else
		echo "common"
		time -p $PFMON_COMMAND ${exe} ${opt} ${i} | tee log.common
	fi	
	#fi
done
