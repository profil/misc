/*
** To compile:
**	winegcc sptfy_hotkey.c -o sptfy_hotkey.exe
*/

#include <stdio.h>
#include <windows.h> /* AM I MENTAL?! */

#define TOGGLE 917504
#define NEXT 720896
#define PREV 786432


int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Usage: sptfy_hotkey  [toggle|next|prev]\n");
		return 1;
	}
	else {
		HWND wh = FindWindow("SpotifyMainWindow", NULL);
		if(wh == NULL) {
			printf("error: is spotify running?\n");
			return 1;
		}
		else {
			char c;
			c = argv[1][0];
			switch(c) {
				case 't':
					SendMessage(wh, 0x0319, 0, TOGGLE);
					break;
				case 'n':
					SendMessage(wh, 0x0319, 0, NEXT);
					break;
				case 'p':
					SendMessage(wh, 0x0319, 0, PREV);
					break;
				default:
					printf("error: unkown argument\n");
					break;
			}
		}
	}
	return 0;
}