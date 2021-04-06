#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//MACHINE可以根据自己的机器以及编译器进行调整,以最大程度利用空间
#define MACHINE 8
struct StrNode;
typedef struct StrNode *PStrNode;
struct StrNode{
    char c[MACHINE];
    PStrNode next;
};
typedef struct StrNode *LinkString;

//创建带头结点的空链表
LinkString createNullStr_link(void){
    LinkString s;
    s = (LinkString)malloc(sizeof(struct StrNode));
    if(s!=NULL){
        s->next = NULL;
    }
    else{
        printf("Out of space!\n");
    }
    return s;
}

//检测是否为空字符串    带头节点
int isNullStr_link(PStrNode s){
    return (s->next==NULL);
}

//返回字符串的长度      带头结点
int length(PStrNode s){
    int counter=0, i;
    PStrNode p;
    p = s->next;
    while(p->next!=NULL){
        for(i=0;i<MACHINE;i++){
            if(p->c[i]=='\0'){
                break;
            }
        }
        if(i==MACHINE-1){
            counter += MACHINE-1;
        }
        else{
            counter += i;
        }
        p = p->next;
    }
    for(i=0;i<MACHINE;i++){
        if(p->c[i]=='\0'){
            break;
        }
    }
    return (i+counter);
}

//赋值处理
int assign(PStrNode s, char *a){
    int i=0;
    if(strlen(a)>MACHINE-1){
        printf("最多容许%d个字符,请减少字符数量\n", MACHINE-1);
        return 0;
    }
    while(1){
        if(a[i]=='\0'){
            break;
        }
        s->c[i] = a[i];
        i++;
    }
    if(strlen(a)<MACHINE){
        s->c[strlen(a)] = '\0';
    }
    return 1;
}


//打印字符串    带头结点
int printStr(PStrNode s){
    if(s==NULL){
        printf("数据不合法,请检查!\n");
        return 0;
    }
    while(s->next!=NULL){
        printf("%s", s->next->c);
        s = s->next;
    }
    printf("%s\n", s->next->c);
    printf("\n");
    return 1;
}

//返回将串m和串n拼接在一起的新串    带头结点
PStrNode concat(PStrNode m, PStrNode n){
    PStrNode s, link, s1, s2;
    int i, j, counter1, counter2;
    s1 = m->next;
    s2 = n->next;
    link = createNullStr_link();
    s = createNullStr_link();
    link->next = s;
    counter1 = length(m);
    counter2 = length(n);
    //处理s1
    while(s1->next!=NULL){
        for(i=0;i<MACHINE;i++){
            s->c[i] = s1->c[i];
            counter1--;
        }
        s->next = createNullStr_link();
        s = s->next;
        s1 = s1->next;
    }
    i=0;
    while (counter1>=i)
    {
        s->c[i] = s1->c[i];
        i++;
    }
    //处理s2
    while(s2->next!=NULL){
        i = counter1;
        for(j=0;j<(MACHINE-1);j++){
            s->c[i] = s2->c[j];
            counter2--;
            if(i==MACHINE-2){
                s->c[MACHINE-1] = '\0';
                i = 0;
                s->next = createNullStr_link();
                s = s->next;
            }
            else{
                i++;
            }
        }
        s2 = s2->next;
        counter2--;
    }
    j = 0;
    while (j<=counter2)
    {
        s->c[i] = s2->c[j];
        if(i==MACHINE-2){
            s->c[MACHINE-1] = '\0';
            i = -1;
            s->next = createNullStr_link();
            s = s->next;
        }
        i++;
        j++;
    }
    s->next = NULL;
    return link;
}

//在串m中,求从串的第一个字符开始连续j个字符所构成的字符串
PStrNode subStr(PStrNode m, int i, int j){
    int len, times, begin, counter=0, x, y=0;
    PStrNode p, q, s;
    s = m->next;
    q = createNullStr_link();
    p = createNullStr_link();
    q->next = p;
    len = length(m);
    if(i+j-1>len){
        printf("输入越界,请检查后输入\n");
        return NULL;
    }
    times = i / (MACHINE-1);
    while(times>0){
        times--;
        s = s->next;
    }
    begin = i - 1 - times * (MACHINE-1);
    while(1){
        for(x=0;x<MACHINE-1;x++){
            p->c[x] = s->c[begin];
            counter++;
            begin++;
            if(begin==MACHINE-1 || s->c[begin]=='\0'){
                begin = 0;
                s = s->next;
            }
            if(counter==j){
                goto label1;
            }
        }
        p->c[MACHINE-1] = '\0';
        p->next = createNullStr_link();
        p = p->next;
    }
    label1: p->c[x+1] = '\0';
    return q;
}

//如果串s2为s1的子串,则可求字串s2在s1中第一次出现的位置
//带回溯的算法,非KMP算法    KMP算法待补充
int indexTest(PStrNode s1, PStrNode s2){
    PStrNode m1, m2;
    int i=0, j=0, len1, len2, counter=0, jTimes=0;
    m1 = s1->next;
    m2 = s2->next;
    len1 = length(s1);
    len2 = length(s2);
    while(i<len1 && j<len2)
    {
        if(i==MACHINE-1 || m1->c[i]=='\0'){
            len1 -= i;
            i = 0;
            m1 = m1->next;
        }
        if(j==MACHINE-1 || m2->c[j]=='\0'){
            jTimes += j;
            len2 -= j;
            j = 0;
            m2 = m2->next;
        }
        if(m1->c[i]==m2->c[j]){
            j++;
            i++;
            counter++;
        }
        else{
            i = i - j + 1;
            j = 0;
            counter++;
        }
    }
    if(j==len2){
        return (counter-j-jTimes+1);
    }
    else{
        return 0;
    }
}

//测试用例
int main(){
    PStrNode s1, s2, s3, s4;
    int i, j;
    s1 = createNullStr_link();
    s2 = createNullStr_link();
    s1->next = createNullStr_link();
    s1->next->next = createNullStr_link();
    s2->next = createNullStr_link();
    s2->next = createNullStr_link();
    s2->next->next = createNullStr_link();
    s4 = s2->next->next;
    s4->next = createNullStr_link();
    assign(s1->next, "youok ");
    assign(s1->next->next, "?hahah");
    assign(s2->next, "sam");
    assign(s2->next->next, "test");
    assign(s4->next, "@jwhan");
    //printf("%d", length(s2->next));
    //printStr(s1);
    //printStr(concat(s1, s2));
    s3 = subStr(s2, 3, 8);
    printf("s3's key is ");
    printStr(s3);
    printf("s2's key is ");
    printStr(s2);
    printf("s2's length is %d.\n", length(s2));
    printf("%d", indexTest(s2, s3));
    return 0;
}