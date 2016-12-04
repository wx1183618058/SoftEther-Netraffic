#include <stdint.h>
#define config "/vpnserver/vpn_server.config" //配置文件
#define count "/vpnserver/count"  //用户总流量文件
#define oline "/vpnserver/oline"  //用户在线列表文件
#define oline2 "/vpnserver/oline2"  //用户在线信息文件


#define LOAD "/vpnserver/load/"   //负载信息目录
#define LIST "/vpnserver/load/ClinetList"    //客户端
#define SERVER "/vpnserver/server"   //总信息


//在线信息库
typedef struct o {
	char Session[30];
	char name[20];
	uint64_t Transfer;
	uint64_t Outgoing;
	uint64_t Incoming;
	char Mode[5];
	int n;
	struct o *next;
} ol;

//用户信息库
typedef struct u {
	char name[20];
	uint64_t time;
	int access;
	int down;
	int upload;
	int logins; //用户登录数
	uint64_t SendBroad;
	uint64_t SendUni;
	uint64_t RecvBroad;
	uint64_t RecvUni;
	uint64_t Count3;  //已使用流量
	int Count;   //已使用流量int形式
	int Count2;  //限制流量
	int online;	 //用户在线数量
	
	ol *onl;
	
	struct u *next;
} user;



//输入数据库
void logs(user *);

//格式化配置文件
void fromSet();

//用户导入数据库返回第一个用户地址
user * usersSet();

//更新MySQL
void file(user *);

//給数据库添加流量限制
void getCount(user *);

//监控流量是否超出,超出停止使用
void  monitor(user *);

//释放数据库
void freelist(user *, ol *);

//提出多于用户
void oli(user *,  ol *);

//判断是否有注册用户
int zero();

//线添加在线信息
ol * onlines(user *);

//获取总信息
void getSum(user *);
