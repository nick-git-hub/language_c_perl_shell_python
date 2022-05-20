#include <iostream>
#include <string.h>

class Man {
public:
	Man():num(0),count(0)
	{
		memset(fName, 0, sizeof(fName));
		strcpy(fName, "Hi");
	}
	const char *getName(void) const
	{
		return fName;
	}
	void setName(char *name)
	{
		strcpy(fName, name);
	}
	int getNum(int number)
	{
		num=number;
		count++;
		return num;
	}
	int getCount(void) const
	{
		return count;
	}
private:
	char fName[80];
	int num;
	int count;
};

int main(void)
{
	const char *name;
	Man a;

	name = a.getName();

	std::cout << a.getNum(10) << std::endl;	
	std::cout << a.getCount() << std::endl;	
	std::cout << name << std::endl;

	return 0;
}
