#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//13-1
double char_percentage(char *buf, int(*func)(int))
{
    double count = 0, sum = 0, persent = 0;
    for(;*buf!='\0';buf++)
    {
        sum++;
        if (func(*buf)!=0)
        {
            count++;
        }
    }
    persent = count/sum;
    return persent;
}

int compute()
{
    char buf[128];
    scanf("%s",buf);
    printf("控制字符占比：%.2f%%\n"     ,char_percentage(buf,iscntrl));
    printf("空白字符占比：%.2f%%\n"     ,char_percentage(buf,isblank));
    printf("数字占比：%.2f%%\n"         ,char_percentage(buf,isdigit));
    printf("小写字母占比：%.2f%%\n"     ,char_percentage(buf,islower));
    printf("大写字母占比：%.2f%%\n"     ,char_percentage(buf,isupper));
    printf("标点符号占比：%.2f%%\n"     ,char_percentage(buf,ispunct));
    printf("不可打印字符占比：%.2f%%\n",1-char_percentage(buf,isprint));
    return 0;
}


//13-3
#include "node.h"
#include "transaction.h"
Node *list, *current;
Transaction *transaction;
typedef enum {NEW, DELETE, FORWARD, BACKWARD, SEARCH, EDIT} Trans_type;
void new(Node *, Node * ,Transaction *);
void delete(Node *, Node * ,Transaction *);
void forward(Node *, Node * ,Transaction *);
void backward(Node *, Node * ,Transaction *);
void Search(Node *, Node * ,Transaction *);
void exit(Node *, Node * ,Transaction *);

void (*func[])(Node *, Node * ,Transaction *) = {new,delete,forward,backward,Search,exit};

if (transaction->type<0 && transaction->type>5)
{
    printf("Illegal transaction type!\n");
}
else
{
    func[transaction->type](list,current,transaction);
}

void new(Node *list, Node *current,Transaction *transaction)
{
    add_new_trans(list,transaction);
}
void delete(Node *list, Node *current,Transaction *transaction)
{
    current = delete_trans(list,current);
}
void forward(Node *list, Node *current,Transaction *transaction)
{
    current = current->next;
}
void backward(Node *list, Node *current,Transaction *transaction)
{
    current = current->prev;
}
void Search(Node *list, Node *current,Transaction *transaction)
{
    current = search(list,transaction);
}
void edit(Node *list, Node *current,Transaction *transaction)
{
    edit(current,transaction);
}



//13-4
//error: invalid use of type 'void' in parameter declaration
/*
int compare(void const a,void const b)
{
    return (int)a==(int)b? 0:(a>b? 1:-1);
}

void sort(void *head, int arr_count, int elm_size, int (*cmp)(void,void))
{
    for(int i=0;i<arr_count-1;i++)
    {
        for(int j=i+1;j<arr_count;j++)
        {
            if( cmp(*(head+i*elm_size),*(head+j*elm_size)) >0)
            {
                for(int byte=0;byte<elm_size;byte++)
                {
                    char exchange = *(head+i*elm_size+byte);
                    *(head+i*elm_size+byte) = *(head+j*elm_size+byte);
                    *(head+j*elm_size+byte) = exchange;
                }
            }
        }
    }
}
*/
int compare_integers(void const *a,void const *b)
{
    //return (int)*a==(int)*b? 0:(a>b? 1:-1);   ERROR:'const void*' is not a pointer-to-object type
    return *(int*)a == *(int*)b? 0:(*(int*)a > *(int*)b? 1:-1);
}
void sort(void *head, int arr_count, int elm_size, int (*cmp)(void const*,void const*))
{
    for(int i=0;i<arr_count-1;i++)
    {
        for(int j=i+1;j<arr_count;j++)
        {
            if( cmp(head+i*elm_size,head+j*elm_size) >0)
            {
                char exchange[16] = {0};
                memcpy(exchange,head+i*elm_size,elm_size);
                memcpy(head+i*elm_size,head+j*elm_size,elm_size);
                memcpy(head+j*elm_size,exchange,elm_size);
            }
        }
    }
}


//13-5
char **do_args(int argc, char **argv, char *control, 
        void (*do_arg)(int ch, char *value), void (*illegal_arg)(int ch))
{
    char **current_argp = argv;
    char *arg = NULL, *check = NULL, *value = NULL;
    int have_value = 0;
    while(*current_argp!=NULL && **++current_argp == '-')
    {
        arg = *current_argp;
        do
        {
            check = strchr(control,*++arg);
            if (check !=NULL)
            {
                have_value = ( *(check+1) == '+'? 1 : 0 );
                if(have_value)
                {
                    if((value = (*(arg+1)!='\0'? ++arg : *++current_argp)) != NULL) 
                    {
                        (*do_arg)(*check,value);
                        break;
                    }
                    else 
                    {
                        (*illegal_arg)(*arg);
                    }
                }
                else
                {
                    (*do_arg)(*check,NULL);
                }
            }
            else
            {
                (*illegal_arg)(*arg);
            }
        }while(*(arg+1)!='\0');
    }
    return current_argp;
}

void do_arg(int ch,char *value)
{
    if(value!=NULL) printf("arg:--%c,%s\n",ch,value);
    else printf("arg:-%c,0\n",ch);
}
void illegal_arg(int ch)
{
    printf("illegal:no %c\n",ch);
}


//
void print_int_array(int *arr,size_t length)
{for(int i=0;i<length;i++) printf("%d\t",*(arr+i));}

int main(int argc, char **argv)
{
    compute();
    
    char control[] = "abcdef";
    char **a = do_args(argc,argv,control,do_arg,illegal_arg);

    int arr[8]={10,20,30,90,80,70,40};
    print_int_array(arr,8);
    printf("\n");
    sort(arr,8,4,compare_integers);
    print_int_array(arr,8);
    return 0;
}

