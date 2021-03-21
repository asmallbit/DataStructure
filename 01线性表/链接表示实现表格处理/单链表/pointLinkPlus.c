#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUM 6

struct Student{
    int index;
    char name[20];
    int id;
    int math;
    int DataStructure;
};
typedef struct Student *DataType;
struct Node;    //单链表节点类型
typedef struct Node *pNode;     //结点指针类型
struct Node{
    DataType info;
    pNode link;
};
typedef struct Node *LinkList;

//创建空链表
LinkList creatNullList_link(void){
    LinkList llist = (LinkList)malloc(sizeof(struct Node));     //申请表头结点空间
    if(llist!=NULL){
        llist->link = NULL;
    }
    else{
        printf("Out of space!\n");      //创建失败处理
    }
    return llist;
}

//判断表是否为空
int isNullList_link(LinkList llist){
    return (llist->link==NULL);
}

int judge(pNode p, pNode q){
    return (q->link->info->DataStructure!=p->info->DataStructure || q->link->info->index!=p->info->index || 
        q->link->info->id!= p->info->id || q->link->info->math!=p->info->math ||
        q->link->info->name!=p->info->name);
}

int judge_2(pNode p, DataType q){
    return (p->info->name!=q->name || p->info->math!=q->math || p->info->index!=q->index|| p->info->id!=q->id
        || p->info->DataStructure!=q->DataStructure);
}

//寻找节点p的钱去并返回其地址
pNode locatePre_link(LinkList llist, pNode p){  
    pNode q;
    q = llist->link;
    if(llist==NULL){
        return NULL;
    }
    while(judge(q, p) && q->link!=NULL){
        q=q->link;
    }
    if(q->link==NULL){
        printf("Not exist!");
        return NULL;
    }
    return q;
    /*
    pNode p1;
    if(llist==NULL){
        return NULL;
    }
    p1 = llist;
    while(p1!=NULL && p1->link!=p){
        p1 = p1->link;
    }
    return p1;
    */
}

//在单链表中求某元素的位置
pNode locate_link(LinkList llist, DataType x){
    //在单链表中寻找值为x的元素的下标
    pNode q;
    if(llist==NULL){
        return llist;
    }
    q = llist->link;
    while(q!=NULL && judge_2(q, x)){
        q = q->link;
    }
    return q;
    /*
    pNode p;
    if(llist==NULL){
        return NULL;
    }
    p = llist->link;
    while(p!=NULL && p->info!=x){
        p = p->link;
    }
    return p;
    */
}

//插入元素(前插)
int insertPre_link(LinkList llist, pNode p, DataType x){
    pNode q, m = (pNode)malloc(sizeof(DataType));
    q = locatePre_link(llist, p);
    if(q!=NULL){
        m->info = x;
        m->link = p;
        q->link = m;
        return 1;
    }
    return 0;
}

//插入元素(后插)
int insertPost_link(LinkList llist, pNode p, DataType x){
    
    pNode m = (pNode)malloc(sizeof(struct Node));
    if(p!=NULL){
        m->info = x;
        if(p->link!=NULL)
            m->link = p->link;
        else
            m->link = NULL;
        p->link = m;
        return 1;
    }
    return 0;
    /*
    pNode q = (pNode)malloc(sizeof(struct Node));
    if(q==NULL){
        printf("Out of space!\n");
        return 0;
    }
    else{
        q->info = x;
        q->link = p->link;
        p->link = q;
        return 1;
    }
    */
}

//删除元素(根据值)
int deleteV_link(LinkList llist, DataType x){
    pNode p, temp;
    p = llist->link;
    while(p->link!=NULL && judge_2(p->link, x))
    {
        p=p->link;
    }
    if(p->link==NULL){
        printf("Not exist!\n");
        return 0;
    }
    temp = p->link->link;
    free(p->link);
    p->link = temp;
    return 1;
}

int deleteP_link(LinkList llist, pNode p){
    pNode q, temp;
    q = locatePre_link(llist, p);
    if(q->link!=NULL){
        if(p->link!=NULL)
            q->link = p->link;
        else
            q->link = NULL;
        return 1;
    }
    return 0;
}

//打印表格
void printList(LinkList llist, pNode s){
    s = llist->link;
    printf("编号\t姓名\t学号\t数学成绩\t数据结构成绩\n");
    while(1){
        printf("%d\t%s\t%d\t  %d\t\t   %d\n",s->info->index, s->info->name, s->info->id, s->info->math, s->info->DataStructure);
        if(s->link==NULL){
            break;
        }
        else{
            s = s->link;
        }
        
    }
}

int main(){
    LinkList llist = creatNullList_link();
    pNode p, q, s;
    int i=1, j=0;
    char a[][20]={{"张三"}, {"李四"}, {"小王"}, {"大军"}, {"钱芳"}, {"大刘"}};
    int mathGrades[NUM] = {65, 45, 23, 12, 12, 87};
    int dataStructureGrades[NUM] = {90, 60, 70, 60, 12, 99};
    //创建表格并赋值
    p = q = (pNode)malloc(sizeof(struct Node));
    while(i<=NUM){
        (p->info) = malloc(sizeof(DataType));
        p->info->id = i;
        p->info->index = i;
        strcpy(p->info->name, a[j]);
        p->info->math = mathGrades[j];
        p->info->DataStructure = dataStructureGrades[j];
        if(i==1){
            llist->link = p;
        }
        else{
            q->link = p;
        }
        q = p;
        p = (pNode)malloc(sizeof(struct Node));
        i++;
        j++;
        if(i>NUM){
            q->link = NULL;
        }
    }
    printf("All Done!\nLet me show the list to u:\n");
    printList(llist, s);
    return 0;
}
