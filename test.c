#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	int s, c;
	struct sockaddr_in dest;
	FILE *fp;
	char *mess = "NICK aegc\r\nUSER as 8 * :KandR\r\nJOIN #cout.dev\r\nPRIVMSG #cout.dev :profil\r\nPART #cout.dev\r\nQUIT\r\n";


	if((s = socket(AF_INET, SOCK_STREAM, 0))<0) {
		printf("error: socket\n");
		return 1;
	}

	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("130.239.18.172");
	dest.sin_port = htons(6667);

	if(connect(s, (struct sockaddr *)&dest, sizeof(struct sockaddr))<0) {
		printf("error: connect\n");
		return 1;
	}

	fp = fdopen(s, "r+");
	while(*mess != '\0') {
		putc(*mess, fp);
		mess++;
	}


	while((c=getc(fp))!=EOF) {
		putchar(c);
	}


	close(s);
	return 0;
}

