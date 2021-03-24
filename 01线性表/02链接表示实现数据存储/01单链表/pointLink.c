#include<stdio.h>
#include<stdlib.h>
#define NUM 40

/*
//暂时不考虑此结构体,以int为例
struct Person{
    int sex;
    int age;
    char name[20];
};
typedef struct Person DataType;
*/

typedef int DataType;
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


pNode locatePre_link(LinkList llist, pNode p){
    pNode q;
    q = llist->link;
    if(llist==NULL){
        return NULL;
    }
    while(q->link->info!=p->info && q->link!=NULL){
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
    while(q!=NULL && q->info!=x){
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
    while(p->link!=NULL && p->link->info!=x)
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
    int i = 0;
    while(s->link!=NULL){
        printf("%d\t", s->info);
        i++;
        if(i%10==0)
            printf("\n");
        s = s->link;
        if(s->link==NULL)
            printf("%d\n", s->info);
    }
}

//课本作业(前插)
int insertPre(struct Node* list, struct Node* p, DataType x){
    if(list==NULL){
        printf("The list is a null list!/n");
        return 0;
    }
    struct Node* font, *m;
    font = list->link;
    m = (struct Node*)malloc(sizeof(struct Node));
    while(font->link!=p && font->link!=NULL)
        font = font->link;
    m->info = x;
    m->link = font->link;
    font->link = m;
    return 1;
}

int main(){
    LinkList llist = creatNullList_link();
    pNode p, q;
    int i;
    //判断列表是否为空
    if(isNullList_link(llist)){
        printf("\nYeah, this is a null list.\n");
    }
    else{
        printf("Sorry, this is not a null list.\n");
    }
    //给列表赋值并打印
    p = q = (pNode)malloc(sizeof(struct Node));
    printf("The list is:\n");
    for(i=0;i<NUM;i++){
        p->info = i;
        if(i==0){
            llist->link = p;
        }
        else{
            q->link = p;
        }
        q = p;
        p = (pNode)malloc(sizeof(struct Node));
    }
    q->link = NULL;
    printList(llist, p);
    //查找元素
    q = locate_link(llist, 19);
    //删除元素(根据元素的位置来删除元素)
    if(deleteP_link(llist, q)){
        printf("\nGood, delete succeed!\nHere is the list now:\n");
        printList(llist, p);
    }
    //插入元素(前插)
    if(insertPre_link(llist, q->link, 19)){
        printf("\nInsert(Pre) succeed!\nHere is the list now:\n");
        printList(llist, p);
    } 
    //删除元素(根据值来删除元素)
    if(deleteV_link(llist, 12)){
        printf("\nDelete succeed!\nHere is the list now:\n");
        printList(llist, p);
    }
    //插入元素(后插)
    if(insertPost_link(llist, locate_link(llist, 11), 12)){
        printf("\nInsert(Post) succeed!\nHere is the list now:\n");
        printList(llist, p);
    }
    
    //测试前插
    if(insertPre(llist, locate_link(llist, 20), 100)){
        printf("\nGood!We de it succeedfully!\n");
        printList(llist, p);
    }
    printf("Done");
    return 0;
}