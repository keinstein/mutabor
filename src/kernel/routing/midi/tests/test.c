#include <stdio.h>

int main() {
	int time = 0;
	int value = 55;
	for (int i = 0; i < 127 ; i++) {
		printf("%d Param ch=1 con=%d val=%d\n",++time,i,value);
		value += 55;
		value %= 0x80;
		printf("%d Param ch=1 con=%d val=%d\n",++time,i,value);
		value += 55;
		value %= 0x80;
		printf("%d Param ch=1 con=%d val=%d\n",++time,i,0);
		printf("%d Param ch=1 con=%d val=%d\n",++time,i,value);
		value += 55;
		value %= 0x80;
	}
}
