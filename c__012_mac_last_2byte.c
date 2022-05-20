#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>

int main(void)
{
unsigned char pkt_mac[6];
unsigned short index;

pkt_mac[0]=0x01;
pkt_mac[1]=0x02;
pkt_mac[2]=0x03;
pkt_mac[3]=0x04;
pkt_mac[4]=0x05;
pkt_mac[5]=0x06;

index = (pkt_mac[4] & 0x03); //mask pkt_mac[4] 2 bit
index <<= 8;
index |= pkt_mac[5];

printf("HEX=> 0x%04x\n",index);
printf("DEC=> %d\n",index);

return 1;
}

