#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
UserPolicySet
$1
MaxUpload
$2
exit
EOF