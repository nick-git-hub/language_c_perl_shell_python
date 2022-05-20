#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <cstring>
using namespace std;
int main(int argc, char **argv)
{
	
	int i,j,k=0,m=0,tp;
	float count_lv1=0.0,count_lv2=0.0,count_lv3=0.0,count_lv4=0.0;
	int count_max2=0,count_max3=0,count_max4=0;
	int count_max2_age=0,count_max3_age=0,count_max4_age=0;
	float count_lv1_age=0.0,count_lv2_age=0.0,count_lv3_age=0.0,count_lv4_age=0.0;
	int mac_size =0;
	int loop_max=0;
	if(argc>=2)
		mac_size = atoi(argv[1]);
	else
		mac_size = 200;
    if(argc>=3)
        k=loop_max=atoi(argv[2]); 
    else
        k=loop_max = 10000;

	srand(time(NULL)+getpid());
#if 1 
	while(k>=1)
	{
#endif
	int mac[mac_size][6]={0};
	unsigned char xltable[4096]={0};

	int tmp1=0,tmp2=0;
	bool collision=false;
	int index_lv1=0,index_lv2=0,index_lv3=0,index_lv4=0;
	//srand(time(NULL)+getpid());
    //printf("\nYour generated MAC address is: \n");

	count_max2=0;
	count_max3=0;
	count_max4=0;
	count_lv1=0.0;
	count_lv2=0.0;
	count_lv3=0.0;
	count_lv4=0.0;
	int check_mac_flag=0;
	for	(j=0; j<mac_size; j++)
	{
		//printf("[%d]",j);
#if 1
		mac[j][0]=0x00;
		mac[j][1]=0x1C;
		mac[j][2]=0x7B;
		for (i=3; i<6 && (tp=rand()%255) > -1; i++)
		{
			mac[j][i]= tp;
			//printf("%s%X%s",tp<16?"0":"",mac[j][i],i<5 ?":": "\n");
		}
		//printf("%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
#else
		for (i=0; i<6 && (tp=rand()%255) > -1; i++) 
		{
			mac[j][i]= tp;
			//printf("%s%X%s",tp<16 ? "0" : "",tp, i<5 ? ":" : "\n");
			//printf("%s%X%s",tp<16?"0":"",mac[j][i],i<5 ?":": "\n");
		}
#endif

		if(check_mac_flag)
		{		
			//printf("fix [%d]%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",j,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
			check_mac_flag=0;
		}

		for (m=0; m<j;m++)
		{
				if(memcmp(&mac[j],&mac[m],6*sizeof(int))==0)
				{
					//printf("mac multi..................%d..%d..\n",j,m);
					//printf("[%d]%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",j,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
					j--;
					check_mac_flag=1;
					break;
				}
				
		}
	}
#if 0
	if(check_mac_flag)
	{
	    for (j=0; j<mac_size; j++)
		{
			printf("%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
		}
	}
#endif

#if 0 //tomu
	for (j=0; j<mac_size; j++)
	{
#if 0
mac[j][0]=0x11;
mac[j][1]=0x12;
mac[j][2]=0x13;
mac[j][3]=0x14;
mac[j][4]=0x15;
mac[j][5]=0x16;
#endif
		index_lv1 = (mac[j][4] & 0x03);
		index_lv1 <<= 8;
		index_lv1 |= mac[j][5];
        //printf("%d\n",index_lv1);

		if(xltable[index_lv1]!=1)
		{
			xltable[index_lv1]=1;
			collision=false;
		}
        else
        {
            count_lv1++;
            collision=true;                                                                                                                                                                                                                   
        }
        if(collision)
        {
            index_lv2 = (index_lv1 & 0x3FF)+2048;
            //printf("%d\n",index);
            if(xltable[index_lv2]!=1)
            {
                xltable[index_lv2]=1;
                collision=false;
                //printf("lv2_index=%d\n",index_lv2);
            }
            else
            {
                count_lv2++;
                collision=true;
            }
            count_max2++;
        }
        if(collision)
        {
            index_lv3 = (index_lv2 & 0x1FF)+3072;
            //printf("%d\n",index);
            if(xltable[index_lv3]!=1)
            {
                xltable[index_lv3]=1;
                collision=false;
                //printf("lv3_index=%d\n",index_lv3);
            }
            else
            {
                count_lv3++;
                collision=true;
            }
            count_max3++;
        }

        if(collision)
        {
            index_lv4 = (index_lv3 & 0x1FF)+3584;
            //printf("%d\n",index);
            if(xltable[index_lv4]!=1)
            {
                xltable[index_lv4]=1;
                collision=false;
                //printf("col_lv4_index=%d\n",index_lv4);
            }
            else
            {
                count_lv4++;
                collision=false;
                //printf("lv4_index=%d\n",index_lv4);
                
            }
            count_max4++;
        }
	}
#endif



#if 1 //gold 

    for (j=0; j<mac_size; j++)
	{
//Lv1 //////////////////////////////////////////////////////////////////////////////
#if 0
mac[j][0]=0x00;
mac[j][1]=0x1c;
mac[j][2]=0x7b;
mac[j][3]=0x14;
mac[j][4]=0x15;
mac[j][5]=0x16;
#endif

		tmp1=0;
		tmp2=0;
		tmp1 = (mac[j][0] & 0xFF);
		tmp1 <<= 8;
		tmp1 |= (mac[j][1] & 0xFF);
		tmp1 <<= 8;
		tmp1 |= mac[j][2] & 0xFF;

        tmp2 = (mac[j][3] & 0xFF);
        tmp2 <<= 8;
        tmp2 |= (mac[j][4] & 0xFF);
        tmp2 <<= 8;
        tmp2 |= mac[j][5] & 0xFF;

		index_lv1 = tmp1 ^ tmp2;

		tmp1=0;
		tmp2=0;
        tmp1 = (index_lv1 & 0xFFF);
		index_lv1 >>= 12;
        tmp2 = (index_lv1 & 0xFFF);



		index_lv1 = tmp1 ^ tmp2;
		//printf("tmp1= %x, tmp2= %x\n",tmp1,tmp2);
		index_lv1 = index_lv1 & 0x7FF;
		//printf("%d\n",index_lv1);
		if(xltable[index_lv1]!=1)
		{
			xltable[index_lv1]=1;
			collision=false;
			//printf("lv1_index=%d, %.2X%.2X%.2X%.2X%.2X%.2X\n",index_lv1,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
		}
		else
		{
			count_lv1++;
			collision=true;
		}
//Lv2 //////////////////////////////////////////////////////////////////////////
		if(collision)
		{
			index_lv2 = (index_lv1 & 0x3FF)+2048;
	        //printf("%d\n",index);
	        if(xltable[index_lv2]!=1)
	        {
	            xltable[index_lv2]=1;
	            collision=false;
				//printf("lv2_index=%d, %.2X%.2X%.2X%.2X%.2X%.2X\n",index_lv2,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
	        }
	        else
	        {
	            count_lv2++;
	            collision=true;
	        }
			count_max2++;
		}

        if(collision)
        {
            index_lv3 = (index_lv2 & 0x1FF)+3072;
            //printf("%d\n",index);
            if(xltable[index_lv3]!=1)
            {
                xltable[index_lv3]=1;
                collision=false;
				//printf("lv3_index=%d\n",index_lv3);
				//printf("lv3_index=%d, %.2X%.2X%.2X%.2X%.2X%.2X\n",index_lv3,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
            }
            else
            {
                count_lv3++;
                collision=true;
            }
			count_max3++;
        }

        if(collision)
        {
            index_lv4 = (index_lv3 & 0x1FF)+3584;
            //printf("%d\n",index);
            if(xltable[index_lv4]!=1)
            {
                xltable[index_lv4]=1;
                collision=false;
				//printf("col_lv4_index=%d\n",index_lv4);
				//printf("lv4_index=%d, %.2X%.2X%.2X%.2X%.2X%.2X\n",index_lv4,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
            }
            else
            {
                count_lv4++;
                collision=false;
				//printf("lv4_index_mul=%d, %.2X%.2X%.2X%.2X%.2X%.2X\n",index_lv4,mac[j][0],mac[j][1],mac[j][2],mac[j][3],mac[j][4],mac[j][5]);
				//printf("lv4_index=%d\n",index_lv4);
				
            }
			count_max4++;
		}
	}
#endif

#if 0
	printf("count_lv1 = %.0f(%.2f%%, count_max=%d)\n",count_lv1,(100*(count_lv1/mac_size)),mac_size);
	printf("count_lv2 = %.0f(%.2f%%, count_max=%d)\n",count_lv2,(100*(count_lv2/count_max2)),count_max2);
	printf("count_lv3 = %.0f(%.2f%%, count_max=%d)\n",count_lv3,(100*(count_lv3/count_max3)),count_max3);
	printf("count_lv4 = %.0f(%.2f%%, count_max=%d)\n",count_lv4,(100*(count_lv4/count_max4)),count_max4);
#endif
#if 1
	count_lv1_age+=count_lv1;
	count_lv2_age+=count_lv2;
	count_lv3_age+=count_lv3;
	count_lv4_age+=count_lv4;
	count_max2_age+=count_max2;
	count_max3_age+=count_max3;
	count_max4_age+=count_max4;

#if 0
	printf("count_lv1_age=%.2f\n",count_lv1_age);
	printf("count_lv2_age=%.2f\n",count_lv2_age);
	printf("count_lv3_age=%.2f\n",count_lv3_age);
	printf("count_lv4_age=%.2f\n",count_lv4_age);
#endif
	k--;
	}
#if 1
    printf("%.2f%%\n",100*(count_lv1_age/(mac_size*loop_max)));
    printf("%.2f%%\n",100*(count_lv2_age/count_max2_age));
    printf("%.2f%%\n",100*(count_lv3_age/count_max3_age));
    printf("%.2f%%\n",100*(count_lv4_age/count_max4_age));
#else
    printf("count_lv1_all_age = %.0f(%.2f%%, %d)\n",count_lv1_age,100*(count_lv1_age/(mac_size*loop_max)),mac_size*loop_max);
    printf("count_lv2_all_age = %.0f(%.2f%%, %d)\n",count_lv2_age,100*(count_lv2_age/count_max2_age),count_max2_age);
    printf("count_lv3_all_age = %.0f(%.2f%%, %d)\n",count_lv3_age,100*(count_lv3_age/count_max3_age),count_max3_age);
    printf("count_lv4_all_age = %.0f(%.2f%%, %d)\n",count_lv4_age,100*(count_lv4_age/count_max4_age),count_max4_age);
#endif

#endif
	return 0;
}
