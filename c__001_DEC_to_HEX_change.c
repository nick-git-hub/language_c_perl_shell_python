#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>
#define DEBUG 0
#define debug if (DEBUG) printf

int main(void)
{
	long long int p=0;
	int m=0,n=0,a=0, plen=0;
	char ch[100];
	char len[100];

	printf("[Change DEC to HEX (MAX 18 number)]\n");
	printf("Enter 10 byte :");
	scanf("%lld",&p);
	sprintf(len,"%lld",p);
	plen = strlen(len);
	printf("DEC Input Length : %d\n",plen);
	if(plen > 18)
	{
		printf("Error input MAX 19 number\n");
		return 0;
	}

	for(m=0;p>0;m++)
	{
		debug("Nick_Debug :Input number %lld\n",p);
		a=p%16;
		debug("Nick_Debug :Change HEX %d\n",a);
		if(a<10)
			ch[m]=a+'0';
		else
			ch[m]=a-10+'A';
		p=p/16;
	}

	printf("HEX output length : %d\n",m);

	for(n=m-1;n>=0;n--)
	{
		printf("%c",ch[n]);
	}
	printf("\n");
	return 0;
}
