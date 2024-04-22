#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//#include "signly_linked_list_node.h"
//#include "doubly_linked_list_node.h"

//单链表
typedef struct NODES
{
    struct NODES *link;
    int value;
} Node_s;

//双链表
typedef struct NODED
{
    struct NODED *fwd;
    struct NODED *bwd;
    int value;
} Node_d;

//通用的有序链表插入算法，以节点为基本对象，通过若干指向节点的指针来操作节点。
int sll_ordered_insert(Node_s **root,int new_value)
{
    Node_s *current=*root, *previous = NULL, *new_node; 
    while(current!=NULL && current->value < new_value)
    {
        previous = current;
        current = current->link;
    }
    new_node = (Node_s *)malloc(sizeof(Node_s));
    new_node->value = new_value;
    new_node->link = current;
    if(previous) 
        previous->link = new_node;
    else
        *root = new_node;
    return 0;
}

//C语言下更理想的有序单链表插入，以指向下一节点的指针为基本对象，通过二级指针操作节点指针。
//指向link的指针发挥重要作用，既控制本节点的link字段，同时可以对link解引用来访问下一节点（及其两个字段）。实现用单一量控制前后两个节点
//（这种方法是针对单方向的问题，对于双链表有前后两个方向则不必使用二级指针;但是要用两个指针控制两个节点）
int sll_insert(Node_s **linkp,int new_value)
{
    Node_s *new_node;
    while(*linkp!=NULL && (*linkp)->value <new_value)
    {
        linkp = &(*linkp)->link;
    }
    new_node = (Node_s *)malloc(sizeof(Node_s));
    new_node->value = new_value;
    new_node->link = *linkp;
    *linkp = new_node;
    return 0;
}


//12-1
int sll_count_nodes(Node_s *root)
{
    int count=0;
    Node_s *node = root;
    while(node)
    {
        count++;
        node = node->link;
    }
    return count;
}

//12-2
Node_s *sll_find(Node_s *root,int value)
{
    Node_s *node = root;
    for(;;)
    {
        if(node->value == value)
        {
            return node;
        }
        node = node->link;
    }
    return NULL;
}

//12-4
/*Node_s *sll_reverse(Node_s *first)
{
    Node_s **linkp = &first->link;

}*/
Node_s *sll_reverse(Node_s *first)
{
    Node_s *previous=NULL,*current=first,*next;
    while (current && (next = current->link) != NULL)
    {
        current->link = previous;
        previous = current;
        current = next;
    }
    current->link = previous;
    return current;
}


//12-5
int sll_remove(Node_s **rootp, Node_s *node)
{
    while (*rootp)
    {
        if (*rootp == node)
        {
            *rootp = node->link;
            free(node);
            return 1;
        }
        if (*rootp == NULL) 
            return 0;
        else 
            rootp = &(*rootp)->link;
    }
    return 0;
}


int dll_insert(Node_d *rootp,int value)
{
    Node_d *current=rootp, *next=rootp->fwd, *insert_node=NULL;
    while (next!=NULL)
    {
        if(next->value == value) 
            return 0;
        if(next->value > value)
            break;
        current=next;
        next=current->fwd;
    }
    if((insert_node = (Node_d *)malloc(sizeof(Node_d)))==NULL)
        return -1;
    insert_node->value = value;
    
    //由于双链表的根节点和 首节点，尾节点 的不完全联系，需要注意处理特殊情况
    insert_node->fwd = next;
    //insert_node->bwd = current;
    insert_node->bwd = (current==rootp?NULL:current);

    current->fwd = insert_node;
    //next->bwd = insert_node;
    (next==NULL?rootp:next)->bwd = insert_node;
    return 1;
}


//12-6
int dll_remove(Node_d *rootp, Node_d *node)
{
    Node_d *current = rootp, *next;
    while((next = current->fwd) != NULL)
    {
        if(next == node)
        {
            current->fwd = next->fwd;
            (next->fwd)->bwd = next->bwd;
            free(next);
            return 1;   
        }
        current = next;
    }
    return 0;
}




void print_dll(Node_d *root)
{
    Node_d *current = root->fwd;
    while(current!=NULL)
    {
        printf("%d  ",current->value);
        current = current->fwd;
    }
}
void print_sll(Node_s *root)
{
    while(root)
    {
        printf("%d  ",root->value);
        root = root->link;
    }
}



//12-7
typedef struct List
{
    char word[16];
    List *link;
}List;

typedef struct Concordance
{
    char letter;
    Concordance *link;
    List *chain;
}Concordance;

int insert_word(Concordance **list, char *string)
{
    char initial_char = *string;
    if(!isalpha(initial_char)) 
        return 0;


    /*while((*list)->letter != initial_char)
    {
        if(*list!=NULL && (*list)->letter<initial_char) 
        {
            list = &(*list)->link;
        }
        else
        {
            //此时节点要插入到**rootp和*rootp指向的节点之间
            Concordance *chr_node = (Concordance *)malloc(sizeof(Concordance));
            chr_node->letter = initial_char;
            chr_node->chain = NULL;
            chr_node->link = (*list)->link;
            *list = chr_node;
            break;
        }
    }*/

    for(;;)
    {
        if(*list==NULL && (*list)->letter>initial_char)
        {
            Concordance *chr_node = (Concordance *)malloc(sizeof(Concordance));
            chr_node->letter = initial_char;
            chr_node->chain = NULL;
            chr_node->link = (*list)->link;
            *list = chr_node;
            break;
        }
        if((*list)->letter == initial_char)
            break;
        list = &(*list)->link;
    }
            

    //此时*list即为二级链表位置
    List **words = &(*list)->chain;
    for(;;)
    {
        if(*words==NULL || strcmp(string,(*words)->word)>0)
        {
            List *word_node = (List *)malloc(sizeof(List));
            strcpy(word_node->word,string);
            word_node->link = (*words)->link;
            *words = word_node;
            break;
        }
        if(strcmp(string,(*words)->word) == 0)
            return 0;
        words = &(*words)->link;
    }
    return 1;
}



int main()
{
    //*单链表
    Node_s *roots = (Node_s *)malloc(sizeof(Node_s));
    roots->value=22;
    Node_s *n1 = (Node_s *)malloc(sizeof(Node_s));
    roots->link=n1;
    n1->value=33;
    Node_s *n2 = (Node_s *)malloc(sizeof(Node_s));
    n1->link=n2;
    n2->value=44;
    n2->link=NULL;

    
    sll_insert(&roots,36);
    print_sll(roots);
    sll_remove(&roots,n1);
    Node_s *slr = sll_reverse(roots);
    printf("\n");
    print_sll(slr);



    /*双链表
    Node_d *d1 = (Node_d *)malloc(sizeof(Node_d));
    Node_d *d2 = (Node_d *)malloc(sizeof(Node_d));
    Node_d *d3 = (Node_d *)malloc(sizeof(Node_d));
    Node_d *d4 = (Node_d *)malloc(sizeof(Node_d));
    Node_d *rootp = (Node_d *)malloc(sizeof(Node_d));
    rootp->fwd=d1;rootp->bwd=d4;
    d1->value=10;d1->fwd=d2;d1->bwd=NULL;
    d2->value=20;d2->fwd=d3;d2->bwd=d1;
    d3->value=30;d3->fwd=d4;d3->bwd=d2;
    d4->value=40;d4->fwd=NULL;d4->bwd=d3;

    print_dll(rootp);
    int c=dll_insert(rootp,5);
    printf("%d\n",c);
    dll_remove(rootp,d3);
    print_dll(rootp);
    */

    return 0;
}