#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 50
typedef int DataType;

//存放队列的结构体
struct Queue_seq
{
    int maxnum;
    int rear;
    int quelen;
    DataType *x;
};
typedef struct Queue_seq *PQueue_seq;

//创建空队列
PQueue_seq creatEmptyQueue(int max){
    PQueue_seq new;
    DataType *x;
    new = (PQueue_seq)malloc(sizeof(struct Queue_seq));
    if(new!=NULL){
        new->x = (DataType*)malloc(sizeof(DataType[max]));
        if(x!=NULL){
            new->maxnum = max;
            new->quelen = 0;
            new->rear = -1;
            return new;
        }
        free(new);
    }
    return NULL;
}

//判断是否为空队列
int isEmptyStrack(PQueue_seq p){
    return (p->quelen == 0);
}

//入队操作
int enQueue(PQueue_seq p, DataType m1){
    if(p->quelen>MAX-1){
        printf("The queue has no space!\n");
        return 0;
    }
    else if(p->rear==MAX-1){
        p->rear = -1;
        p->rear += 1;
        p->x[p->rear] = m1;
        p->quelen += 1;
    }
    else{
        p->x[p->rear + 1] = m1;
        p->quelen += 1;
        p->rear += 1;
    }
    return 1;
}

//出队操作
DataType deQueue(PQueue_seq p){
    if(p->quelen==0){
        printf("The queue is empty.\n");
        return 0;
    }
    //返回出队的元素
    else{
        p->quelen -= 1;
        if(p->rear>p->quelen-1){
            return (p->x[p->rear - p->quelen]);
        }
        else{
            return (p->x[p->rear + MAX - p->quelen]);
        }
        
    }
}

//打印队列中的元素
void printQueue(PQueue_seq p){
    int counter=0, i;
    if(p->quelen==0){
        printf("This is a empty queue.\n");
    }
    if(p->rear>=p->quelen-1){
        i = p->rear - p->quelen + 1;
    }
    else{
        i = p->rear + p->maxnum - p->quelen + 1;
    }
    while(counter<p->quelen){
        printf("%d\t", p->x[i]);
        counter++;
        i++;
        if(i==MAX){
            i = 0;
        }
        if(counter%10==0){
            printf("\n");
        }
    }
}

//测试用例
int main(){
    PQueue_seq p;
    int i;
    DataType num;
    p = creatEmptyQueue(MAX);
    for (i=1;i<=50;i++){
        enQueue(p, i);
    }
    //printQueue(p);
    for (i = 0; i < 10;i++){
        num = deQueue(p);
        printf("本次出队的元素是: %d\n", num);
    }
    for (i = 30; i < 40;i++){
        enQueue(p, i);
    }
        //再次打印队列
        printQueue(p);
        return 0;
}