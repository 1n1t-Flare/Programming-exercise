#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1-2
void printrows()
{
    size_t count=1;
    char ch;
    int beginning=1;
    while((ch=getchar())!=EOF)
    {
        if(beginning) 
        {
            printf("%d\t",count);
            count++;
            beginning=0;
        }
        putchar(ch);
        if (ch == '\n') beginning=1;
    }
}

//1-3
void printcheck()
{
    signed char checksum = -1,ch;
    while((ch=getchar())!=EOF)
    {
        putchar(ch);
        checksum+=ch;
        if (ch =='\n') break;
    }
    printf("%d",checksum);
}

//1-4
void longest_row()
{
    char buf[1002],longest[1002];
    size_t length = 0;
    while (gets(buf)!=NULL)
    {
        if (strlen(buf)>length)
        {
            length=strlen(buf);
            strcpy(longest,buf);
        }
        printf("%s",longest);
    }

}

#define MAX_INPUT 1000
#define MAX_COLS 20
//1-5,1-6
void rearrange(char *output, char const *input, int n_columns, int const columns[])
{
    int col;
    int output_col;
    int len;
    len = strlen(input);
    output_col=0;
    
    for (col=0;col<n_columns;col+=2)
    {
        int nchars;
        if (n_columns%2){ 
            nchars = len -columns[col]+1;}
        else{
            nchars = columns[col+1]-columns[col]+1;}
        if(columns[col]>=len) continue;
        if(output_col == MAX_INPUT-1) break;
        if(output_col + nchars>MAX_INPUT-1) nchars = MAX_INPUT - output_col-1;
        strncpy(output+output_col,input+columns[col],nchars);
        output_col+=nchars;
    }
    output[output_col]='\0';
}
int main()
{
    printf("Hello,world!\n");
    //printrows();
    //printcheck();
    return 0;
}
