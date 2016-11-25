#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cmdtool.h"
#include "cmdother.h"

void logs(user *u) {
	user *us;
	us=u;
	while(us!=NULL) {
		printf("%s %ld %ld %d %ld\n", us->name, us->SendBroad+us->SendUni, us->RecvUni+us->RecvBroad, us->online, us->onl->Outgoing);
		us=us->next;
	}
}

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
	fp2=fopen(config"2","w");
	if((fp1=fopen(config,"r")) != NULL)
	{
		while((ch=fgetc(fp1))!=EOF ) {
			if(ch!='	' && ch!='{' && ch!='}') {
				fputc(ch,fp2);
			}
		}
	}
	fclose(fp1);
    fclose(fp2);
	fp2=fopen(config"2","r");
	fp3=fopen(config"3","w");
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
	remove(config"2");
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
	fp=fopen(config"3","r");
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
													c->onl=NULL;
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
	getCount(a);
	onlines(a);
	return a;
}

void file(user *u) {
	user *x;
	char buf[200];
	x=u;
	while(x!=NULL) {
		if(x->onl!=NULL) {
			sprintf(buf, "/vpnserver/cmd/update.sh %s %ld %ld %d %ld %ld %s %s", x->name, x->SendBroad+x->SendUni, x->RecvUni+x->RecvBroad, x->online, x->onl->Outgoing, x->onl->Incoming, x->onl->Mode, x->onl->Session);
			system(buf);
		} else {
			sprintf(buf, "/vpnserver/cmd/update2.sh %s %ld %ld %d %d %d %d %d", x->name, x->SendBroad+x->SendUni, x->RecvUni+x->RecvBroad, x->online, x->upload, x->down, x->logins, x->access);
			system(buf);
		}
		x=x->next;
	}
}



void getCount(user *u) {
	FILE *fp;
	user *x;
	x=u;
	int m=0;
	char buf[20];
	char buff[30];
	fp=fopen(count,"r");
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
	char buf[50];
	while(x!=NULL){
		m=x->Count;
		n=x->Count2;
		if(m>n) {
			if(x->access==1) {
			sprintf(buf, "/vpnserver/cmd/Access.sh %s %s", x->name, "no");
			system(buf);
			x->access=0;
			}
			if(x->online > 0) {
				sprintf(buf, "/vpnserver/cmd/SessionDisconnect.sh %s", x->onl->Session);
				system(buf);
			}
		}
		if(m<n&&x->access==0) {
			sprintf(buf, "/vpnserver/cmd/Access.sh %s %s", x->name, "yes");
			system(buf);
			x->access=1;
		}
		x=x->next;
	}
}

void freelist(user *u) {
	user *m;
	ol *n,*a;
	n=u->onl;
	while(n!=NULL) {
		a=n;
		n=n->next;
		free(a);
	}
	while(u!=NULL) {
		m=u;
		u=u->next;
		free(m);
	}
}

void oli(user *u, ol *o) {
	user *a;
	ol *b;
	char buf[50];
	a=u;
	while(a!=NULL) {
		b=o;
		if(a->online > a->logins && a->logins!=0) {
			while(b!=NULL) {
				if(strcmp(b->name,a->name)==0 && a->online > a->logins) {
					sprintf(buf, "/vpnserver/cmd/SessionDisconnect.sh %s", b->Session);
					system(buf);
					a->online--;
				}
				b=b->next;
			}
		}
		a=a->next;
	}
}

int zero() {
	FILE *fp;
	fp=fopen(count, "r");
	if(getc(fp)==EOF) {
		fclose(fp);
		return 0;
	} else {
		fclose(fp);
		return 1;
	}
}

void onlines(user *u) {
	int m=0;
	char buff[200];
	char *s="SID-";
	char *s2="Client IP Address                         |";
	char *s3="User Name (Authentication)                |";
	char *s4="Outgoing Data Size                        |";
	char *s5="Incoming Data Size                        |";
	char *s6="127.0.0.1";
	char *p;
	user *us;
	ol *a;
	ol *b;
	ol *c;
	FILE *fp;
	a=(ol *)malloc(sizeof(ol));
	b=a;
	b->next=NULL;
	sprintf(buff, "/vpnserver/cmd/SessionList.sh >> "oline);
	system(buff);
	fp=fopen(oline, "r");
	while(fgets(&buff[0],199,fp)!=NULL) {
		if((p=strstr(buff, s))!=0) {
			(p+strlen(p)-1)[0]='\0';
			strcpy(b->Session, p);
			b->next=(ol *)malloc(sizeof(ol));
			c=b;
			b=b->next;
		}
	}
	free(b);
	c->next=NULL;
	fclose(fp);
	remove(oline);	
	c=a;
	while((c=c->next)!=NULL) {
		sprintf(buff, "/vpnserver/cmd/SessionGet.sh %s >> "oline2, c->Session);
		system(buff);
		fp=fopen(oline2, "r");
		m=0;
		while(fgets(&buff[0],199,fp)!=NULL) {
			if(m==0&&(p=strstr(buff, s2))!=0) {
				(p+strlen(p)-1)[0]='\0';
				if(strstr(p, s6)!=0) {
					strcpy(c->Mode, "TCP");
					m++;
				}
				else
				{
					strcpy(c->Mode, "UDP");
					m++;
				}
			}
			if(m==1&&(p=strstr(buff, s3))!=0) {
				(p+strlen(p)-1)[0]='\0';
				strcpy(c->name, p+strlen(s3));
				m++;
			}
			if(m==2&&(p=strstr(buff, s4))!=0) {
				(p+strlen(p)-1)[0]='\0';
				c->Outgoing=cton(p+strlen(s4));
				m++;
			}
			if(m==3&&(p=strstr(buff, s5))!=0) {
				(p+strlen(p)-1)[0]='\0';
				c->Incoming=cton(p+strlen(s5));
				c->Transfer=c->Outgoing+c->Incoming;
				m++;				
			}
		}
		fclose(fp);
		remove(oline2);
	}
	c=a;
	while((c=c->next)!=NULL) {
		us=u;
		m=0;
		while(us!=NULL&&m==0) {
			if(strcmp(c->name, us->name)==0) {
				us->onl=c;
				us->online++;
				m++;
				break;
			}
			us=us->next;
		}
	}
	oli(u,a->next);
}
