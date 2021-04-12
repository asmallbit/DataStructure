#include<stdlib.h>
#include<stdio.h>

typedef int DataType;
struct QueueLinkNode;
typedef struct QueueLinkNode *PQueueLinkNode; 
struct QueueLinkNode
{
    DataType x;
    PQueueLinkNode next;
};
typedef struct QueueLinkNode *PQueueLink;

struct Point
{
    PQueueLink head;
    PQueueLinkNode tail;
};
typedef struct Point *PPoint;


PPoint creatEmptyQueue(void){
    PPoint p;
    p = (PPoint)malloc(sizeof(struct Point));
    if(p!=NULL){
        p->head = NULL;
        p->tail = NULL;
    }
    else{
        printf("Out of space!\n");
    }
    return p;
}


int isEmptyQueue(PPoint p){
    return (p->head==NULL);
}

//从队尾插入元素
int enQueue(DataType m, PPoint p){
    PQueueLinkNode new;
    new = (PQueueLinkNode)malloc(sizeof(struct QueueLinkNode));
    if(new!=NULL){
        new->x = m;
        new->next = p->tail;
        //考虑队列为空的情况
        if(p->head==NULL){
            p->head = new;
        }
        else{
            p->tail->next = new;
        }
        new->next = NULL;
        p->tail = new;
        return 1;
    }
    printf("Out of space.\n");
    return 0;
}

//从队首删除元素
int deQueue(PPoint p){
    if(p->head==NULL){
        printf("This is a empty queue, you cant delete anything from it!\n");
        return 0;
    }
    PQueueLinkNode q;
    //考虑队列只有一个元素的状况
    if(p->head==p->tail){
        free(p->head);
        p->head = p->tail = NULL;
    }
    else{
        q = p->head;
        p->head = q->next;
        free(q);
    }
    return 1;
}

//返回队列头部元素的值
DataType frontQueue(PPoint p){
    if(p->head==NULL){
        printf("This is a empty queue.\n");
    }
    return p->head->x;
}

//打印所有队列中的元素
void printQueue(PPoint p){
    PQueueLinkNode pq;
    int counter=0;
    pq = p->head;
    if(pq==NULL)
    {
        printf("This is a empty queue\n");
    }
    while(pq->next!=NULL){
        printf("%d\t", pq->x);
        counter++;
        pq = pq->next;
        if(counter%10==0){
            printf("\n");
        }
        if(pq->next==NULL){
            printf("%d", pq->x);
        }
    }
    printf("\n");
}

//测试用例
int main(){
    PPoint point;
    PQueueLinkNode node, temp;
    int i, first;
    point = creatEmptyQueue();
    //插入操作
    for(i=1;i<=20;i++){
        enQueue(i, point);
    }
    printf("We creat a new queue, it's:\n");
    printQueue(point);
    //删除操作
    for(i=1;i<=10;i++){
        deQueue(point);
    }
    printf("We delete some elements of it, it's change to:\n");
    printQueue(point);
    first = frontQueue(point);
    printf("Ths first of this queue is ");
    printf("%d", first);
    //释放指针
    node = point->head;
    while (node->next!=NULL)
    {
        temp = node->next;
        free(node);
        node = temp;
    }
    free(node);
    return 0; 
}