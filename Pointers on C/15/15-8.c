#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
/*
 *print dump data of a file. 
 *options: [filename]
 *if do not choose option, the program will dump from Stdin (less than 512 bytes).
 */

void print_dumpline(int lineoffset, unsigned char *bytearray)
{
    unsigned char chr;

    printf("%06x  ",lineoffset);
    for (int i=0;i<16;i++)
    {   
        printf("%02X",bytearray[i]);
        if(i%4==3) putchar(' ');
    }

    printf("  *");
    for (int i=0;i<16;i++)
    {
        chr = isprint(bytearray[i])? bytearray[i] : '.';
        putchar(chr);
    } 
    printf("*\n");
}

int main(int argc,char **argv)
{
    long offset = 0,i=0;
    unsigned char byte_buf[17]={0};
    char *buffer;
    switch (argc)
    {
    case 1:
        buffer = (char *)calloc(512,sizeof(char));//size
        fgets(buffer,512,stdin);
        while (offset < strlen(buffer))
        {
            memcpy(byte_buf,buffer+offset,16);
            print_dumpline(offset,byte_buf);
            memset(byte_buf,0,17);
            offset += 16;
        }
        free(buffer);
        break;

    case 2 :
        FILE *file = fopen(*(argv+1),"rb+");
        if (file == NULL) 
        {
            return EXIT_FAILURE;
        }
        while(fread(byte_buf,1,16,file) > 0)
        {
            print_dumpline(offset,byte_buf);
            offset = ftell(file);
            memset(byte_buf,0,17);
        }
        break;
    }
    return 0;
}