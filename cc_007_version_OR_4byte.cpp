#include <iostream>
using namespace std;

int main()
{
unsigned char temp1[2];
unsigned char temp2[2];
int test=0;
temp1[0]=0x0;
temp1[1]=0x0;
temp2[0]=0x01;
temp2[1]=0x02;
test = ((temp1[0]<<12)|(temp2[0]<<8)|(temp1[1]<<4)|temp2[1]);
cout <<test <<endl;
return 1;
}
