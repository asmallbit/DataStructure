#include<stdio.h>
#include<stdlib.h>
#define MAX 40

typedef int DataType;
struct Node;
typedef struct Node *pNode;
struct Node
{
    DataType num;
    pNode front, next;
};
typedef struct Node *pList;

//创建表头
pList creatNullList(){
    pList list;
    list = (pList)malloc(sizeof(list));
    if(list==NULL){
        printf("Out of space!\n");
        return NULL;
    }
    else{
        return list;
    }
}

//判断是否为空表
int isNullList(pList list){
    return (list->next==NULL);
}

//查找某节点的前驱
pNode locatePre(pNode p){
    pNode q;
    q = p;
    if(p==NULL){
        return NULL;
    }
    while (q->next!=p)
    {
        q = q->next;
    }
    return q;
}

//单链表变为双链表
int makeDoubleLinkList(pList list){
    if(list==NULL){
        printf("This is a null list\n");
        return 0;
    }
    pNode p1, p2=NULL;
    p1 = list;
    while (p2!=list)
    {
        p2 = locatePre(p1);
        p1->front = p2;
        p1 = p2;
    }
    return 1;
}

//插入元素(前插)
int insertPre(pNode p, DataType x){
    if(p==NULL){
        printf("This list is a null list!\n");
        return 0;
    }
    pNode q, r;
    q = locatePre(p);
    r = (pNode)malloc(sizeof(struct Node));
    r->next = p;
    q->next = r;
    r->front = NULL;
    return 1;
}

//打印表格(正向)
void printList(pList list){
    pNode p;
    int counter=1;
    p = list->next;
    while (p!=list)
    {
        printf("%d\t", p->num);
        p = p->next;
        if(counter%10==0){
            printf("\n");
        }
        counter++;
    }
    printf("\n");
}

//打印表格(反向)
void printListReverse(pList list){
    pNode p;
    int counter=1;
    p = list->front;
    while (p!=list)
    {
        printf("%d\t", p->num);
        p = p->front;
        if(counter%10==0){
            printf("\n");
        }
        counter++;
    }
    printf("\n");
}

int main(){
    pList list;
    int i=0;
    pNode p, q, waitfree1, waitfree2;
    list = creatNullList();
    p = q = (pNode)malloc(sizeof(struct Node));
    list->front = NULL;
    while(i<MAX){
        p->num = i+1;
        p->front = NULL;
        if(i==0){
            list->next=p;
        }
        else{
            q->next = p;
        }
        q = p;
        p = (pNode)malloc(sizeof(struct Node));
        i++;
    }
    free(p);
    q->next = list;
    printList(list);
    //给front指针赋值
    makeDoubleLinkList(list);
    //按照front指针打印
    printListReverse(list);
    //释放申请的空间
    waitfree1 = list->next;
    while (waitfree1->next!=list)
    {
        waitfree2 = waitfree1->next;
        free(waitfree1);
        waitfree1 = waitfree2;
    }
    return 0;
}