#!/bin/sh
cd /vpnserver
if
cat user | grep "${1} "
then
	echo 1
else
	echo 0
fi
