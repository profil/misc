// made by profil
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {

	int sock, con, port, c;
	struct sockaddr name;

	char buf;
	port = 6667;
	char serv[255] = "irc.freenode.net";
//	nick = getenv("USER");
	char nick[255] = "test33323";

	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = inet_addr(serv);

	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0) {
		printf("Error: socket\n");
		return -1;
	}
	con = connect(sock, (struct sockaddr *)&name,sizeof(struct sockaddr));
	if(con < 0) {
		printf("Error: connect\n");
		return -1;
	}

	while(read(sock,buf,sizeof(buf))) {
		//läs in 004 = inloggad
		printf("%s\n",buf);
	}
	shutdown(sock,2);
	return 0;
}