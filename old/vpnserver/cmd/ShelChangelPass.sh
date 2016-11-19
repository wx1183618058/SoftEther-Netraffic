#!/bin/sh
cd /vpnserver
sed -i "s/^${1} .*$/${1} ${2}/g" /vpnserver/user
