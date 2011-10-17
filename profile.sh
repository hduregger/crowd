#!/bin/sh

NOW=$(date +"%Y-%m-%d-%H:%M:%S")
DIR_NAME=$(dirname $1)

echo /home/user/Downloads/opencl/AMDAPPProfiler-2.3/x86_64/sprofile -o ./profile-$NOW.csv -w $DIR_NAME $1 $2
/home/user/Downloads/opencl/AMDAPPProfiler-2.3/x86_64/sprofile -o ./profile-$NOW.csv -w $DIR_NAME $1 $2
