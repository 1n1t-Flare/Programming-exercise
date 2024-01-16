#include <stdio.h>
#include <stdarg.h>
//7-1
int hermite(int n, int x)
{
    if (n<=0) return 1;
    else if (n == 1) return 2*x;
    else if (n >= 2) 
    {
        int num = 2*x*hermite(n-1,x)-2*(n-1)*hermite(n-2,x);
        return num;
    }
    else return 0;   
}

//7-4
int max_list(int num,...)
{
    va_list var;
    int max = 0;
    va_start(var,num);
    for(int i=num;i>=0;i=va_arg(var,int))
    {
        if(i>max) max=i;
    }
    va_end(var);
    return max;
}


//7-5
void print(char *format,...)
{
    va_list var;
    va_start(var,format);
    for (;*format !='0';format++)
    {
        if(*format !='%')putchar(*format);
        else
        {
            char code=*(format+1);
            int outputd;
            float outputf;
            char *outputs;
            char outputc; 
            switch (code)
            {
            case 'd':
                outputd = va_arg(var,int);
                //print_integer(str);
                break;
            case 'f':
                outputf = va_arg(var,double);
                //print_float(str);
                break;
            case 's':
                outputs = va_arg(var,char*);
                for (;*outputs!='\0';outputs++)
                {
                    putchar(*outputs);
                }
                break;
            case 'c':
                outputc = va_arg(var,int);
                putchar(outputc);
                break;
            }
            format+=1;
        }
    }
    va_end(var);
}



int main()
{
    int h = hermite(3,2);
    printf("%d\n",h);
    int m = max_list(5,6,2048,10,-1);
    printf("%d",m);
    return 0;
}