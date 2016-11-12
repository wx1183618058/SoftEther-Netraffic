#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserPolicySet
$1
MultiLogins
$2
exit
EOF