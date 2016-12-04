#!/bin/sh
cd /vpnserver
./vpncmd <<EOF
1


ServerPasswordSet
SoftEtherVPN
SoftEtherVPN
exit
EOF