#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserExpiresSet
$1
$2 $3
exit
EOF