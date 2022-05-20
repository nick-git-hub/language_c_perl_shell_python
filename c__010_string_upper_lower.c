#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char * upper_lower(char *orig)
{
	char *tmp;
	int i =0;
    if ((tmp = (char *) malloc(strlen(orig)+1)) == NULL)
        return (NULL);
	memset(tmp, 0, sizeof(*tmp));
	while (*orig !='\0')
	{
		if(islower(*orig))
			tmp[i] = toupper(*orig);
		else
			tmp[i] = tolower(*orig);
		orig++;
		i++;
	}
	return tmp;
}


int main()
{
    char *t = "SeeING is BeL-IEV.iNG";
    printf("%s\n", t);
    printf("%s\n", upper_lower(t));

    return 0;


}

