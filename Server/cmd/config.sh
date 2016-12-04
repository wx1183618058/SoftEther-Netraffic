#!/bin/sh
cp -f /vpnserver/vpn_server.config /home/wwwroot/default
cp -f /vpnserver/count /home/wwwroot/default
sed -i "s/uint64 BroadcastBytes .*$/uint64 BroadcastBytes 0/g" /home/wwwroot/default/vpn_server.config
sed -i "s/uint64 BroadcastCount .*$/uint64 BroadcastCount 0/g" /home/wwwroot/default/vpn_server.config
sed -i "s/uint64 UnicastBytes .*$/uint64 UnicastBytes 0/g" /home/wwwroot/default/vpn_server.config
sed -i "s/uint64 UnicastCount .*$/uint64 UnicastCount 0/g" /home/wwwroot/default/vpn_server.config