/*
#include<stdio.h>
#include<stdlib.h>
#define MAX 50

typedef int DataType;
struct Test{
    DataType* num;
    int max;
    int n;
};
typedef struct Test *List;

//创建列表
List creatNullList(int m){
    List list;
    list = (List)malloc(sizeof(struct Test));
    list->num = (DataType*)malloc(sizeof(DataType[m]));
    if(list==NULL || list->num==NULL){
        printf("Out of space!\n");
    }
    return list;
}


//定位,根据值
int locateKey(List list, DataType x){
    int i=0;
    while (i<list->n && list->num[i]!=x)
    {
        i++;
    }
    if(list->num[i]==x){
        return i;
    }
    else{
        return 0;
    }
}

//插入(后插)
int insertPost(List list, int p, DataType x){
    int i;
    if(p<0){
        printf("Faided to insert the key!\n");
        return 0;
    }
    for(i=(list->n)-1;i>p;i--){
        list->num[i+1] = list->num[i];
    }
    (list->n++);
    return 1;
}

//删除,删除下标为p的元素
int deleteKey(List list, int p){
    int i;
    if(p<0){
        printf("Faided to delete key!\n");
        return 0;
    }
    for(i=p+1;i<list->n;i++){
        list->num[i-1] = list->num[i];
    }
    (list->n)--;
    return 1;
}
*/

//反转存储的数据
int reserveData(List list){
    List temp = (List)malloc(sizeof(struct Test));
    temp->num = (DataType*)malloc(sizeof(DataType[1]));
    int i, j;
    temp->n = temp->max = 1;
    j = list->n - 1;
    for(i=0;i<(list->n)/2;i++){
        temp->num[0] = list->num[i];
        list->num[i] = list->num[j];
        list->num[j] = temp->num[0];
        j--;
    }
    free(temp->num);
    free(temp);
    return 1;
}


/*
//打印列表
void printList(List list){
    int i=1;
    while(i<list->n+1){
        printf("%d\t", list->num[i-1]);
        if(i%10==0){
            printf("\n");
        }
        i++;
    }
}

int main(){
    List list;
    int n;
    list = creatNullList(MAX);
    list->n = MAX;
    list->max = MAX;
    for(n=0;n<MAX;n++){
        list->num[n] = n+1;
    }
    printf("调转前:\n");
    printList(list);
    reserveData(list);
    printf("调转后:\n");
    printList(list);
    return 0;
}
*/