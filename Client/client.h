#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>

#define SMYPORT  9887
#define RMYPORT  9888
#define BUFFER_SIZE 1024
#define TIME_OUT 3
#define client "/vpnserver/client"
#define server "/vpnserver/server"  //负载信息汇总文件
#define serverlist "/vpnserver/Serverlist"
char IP[20]

int srf();
int sendf();
int revef();
