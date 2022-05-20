#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>


int main(void)
{
	FILE *f;
	char buf[80] = {0};
	char str_buf[80] = {0};
	unsigned int rx_counter1 = 0;
	unsigned int rx_counter2 = 0;
	f = popen("cat ./data/1.txt | grep -E \"Oversize|Alignment|FCS\"", "r");

	memset(buf, 0, sizeof(buf));
	fgets(buf, sizeof(buf), f);
	sscanf(buf,"Rx Oversize: %d", &rx_counter1);

	memset(buf, 0, sizeof(buf));
	fgets(buf, sizeof(buf), f);
	sscanf(buf,"Rx Alignment: %s", str_buf);

    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), f); 
    sscanf(buf,"Rx FCS: %u", &rx_counter2);

	printf("RX Oversize :%d\n",rx_counter1);
	printf("RX Alignment :%s\n",str_buf);
	printf("Rx FCS :%u\n",rx_counter2);
	pclose(f);

/////////////////////////////////////////////////////////////////
    char data[5] = {0};
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "grep -c port-1 ./data/1.txt");
    f = popen(buf, "r");
    fread(data, 1, sizeof(data), f); 
    pclose(f);

    printf("=>%s\n",data); //cmd -c have enter char
    printf("=>%d\n",(strstr(buf,"1")!=NULL));
    printf("=>%d\n",strstr("123123333qweqwe","pktc")!=NULL);

	return 0;
}
