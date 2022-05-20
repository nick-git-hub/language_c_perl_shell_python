#include <stdio.h>
#include <string.h>                               
#include <stdlib.h>


int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char buffer[3][128];

    fp = fopen("./data/3.txt", "r");
    if (fp == NULL)
		return 0;
    while ((read = getline(&line, &len, fp)) != -1) {
		sscanf(line,"%s %s %s", buffer[0],buffer[1],buffer[2]);
		printf("[%s],[%s],[%s]\n", buffer[0],buffer[1],buffer[2]);
    }
    fclose(fp);
    if (line)
        free(line);

	return 0;


}
