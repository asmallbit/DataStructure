#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GradeNode;
typedef struct GradeNode *PGradeNode;
struct GradeNode
{
    int grade;
    char name[20];
    PGradeNode next;
};
typedef struct GradeNode *PGrade;

//创建空的成绩表
PGrade creatNullList(void)
{
    PGrade new;
    new = (PGrade)malloc(sizeof(struct GradeNode));
    if (new != NULL)
    {
        new->next = NULL;
        return new;
    }
    printf("当前系统内存不足!\n");
    return NULL;
}

//求索引
PGradeNode findIndex(PGrade p, char *name)
{
    int flag = 0, counter1 = 0, counter2 = 0;
    p = p->next;
    while (p != NULL)
    {
        //判断两个名字是否相同
        while (counter2 < 20 && name[counter2] != '\0')
        {
            if (name[counter1] == p->name[counter1])
            {
                counter1++;
            }
            counter2++;
        }
        if (counter1 == counter2 && name[counter1] == '\0')
        {
            flag = 1;
        }
        if (flag == 1)
        {
            return p;
        }
        p = p->next;
    }
    printf("此名字不在名单中,请检查你的输入\n");
    return NULL;
}

//初始化第一个变量
int initList(PGrade p, int x, char *n)
{
    PGrade new, index, indexnext;
    new = creatNullList();
    if (new == NULL)
    {
        printf("当前系统内存不足!\n");
        return 0;
    }
    new->grade = x;
    strcpy(new->name, n);
    p->next = new;
    return 1;
}

//插入 后插
int enList(PGrade p, int x, char *n, char *name)
{
    PGrade new, index, indexnext;
    new = creatNullList();
    if (new == NULL)
    {
        printf("当前系统内存不足!\n");
        return 0;
    }
    new->grade = x;
    strcpy(new->name, n);
    index = findIndex(p, name);
    if (index == NULL)
    {
        return 0;
    }
    indexnext = index->next;
    index->next = new;
    new->next = indexnext;
    return 1;
}

//删除
int deList(PGrade p, char *name)
{
    PGrade index, indexnext;
    if (p->next == NULL)
    {
        printf("对不起,当前成绩表为空,无法执行删除操作\n");
        return 0;
    }
    index = findIndex(p, name);
    if (index == NULL)
    {
        return 0;
    }
    indexnext = index->next;
    //考虑为最后一个位置的情况
    if (indexnext == NULL)
    {
        free(indexnext);
        index->next = NULL;
    }
    else
    {
        index->next = indexnext->next;
        free(indexnext);
    }
    return 1;
}

//假设统计的功能为计算成绩的最大值与最小值,与计算中位数
//求最大值的节点
PGradeNode getMax(PGrade p)
{
    if (p->next == NULL)
    {
        printf("Sorry, it's an empty list!\n");
        return NULL;
    }
    p = p->next;
    int max = p->grade;
    PGradeNode maxnum = p;
    while (p->next != NULL)
    {
        if (p->grade > max)
        {
            max = p->grade;
            maxnum = p;
        }
        p = p->next;
    }
    if (p->grade > max)
    {
        maxnum = p;
    }
    return maxnum;
}

//求最小值
PGradeNode getMin(PGrade p)
{
    if (p->next == NULL)
    {
        printf("Sorry, it's an empty list!\n");
        return NULL;
    }
    p = p->next;
    int min = p->grade;
    PGradeNode minnum = p;
    while (p->next != NULL)
    {
        if (p->grade < min)
        {
            min = p->grade;
            minnum = p;
        }
        p = p->next;
    }
    if (p->grade < min)
    {
        minnum = p;
    }
    return minnum;
}

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
    PGrade grade, gradeNode, temp;
    PGradeNode index;
    int i, j, counter = -1, thegrade, status;
    char option, name[20], name2[20], *get;
    grade = creatNullList();
    gradeNode = grade->next = creatNullList();
    gradeNode->grade = 99;
    strcpy(gradeNode->name, "张三");
    //暂时不涉及交互界面,采用直接赋值方式
    //直接采用循环:>
    option = 'a';
    printf("************成绩管理系统************\n");
    //开始设置用户界面
    while (option != 'q')
    {
    label1:
        printf("菜单:\n1.执行插入操作\n2.执行删除操作\n3.查询最大值\n4.查询最小值\n5.查询某个同学的成绩\n6.打印当前成绩表\n如要退出请输入9\n");
        printf("请输入您需要的操作:  ");
    label2:
        get = getString();
        //插入操作
        if (strcmp(get, "1") == 0)
        {
            counter++;
            if (counter == 0)
            {
                printf("请输入你要加入的第一个学生的姓名: ");
                scanf("%s", name);
                printf("请输入这个学生的成绩: ");
                scanf("%d", &thegrade);
                status = initList(grade, thegrade, name);
            }
            else
            {
                printf("请输入你要加入的学生的姓名: ");
                scanf("%s", name);
                printf("请输入这个学生的成绩: ");
                scanf("%d", &thegrade);
                printf("请输入您要插入在那个学生的后面,请输入当前列表中的任意一个人的姓名: ");
                scanf("%s", name2);
                status = enList(grade, thegrade, name, name2);
            }
            if (status)
            {
                printf("插入成功\n");
            }
            else
            {
                printf("插入失败\n");
            }
        }
        //删除操作
        else if (strcmp(get, "2") == 0)
        {
            printf("请输入你要删除的学生的姓名: ");
            scanf("%s", name);
            status = deList(grade, name);
            if (status)
            {
                printf("删除成功\n");
            }
            else
            {
                printf("删除失败\n");
            }
        }
        //求最大值
        else if (strcmp(get, "3") == 0)
        {
            gradeNode = getMax(grade);
            printf("当前最高成绩是: %d, 对应的学生是: %s\n", gradeNode->grade, gradeNode->name);
        }
        //求最小值
        else if (strcmp(get, "4") == 0)
        {
            gradeNode = getMin(grade);
            printf("当前最低成绩是: %d, 对应的学生是: %s\n", gradeNode->grade, gradeNode->name);
        }
        //查询某个同学的成绩
        else if(strcmp(get, "5")==0){
            printf("请输入要查询的同学姓名: ");
            scanf("%s", name);
            index = findIndex(grade, name);
            if(index==NULL){
                goto label1;
            }
            printf("%s的成绩是%d\n", index->name, index->grade);
        }
        //打印当前成绩表
        else if (strcmp(get, "6") == 0)
        {
            printf("姓名\t\t成绩\n");
            gradeNode = grade->next;
            while (gradeNode != NULL)
            {
                printf("%s\t%d\n", gradeNode->name, gradeNode->grade);
                gradeNode = gradeNode->next;
            }
        }
        //退出及错误输入处理
        else
        {
            if (strcmp(get, "9") == 0)
            {
                //释放指针
                gradeNode = grade;
                while (gradeNode != NULL)
                {
                    temp = gradeNode->next;
                    free(gradeNode);
                    gradeNode = temp;
                }
                //跳出循环
                option = 'q';
            }
            else
            {
                if (strcmp(get, "\0") == 0)
                {
                    goto label2;
                }
                else
                {
                    printf("输入有误,请检查你的输入,应该输入功能前面的序号\n");
                    goto label1;
                }
            }
        }
    }
    return 0;
}
