#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
SessionDisconnect
$1
exit
EOF