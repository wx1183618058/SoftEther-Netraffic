#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserPasswordSet
$1
$2
$2
exit
EOF