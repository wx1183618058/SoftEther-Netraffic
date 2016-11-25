#!/bin/sh
 
while true; do
        #启动一个循环，定时检查进程是否存在
        server=`ps aux | grep cmdtool | grep -v grep`
        if [ ! "$server" ]; then
            #如果不存在就重新启动
            /vpnserver/cmdtool
            #启动后沉睡10s
            sleep 10
        fi
        #每次循环沉睡10s
        sleep 5
done
