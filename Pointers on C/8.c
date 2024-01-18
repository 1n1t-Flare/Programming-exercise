#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
//8-2
float single_tax(float income)
{
    float standards[5] = {0,23350,56550,117950,256500};
    float percent[5] = {0.15,0.28,0.31,0.36,0.396};
    float *p=standards;
    float tax = 0.0;
    while(income > *p) p++;
    for(int i=0;i<p-standards;i++)
    {
       if(i == p-standards) tax += percent[i] * (income-standards[i]);
       else tax += percent[i] * (standards[i+1]-standards[i]);
    }
    return tax;
}

//8-3
int identity_10matrix(const int (*matrix)[10])
{
    const int FALSE =0;
    const int (*m)[10] = (int (*)[10])matrix;
    for (int i=0;i<10;i++)
    {
        if((*m)[i]!=1) return FALSE;
        for (int j=0;j<10;j++)
        {
            if ((j!=i)&&((*m)[j] !=0)) return FALSE;
        }
        m++;
    }
    return 1;
}

//8-4
int identity_matrix(const int *matrix,int size)
{
    const int FALSE =0;
    const int (*m)[size] = (int (*)[size])matrix;
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if ((j!=i)&&((*m)[j] !=0)) return FALSE;
            if ((j==i)&&((*m)[j] !=1)) return FALSE;
        }
        m++;
    }
    return 1;
}


//8-5
void matrix_multiply(int *m1,int *m2,int *r,int x,int y,int z)
{
    int (*pi)[y]=(int (*)[y])m1;
    for (;pi-(int (*)[y])m1<x;pi++)
    {
        for(int j=0;j<z;j++)
        {
            for (int k=0;k<y;k++)
            {
                *r+=(*pi)[k]*m2[j+k*z];
            }
            r++;
        }
    }
}


//8-6
int array_offset(int *array_info,...)
{
    int array_dim = *array_info,low,high,distance,offset=0;
    if (array_dim<1 && array_dim>10) return -1;
    int *indexlist = (int *)malloc(sizeof(int)*array_dim);
    va_list vars;
    va_start(vars,array_info);    
    for (int k=0;k<array_dim;k++)
    {
        *(indexlist+k) = va_arg(vars,int);
    }
    va_end(vars);

    for (int i=1;i<=array_dim*2;i+=2)
    {
        low = *(array_info+i);
        high = *(array_info+i+1);
        distance = *(indexlist+i/2) - low;
        if (low > high || distance < 0) return -1;
        offset = offset*(high-low+1) + distance; 
    }
    free(indexlist);
    return offset;
}


//8-7
int array_offset2(int *array_info,...)
{
    int array_dim = *array_info,low,high,distance,offset=0;
    if (array_dim<1 && array_dim>10) return -1;
    int *indexlist = (int *)malloc(sizeof(int)*array_dim);
    va_list vars;
    va_start(vars,array_info);    
    for (int k=0;k<array_dim;k++)
    {
        *(indexlist+k) = va_arg(vars,int);
    }
    va_end(vars);

    for (int i=array_dim*2;i>=1;i-=2)
    {
        low = *(array_info+i-1);
        high = *(array_info+i);
        distance = *(indexlist+i/2-1) - low;
        if (low > high || distance < 0) return -1;
        offset = offset*(high-low+1) + distance; 
    }
    free(indexlist);
    return offset;
}


//8-8
void print_board(int (*board)[8])
{
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            printf("%3d",*(*(board+i)+j));
        }
        putchar('\n');
    }
}
//函数设计有问题
void solve_EightQueen(int *(board)[8],int *row)
{
    static int r=0;
    int safety=1;
    /*
    To be continued...
    */
}


int main()
{
    int x=3,y=2,z=4;
    int A[3][2]={2,-6,3,5,1,-1},B[2][4]={4,-2,-4,-5,-7,-3,6,7};
    static int R[3][4];
    int *a=(int *)A,*b=(int *)B,*r=(int *)R;
    matrix_multiply(a,b,r,x,y,z);
    for (int m=0;m<3;m++)
    {
        for (int n=0;n<4;n++)
        {
            printf("%3d",*(*(R+m)+n));
        }
    }
    static int chessboard[8][8];

    int array_info[7]={3,4,6,1,5,-3,3};
    int os = array_offset2(array_info,6,5,3);
    printf ("%d",os);
    
    return 0;
}