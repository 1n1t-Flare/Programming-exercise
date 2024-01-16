#include <stdio.h>
#define TURE 1
#define FALSE 0
//6-1
char *find_char(char const *source,char const *chars)
{
    const char *s=source , *c=chars;
    if (s&&c)
    {
        for (;*s!='\0';s++)
        {
            for (c=chars;*c!='\0';c++)
            {
                if(*s==*c) return (char*)s;
            }
        }
    }
    return NULL;
}


//6-2
int del_substr(char *str,char const  *substr)
{
    const char *check=substr;
    char* start = NULL;
    for (; *str!='\0'; str++)
    {
        if (*str==*check)
        {
            if (check == substr) start = str;
            check++;
        }
        else check=substr;
        if (*check == '\0')
        {
            do
            {
                *start++ = *++str;
            } while (*str!='\0');
            return 1;
        }
    }
    return 0;
}

//6-3
void reverse_string(char *string)
{
    char *later = string;
    for (;*(later+1)!='\0';later++);
    for (;string<later;)
    {
        char exchange = *string;
        *string++ = *later;
        *later-- = exchange;
    }
}

//6-4
void Eratosthenes(int *range,int length)
{
    int *end = &range[length-1];//"length" means the length of the array (range)
    int *index;
    for (int i=0;i<length;i++) *(range+i)=TURE;
    for (;;)
    {    
        static int count = 2;
        while (!*(index = range+count-2) && count <= length+2)
        {
            count++;
        }
        if (count > length+2) break;
        for (index+=count;index<=end;index+=count)
        {
            if (*index == TURE)
            {
                *index = FALSE;
            }
        }
        count++;
    }
}


// include "5.c" 
void set_bit(char* bit_array,unsigned bit_number);
void clear_bit(char* bit_array,unsigned bit_number);
void assign_bit(char* bit_array,unsigned bit_number,int value);
int test_bits(char* bit_array,unsigned bit_number);
//6-5
void bitarr_Eratosthenes(char *range,unsigned length)
{
    for (int i=0;i<length;i++) set_bit(range,i);
    unsigned count = 2,bit_index;
    for(;;)
    {
        while (!test_bits(range,bit_index = count - 2)&& count <= length+2) 
        {
            count++;
        }
        if (count > length+2) break;
        for (bit_index += count; bit_index <= length; bit_index += count)
        {
            clear_bit(range,bit_index);
        }
        count++;
    }
}


int main()
{
    int sr[12];
    for(int i=0;i<12;i++)
    {
        sr[i]=1;
    }
    reverse_string(sr);
    int src[50]={0};
    Eratosthenes(src,50);
    for(int i=0;i<50;i++)
    {
        printf("%d,",src[i]);
    }
    return 0;
}