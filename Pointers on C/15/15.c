#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//15-1
void copy1()
{
    char ch;
    while ((ch=getchar())!=EOF) putchar(ch);
}

//15-2
void copy2()
{
    static char linebuf[81];
    fgets(linebuf,81,stdin);
    puts(linebuf);
}

//15-3
void copy3()
{
    static char linebuf[82];
    char *s=fgets(linebuf,82,stdin);
    for(;s!=NULL;)
    {
        fputs(linebuf,stdout);
        //memset(linebuf,'\0',82);
        s=fgets(linebuf,82,stdin);
    }
}
/*void copy3()
{
    static char linebuf[82];
    char *s=fgets(linebuf,82,stdin);
    for(;s!=NULL;)
    {
        if(strlen(s)==81) 
        {
            fputs(linebuf,stdout);
            memset(linebuf,'\0',82);
            s=fgets(linebuf,82,stdin);
        }
        else 
        {
            fputs(linebuf,stdout);
            break;
        }
    }
}*/

//15-4
int copy4()
{
    char file1[20],file2[20];
    scanf("%s %s",file1,file2);
    FILE *f1=fopen(file1,"r"),*f2=fopen(file2,"w");
    if (f1==NULL||f2==NULL) return EXIT_FAILURE;

    static char linebuf[82];
    char *s=fgets(linebuf,82,f1);
    while(s!=NULL)
    {
        fputs(linebuf,f2);
        //memset(linebuf,'\0',82);
        s=fgets(linebuf,82,f1);
    }
    fclose(f1);
    fclose(f2);
    return EXIT_SUCCESS;
}

/*int copy4()
{
    char file1[20],file2[20],ch;
    scanf("%s %s",file1,file2);
    FILE *f1=fopen(file1,"r"),*f2=fopen(file2,"w");
    if (f1==NULL||f2==NULL) return EXIT_FAILURE;

    while ((ch=fgetc(f1))!=EOF) fputc(ch,f2); 
    fclose(f1);
    fclose(f2);
    return EXIT_SUCCESS;
}
*/

//15-5
int copy5()
{
    char file1[20],file2[20];
    scanf("%s %s",file1,file2);
    FILE *f1=fopen(file1,"r"),*f2=fopen(file2,"w");
    if (f1==NULL||f2==NULL) return EXIT_FAILURE;

    static char linebuf[82];
    char *s=fgets(linebuf,82,f1);
    int line_start=1,sum=0;
    while(s!=NULL)
    {
        if (line_start)
        {
            if(isdigit(*linebuf)) sum+= *linebuf-'0';
            line_start = 0;
        }
        if (strchr(linebuf,'\n')) line_start=1;
        fputs(linebuf,f2);
        s=fgets(linebuf,82,f1);
    }
    fprintf(f2,"\n%d",sum);
    fclose(f1);
    fclose(f2);
    return EXIT_SUCCESS;
}

//15-6
int numberic_palindrome(int value)
{
    int digit[10],count=0;
    for (;value;value/=10)
    {
        *(digit+count) = value % 10;
        count++;
    }
    for (int *start=digit,*end=digit+count-1;start<end;start++,end--)
    {
        if(*start != *end) return 0;
    }
    return 1;
}

//15-7
int ave_familyage()
{
    double average,sum,count,age;
    char filename[20],familyage[40];
    scanf("%s",filename);
    FILE *fp=fopen(filename,"r");
    char *line=fgets(familyage,40,fp),*fage=line;
    if (fp==NULL) return EXIT_FAILURE;
    
    while(line!=NULL)
    {
        sum=0,count=0;
        for(int i=0;i<10;i++)
        {
            sscanf(fage,"%lf",&age);
            sum+=age;
            count++;
            fage=strchr(fage,' ');
            if (fage==NULL) break;
            else fage++;
        }
        average=sum/count;
        printf("%5.2f: %s",average,familyage);
        fage=line=fgets(familyage,40,fp);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}


int main()
{
    int r = numberic_palindrome(1221);
    printf("%d\n",r);
    ave_familyage();
    return 0;
}