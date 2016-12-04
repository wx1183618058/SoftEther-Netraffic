#!/bin/sh
cd /vpnserver
if
cat admin | grep "${1} ${2}"
then
	echo 1
else
	echo 0
fi
