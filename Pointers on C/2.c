#include<stdio.h>
//2-2
int check_brace()
{
    int brace=0;
    char ch;
    while((ch = fgetc(stdin))!=EOF)
    {
        if (ch == '{')
        {
            brace++;
        }
        if (ch == '}')
        {
            if (brace>0) brace--;
            else return 0;
        }
    }
    if (brace) return 0;
    else return 1;
}

//another version ,enable this function to check paired brace from other C program.
//but it would also check for braces in comments and strings.
int fcheck_brace(const char *filename)
{
    int brace=0;
    char ch;
    FILE *fp = fopen(filename,"r");
    while((ch = fgetc(fp))!=EOF)
    {
        if (ch == '{')
        {
            brace++;
        }
        if (ch == '}')
        {
            if (brace>0) brace--;
            else 
            {
                brace --;
                break;
            }
        }
    }
    fclose(fp);
    if (brace) return 0;
    else return 1;
}

int main()
{
    //int check = fcheck_brace("1.c");
    //printf("%d",check);
    return 0;
}