#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cmdtool.h"

int main() {
	user *a,*b;
	daemon(1,1);
	while(1) {
		if(zero()) {
			sleep(3);
			//构建用户数据
			fromSet();
			b=usersSet();
			
			//检查流量超出,在线,更新
			monitor(b);
			file(b);
			
			//释放数据
			freelist(b);
		}else{
			sleep(5);
		}
	}
	return 0;
}