#include <string.h>
#include "cmdtool.h"

uint64_t cton(char *num) {
	int x;
	uint64_t y=0;
	for(x=0; x<strlen(num); x++) {
		if(num[x]>='0'&&num[x]<='9') {
			y=y*10+(num[x]-'0');
		}
	} 
	return y;
}

char * getchars(char *buffer,char *data , char *u, char a) {
	char *tmp;
	int n;
	if((tmp = strstr(data, u)) != 0) {
		tmp=tmp+strlen(u);
		for(n=0; tmp[n] != a; n++) {
			buffer[n] = tmp[n];
		}
		buffer[n]='\0';
		return buffer;
	} else {
		return NULL;
	}
}