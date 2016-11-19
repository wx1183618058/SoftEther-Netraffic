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