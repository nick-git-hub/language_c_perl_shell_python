#include <stdio.h>
int main()
{
    FILE *out = NULL;
    //create and open the text file
//1.txt###################
	out = fopen("./data/1.txt", "w");
    if(out == NULL)
    {
        printf("Error in creating the file\n");
        return 0;
    }
    //write the structure array in file
	fputs("port-1: Ge1\n",out);
	fputs("Tx High: 0\n",out);
	fputs("Tx Low: 16838\n",out);
	fputs("Rx High: 20\n",out);
	fputs("Rx Low: 21\n",out);
	fputs("Tx Packet: 31\n",out);
	fputs("Rx Packet: 33\n",out);
	fputs("Rx Pause: 0\n",out);
	fputs("Rx Oversize: 5\n",out);
	fputs("Rx Alignment: 00:1c:7b:11:11:11\n",out);
	fputs("Rx FCS: 12\n",out);
	fputs("Rx Drop: 0\n",out);
	fputs("Member: 0x01000f\n",out);
	fputs("Rx Unicast: 0\n",out);
	fputs("Rx Multicast: 0\n",out);
	fputs("Rx Broadcast: 0\n",out);
	fputs("Rx Packet 64: 0\n",out);
	fputs("Rx Packet 1522: 0\n",out);
	fputs("112233,123,456\n",out);
	fputs("123123123\n",out);
    fclose(out);
//2.txt#################
    out = fopen("./data/2.txt", "w");
    if(out == NULL)
    {   
        printf("Error in creating the file\n");
        return 0;
    }   
    //write the structure array in file
    fputs("1=TA-BC02055\n",out);
	fputs("2=aaaaa\n",out);
	fputs("13=cccccc\n",out);
	fputs("1=20.20.250.100\n",out);
	fputs("2=20.20.250.101\n",out);
	fputs("13=20.20.250.102\n",out);
	fputs("1=00:90:9E:9A:9E:35\n",out);
	fputs("2=00:90:9E:9A:9E:36\n",out);
	fputs("13=00:90:9E:9A:9E:37\n",out);
	fclose(out);
//3.txt#################
    out = fopen("./data/3.txt", "w");
    if(out == NULL)
    {   
        printf("Error in creating the file\n");
        return 0;
    }   
    //write the structure array in file
    fputs("prov 20.20.250.25 C8:D3:FF:D2:2B:B1\n",out);
    fputs("TA-BC02055 20.20.250.17 00:90:9E:9A:9E:35\n",out);
    fputs("ccccccc 20.20.250.11 00:1C:7B:11:11:11\n",out);
    fclose(out);

//4.txt#################
    out = fopen("./data/4.txt", "w");
    if(out == NULL)
    {   
        printf("Error in creating the file\n");
        return 0;
    } 
	fputs("CMC>\n",out);
	fputs("nick test\n",out);
	fputs("CMC> 111 qweqweqwe qwe\n",out);
	fputs("nick test\n",out);
	fputs("DDR:33,RFAmp:11,USAmp:44,BCM3218:70,Supply3:66\n",out);

    return 0;
}
