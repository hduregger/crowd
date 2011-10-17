#!/bin/sh

NOW=$(date +"%Y-%m-%d-%H:%M:%S")
DIR_NAME=$(dirname $1)

echo /home/user/opencl/AMDAPPProfiler-2.3/x86_64/sprofile -o ./trace-$NOW.atp -t -w $DIR_NAME $1
/home/user/opencl/AMDAPPProfiler-2.3/x86_64/sprofile -o ./trace-$NOW.atp -t -w $DIR_NAME $1
