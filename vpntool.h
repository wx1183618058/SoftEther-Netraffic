#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "/usr/local/mysql/include/mysql.h"


#define VPN_INI "/home/weixiao/桌面/vpn/vpntool.ini"
#define Vpncmd_path "/home/weixiao/桌面/vpnserver/"
#define Save "/home/weixiao/桌面/vpnserver/vpnconfig/"
#define SessionGet_path "/home/weixiao/桌面/vpnserver/vpnconfig/SessionGet.config"
#define UserGet_path "/home/weixiao/桌面/vpnserver/vpnconfig/UserGet.config"
#define SessionList_path "/home/weixiao/桌面/vpnserver/vpnconfig/SessionList.config"
#define v_s_path2 "/home/weixiao/桌面/vpnserver/vpnconfig/vpn_server.config"
#define v_s_path1 "/home/weixiao/桌面/vpnserver/vpn_server.config"
#define Pass_path "/home/weixiao/桌面/vpnserver/user_pass.config"
#define LINE 15
#define C 9

#define PLINE 44
#define PC1 15
#define PC2 72

#define BUFFER 500


#ifndef JIEGOU
#define JIEGOU
struct vpn_tool
{

    //IP
    char Ip[15];

    //time
    int Cycle;

    //mysql
    char Mshost[15];
    int Msport;
    char Msuser[20];
    char Mspass[20];
    char Msdb[10];

    //softether
    char Sfhub[10];
    char Sfpass[20];
};

typedef struct _User_Config
{
    char name[20];
    char mode[4];
    char Session[40];
    uint64_t outgoing;
    uint64_t incoming;
    uint64_t Ooutgoing;
    uint64_t Oincoming;
    int up;
    int down;
    int logins;
    struct _User_Config *next;
} User_Config;

typedef struct _User_Pass
{
    char name[20];
    char pass[20];
    int access;
    struct _User_Pass *front;
    struct _User_Pass *next;
} User_Pass;

enum LINES { MODE = 15, NAME = 17, OOUT = 40, OIN = 41, OUT = 24, OBT = 26, IUT = 28, IBT = 30, UP =
                 53, DOWN = 54, LOGINS = 56
           };

#endif

extern struct vpn_tool C_Vpntool;
extern MYSQL * mysql;
extern char buffer[BUFFER];
extern enum LINES lines;
