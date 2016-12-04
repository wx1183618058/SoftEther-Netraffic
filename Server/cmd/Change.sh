#!/bin/sh
cd /vpnserver
sed -i "s/		uint AutoSaveConfigSpan .*$/		uint AutoSaveConfigSpan 3/g" /vpnserver/vpn_server.config