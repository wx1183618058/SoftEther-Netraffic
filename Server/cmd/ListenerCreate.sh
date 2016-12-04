#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1


OpenVpnEnable
yes
137,138,1194
exit
EOF