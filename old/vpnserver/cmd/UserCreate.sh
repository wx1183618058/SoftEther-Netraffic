#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserCreate
$1



exit
EOF