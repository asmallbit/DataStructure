#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
struct BinTree;
typedef struct BinTree *PBinTreeNode;
struct BinTree
{
    DataType info, ltag, rtag;
    PBinTreeNode llink, rlink, next;
};
typedef struct BinTree *PBinTree;

//初始化二叉树根节点
PBinTree creatBinTree(void)
{
    PBinTree new;
    new = (PBinTree)malloc(sizeof(struct BinTree));
    if (new != NULL)
    {
        new->llink = new->rlink = new->next = NULL;
        //0代表无子树
        new->ltag = new->rtag = 0;
        return new;
    }
    printf("Out of space!\n");
    return NULL;
}

//增加二叉树节点
int pushBinTree(PBinTree p, DataType x)
{
    //边界条件
    if (p->llink == NULL && x <= p->info)
    {
        //加到左子树的下面
        p->llink = creatBinTree();
        if (!p->llink)
        {
            return 0;
        }
        p->llink->info = x;
        return 1;
    }
    if (p->rlink == NULL && x > p->info)
    {
        p->rlink = creatBinTree();
        if (!p->rlink)
        {
            return 0;
        }
        p->rlink->info = x;
        return 1;
    }
    if (x <= p->info)
    {
        pushBinTree(p->llink, x);
    }
    else
    {
        pushBinTree(p->rlink, x);
    }
}

//二叉树元素入栈
int push(PBinTree p, PBinTreeNode node)
{
    PBinTreeNode temp;
    if (node == NULL)
    {
        return 0;
    }
    temp = p->next;
    p->next = node;
    node->next = temp;
    return 1;
}

//二叉树出栈
int pop(PBinTree p)
{
    PBinTreeNode temp;
    if (p->next == NULL)
    {
        printf("Empty stack\n");
        return 0;
    }
    temp = p->next;
    p->next = temp->next;
    //free(temp);
    return 1;
}

//获取栈中的顶部元素
PBinTreeNode getTop(PBinTree p)
{
    if (p->next == NULL)
    {
        printf("This is a empty stack.\n");
        return NULL;
    }
    return p->next;
}

//遍历二叉树,顺带给二叉树指针按中序遍历的方式赋值
void thread(PBinTree p)
{
    PBinTree q;
    PBinTree x, xpre;
    if (p == NULL)
    {
        printf("It's an empty bintree!\n");
        return;
    }
    q = creatBinTree(); //创建一个存储二叉树的栈
    x = p;
    xpre = NULL;
    do
    {
        while (x != NULL)
        {
            push(q, x);
            x = x->llink;
        }
        x = getTop(q);
        pop(q);
        if (xpre != NULL)
        {
            if (xpre->rlink == NULL)
            {
                xpre->rtag = 1;
                xpre->rlink = x;
            }
            if (x->llink == NULL)
            {
                x->ltag = 1;
                x->llink = xpre;
            }
        }
        xpre = x;
        x = x->rlink; //到右子树去
    } while (q->next != NULL || x != NULL);
}

//按照中序线索二叉树进行周游并打印
void printBinTree(PBinTree p)
{
    if (p == NULL)
    {
        printf("It's an empty bintree.\n");
        return;
    }
    PBinTree temp;
    temp = p;
    while (temp->llink != NULL && temp->ltag == 0)
    {
        temp = temp->llink;
    }
    while (temp != NULL)
    {
        printf("%d\t", temp->info);
        if (temp->rlink != NULL && temp->rtag == 0)
        {
            temp = temp->rlink;
            while (temp->llink != NULL && temp->ltag == 0)
            {
                temp = temp->llink;
            }
        }
        else
        {
            temp = temp->rlink;
        }
    }
}

//计算二叉树高度    递归    调用此函数前length应初始化为0
int getHeight(PBinTree p){
    //边界条件
    if(p==NULL){
        return -1;
    }
    //递归体
    int left, right;
    left = getHeight(p->llink);
    right = getHeight(p->rlink);
    return max(left, right) + 1;
}

//读入字符
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

//测试用例
int main()
{
    PBinTree p;
    char *store;
    int num, counter = 0;
    p = creatBinTree();
    printf("Please input the number you want store in BinTree\n");
    store = getString();
    //存储
    while (*store != '\0')
    {
        if (*store < 48 || *store > 57)
        {
            store++;
            continue;
        }
        if (counter == 0)
        {
            p->info = *store - '0';
            counter++;
        }
        else
        {
            pushBinTree(p, *store - '0');
        }
        store++;
    }
    //线索化二叉树
    thread(p);
    //遍历并打印二叉树
    printf("The inorder of this bintree is:\n");
    printBinTree(p);
}
