#include "vpntool.h"
#include "vpnmt.h"
#include "vpnsql.h"
#include "vpnother.h"
#include <unistd.h>

enum LINES lines;
struct vpn_tool C_Vpntool;
MYSQL * mysql;
char buffer[BUFFER];


int main()
{
    User_Config *user, *b;
	User_Pass *pass;
    Get_INI();
	mysqlconnect();
	daemon(1,1);
	while(1) {
		sleep(C_Vpntool.Cycle);
		
   		user=U_olConfigGet();
		mysql_user(user);
		
		pass=Get_Ass();
		pass=mysql_snyc(pass);
		//logs(user, pass);
    	freelist(user, pass);
	}
	mysql_close(mysql);
   	mysql_library_end();
}
