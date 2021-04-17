#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//创建一个返回结果的结构体
struct FinalResult;
typedef struct FinalResult *PFinalResult;
struct FinalResult
{
    char s;
    PFinalResult next;
};

//创建一个用于存储中间结果的结构体
struct TempStore;
typedef struct TempStore *PTempStore;
struct TempStore
{
    int index;
    int data;
    PTempStore next;
};

//创建一个空的用于存储返回结果的列表
PFinalResult creatEmptyResult(void)
{
    PFinalResult new;
    new = (PFinalResult)malloc(sizeof(struct FinalResult));
    if (new != NULL)
    {
        new->next = NULL;
        return new;
    }
    printf("Out of space!\n");
    return NULL;
}

//创建一个临时变量链表
PTempStore creatNullList(void)
{
    PTempStore new;
    new = (PTempStore)malloc(sizeof(struct TempStore));
    if (new != NULL)
    {
        new->next = NULL;
        return new;
    }
    printf("Out of space!\n");
    return NULL;
}

//寻找临时变量链表中的元素的最大值对应的坐标
int getMaxIndex(PTempStore p)
{
    p = p->next;
    int max = p->data;
    PTempStore result;
    result = p;
    while (p->next != NULL)
    {
        if (p->data > max)
        {
            result = p;
            max = p->data;
        }
        p = p->next;
    }
    if (p->data > max)
    {
        result = p;
    }
    return result->index;
}

//寻找临时变量链表中元素的最大值
int getMax(PTempStore p)
{
    p = p->next;
    int max = p->data;
    while (p->next != NULL)
    {
        if (p->data > max)
        {
            max = p->data;
        }
        p = p->next;
    }
    if (p->data > max)
    {
        max = p->data;
    }
    return max;
}

//查找两个字符串中最长的公共子串
PFinalResult getMaxLengthStr(char *p1, char *p2, int l1, int l2, PFinalResult p)
{
    int i, j, result, m, tempi, theBeginIndex, theEndIndex, counter = 0, temp1, temp2, tempj, tempIndex;
    PTempStore length, index, lengthc, indexc;
    PFinalResult finalresult;
    length = creatNullList();
    index = creatNullList();
    lengthc = creatNullList();
    indexc = creatNullList();
    length->next = lengthc;
    index->next = indexc;
    indexc->index = lengthc->index = -1;
    finalresult = (PFinalResult)malloc(sizeof(struct FinalResult));
    for (i = 0; i < l1; i++)
    {
        tempi = i;
        j = 0;
        result = 0;
        while (j < l2)
        {
            if (p1[i] == p2[j])
            {
                result += 1;
                i++;
                j++;
                if (j == l2)
                {
                    lengthc->data = result;
                    lengthc->index++;
                    temp2 = lengthc->index;
                    lengthc->next = creatNullList();
                    lengthc = lengthc->next;
                    lengthc->index = temp2;
                    if (result == 1)
                    {
                        indexc->data = i - 1;
                        indexc->index++;
                        temp1 = indexc->index;
                        indexc->next = creatNullList();
                        indexc = indexc->next;
                        indexc->index = temp1;
                        tempj = j;
                    }
                    result = 0;
                }
                if (result == 1)
                {
                    indexc->data = i - 1;
                    indexc->index++;
                    temp1 = indexc->index;
                    indexc->next = creatNullList();
                    indexc = indexc->next;
                    indexc->index = temp1;
                    tempj = j;
                }
            }
            else if (p1[i] != p2[j] && result != 0)
            {
                lengthc->data = result;
                lengthc->index++;
                temp2 = lengthc->index;
                lengthc->next = creatNullList();
                lengthc = lengthc->next;
                lengthc->index = temp2;
                result = 0;
                i = tempi;
                j = tempj;
            }
            else
            {
                j++;
            }
        }
        i = tempi;
    }
    //如果length链表为空
    if (length->next->next == NULL)
    {
        return NULL;
    }
    //将冗余节点存储的值化为0
    lengthc->data = 0;
    //求出最长共有字串的长度
    m = getMax(length);
    //找出最大长度对应的起始坐标
    tempIndex = getMaxIndex(length);
    for (i = 0; i <= tempIndex; i++)
    {
        index = index->next;
    }
    theBeginIndex = index->data;
    theEndIndex = theBeginIndex + m;
    if (m == 0)
    {
        return NULL;
    }
    //申请一块存储返回字符串的指针
    p = creatEmptyResult();
    finalresult = p;
    while (1)
    {
        p->s = p1[theBeginIndex];
        theBeginIndex++;
        if (theBeginIndex == theEndIndex)
        {
            break;
        }
        p->next = creatEmptyResult();
        p = p->next;
    }
    return finalresult;
}

//存储输入的值值(动态分配空间)
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

int main()
{
    int l1, l2;
    printf("Please input the first string: ");
    char *x = getString();
    printf("Please input the second string: ");
    char *y = getString();
    l1 = strlen(x);
    l2 = strlen(y);
    PFinalResult result, rest;
    result = getMaxLengthStr(x, y, l1, l2, result);
    rest = result;
    if (result != NULL)
    {
        printf("The greatest substring is: ");
        //输出最长的子字符串
        while (result->next != NULL)
        {
            printf("%c", result->s);
            result = result->next;
        }
        printf("%c", result->s);
        //释放掉无用指针
        while (rest->next != NULL)
        {
            result = rest->next;
            free(rest);
            rest = result;
        }
        free(rest);
    }
    else
    {
        printf("There no substring between these two strings.\n");
    }
    return 0;
}