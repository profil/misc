/*
**	TODO:
**		* Parse output.
**		* Read 512 bytes, split up on "\r\n" and put into the queue
**
**		* Get url from argument.
**		* Get bitrate from argument.
**
**
** PROOF-OF-CONCEPT
**
** svtplay is a program that lets you extract RTMP URLs from
** SVT Play. You can feed this URL to e.g. rtmpdump and extract
** the video. Note, --subtitle and --bitrate isn't implemented yet.
**
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 255
#define IPADDR "82.99.28.179"

int printurl(char string[], char pattern[], char stop);

char *pattern = "rtmp://";

int main(int argc, char *argv[]) {
	int s;
	struct sockaddr_in dest;
	char line[MAXLINE];

	char *file = "/t/102959/pa_sparet";
	char *start = "GET ";
	char *stop = " HTTP/1.1\nConnection: close\n\n";

/* TODO
	if(argc < 2) {
		printf("%s [--subtitle] [--bitrate <bitrate>] <url>\n",argv[0]);
		return 1;
	}
*/

	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("error: socket\n");
		return 1;
	}
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(IPADDR);
	dest.sin_port = htons(80);

	if(connect(s, (struct sockaddr *)&dest, sizeof(struct sockaddr)) < 0) {
		printf("error: connect\n");
		return 1;
	}

	send(s, start, strlen(start),0);
	send(s, file, strlen(file),0);
	send(s, stop, strlen(stop),0);

	while(read(s, line, MAXLINE) > 0) {
		if(printurl(line, pattern, ',') > 0) {
			putchar('\n');
		}
	}

	close(s);
	return 0;
}

int printurl(char c[], char t[], char s) {
	char *i;
	if((i=strstr(c, t)) !=NULL) {
		for(;*i!=s && *i != '\0';i++) {
			putchar(*i);
		}
	return 1;
	}
	else {
		return 0;
	}
}
