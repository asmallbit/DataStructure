#include<stdio.h>
#include<stdlib.h>

typedef int DataType;

struct LinkStack;
typedef struct LinkStack *PStackNode;
struct LinkStack
{
    DataType x;
    PStackNode next;
};
typedef struct LinkStack *PLinkStack;
//带头节点,头节点为top
//创建空栈
PLinkStack createEmptyStack_link(void){
    PLinkStack p;
    p = (PLinkStack)malloc(sizeof(struct LinkStack));
    if(p!=NULL){
        p->next = NULL;
        return p;
    }
    printf("Out of space!\n");
    return NULL;
}

//检测栈是否为空    
int isEmptyStack_link(PLinkStack s){
    return (s->next==NULL);
}

//向栈中插入元素
int push_link(PLinkStack s, DataType m){
    PStackNode p;
    p = (PStackNode)malloc(sizeof(struct LinkStack));
    if(p!=NULL){
        p->x = m;
        p->next = s->next;
        s->next = p;
        return 1;
    }
    else{
        printf("Out of space!\n");
        return 0;
    }
}

//删除栈顶元素
int pop_link(PLinkStack s){
    if(isEmptyStack_link(s)){
        printf("This is a empty stack!\n");
        return 0;
    }
    PStackNode p;
    p = s->next;
    s->next = p->next;
    free(p);
    return 1;
}

//返回栈顶元素
DataType top_link(PLinkStack p){
    if(isEmptyStack_link(p)){
        printf("This is a empty stack.\n");
    }
    return (p->next->x);
}

//释放整个栈的空间
int freeStack(PLinkStack s){
    PStackNode p, q;
    p = q = s->next;
    while (p->next!=NULL)
    {
        p = q->next;
        free(q);
        q = p;
    }
    free(s);
}

//测试用例
int main(){
    PLinkStack p, q, start;
    int i;
    start = createEmptyStack_link();
    //插入节点
    for(i=0;i<20;i++){
        push_link(start, i);
    }
    //输出栈中的元素
    printf("Now the stack has these elements:\n");
    p = start->next;
    for(i=0;i<20;i++){
        printf("%d\t", p->x);
        p = p->next;
        if(i%10==0 && i!=0){
            printf("\n");
        }
    }
    printf("\n");
    //删除元素
    for(i=0;i<10;i++){
        pop_link(start);
    }
    //打印删除后的栈中的元素
    printf("Now the stack has these elements:\n");
    p = start->next;
    for(i=0;i<10;i++){
        printf("%d\t", p->x);
        p = p->next;
    }
    printf("\n");
    //求栈顶的元素
    printf("Now the top number of this stack is %d\n", top_link(start));
    //释放当前栈所占空间
    freeStack(start);
    start = NULL;
    return 0;   
}