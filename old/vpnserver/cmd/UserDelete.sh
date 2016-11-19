#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserDelete
$1
exit
EOF