#include<stdio.h>
#include<stdlib.h>

struct ConterNode;
typedef struct ConterNode *PConterNode;
struct ConterNode{
    int x;
    PConterNode next;
};
typedef struct ConterNode *PConter;

//创建栈
PConter createEmptyStack(void){
    PConter p;
    p = (PConter)malloc(sizeof(struct ConterNode));
    if(p!=NULL){
        p->next = NULL;
        return p;
    }
    printf("Out of space!\n");
    return NULL;
}

//向栈中存储元素
int push(PConter s, int m){
    PConterNode p;
    p = (PConterNode)malloc(sizeof(struct ConterNode));
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

//释放栈所占用的空间
int freeStack(PConter s){
    PConterNode p, q;
    p = q = s->next;
    while (p->next!=NULL)
    {
        p = q->next;
        free(q);
        q = p;
    }
    free(s);
}

//进制转换函数,用于将转换完成的数据存储到栈中
PConter hexConverter(int decimalNumber, int hex){
    PConter p;
    p = createEmptyStack();
    int i, flag=0;
    if(decimalNumber<0){
        flag = 1;
        decimalNumber = -decimalNumber;
    }
    while (decimalNumber!=0)
    {
        i = decimalNumber % hex;
        push(p, i);
        decimalNumber /= hex;
    }
    if(flag==1){
        p->next->x = -(p->next->x);
    }
    return p;
}

//一次性用于打印出栈中所存储的所有数据
void printStackThings(PConter p, int hex){
    PConterNode s;
    s = p->next;
    printf("After converter, the %d hex number is: ", hex);
    while (s->next!=NULL)
    {
        printf("%d", s->x);
        s = s->next;
    }
    //输出最后一个字符,以及考虑输入的值为0的情况
    if(s->next==NULL){
        printf("%d", s->x);
    }
    label: printf("\n");
}

//测试用例
int main(){
    int decimalNum, hex;
    PConter saveResults;
    //输入一个10进制的数
    printf("Please enter a decimal number: ");
    scanf("%d", &decimalNum);
    printf("你想将它转化为几进制的数字: ");
    scanf("%d", &hex);
    //进行进制转换
    saveResults = hexConverter(decimalNum, hex);
    //打印转换完成的数
    printStackThings(saveResults, hex);
    return 0;
}