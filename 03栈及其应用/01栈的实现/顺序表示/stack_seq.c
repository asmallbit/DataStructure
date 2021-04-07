#include<stdio.h>
#include<stdlib.h>
#define MAX 50

typedef int DataType;

struct SeqStack
{
    int max;
    int n;      //此处n的实际含义为最大的一个元素的下标,即元素个数加1
    DataType* x;
};
typedef struct SeqStack *PSeqStack;

//创建栈
PSeqStack creatEmptyStack_seq(int m){
    PSeqStack p;
    p = (PSeqStack)malloc(sizeof(struct SeqStack));
    if(p!=NULL){
        p->x = (DataType*)malloc(sizeof(int[MAX]));
        if(p->x!=NULL){
            p->n=-1;
            return p;
        }
        else{
            free(p);
        }
    }
    return NULL;
}

//检测栈是否为空
int isEmptyStack(PSeqStack s){
    return (s->n<0);
}

//从顶部插入元素
int push_seq(PSeqStack s, DataType m){
    if(s->n>=MAX){
        printf("Out of space!\n");
        return 0;
    }
    s->n += 1;
    s->x[s->n] = m;
    return 1;
}

//从栈顶删除元素
int pop_seq(PSeqStack s){
    if(isEmptyStack(s)){
        printf("It's an empty stack!\n");
        return 0;
    }
    s->n--;
    return 1;
}

//求栈顶元素的值
DataType top_seq(PSeqStack s){
    if(isEmptyStack(s)){
        printf("It's an empty stack!\n");
    }
    return s->x[s->n];
}

//测试用例
int main(){
    PSeqStack st;
    int m, i;
    //创建
    st = creatEmptyStack_seq(MAX);
    //添加元素
    for(i=0;i<=20;i++){
        push_seq(st, i);
    }
    //输出元素
    for(i=0;i<=20;i++){
        printf("%d\t", st->x[i]);
        if(i%10==0 && i!=0){
            printf("\n");
        }
    }
    for(i=0;i<10;i++){
        pop_seq(st);
    }
    for(i=0;i<11;i++){
        printf("%d\t", st->x[i]);
    }
    printf("Now the top number of this stack is %d\n", top_seq(st));
    return 0;
}