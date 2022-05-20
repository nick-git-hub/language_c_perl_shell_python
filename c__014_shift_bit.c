#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>
#include <stdint.h> //uint64_t

int main(void)
{
printf("\n#### 1 ####\n");
	unsigned int index=0;
	index |= (1 << 0); 
	printf("%x\n",index); //index=1
	index |= (1 << 2); 
	printf("%x\n",index); //index=1|4 =>5
////////////////////////////////////////////////////
printf("\n#### 2 ####\n");
	unsigned int num=0x00ff;
	num &=~(1 << 2 );
	printf("%x\n",num);
///////////////////////////////////////////////////
printf("\n#### 3 ####\n");
	char * tmp;
	uint64_t member=0x0000000000aa11ff; 
	printf("0x%lx\n",member>>8); //-> 2bytes
///////////////////////////////////////////////////
printf("\n#### 4 ####\n");
	uint64_t index_1=0x01010101010101;
	index_1 <<= 8;
	index_1 |= 0x4c;
	//index_1 |= (UINT64_C(0x40) << 56);
	uint8_t sum1=0;
	sum1 = index_1 & 0xff;
	printf("0x%lx\n",index_1);
	printf("0x%lx\n",index_1 >>=8);
	printf("%x\n",sum1);
///////////////////////////////////////////////////
printf("\n#### 5 ####\n");
	unsigned char index_3=0;
	unsigned char value1=0x23;
	unsigned char value2=0x45;
	index_3 = value1;
	index_3 <<= 4; //get value1 =>3
	printf("0x%x\n",index_3);
	index_3 |= (value2 & 0x0f); //get value2 =>5
	printf("0x%x\n",index_3);
///////////////////////////////////////////////////	
printf("\n#### 6 ####\n");
	unsigned int index_4=0x00010000;
	index_4 = index_4 | ( 1 << 4);
	printf("0x%08x\n",index_4);
	index_4 = index_4 | ( 1 << 8);
	printf("0x%08x\n",index_4);
	index_4 = index_4 & ~( 1 << 4); //~(1 << 4)
	printf("0x%08x\n",index_4);    

	return 1;
}

