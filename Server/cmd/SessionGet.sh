#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
SessionGet
$1
exit
EOF