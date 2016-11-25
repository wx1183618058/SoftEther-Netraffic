#!/bin/sh
user=$1
sent=$2
recv=$3
onli=$4
osent=$5
orecv=$6
mode=$7
sid=$8
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET isent = '$sent' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET irecv = '$recv' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET online = '$onli' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET osent = '$osent' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET orecv = '$orecv' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET mode = '$mode' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET sid = '$sid' WHERE iuser='$user';"
curl "http://192.168.1.1:8888/app_api/top_api.php?name=$user&s=$sent&r=$recv&version=1"