#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>


int main(void)
{
	int q=0;
	char cmd[256] = {0};
    for (q=1;q<20;q++) {
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd,"cat ./data/2.txt |grep '%d=' |cut -f2 -d '='|awk 'ORS=NR%%3?\" \":\"\\n\"{print}'\n",q);
		system(cmd);
	}
	return 0;


}
