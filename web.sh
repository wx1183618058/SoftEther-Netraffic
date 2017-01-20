#!/bin/sh
WEB="http://ok2jeq74z.bkt.clouddn.com/"
web_path="/home/wwwroot/default/"
port=80
clear

#↓↓↓↓↓↓↓↓↓↓公告↓↓↓↓↓↓↓↓↓↓#
echo -e "================================================================="
echo -e "                                                                 "        
echo -e "       SoftEtherVPN+blg流控+云端app+自动配置模式+SSR一键         " 
echo -e "                                                                 " 
echo -e "  	 监控为本人编写,流控基于blg二次开发.云app修改的叮咚流量卫士   " 
echo -e "  感谢以上源码的提供者,和制作者。                                " 
echo -e "    因为是开源产物,所以本人并不提供任何商业代码。去除了所有的代  " 
echo -e "  理功能,卡密功能。											  "
echo -e "                                                                 "
echo -e "          请接着看,因为20s后才会执行下一步，谢谢！！             "  
echo -e "                                                                 "      
echo -e "    本源码理论支持所有安装了SoftEtherVPN的机器,但没这个条件测试  "
echo -e " 			   本人欢迎大家对我的源码进行二次开发                 " 
echo -e "  开源地址:https://github.com/wx1183618058/SoftEther-Netraffic/  " 
echo -e "                                                                 "
echo -e "    最后在啰嗦一句本人只是源码的搬运工。任何版权问题与本人无关   " 
echo -e "              								                      "
echo -e "        作者不易；如果觉得本流控还不错欢迎大家支持               "
echo -e "              支付宝：weixiao1996722@qq.com                      "
echo -e "        感谢捐赠名单:http://bxu2359140757.my3w.com/              "
echo -e "================================================================="
sleep 7
clear

echo -e "================================================================="
echo -e "                                                                 "        
echo -e "                  感谢一下网友支持捐赠                           " 
echo -e "                                                                 " 
echo -e "  	       弐柒丶/ 利世 / 不准、不开心 / qq:1290596954            " 
echo -e "          Traveler / 网易op / 胶己人-搞事君 / 包包/kel           " 
echo -e "                                                                 " 
echo -e "                   特别鸣谢:  ﹎..低凋℡                         " 
echo -e "                                                                 " 
echo -e "                   稍等自动跳转下一步                            "
echo -e "================================================================="
sleep 7
clear
#↑↑↑↑↑↑↑↑↑↑公告↑↑↑↑↑↑↑↑↑↑#

#↓↓↓↓↓↓↓↓↓↓SEVPN选择系统↓↓↓↓↓↓↓↓↓↓#
echo "
---------------------------------------------------------
请选择您安装的系统，输入相应的序号后回车
---------------------------------------------------------

---------------------------------------------------------

【1】网易极速5分钟 (仅限使用我的镜像否则选择其他)

【2】其他

---------------------------------------------------------
"
read os
clear
#↑↑↑↑↑↑↑↑↑↑选择系统↑↑↑↑↑↑↑↑↑↑#

#↓↓↓↓↓↓↓↓↓↓安装SEVPN↓↓↓↓↓↓↓↓↓↓#
while [ "$domain" =  "" ]  
do
   domain=$(wget -qO- -t1 -T2 ipv4.icanhazip.com)
done

echo -e "您的IP是:$domain"
echo -e "输入您的APP名称（默认：叮咚流量卫士）"
read app_name
if test -z $app_name;then
echo -e "已经默认为叮咚流量卫士"
app_name="叮咚流量卫士"
fi
clear

echo "开始整理安装环境..."
yum -y update
yum -y install openssl gcc make cmake vim tar java
	
wget ${WEB}lnmp.zip
if [ $os == 2 ];then
wget ${WEB}phpmyadmin.zip
echo "开始安装lnmp"
unzip -o lnmp.zip
unzip -o phpmyadmin.zip
chmod -R 777 /lnmp
cd /lnmp
./install.sh
mysqladmin -u root password "root"
cd /
mv /phpmyadmin /home/wwwroot/default/phpmyadmin
else
lnmp restart
fi


echo "开始安装SEVPN"
cd /
wget ${WEB}vpnserver.zip
wget ${WEB}vpntool.zip
unzip -o vpnserver.zip
chmod -R 777 /vpnserver
cd /vpnserver
make i_read_and_agree_the_license_agreement
cd /
sleep 1
unzip -o vpntool.zip
chmod -R 777 /vpnserver

