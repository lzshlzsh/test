#!/bin/bash

#declare -a apps=(barnes fmm ocean raytrace water-nsquared water-spatial) 
#declare -a kernels=(cholesky fft lu radix)

declare -a apps=(barnes fmm ocean raytrace water-nsquared water-spatial) 
declare -a kernels=(cholesky fft lu radix)

for i in ${apps[*]}; do
	rundir="${PWD}/apps/${i}"
	if [ -f "${rundir}/run.sh" ]; then
		cd "${rundir}"
		echo "enter ${rundir}";
		if [ "$1" == "-e" ]; then
			echo "really executing ${rundir}..."
			export PATH="${rundir}:$PATH"
			sh "${rundir}/run.sh"
		fi
		cd "-" >/dev/null
	fi
done


for i in ${kernels[*]}; do
	rundir="${PWD}/kernels/${i}"
	if [ -f "${rundir}/run.sh" ]; then
		cd "${rundir}"
		echo "enter ${rundir}";
		if [ "$1" == "-e" ]; then
			echo "really executing ${rundir}..."
			export PATH="${rundir}:$PATH"
			sh "${rundir}/run.sh"
		fi
		cd "-" >/dev/null
	fi
done
