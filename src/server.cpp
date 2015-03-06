//============================================================================
// Name        : server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 1234

#define BACKLOG 1

int main() {
	int listenfd, connectfd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t addrlen;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error.");
		return 1;
	}

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int opt = SO_REUSEADDR;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("setsockopt() error ");
		return 1;
	}
//	int opt1 = SO_REUSEPORT;
//	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt1, sizeof(opt1)) == -1)
//	{
//		perror("setsockopt() error ");
//		return 1;
//	}
	if (bind(listenfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		cout << server.sin_addr.s_addr << endl;
		perror("bind() error");
		return 1;
	}
	addrlen = sizeof(server);
	int a = getsockname(listenfd, (struct sockaddr *) &server, &addrlen);
	cout << a << endl;

	cout << "bind finish" << endl;
	if (listen(listenfd, BACKLOG) == -1) {
		perror("listen() error");
		return 1;
	}
	cout << "listen finish" << endl;
	addrlen = sizeof(client);

	if ((connectfd = accept(listenfd, (struct sockaddr *) &client, &addrlen))
			== -1) {
		perror("accept() error");
		return 1;
	}
	cout << "accept finish" << endl;
	printf("Client's ip is %s,port is %d\n", inet_ntoa(client.sin_addr),
			htons(client.sin_port));

	send(connectfd, "WELCOME!\n",9, 0);

	close(connectfd);
	close(listenfd);
	return 0;
}
