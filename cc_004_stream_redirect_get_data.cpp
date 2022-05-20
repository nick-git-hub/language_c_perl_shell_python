#include "cstdio"
#include "iostream"
#include "fstream"
#include "string"
#include <limits>
using namespace std;

void f()
{
    std::string line;
	//int count =5;
    while(std::getline(std::cin, line))  //input from the file in.txt
    {
		//std::cin.ignore();
		//std::getline(std::cin,line);
        	std::cout << line<< "\n";   //output to the file out.txti
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//count--;
		//if(count<1)
		break;
    }
}

int main()
{
	std::ofstream outbuf("./data/4.txt",std::ios_base::out | std::ios_base::app);
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(outbuf.rdbuf()); //redirect std::cout to out.txt!

	//std::string word;
	std::cout  << "hello stream  ";  //output to the file out.txt
	f(); //call function

	std::cout.rdbuf(coutbuf); //reset to standard output again
	std::cout.clear();
	std::cin.clear();
	std::cout <<"hhihihi";
	//std::cout << word;  //output to the standard input
	return 0;
}
