#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserPolicySet
$1
MaxDownload
$2
exit
EOF