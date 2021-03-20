#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
#define N 6


struct Student{
    int index;
    char name[20];
    int id;
    int math;
    int DataStructure;
};
typedef struct Student DataType;

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
        if(palist->element[q].DataStructure==x.DataStructure && palist->element[q].id==x.id &&
          palist->element[q].index==x.index && palist->element[q].math==x.math && 
          !strcpy(palist->element[q].name, x.name)){
            return q;
        }
    return -1;
}


//顺序表的插入
int insertPre_seq(PSeqList palist, int p, DataType x){
    //在palist所指顺序表中下表为p的元素之前插入元素
    int q;
    if(palist->n>=palist->MAXNUM){      //溢出
        printf("Overflow!\n");
        return 0;
    }
    if(p<0||p>palist->n)        //显然不存在下表为p的元素
        printf("Not exist!\n");
    return 0;
    for(q=palist->n-1;q>=p;q--){
        palist->element[q+1] = palist->element[q];
    }
    palist->element[p] = x;
    palist->n+=1;
    return 1;
}

int insertPost_seq(PSeqList palist, int p, DataType x){
    int q;
    if(palist->n>palist->MAXNUM)
        printf("Overflow!\n");
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

//第五题
int main(){
    int i;
    PSeqList class = creatNullList_seq(MAX);
    class->n = N;
    for(i=0;i<N;i++){
        class->element[i].id = i+1;
        class->element[i].index = i+1;
    }
    class->element[0].math = 65;
    class->element[1].math = 45;
    class->element[2].math = 23;
    class->element[3].math = 12;
    class->element[4].math = 12;
    class->element[5].math = 87;
    class->element[0].DataStructure = 90;
    class->element[1].DataStructure = 60;
    class->element[2].DataStructure = 70;
    class->element[3].DataStructure = 60;
    class->element[4].DataStructure = 12;
    class->element[5].DataStructure = 99;
    strcpy(class->element[0].name, "张三");
    strcpy(class->element[1].name, "李四");
    strcpy(class->element[2].name, "小王");
    strcpy(class->element[3].name, "大军");
    strcpy(class->element[4].name, "钱芳");
    strcpy(class->element[5].name, "大刘");
    printf("编号\t姓名\t学号\t数学成绩\t数据结构成绩\t\n");
    for(i=0;i<N;i++){
        printf("%d\t%s\t%d\t%d\t\t%d\n",class->element[i].index, class->element[i].name, class->element[i].id,
          class->element[i].math, class->element[i].DataStructure);
    }
    return 0;
}
