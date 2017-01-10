# SoftEther-Netraffic
**本软件**是一款SoftEther的第三方流量监控 

- 使用本软件适用于使用SoftEther的服务器。

- 核心是C语言编写

###使用方法

 1. 在根目录下安装 SoftEther
 
 2. 先将vpntool在服务器上编译在vpntool.h中改好对应目录 ,编译代码如下,部分需要修改
```
gcc -g vpntool.c vpncmd.c vpnother.c vpnsql.c vpnmt.c -L/usr/local/mysql/lib -lmysqlclient
```
3.把编译好的文件和vpnconfig文件夹,vpntool.ini复制到SoftEther目录中，在创建user_pass.config文件
4.在修改vpntool.ini中的配置，监控时间推荐5s，如果两台服务器就10s以此类推
5.安装对应流控，运行即可

###负载功能
> 服务器安装好后，运行在前端能看见，服务器ip对接成功