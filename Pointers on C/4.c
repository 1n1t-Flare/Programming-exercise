#include <stdio.h>
#include <string.h>
//4-4
void copy_n(char *dst,const char *src,int n)
{
    for (int i=0;i<n;i++)
    {
        static int k=0;
        *(dst+i)=*(src+k);
        if (*(src+k) !='\0')
        k++;
    }
}
/*void copy_n(char *dst,const char *src,int n)
{
    for (int i=0;i<n;i++)
    {
        static int END=0;
        if(!END) {if (*(src+i) =='\0') END=1;}
        if(END)
        {
            *(dst+i) = '\0';
        }
        else
        {
            *(dst+i) = *(src+i);
        }
    }
}*/

//4-5
void print_sameline()
{
    char buffer[128],next[128];
    int isprinted=0;
    gets(buffer);
    while(gets(next)!=NULL && buffer !=NULL)
    {
        if(!strcmp(buffer,next) && !isprinted)
        {
            printf("%s\n",buffer);
            isprinted = 1;
        }
        else isprinted = 0; 
        strcpy(buffer,next);
    }
}

//4-6
int substr(char *dst,char *src,int start,int len)
{
    if (start>=0 && start<strlen(src) && len>=0)
    {
        char *d=dst,*s=src+start;
        for (;d<dst+len;d++)
        {
            *d=*s;
            if(*s!='\0') s++;
        }
        *d='\0';
    }
    return strlen(dst);
}
/*int substr(char *dst,const char *src,int start,int len)
{
    static int END=0;
    if (start>=0 && start<strlen(src) && len>=0)
    {
        for (int i=0;i<len;i++)
        {
            if( *(src+start+i) =='\0') END=1;
            if(!END)
            {
                *(dst+i) = *(src+start+i);
            }
            else
            {
                *(dst+i) = '\0';
                break;
            }
        }
    }
    return strlen(dst);
}*/


//双指针
//4-7
void deblank(char *string)
{
    for (char *s=string; *s !='\0'; s++)
    { 
        static char *c;
        if (*s==' '&& *(s-1)!=' ') c=s+1;
        if (c)
        {
            if (*s !=' ')
            {
                int length = s-c;
                for (; *s !='\0'; s++)
                {
                    *(s-length) = *s;
                }
                *(s-length) = '\0';
                s=c;
                c=NULL;
            }
        }
    }
}


    

int main()
{
    char dst[20]={0};
    char src[]="Hello World";
    copy_n(dst,src,20);
    printf("%s",dst);

    char dst[20]={'\0'},src[]="hello World";
    substr(dst,src,5,5);
    printf("%s",dst);

    char hi[] ="Hello  world      i  love you";
    deblank(hi);
    printf("%s",hi);

    print_sameline();
    return 0;
}