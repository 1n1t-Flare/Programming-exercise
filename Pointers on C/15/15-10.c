#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
 *calculate the checksum of a set of files
 *options: [-f] [filename...]
 */


//char file_output = 0;
//定义全局变量来记录命令行参数。避免直接在主函数分析复杂参数。

unsigned int checksum(FILE *stream)
{
    int ch = 0;
    unsigned int sum = 0;
    while((ch = getc(stream))!=EOF)
    {
        sum += (unsigned int)ch;
    }
    return sum;
}


int main(int argc, char** argv)
{
    unsigned int result = 0, outputTofile = 0;
    if(*++argv == NULL)
    {
        result = checksum(stdin);
        printf("%u\n",result);
        return EXIT_SUCCESS;
    }
    else if (!strcmp(*argv,"-f"))
    {
        outputTofile = 1;
        if(*++argv == NULL) 
        {
            printf("-f illegal when reading standard inupt");
            return EXIT_FAILURE;
            /*
            fprintf( stderr, "-f illegal with standard input\n" ); 
            exit (EXIT_FAILURE);
            */
        }
    }

    while(*argv!=NULL)
    {
        FILE *inputfile = fopen(*argv,"r+");
        FILE *outputfile = outputTofile? fopen(strcat(*argv,".cks"),"w+") : stdout;
        result = checksum(inputfile);
        fprintf(outputfile,"%u\n",result);
        argv++;
    }
    
    return EXIT_SUCCESS;
}