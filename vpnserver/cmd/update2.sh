#!/bin/sh
user=$1
sent=$2
recv=$3
onli=$4
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET isent = '$sent' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET irecv = '$recv' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET online = '$onli' WHERE iuser='$user';"