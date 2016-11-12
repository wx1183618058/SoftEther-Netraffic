#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cmdtool.h"

int main() {
	user *a,*b;
	daemon(1,1);
	while(1) {
		fromSet();
		a=usersSet();
		getCount(a);
		sleep(10);
		fromSet();
		b=usersSet();
		getCount(b);
		
		monitor(b);
		oli(a, b);
		file(b);
		
		freelist(a);
		freelist(b);
	}
	return 0;
}