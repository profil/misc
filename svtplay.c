/*
**	TODO:	* Parse output.
**		* Get url from argument.
**		* Get bitrate from argument.
**
**
** svtplay is a program that lets you extract RTMP URLs from
** SVT Play. You can feed this URL to e.g. rtmpdump and extract
** the video. Note, --subtitle and --bitrate isn't implemented yet.
**
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1000

int getline(char s[], FILE *fp, int lim);
int strindex(char s[], char t[]);

char *pattern = "<param name=\"flashvars\" value=\"";

int main(int argc, char *argv[]) {
	int s;
	struct sockaddr_in dest;
	char line[MAXLINE];
	char *ip = "82.99.28.179";
	char *file = "/t/102959/pa_sparet";

	FILE *fp;

/* TODO
	if(argc < 2) {
		printf("%s [--subtitle] [--bitrate <bitrate>] <url>\n", argv[0]);
		return 1;
	}
*/

	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("error: socket\n");
		return 1;
	}
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(ip);
	dest.sin_port = htons(80);

	if(connect(s, (struct sockaddr *)&dest, sizeof(struct sockaddr)) < 0) {
		printf("error: connect\n");
		return 1;
	}

	fp = fdopen(s, "r+");
	fprintf(fp, "GET %s HTTP/1.1\n\n", file);
	while(getline(line, fp, MAXLINE) > 0) {
		if(strindex(line, pattern) >= 0) {
			printf("%s", line);
		}
	}
	close(s);
	return 0;
}

int getline(char s[], FILE *fp, int lim) {
	int c, i=0;

	while(--lim > 0 && (c=getc(fp)) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strindex(char s[], char t[]) {
	int i, j ,k;

	for(i=0; s[i] != '\0'; i++) {
		for(j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if(k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}
