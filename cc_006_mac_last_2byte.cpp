#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> //type uint32 uint64
using namespace std;


int main()
{
	uint32_t mac;
	uint8_t u1, u2, u3, u4, u5, u6;  

		u5=0xab;
		u6=0xcd;
		mac= u5 << 8 & 0x0000ff00|
			u6  & 0x000000ff;
	printf("MAC last 2bytes :%X\n",mac);
	return 0;
}
