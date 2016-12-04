#!/bin/sh
user=$1
sent=$2
recv=$3
onli=$4
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE server SET send = '$sent' WHERE ip='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE server SET recv = '$recv' WHERE ip='$user';"
mysql -hlocalhost -uroot -proot -e "use ov;UPDATE server SET online = '$onli' WHERE ip='$user';"