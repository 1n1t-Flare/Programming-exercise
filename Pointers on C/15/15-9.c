#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINESIZE 512

/*fgrep
 *option: string [filename ...]  
 */

enum Mode{From_stdin,From_file};
int search_file(char *string, char *filename)
{
    char buffer[MAX_LINESIZE], *result;
    FILE *fl = fopen(filename,"r+");
    if(fl==NULL)
        return EXIT_FAILURE;

    while(!feof(fl))
    {
        fgets(buffer,MAX_LINESIZE,fl);
        result = strstr(buffer,string);
        if(result!=NULL)
            printf("%s: %s",filename,buffer);
    }
    fclose(fl);
    return EXIT_SUCCESS;
}

int search_stdin(char *string)
{
    char buffer[MAX_LINESIZE], *result;
    while(fgets(buffer,MAX_LINESIZE,stdin)!=NULL)
    {
        result = strstr(buffer,string);
        if(result!=NULL)
            printf("%s",buffer);
    }
    return EXIT_SUCCESS;
}



int main(int argc, char **argv)
{   
    int mode = argc>=3? From_file : From_stdin;
    char *string = *(++argv), *file;
    switch (mode)
    {
    case From_stdin:
        search_stdin(string);
        break;

    case From_file:
        while((file = *(++argv)) !=NULL)
        {
            search_file(string,file);
        }
        break;
    }
    return 0;
}