echo "开始安装web"
cd /
wget ${WEB}default.zip
unzip -o default.zip
mv default/* /home/wwwroot/default
rm -rf default
cd /vpnserver
rm /home/wwwroot/default/index.html

if [ $os == 1 ];then
mv -f php.ini /usr/local/php/etc/
cd /usr/local/php/etc/
else
mv -f php.ini /etc/
cd /etc/
fi
chmod 644 php.ini

echo "开始安装云app"
echo -e "流控目录为：$web_path"
clear
echo -e "开始进行数据库导入"
db_host="localhost"
db_port=3306
db_user="root"
db_pass="root"
db_ov="ov"
echo -e "地址：$db_host"
echo -e "端口：$db_port"
echo -e "用户：$db_user"
echo -e "密码：$db_pass"
echo -e "库名：$db_ov"
echo -e "开始创建数据库"
mysql -h$db_host -P$db_port -u$db_user -p$db_pass -e "create database ${db_ov}"
echo -e "开始导入数据库"
mysql -h$db_host -P$db_port -u$db_user -p$db_pass $db_ov < ${web_path}ov.sql
#sed -i 's/192.168.1.1/'${domain}'/g' "/home/wwwroot/default/line.sql"
#mysql -h$db_host -P$db_port -u$db_user -p$db_pass $db_ov < ${web_path}line.sql
echo -e "数据库导入完成"
sed -i 's/192.168.1.1:8888/'${domain}:${port}'/g' "/vpnserver/vpnconfig/disconnect.sh"
clear
echo -e  "开始制作APP"
echo -e "正在加载基础环境(较慢 耐心等待)...."
cd /home
wget ${WEB}android.apk
wget ${WEB}apktool.jar
wget ${WEB}autosign.zip
chmod 0777 -R /home

cd /home
echo -e "清理旧的目录"
rm -rf android
echo -e "分析APK"
java -jar apktool.jar d android.apk
echo -e "批量替换"
chmod 0777 -R /home/android
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' /home/android/smali/net/openvpn/openvpn/base.smali >/dev/null 2>&1
			sed -i 's/APP_KEY_CODE/'${app_key}'/g' /home/android/smali/net/openvpn/openvpn/base.smali >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' "/home/android/smali/net/openvpn/openvpn/OpenVPNClient.smali" >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' "/home/android/smali/net/openvpn/openvpn/OpenVPNClient\$10.smali" >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' "/home/android/smali/net/openvpn/openvpn/OpenVPNClient\$11.smali" >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' "/home/android/smali/net/openvpn/openvpn/OpenVPNClient\$13.smali" >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' "/home/android/smali/net/openvpn/openvpn/Main2Activity\$MyListener\$1.smali" >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' '/home/android/smali/net/openvpn/openvpn/Main2Activity$MyListener.smali' >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' '/home/android/smali/net/openvpn/openvpn/MainActivity.smali' >/dev/null 2>&1
			sed -i 's/demo.dingd.cn:80/'${domain}:${port}'/g' '/home/android/smali/net/openvpn/openvpn/update$myClick$1.smali' >/dev/null 2>&1
			sed -i 's/叮咚流量卫士/'${app_name}'/g' "/home/android/res/values/strings.xml" >/dev/null 2>&1
echo -e "打包"
java -jar apktool.jar b android
if test -f /home/android/dist/android.apk;then 
	echo -e "APK生成完毕"
	unzip -o autosign.zip 
	cd autosign 
	echo "签名APK...."
	cp -rf /home/android/dist/android.apk /home/unsign.apk
	java -jar signapk.jar testkey.x509.pem testkey.pk8 /home/unsign.apk /home/sign.apk 
	cp -rf /home/sign.apk  ${web_path}dingd.apk
	rm -rf /home/sign.apk
	rm -rf /home/unsign.apk
	rm -rf /home/android.apk
	rm -rf /home/android
	rm -rf /home/autosign.zip
	rm -rf /home/autosign
	rm -rf /home/apktool.jar
	rm -rf /default.zip
	rm -rf /vpnserver.zip
	rm -rf /vpntool.zip
	chmod 777 ${web_path}dingd.apk
	chmod -R 755 ${web_path}phpmyadmin
	
	echo "添加服务命令和自启"
	if [ $os == 1 ];then
	mv /vpnserver/vpnw /bin/vpn
	rm -rf /vpnserver/vpnq
	#sleep 1
	#echo "/usr/bin/vpn start" >> /etc/rc.d/rc.local
	else
	mv /vpnserver/vpnq /bin/vpn
	rm -rf /vpnserver/vpnw
	#sleep 1
	#echo "/usr/bin/vpn start" >> /etc/start
	rm -rf /lnmp.zip
	rm -rf /phpmyadmin.zip
	fi
	cd /bin
	chmod 777 vpn
	vpn restart
else
	echo "
	---------------------------------------------------------
	ERROR----------- APP制作出错 请手动对接
	---------------------------------------------------------
	"
	exit 0
fi

echo "
---------------------------------------------------------
		复活成功！！
					
后台管理系统： http://${domain}:${port}/admin
APP地址：   http://${domain}:${port}/dingd.apk 

		后台账号：admin
		后台密码：admin
	  服务启动命令：vpn
	  
已经开通137,138(TCP和UDP)端口和8080端口
	后台已经自动生成模式
	
作者不易；如果觉得本流控还不错欢迎大家支持               
   支付宝：weixiao1996722@qq.com            

 感谢捐赠名单:http://bxu2359140757.my3w.com/            
---------------------------------------------------------
"
exit 0
#↑↑↑↑↑↑↑↑↑↑安装SEVPN↑↑↑↑↑↑↑↑↑↑#