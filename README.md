# SoftEther-Netraffic
**本软件**是一款SoftEther的第三方流量监控 
- 使用本软件适用于使用SoftEther的服务器。
- 核心是C语言编写其他SHELL脚本测试环境网易centos6.7(理论上其他通用)
- old为旧版流控支持旧版BLG和JY WEB端
- 新版只支持新BLG WEB

###使用方法
> 先将cmdtool在服务器上编译，在再根目录下安装 SoftEther然后把对应文件复制进/vpnserver，接着运行cmdtool即可。

###添加负载功能
> Server下的是主服务器 Clinet是成员服务器，编译好后对应放入即可
> /Client/Serverlist 是主服务器IP列表，clinet连接时需要
> /Server/load/ClinetList 是成员服务器IP列表，server判断是否规定ip
> WEB端需要用负载专用版
