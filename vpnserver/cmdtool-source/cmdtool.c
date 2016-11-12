#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "cmdtool.h"


void fromSet(){
	char *s1="declare UserList";
	char *s2="declare Policy";
	char *s3="declare Traffic";
	char *s4="declare RecvTraffic";
	char *s5="declare SendTraffic";
	char *s6="declare VirtualLayer3SwitchList";
	FILE *fp1, *fp2, *fp3;
	char ch;
	int i,a=0,n,flag;
	char buff[200];
	fp2=fopen(dir"2","w");
	if((fp1=fopen(dir,"r")) != NULL)
	{
		while((ch=fgetc(fp1))!=EOF ) {
			if(ch!='	' && ch!='{' && ch!='}') {
				fputc(ch,fp2);
			}
		}
	}
	fclose(fp1);
    fclose(fp2);
	fp2=fopen(dir"2","r");
	fp3=fopen(dir"3","w");
	while (fgets(&buff[0],199,fp2) !=NULL) {
		if(a==1) {
			if(strstr(buff,s2)||strstr(buff,s3)||strstr(buff,s4)||strstr(buff,s5)||strstr(buff,s6))
			{
				int len=strlen(buff);
				int x;
				for(x=0; x<len; x++)
					buff[x]=' ';
			}
			n = strlen(buff);
			flag = 0;
			if(n>1) for (i=0;i<n-1;i++)
				if (buff[i] != ' ')
					flag=1;
			if(n!=1 && flag==1)
					fprintf(fp3,"%s",buff);
		}
		if(strstr(buff, s1)!=0) a=1;
}

    fclose(fp2);
	fclose(fp3);
	remove(dir"2");
}

user * usersSet() {
	int m=0;
	char buff[200];
	char *s0="declare ";
	char *s1="uint64 ExpireTime ";
	char *s2="bool Access ";
	char *s3="uint MaxDownload ";
	char *s4="uint MaxUpload ";
	char *s5="uint MultiLogins ";
	char *s6="uint64 BroadcastBytes ";
	char *s7="uint64 UnicastBytes ";
	char *s8="uint64 BroadcastBytes ";
	char *s9="uint64 UnicastBytes ";
	FILE *fp;
	user *a;
	user *c;
	user *b;
	a=(user *)malloc(sizeof(user));
	c=a;
	c->next=NULL;
	fp=fopen(dir"3","r");
	while (fgets(&buff[0],199,fp)!=NULL) {
		if(strstr(buff, s0)==0||m!=0) {
			if(strstr(buff, s1)==0||m!=1) {
				if(strstr(buff, s2)==0||m!=2) {
					if(strstr(buff, s3)==0||m!=3) {
						if(strstr(buff, s4)==0||m!=4) {
							if(strstr(buff, s5)==0||m!=5) {
								if(strstr(buff, s6)==0||m!=6) {
									if(strstr(buff, s7)==0||m!=7) {
										if(strstr(buff, s8)==0||m!=8) {
											if(strstr(buff, s9)==0||m!=9) {
												if(m==10) {
													c->Count=(c->RecvUni+c->RecvBroad+c->SendUni+c->SendBroad)/1024/1024;
													c->Count3=c->RecvUni+c->RecvBroad+c->SendUni+c->SendBroad;
													c->Count2=0;
													c->online=0;
													c->next=(user *)malloc(sizeof(user));
													b=c;
													c=c->next;
													c->next=NULL;
													m=0;
												}
											}else{
												int x=strlen(s9);
                                                c->RecvUni=cton(buff+x);
												m++;
											}
										}else{
											int x=strlen(s8);
                                            c->RecvBroad=cton(buff+x);
											m++;
										}
									}else{
                                        int x=strlen(s7);
                                        c->SendUni=cton(buff+x);
										m++;
									}
								}else{
									int x=strlen(s6);
									c->SendBroad=cton(buff+x);
									m++;
								}
							}else{
								int x=strlen(s5);
								int n=atoi(buff+x);
								c->logins=n;
								m++;
							}
						}else{
							int x=strlen(s4);
							int n=atoi(buff+x);
							c->upload=n;
							m++;
							}
					}else{
						int x=strlen(s3);
						int n=atoi(buff+x);
						c->down=n;
						m++;
					}
				} else {
					int x=strlen(s2);
					int n=strlen(buff);
					buff[n-2]='\0';
					if(strcmp(buff+x, "true")==0) {
						c->access=1;
					}else {
						c->access=0;
					}
					m++;
				}
			} else {
				int x=strlen(s1);
                c->time=cton(buff+x);
				m++;
			}
		} else {
			int x=strlen(s0);
			int n=strlen(buff);
			buff[n-2]='\0';
			strcpy(c->name, buff+x);
			m++;
		}
	}
	free(c);
	b->next=NULL;
	return a;
}

