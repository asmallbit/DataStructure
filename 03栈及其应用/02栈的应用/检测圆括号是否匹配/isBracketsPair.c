#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char DataType;

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
PLinkStack createEmptyStack_link(void)
{
    PLinkStack p;
    p = (PLinkStack)malloc(sizeof(struct LinkStack));
    if (p != NULL)
    {
        p->next = NULL;
        return p;
    }
    printf("Out of space!\n");
    return NULL;
}

//检测栈是否为空
int isEmptyStack_link(PLinkStack s)
{
    return (s->next == NULL);
}

//向栈中插入元素
int push_link(PLinkStack s, DataType m)
{
    PStackNode p;
    p = (PStackNode)malloc(sizeof(struct LinkStack));
    if (p != NULL)
    {
        p->x = m;
        p->next = s->next;
        s->next = p;
        return 1;
    }
    else
    {
        printf("Out of space!\n");
        return 0;
    }
}

//删除栈顶元素
int pop_link(PLinkStack s)
{
    if (isEmptyStack_link(s))
    {
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
DataType top_link(PLinkStack p)
{
    if (isEmptyStack_link(p))
    {
        printf("This is a empty stack.\n");
    }
    return (p->next->x);
}

//释放整个栈的空间
int freeStack(PLinkStack s)
{
    PStackNode p, q;
    p = q = s->next;
    while (p->next != NULL)
    {
        p = q->next;
        free(q);
        q = p;
    }
    free(s);
}

//判断圆括号是否匹配
int isPair(PLinkStack p)
{
    PLinkStack index;
    int x, y;
    x = y = 0;
    index = p->next;
    while (1)
    {
        if (index->x == '(')
        {
            x++;
        }
        if (index->x == ')')
        {
            y++;
        }
        if (index->next == NULL)
        {
            break;
        }
        index = index->next;
    }
    if (x == y)
    {
        return 1;
    }
    return 0;
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
    char *x;
    printf("If you want to check whether the bracket pair, please input the string: ");
    x = getString();
    int len, counter;
    PLinkStack stack;
    stack = createEmptyStack_link();
    len = strlen(x);
    for (counter = 0; counter < len; counter++)
    {
        push_link(stack, x[counter]);
    }
    //检测匹配问题
    if (isPair(stack))
    {
        printf("左右括号数量匹配\n");
    }
    else
    {
        printf("左右括号数量不匹配\n");
    }
    freeStack(stack);
    return 0;
}