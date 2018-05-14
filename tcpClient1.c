#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3456

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[102400];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("Connection error.\n");
		exit(1);
	}
	printf("Client Socket created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("137.207.82.53");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Connection error.\n");
		exit(1);
	}
	printf("Connected to Server.\n");

	while(1){
		printf("Client:  ");
		scanf("%[^\n]%*c", &buffer[0]);
		send(clientSocket, buffer, strlen(buffer), 0);

		if(strcmp(buffer, "quit") == 0){
			close(clientSocket);
			printf("Disconnected from server.\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 102400, 0) < 0){
			printf("Error in receiving data.\n");
		}else{
			printf("Server:  %s\n", buffer);
			bzero(buffer, sizeof(buffer));
		}
	}

	return 0;
}
