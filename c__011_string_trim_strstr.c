#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>


int main(void)
{
	char buf[5] = {0};
	char query[80] = {0};
	snprintf(query, sizeof(query),"eth0 eth1 eth2 eth3 wl0 wl1 eth4");

	if (strstr(query,"moca"))
		printf("is string\n");
	else
		printf("not string\n");
	return 0;

}
