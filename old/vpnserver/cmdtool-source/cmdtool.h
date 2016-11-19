#include <stdint.h>
#define dir "/vpnserver/vpn_server.config" //配置文件
#define dir2 "/vpnserver/config" //最终配置文件
#define dir3 "/vpnserver/count"  //用户总流量文件
#define dir4 "/home/wwwroot/default/console/config" //JY流控web显示用户信息文件
#define BLG
//#define JY


typedef struct u {
	char name[20];
	uint64_t time;
	int access;
	int down;
	int upload;
	int logins;
	uint64_t SendBroad;
	uint64_t SendUni;
	uint64_t RecvBroad;
	uint64_t RecvUni;
	uint64_t Count3;
	int Count;
	int Count2;
	int online;
	struct u *next;
} user;

//导出最终配置文件
void file(user *);

//监控流量是否超出,超出停止使用
void  monitor(user *);

//释放数据库
void freelist(user *);

//判断是否在线
void oli(user *old, user *new);

//格式化配置文件
void fromSet();

//用户导入数据库返回第一个用户地址
user * usersSet();

//給数据库添加流量限制
void getCount(user *);

//将字符串转化为uint64_t整数
uint64_t cton(char *);

//格式化时间
char * times(user *);