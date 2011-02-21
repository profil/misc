/*
**	Nothing serious yet.
*/

#include <stdio.h>

#define MAXLINE 1000

int getline(char s[], int lim);
int getop();
int run;
int main(int argc, char *argv[]) {
/*
** if first char is 'i', start insert mode eg. use getline.
** if first char is 'q', quit the program gracefully.
*/
	run = 1;

	while(run && getop()) {
	;
	}
	return 0;
}



int getline(char s[], int lim) {
	int c, i;

	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
		s[i] = c;
	}
	if(c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

int getop() {
	int c;

	c=getchar();
	switch(c) {
		case 'i':
			printf("insert mode!\n");
			break;
		case 'w':
			printf("write!\n");
			break;
		case 'q':
			printf("quit!\n");
			run = 0;
			break;
		default:
			printf("error.\n");
			break;
	}
	return 1;
}
