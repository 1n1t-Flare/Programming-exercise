#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//11-1
void *my_calloc(size_t num_elements,size_t element_size)
{
    size_t byte_length = num_elements*element_size;
    void *memory = malloc(byte_length);
    if (memory !=NULL)
    {
        return memset(memory,0,byte_length);
    }
    else return NULL;
}

/*先申请，再调整*/
//11-2
int *read_integers()
{
    size_t persize = 50, count = 0;
    int *memory = (int *)malloc(persize*sizeof(int));
    if(memory == NULL) return  NULL;
    while (scanf("%d",memory+count+1) == 1)
    {
        count++;
        if (count>=persize-1)
        {
            persize += persize;
            memory = (int *)realloc(memory,persize*sizeof(int));
            if(memory == NULL) return  NULL;   
        }
    }
    if (count<persize)
    {
        memory = (int *)realloc(memory,(count+1)*sizeof(int));
        if(memory == NULL) return  NULL; 
    }
    *memory = (int)count;//
    return memory;
}


//11-3
char *read_string()
{
    size_t size =65*sizeof(char),setoff=0;
    char *allocbuf = (char *)malloc(size);
    while (fgets(allocbuf+setoff,65,stdin)!=NULL)
    {
        size += 64*sizeof(char);
        allocbuf = (char *)realloc(allocbuf,size);
        setoff += 64;
    }
    return allocbuf;
}
//Solution:用getchar进行读取；最后分配新的动态数组来返回。

//11-4
struct Link
{
    int n;
    struct Link *next;
};

/*Solution比较简洁的创建新节点方法：
把新建节点封装成一个函数，返回值为新节点的指针。把这个指针的值保存到link字段即可

Node *newnode( int value )
{ 
    Node*new;
    (Node *)malloc( sizeof( Node ) );
    assert ( new != 0 );
    new->value = value;
    return new;
}
main ()
{
    Node*head;
    head = newnode ( 5 );
    head->link = newnode( 10 );
    head->link->link = newnode( 15 );
    head->link->link->link = 0;
}

*/
int main()
{
    
    //struct Link dot,dot2,dot3;
    struct Link *dot = malloc(sizeof(struct Link));
    if (dot != NULL)
    {
        dot -> n = 5;
        struct Link *dot1 = malloc(sizeof(struct Link));
        if (dot1 != NULL)
        {
            dot -> next = dot1;
            dot1 -> n = 10;
            struct Link *dot2 = malloc(sizeof(struct Link));
            if (dot2 != NULL)
            {
                dot1 -> next = dot2;
                dot2 -> n = 15;
                dot2 -> next = NULL; 
            }
        }
    }
    //end，有点复杂了

    int *arr = read_integers();
    free(arr);
    char *buf = read_string();
    printf("%s",buf);
    free(buf);
    return 0;
}

