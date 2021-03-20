#include<stdio.h>
#include<stdlib.h>
#define MAX 50
#define N 40

typedef int DataType;

struct SeqList
{
    int MAXNUM;         //顺序表中最大元素的个数
    int n;              //存放线性表中元素的个数n<=MAXNUM
    DataType *element;  //elemen[0], element[1]..., element[n-1]存放线性表中元素的个数
};
typedef struct SeqList *PSeqList;

//创建空顺序表
PSeqList creatNullList_seq(int m){
    PSeqList palist = (PSeqList)malloc(sizeof(struct SeqList));
    if(palist!=NULL){
        palist->element = (DataType*)malloc(sizeof(DataType)*m);
        if(palist->element){
            palist->MAXNUM = m;
            palist->n = 0;          //空表的长度为0
            return palist;
        }
        else
            free(palist);
    }
    printf("Out of space!\n");
    return NULL;
}

//判断线性表是否为空
int isNullList_seq(PSeqList palist){
    return (palist->n==0);
}

//在顺序表中求某元素的下标
int locate_seq(PSeqList palist, DataType x){
    //求x在palist所指顺序表的下标
    int q;
    for(q=0;q<palist->n;q++)
        if(palist->element[q]==x)
            return q;
    return -1;
}

//顺序表的插入(前插)
int insertPre_seq(PSeqList palist, int p, DataType x){
    //在palist所指顺序表中下标为p的元素之前插入元素
    int q;
    if(palist->n>=palist->MAXNUM){      //溢出
        printf("Overflow!\n");
        return 0;
    }
    if(p<0||p>palist->n){        //显然不存在下标为p的元素
        printf("Not exist!\n");
        return 0;
    }
    for(q=palist->n-1;q>=p;q--){
        palist->element[q+1] = palist->element[q];
    }
    palist->element[p] = x;
    palist->n+=1;
    return 1;
}

//顺序表插入(后插)
int insertPost_seq(PSeqList palist, int p, DataType x){
    //在palist所指顺序表中下标为p的元素之后插入元素
    int q;
    if(palist->n>palist->MAXNUM){
        printf("Overflow!\n");
        return 0;
    }
    if(p<0||p>(palist->n)-1){
        printf("Not exist!\n");
        return 0;
    }
    for(q=palist->n-1;q>=p+1;q--)
        palist->element[q+1] = palist->element[q];
    palist->element[p+1]=x;
    (palist->n)+=1;
    return 1;
}

//删除下标为p的元素
int deleteP_seq(PSeqList palist, int p){
    int q;
    if(p<0||p>(palist->n)-1){
        printf("Not exist!\n");          //不存在元素下标为p的元素
        return 0;
    }
    for(q=p+1;q<palist->n;q++){
        palist->element[q-1]=palist->element[q];
    }
    palist->n-=1;                       //元素个数减1
    return 1;
}

//删除值为x的元素
int deleteV_seq(PSeqList palist, DataType x){
    int q = locate_seq(palist, x);
    deleteP_seq(palist, q);
}

int main(){
    int i, j=22;
    PSeqList class4 = creatNullList_seq(MAX);
    /*
    if(isNullList_seq(class4)){
        printf("Yes, it's null list.\n");
    }
    else{
        printf("No, it's not null list.");
    }
    */
    class4->n = N;
    if(!isNullList_seq(class4)){
        printf("Good, it's not a null list!\n");
    }
    //第2题 打印原表
    for(i=1;i<=N;i++){
        (class4->element)[i-1]=i;
        printf("%d\t",class4->element[i-1]);
    }
    //第3题 删除
    if(deleteP_seq(class4, 0)){
        printf("\nDelete succeed!\nHere is the list now:\n");
        for(i=0;i<N-1;i++){
            printf("%d\t",class4->element[i]);
        }
    }
    //插入元素(前插)
    if(insertPre_seq(class4, 0, 1)){
        printf("\nInsert(Pre) succeed!\nHere is the list now:\n");
        for(i=0;i<N;i++){
            printf("%d\t",class4->element[i]);
        }
    }
    //删除值为21的元素
    if(deleteV_seq(class4, 21)){
        printf("\nDeleta succeedly!\nHere is the list now:\n");
        for(i=0;i<N-1;i++){
            printf("%d\t",class4->element[i]);
        }
    }
    //插入元素(后插)
    if(insertPost_seq(class4, 19, 21)){
        printf("\nInsert(Post) succeed!\nHere is the list now:\n");
        for(i=0;i<N;i++){
            printf("%d\t",class4->element[i]);
        }
    }
    //求某一元素的下标
    i = locate_seq(class4, j);
    if(i!=-1){
        printf("\nThe %d is the %d number.", j, i);
    }
    else{
        printf("\nSorry, the number %d is not exist.", j);
    }
    return 0;
}
