#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>

#define TIME_OUT 3
#define RMYPORT  9887
#define SMYPORT  9888
#define QUEUE   20
#define BUFFER_SIZE 1024
#define PID 255
#define LOAD "/vpnserver/load/"  //负载信息目录
#define SERVER "/vpnserver/server"  //负载信息汇总文件
#define LIST "/vpnserver/load/ClinetList"    //客户端

int sendf();
int revef();

int main()
{
	signal(SIGCHLD, SIG_IGN);
	if(fork() == 0) {
		revef();
		
	} 
	if(fork() == 0) {
		sendf();
	}
	return 0;
}

int sendf() {
	 ///定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
	int len,n=1;
	int _pid[PID];
	char buf[20];
	char buff[20];
	pid_t fpid;
	
    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(SMYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1) {
       
	   perror("bind");
       exit(1);
    }

    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1) {
       
	   perror("listen");
       exit(1);
    }

    ///客户端套接字
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
	
	while(1) {
		
		int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
		strcpy(buf, inet_ntoa(client_addr.sin_addr));
		
		signal(SIGCHLD, SIG_IGN);
		
		fpid = fork();
		if(fpid == 0) {
			int n =0;
			FILE *fp1, *fp2;
			char buff[20];
			fp1=fopen(LIST, "r");
			
			while(fgets(buff, 19, fp1) != NULL) {
				buff[strlen(buff)-1] = '\0';
				if(strcmp(buff, buf) == 0) {
					n=1;
					break;
				}
			}
			
			if(n == 0) {
				close(conn);
				close(server_sockfd);
				exit(0);
			}
			
			struct timeval timeout={TIME_OUT,0};
			setsockopt(conn,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));

				fp2=fopen(SERVER,"rb");
				while((len = fread(buffer, 1,BUFFER_SIZE, fp2)) > 0) {
					if(send(conn, buffer, len,0) < 0) {
						break;
					}
				}
				fclose(fp2);
				
				close(conn);
				close(server_sockfd);
				exit(1);
			
		}
		close(conn);
	}
}

int revef() {
	///定义sockfd
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
	int len,n=1;
	int _pid[PID];
	char buf[20];
	char buff[20];
	pid_t fpid;
	
    ///定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(RMYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ///bind，成功返回0，出错返回-1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1) {
        
		perror("bind");
        exit(1);
    }

    ///listen，成功返回0，出错返回-1
    if(listen(server_sockfd,QUEUE) == -1) {
       
	   perror("listen");
       exit(1);
    }

    ///客户端套接字
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
	
	while(1) {
		int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
		strcpy(buf, inet_ntoa(client_addr.sin_addr));
		
		signal(SIGCHLD, SIG_IGN);
		
		fpid = fork();
		if(fpid == 0) {
			int n =0;
			FILE *fp1, *fp2;
			char buff[20];
			fp2=fopen(LIST, "r");
			
			while(fgets(buff, 19, fp2) != NULL) {
				buff[strlen(buff)-1] = '\0';
				if(strcmp(buff, buf) == 0) {
					n=1;
					break;
				}
			}
			
			if(n == 0) {
				close(conn);
				close(server_sockfd);
				exit(0);
			}
			
			struct timeval timeout={TIME_OUT,0};
			setsockopt(conn,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
			
				
				sprintf(buff,LOAD"%s",buf);
				fp1=fopen(buff,"wb");
				memset(buffer,0,sizeof(buffer));
				
				while((len = recv(conn, buffer, BUFFER_SIZE, 0)) > 0) {
					fwrite(buffer, len, 1, fp1);
				}
				fclose(fp1);
				
				close(conn);
				close(server_sockfd);
				exit(1);
			
		}
		close(conn);
	}
}

