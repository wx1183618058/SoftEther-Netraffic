#!/bin/sh
user=$1
#user="i"
#mysql -hlocalhost -uroot -pliuhao2012 -e "use ov;SELECT isent FROM openvpn WHERE iuser='$user';">/data/www/addlog.txt
#mysql -hlocalhost -uroot -pliuhao2012 -e "use ov;SELECT irecv FROM openvpn WHERE iuser='$user';">>/data/www/addlog.txt
#recv=$(sed -n 2p addlog.txt)
#sent=$(sed -n 4p addlog.txt)
#echo $recv
#echo $sent
sent=$2
recv=$3
onli=$4
#recv=$[$recv+123]
#sent=$[$sent+123]
#echo $bytes_sent
#echo $bytes_received
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET isent = '$sent' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET irecv = '$recv' WHERE iuser='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE openvpn SET online = '$onli' WHERE iuser='$user';"
#rm -rf /data/www/addlog.txt
