#include "client.h"

int srf() {
	FILE *fp1;
	signal(SIGCHLD, SIG_IGN);
	
	if(fp1=fopen(Serverlist, "r") != NULL ) {
	fgets(IP, 19, fp1);
	IP[strlen(IP)-1] = '\0';

	if(fork() == 0) {
		sendf();
		
	} 
	revef();
	}
	return 0;
}

int sendf() {
	int len;
	FILE *fp1;
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SMYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(IP);  ///服务器ip

		int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

		///连接服务器，成功返回0，错误返回-1
		if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0) {
	
			struct timeval timeout={TIME_OUT,0};
			setsockopt(sock_cli,SOL_SOCKET,SO_SNDTIMEO,&timeout,sizeof(timeout));
			
			char sendbuf[BUFFER_SIZE];
			fp1=fopen(client,"rb");
				while((len = fread(sendbuf, 1,BUFFER_SIZE, fp1)) > 0) {
					
					if(send(sock_cli, sendbuf, len,0) < 0) {
						break;
					}
				}
			fclose(fp1);    
			close(sock_cli);
			exit(1);
		} else {  
		
			close(sock_cli);
			exit(0);
		}
	
}

int revef() {
	int len;
	FILE  *fp2;
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(RMYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(IP);  ///服务器ip

		int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
	
		///连接服务器，成功返回0，错误返回-1

		if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0) {
	
			struct timeval timeout={TIME_OUT,0};
			setsockopt(sock_cli,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
			
			char recvbuf[BUFFER_SIZE];
			fp2=fopen(server,"wb");
			while((len = recv(sock_cli, recvbuf, BUFFER_SIZE, 0)) > 0) {
				
				fwrite(recvbuf, len, 1, fp2);
			}  
		
		fclose(fp2);   
		close(sock_cli);
		return 1;		
		} else {  
		
			close(sock_cli);
			return 0;			
		}
	
}