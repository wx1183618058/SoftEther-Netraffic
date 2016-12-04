#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1

DEFAULT
SecureNatEnable
exit
EOF