void file(user *u) {
	FILE *fp,*fp2;
	user *x;
	char buf[50];
	x=u;
	fp=fopen(dir2,"w");
	fp2=fopen(dir4,"w");
	while(x!=NULL) {
		//BLG流控
		#ifdef BLG
		sprintf(buf, "./cmd/update.sh %s %ld %ld %d", x->name, x->SendBroad+x->SendUni, x->RecvUni+x->RecvBroad, x->online);
		system(buf);
		#endif
		//JY流控
		#ifdef JY
		fprintf(fp, "用户名:%-11s 总流量:%-7d 使用流量:%-7d 剩余流量:%-7d 到期时间:%-15s;\n", x->name, x->Count2, x->Count, x->Count2-x->Count, times(x));
		fprintf(fp2, "用户名:%-11s 允许登陆:%-7d 使用流量:%-7d 总流量:%-7d 上行速度:%-7d 下行速度:%-7d 多登陆数:%-5d 在线:%-5d 到期时间:%-15s;\n", x->name, x->access, x->Count, x->Count2, x->down/1024, x->upload/1024, x->logins, x->online, times(x));
		#endif
		x=x->next;
	}
	fclose(fp2);
	fclose(fp);
}

uint64_t cton(char *num) {
	int x;
	uint64_t y=0;
	for(x=0; x<strlen(num); x++) {
		if(num[x]>='0'||num[x]>='9') {
			y=y*10+(num[x]-'0');
		}
	} 
	return y;
}

void getCount(user *u) {
	FILE *fp;
	user *x;
	x=u;
	int m=0;
	char buf[20];
	char buff[30];
	fp=fopen(dir3,"r");
	while(x!=NULL) {
		while(fgets(&buff[0],29,fp)!=NULL&&m==0) {
				if(strstr(buff, x->name)!=0) {
					x->Count2=atoi(buff+strlen(x->name));
					m=1;
				}
		}
		x=x->next;
		m=0;
		fseek(fp,0,SEEK_SET);
	}
	fclose(fp);
}

void  monitor(user *u) {
	user *x;
	x=u;
	int m,n;
	char buf[30];
	while(x!=NULL){
		m=x->Count;
		n=x->Count2;
		if(m>n&&x->access==1) {
			sprintf(buf, "./cmd/Access.sh %s %s", x->name, "no");
			system(buf);
			x->access=0;
		}
		if(m<n&&x->access==0) {
			sprintf(buf, "./cmd/Access.sh %s %s", x->name, "yes");
			system(buf);
			x->access=1;
		}
		x=x->next;
	}
}

void freelist(user *u) {
	user *m;
	while(u!=NULL) {
		m=u;
		u=u->next;
		free(m);
	}
}

void oli(user *old, user *new) {
	user *a,*b;
	int x=0;
	a=new;
	while(a!=NULL) {
		b=old;
		if(a->access==1) {
			while(b!=NULL&&x==0) {
				if(strcmp(a->name, b->name)==0) {
					if(b->Count3!=a->Count3) {
						a->online=1;
					}else{
						a->online=0;
					}
					x=1;
				}
				b=b->next;
			}
		}else{
			a->online=0;
		}
		x=0;
		a=a->next;
	}
}

char * times(user *u)
{
	user *x;
	x=u;
    time_t t;
    struct tm *p;
    t=x->time/1000+61200;
    p=gmtime(&t);
    char s[30];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
    return s;
}
