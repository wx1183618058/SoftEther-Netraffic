#!/bin/sh
user=$1
sent=$2
recv=$3
onli=$4
upload=$5
down=$6
logins=$7
access=$8
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET isent = '$sent' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET irecv = '$recv' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET online = '$onli' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET upload = '$upload' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET down = '$down' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET logins = '$logins' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET i = '$access' WHERE iuser='$user';"