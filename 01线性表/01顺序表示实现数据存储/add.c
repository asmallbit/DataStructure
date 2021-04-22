#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Polynomial;
typedef struct Polynomial *PPolynomialNode;
struct Polynomial{
    int index, coff;
    PPolynomialNode next;
};
typedef struct Polynomial *PPolynomial;

//创建一个空表用于存储数据
PPolynomial creatNullList(void){
    PPolynomial new;
    new = (PPolynomial)malloc(sizeof(struct Polynomial));
    if(new!=NULL){
        new->next = NULL;
        return new;
    }
    printf("Out of space.\n");
    return NULL;
}

//插入一个线性表
int push(PPolynomial p, int i, int c){
    PPolynomialNode new;
    new = creatNullList();
    if(new==NULL){
        return 0;
    }
    new->index = i;
    new->coff = c;
    if(p->next==NULL){
        p->next = new;
    }
    else{
        while(p->next!=NULL){
            p = p->next;
        }
        p->next = new;
    }
    return 1;
}

//接受用户输入
char *getString()
{
    char *str1;
    char *str2;
    int i = 1;
    str1 = (char *)malloc(sizeof(char) * (i + 1));
    while ('\n' != (str1[i - 1] = getchar()))
    {
        i++;
        str2 = (char *)malloc(strlen(str1) + 1);
        str1[i - 1] = '\0';
        strcpy(str2, str1);
        free(str1);
        str1 = (char *)malloc(sizeof(char) * (i + 1));
        if (NULL == str1)
        {
            free(str2);
            printf("No enough memory!");
            return NULL;
        }
        strcpy(str1, str2);
        free(str2);
    }
    str1[i - 1] = '\0';
    return str1;
}

//释放指针
void freePointer(PPolynomial p){
    PPolynomialNode temp;
    temp = p;
    while(temp!=NULL){
        p = temp->next;
        free(temp);
        temp = p;
    }
}

//测试用例
int main(){
    char *input1, *input2;
    PPolynomial first, second, p1, p2, result, resultNode;
    int temp, index=-1, flag=0, indextemp, cofftemp;
    first = p1 = creatNullList();
    second = p2 = creatNullList();
    resultNode = result = creatNullList();
    printf("Please input the first Polynomial. Example 2,3,4,5 means 2+3x^1+4x^2+5x^3\n");
    input1 = getString();
    printf("Please input the first Polynomial. Example 2,3,4,5 means 2+3x^1+4x^2+5x^3\n");
    input2 = getString();
    while(*input1!='\0'){
        while(*input1==',' || *input1==' '){
            input1++;
        }
        if(*input1<'0' || *input1>'9'){
            printf("Wrong input, please check your input again!\n");
            break;
        }
        index++;
        temp = *input1 - '0';
        push(p1, index, temp);
        input1++;
    }
    index = -1;
    while(*input2!='\0'){
        while(*input2==',' || *input2==' '){
            input2++;
        }
        if(*input2<'0' || *input2>'9'){
            printf("Wrong input, please check your input again!\n");
            break;
        }
        index++;
        temp = *input2 - '0';
        push(p2, index, temp);
        input2++;
    }
    p1 = p1->next;
    p2 = p2->next;
    //开始相加
    while(p1!=NULL || p2!=NULL || flag==0){
        if(p1==NULL){
            flag = 1;
            break;
        }
        if(p2==NULL){
            flag = 2;
            break;
        }
        indextemp = p1->index;
        cofftemp = p1->coff + p2->coff;
        push(result, indextemp, cofftemp);
        p1 = p1->next;
        p2 = p2->next;
    }
    if(flag==1){
        while(p2!=NULL){
            push(result, p2->index, p2->coff);
            p2 = p2->next;
        }
    }
    if(flag==2){
        while(p1!=NULL){
            push(result, p1->index, p1->coff);
            p1 = p1->next;
        }
    }
    //计算完成,输出结果
    resultNode = resultNode->next;
    printf("The result is:\n");
    while(resultNode!=NULL){
        printf("%dx^%d", resultNode->coff, resultNode->index);
        if(resultNode->next!=NULL){
            printf("+");
        }
        resultNode = resultNode->next;
    }
    //释放指针
    freePointer(first);
    freePointer(second);
    freePointer(result);
    return 0;
}