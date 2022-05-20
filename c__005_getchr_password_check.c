#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>
#define DEBUG 0
#define debug if (DEBUG) printf

int cliGetString(char * ch, int len)
{
	int i=0;
	if(NULL == ch)
		return 0;

	memset(ch, 0, sizeof(len));

	while((ch[i-1] != '\n') && (i < len))
	{
		ch[i] = getchar();
		debug("Nick_debug ch:%c\n",ch[i]);
		i++;
		//putchar(ch[i++]); //again show terminal or console
	}
	debug("Nick_debug len:%d\n",i);
	ch[i-1] = '\0';
	return (i-1);
}

int main(void)
{
	char cmdBuf[80] = {0};
	memset(cmdBuf, 0, sizeof(cmdBuf));
	printf("Password :");
	cliGetString(cmdBuf, sizeof(cmdBuf));
	if (!strcmp(cmdBuf, "123456abc"))
		printf("password check ok !\n");
	else
		printf("password fail !\n");
	return 0;
}
