#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<netdb.h>
#include<stdarg.h>
#include<string.h>
  
#define SERVER_PORT 8000
  
int main()
{
	/* 服务端地址 */
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(SERVER_PORT);

	/* 创建socket */
	int client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_socket_fd < 0)
	{
		perror("Create Socket Failed:");
		exit(1);
	}

	char login[800];
	sprintf(login,"{\"head\":{\"srcid\":\"123313\",\"pkgtype\":%d,\"sendtime\":0,\"index\":0},\"playload\":{}",0x7005);

	if(sendto(client_socket_fd, login, strlen(login),0,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("Send File Name Failed:");
		exit(1);
	}
	while(1){
		sprintf(login,"{\"head\":{\"srcid\":\"123313\",\"pkgtype\":%d,\"sendtime\":0,\"index\":0},\"playload\":{}",0x7002);
		if(sendto(client_socket_fd, login, strlen(login),0,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
		{
			perror("Send File Name Failed:");
			exit(1);
		}
		sleep(1);
	}

	close(client_socket_fd);
	return 0;
} 
