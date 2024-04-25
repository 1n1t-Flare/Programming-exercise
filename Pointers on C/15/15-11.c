#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 *to save records of components and their value.
 *
 *fuctions:
 *-- new description, quantity, cost-each
 *-- buy part-number, quantity, cost-each
 *-- sell part-number, quantity, price-each
 *-- delete part-number
 *-- print part-number 
 *-- print all
 *-- total 
 *-- end
 *  
 *options: recordfile
 */


// 每行代表一个零件，以行为单位整体读写。保持格式化
long locate_partnumber(int part_number, FILE *recordfile)
{
    char record_line[64]={0},empty[20]={0};
    int number = 0;
    if(part_number == 0)//进行查找空行,和new对接，定位到number末尾
    {
        while(!feof(recordfile))
        {
            fgets(record_line,64,recordfile);
            if(*record_line == '~') 
            {
                sscanf(record_line,"~%d",&part_number);
                fseek(recordfile,-(strlen(record_line)+1),SEEK_CUR);
                fprintf(recordfile,"%d ",part_number);
                return ftell(recordfile);
            } 
        }
        sscanf(record_line,"%d",&number);
        fprintf(recordfile,"\n%d ",(number+1));
        return ftell(recordfile);
    }
    else
    {
        for(int i=0;i<part_number;i++)
        {
            fgets(record_line,64,recordfile);
        }
        return ftell(recordfile);//非空行 bug??
    }
}





void new_f(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    char *description = (char *)arg1;
    int quantity = *(int *)arg2, cost_each = *(int *)arg3, value = quantity*cost_each;
    fseek(recordfile,locate_partnumber(0,recordfile),SEEK_SET);
    fprintf(recordfile,"%-20s %9d %9d ",description,quantity,value);
    fflush(recordfile);
}


void delete_f(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    int part_number = *(int *)arg1;
    fseek(recordfile,locate_partnumber(part_number,recordfile),SEEK_SET);
    fprintf(recordfile,"~%d %-20s %9d %9d ",part_number,"",0,0);
    fflush(recordfile);
}//删除的number之前加一个~记号




void buy(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    int part_number = *(int *)arg1, quantity = *(int *)arg2, cost_each = *(int *)arg3;
    int current_quantity, current_value;
    char record_line[64]={0},buf[20]={0};

    fseek(recordfile,locate_partnumber(part_number,recordfile),SEEK_SET);
    fgets(record_line,64,recordfile);

    sscanf(record_line,"%*d %s %9d %9d ",buf,&current_quantity,&current_value);
    current_quantity += quantity;
    current_value += quantity*cost_each;

    fseek(recordfile,-(strlen(record_line)+1),SEEK_CUR);//注意offset
    fprintf(recordfile,"%d %-20s %9d %9d ",part_number,buf,current_quantity,current_value);
    fflush(recordfile);
}

//!!bug
void sell(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    int part_number = *(int *)arg1, quantity = *(int *)arg2, price_each = *(int *)arg3;
    int current_quantity, current_value;
    char record_line[64]={0},buf[20]={0};

    fseek(recordfile,locate_partnumber(part_number,recordfile),SEEK_SET);
    fgets(record_line,64,recordfile);

    sscanf(record_line,"%*d %s %9d %9d ",buf,&current_quantity,&current_value);
    current_quantity -= quantity;
    current_value -= quantity*price_each;

    printf("%d %d",current_quantity,current_value);

    fseek(recordfile,-(strlen(record_line)+1),SEEK_CUR);
    fprintf(recordfile,"%d %-20s %9d %9d ",part_number,buf,current_quantity,current_value);
    fflush(recordfile);

    printf("\n");

    printf("%d\n",quantity*price_each);
}




void print(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    int part_number = *(int *)arg1;
    char record_line[64]={0};
    if (part_number == 0)//print all
    {
        fgets(record_line,64,recordfile);
        while(!feof(recordfile))
        {
            fgets(record_line,64,recordfile);
            if(*record_line!='~') printf(record_line);
        }
    }
    else
    {
        fseek(recordfile,locate_partnumber(part_number,recordfile),SEEK_SET);
        fgets(record_line,64,recordfile);
        printf(record_line);
    }
}

void total(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    int sum = 0,value = 0;
    char record_line[64]={0};
    fgets(record_line,64,recordfile);
    while(!feof(recordfile))
    {
        fscanf(recordfile,"%*d %*s %*d %9d ",value); //bug?
        sum += value; 
    }
    printf("%d\n",sum);
}

void end(void *arg1, void *arg2, void *arg3, FILE *recordfile)
{
    exit(0);
}

const char *opt[]={"new","buy","sell","delete","print","total","end"};
void (*fuctions[7])(void *,void *,void *,FILE *)={new_f,buy,sell,delete_f,print,total,end};




int main(int argc, char **argv)
{
    char *filepath = *++argv, *token, command[64]={0},str_buf[20]={0};
    void *arguments[3]={NULL,NULL,NULL};
    FILE *recordfile;
    if((recordfile = fopen(filepath,"r+")) == NULL)
    {
        recordfile = fopen(filepath,"w+");
    }
    if(recordfile==NULL) return EXIT_FAILURE;

    while (fgets(command,64,stdin)!=NULL)
    {
        int index=0,arg[3]={-1,0,0};
        token = strtok(command," ");//check command
        for(; index<7; index++)
        {
            if(!strcmp(token,opt[index])) break;
        }
        // rewind(recordfile);
        
        token = strtok(NULL," ");
        for(int i=0;token!=NULL;token=strtok(NULL," "))
        {
            arg[i] = atoi(token);
            arguments[i] = &arg[i];
            if(i==0 && *arg==0)
            {
                strcpy(str_buf,token);
                arguments[i]=str_buf;
            }
            i++;
        }
        fuctions[index](arguments[0],arguments[1],arguments[2],recordfile);
    }
    return 0;
}

//bug：运行程序的第一条命令能正常执行，之后的命令可能出问题。
//每次运行程序只给出一个命令是可行的

/*更好的方式是使用结构体。多读少写，避免反复修改文件内容，程序结束时全部覆盖写入*/
// 抽象成多文件更方便