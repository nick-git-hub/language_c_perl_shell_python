#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

bool GetParamFromStream(
	string      &line,
	const string &matchString,
	const char *startString,
	const char *stopString,
	string       &returnString)
{
    bool returnStatus = true;
    //string line;
    //while (getline(inStream, line))
    {
        string::size_type start_pos = line.find(matchString);
		string::size_type end_pos = 0;
        if (start_pos != string::npos)
        {
            start_pos = line.find_first_of(startString, start_pos + matchString.size());
			end_pos = line.find_first_of(stopString, start_pos);
            if (start_pos != string::npos)
            {
                returnString = line.substr(start_pos + 1,(end_pos-start_pos-1));
                returnStatus = false;
                //break;
            }
        }
    }
    return returnStatus;
}

int main()
{
	const char *Data[] = {"DDR", "RFAmp", "USAmp", "BCM3218", "Supply3"};
	ifstream myfile;
	string line;
	int threshold=20;
	myfile.open("./data/4.txt", ios::in);
    	while (getline(myfile, line))
	{
		bool status = true;
		bool threshold_flag= false;
		for(int i=0;i<sizeof(Data)/sizeof(const char *);i++)
		{
			string paramStr[5];
			if (GetParamFromStream(line,Data[i],":",",",paramStr[i])) // file line comple 5 times data[] string
				status = false;

			if(threshold < atoi(paramStr[i].c_str()))
				threshold_flag = true;

			cout<< atoi(paramStr[i].c_str())<<endl; // print Data[] return tempture value
		}
		if(status && threshold_flag)
		{
			cout << "alerm message"<<endl; // alerm threshold 20
		}
	}
	myfile.close();
	return 0;
}
