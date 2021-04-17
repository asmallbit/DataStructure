#include <stdio.h>
#include <stdlib.h>
#define ROW 10
#define CAL 10
/*
//本程序和上一个用栈实现的区别是,用队列的形式存储移动方式的坐标,这样就不用经过后续的翻转的操作.
//即二者的区别仅是存储最后结果的方式不同而已
*/
//迷宫的一行
struct MazeRow;
typedef struct MazeRow *PMazeRow;
struct MazeRow
{
    int *x;
    PMazeRow next;
};
typedef struct MazeRow *PMaze;

//存放移动过程的栈
struct Move;
typedef struct Move *PMove;
struct Move
{
    int up;
    int down;
    int left;
    int right;
    PMove next;
};

//存放坐标
struct XY
{
    int x;
    int y;
};
typedef struct XY XY;

//存放队列头和尾的指针的结构体
struct Queue
{
    PMove head;
    PMove tail;
};
typedef struct Queue *PQueue;

//初始化迷宫的一行
PMaze initMazeRow(int x)
{
    PMaze new;
    int i;
    new = (PMaze)malloc(sizeof(struct MazeRow));
    if (new != NULL)
    {
        new->x = (int *)malloc(sizeof(int) * x);
        if (new->x != NULL)
        {
            for (i = 0; i < CAL; i++)
            {
                new->x[i] = 0;
            }
            new->next = NULL;
            return new;
        }
        free(new);
    }
    return NULL;
}

//设置迷宫的通路,参数分别为迷宫的指针,要修改的行,要修改的列
int setMaze(PMaze p, int row, int cal)
{
    int j;
    for (j = 0; j < row; j++)
    {
        if (p->next == NULL)
        {
            printf("迷宫没有此坐标,适当减小输入的值得大小\n");
            return 0;
        }
        p = p->next;
    }
    p->x[cal - 1] = 1;
    return 1;
}

//返回迷宫确定坐标下的值
int getKey(PMaze p, int cal, int row)
{
    int j;
    //任何一个坐标越界,则直接返回-1
    if (row < 0 || cal < 0 || row >= ROW || cal >= CAL)
    {
        return -1;
    }
    for (j = 0; j < row; j++)
    {
        if (p->next == NULL)
        {
            return -1;
        }
        p = p->next;
    }
    return p->x[cal];
}

//设置记录路线的队列
PMove creatQueue(void)
{
    PMove move;
    move = (PMove)malloc(sizeof(struct Move));
    if (move != NULL)
    {
        move->next = NULL;
        return move;
    }
    printf("Out of space!\n");
    return NULL;
}

//创建指向记录的路线的指针的结构体
PQueue creatPointer(void)
{
    PQueue new;
    new = (PQueue)malloc(sizeof(struct Queue));
    if (new != NULL)
    {
        new->head = NULL;
        new->tail = NULL;
        return new;
    }
    printf("Out of space!\n");
    return NULL;
}

//标记已走过的路线
void labelPast(PMaze p, int x, int y)
{
    int counter;
    for (counter = 0; counter < y; counter++)
    {
        p = p->next;
    }
    p->x[x] = 2;
}

//入队
int enQueue(PQueue p, int *x)
{
    PMove new, temp;
    new = creatQueue();
    new->up = x[0];
    new->down = x[1];
    new->left = x[2];
    new->right = x[3];
    new->next = NULL;
    if (p->head == NULL)
    {
        p->head = p->tail = new;
        return 1;
    }
    temp = p->tail;
    p->tail = new;
    temp->next = new;
    return 1;
}

//出队
int deQueue(PQueue p)
{
    PMove temp;
    if (p->head == NULL)
    {
        //printf("This is an empty stack!\n");
        return 0;
    }
    temp = p->head;
    p->head = temp->next;
    free(temp);
    return 1;
}

//类似栈的出队
int deQueue2(PQueue p)
{
    PMove temp;
    if (p->head == NULL)
    {
        return 0;
    }
    if (p->head->next == NULL)
    {
        free(p->head);
        p->head = p->tail = NULL;
        return 0;
    }
    temp = p->head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    p->tail = temp;
    free(temp->next);
    temp->next = NULL;
    return 1;
}

//探索迷宫
PQueue mazeExplore(PMaze p, PQueue move, int beginx, int beginy, int endx, int endy)
{
    PMove begin;
    PMaze pcopy, pcopynode;
    XY xy;
    int flag = 0, moving[4], i, j = 0;
    //创建迷宫p的副本,避免直接修改原迷宫
    pcopynode = initMazeRow(CAL);
    while (p->next != NULL)
    {
        for (i = 0; i < CAL; i++)
        {
            pcopynode->x[i] = p->x[i];
        }
        if (j == 0)
        {
            j++;
            pcopy = pcopynode;
        }
        pcopynode->next = initMazeRow(CAL);
        pcopynode = pcopynode->next;
        p = p->next;
    }
    for (i = 0; i < CAL; i++)
    {
        pcopynode->x[i] = p->x[i];
    }
    //设置坐标的初始值(起点)
    xy.x = beginx;
    xy.y = beginy;
    //将起点做标记
    labelPast(pcopy, xy.x, xy.y);
    while (!flag)
    {
        //上下左右四个移动方向
        if (getKey(pcopy, xy.x, xy.y - 1) != 0 && getKey(pcopy, xy.x, xy.y - 1) != -1 && getKey(pcopy, xy.x, xy.y - 1) != 2)
        {
            moving[0] = 1;
            moving[1] = 0;
            moving[2] = 0;
            moving[3] = 0;
            enQueue(move, moving);
            xy.y -= 1;
            labelPast(pcopy, xy.x, xy.y);
        }
        else if (getKey(pcopy, xy.x, xy.y + 1) != 0 && getKey(pcopy, xy.x, xy.y + 1) != -1 && getKey(pcopy, xy.x, xy.y + 1) != 2)
        {
            moving[0] = 0;
            moving[1] = 1;
            moving[2] = 0;
            moving[3] = 0;
            enQueue(move, moving);
            xy.y += 1;
            //走过的路线最标记
            labelPast(pcopy, xy.x, xy.y);
        }
        else if (getKey(pcopy, xy.x - 1, xy.y) != 0 && getKey(pcopy, xy.x - 1, xy.y) != -1 && getKey(pcopy, xy.x - 1, xy.y) != 2)
        {
            moving[0] = 0;
            moving[1] = 0;
            moving[2] = 1;
            moving[3] = 0;
            enQueue(move, moving);
            xy.x -= 1;
            labelPast(pcopy, xy.x, xy.y);
        }
        else if (getKey(pcopy, xy.x + 1, xy.y) != 0 && getKey(pcopy, xy.x + 1, xy.y) != -1 && getKey(pcopy, xy.x + 1, xy.y) != 2)
        {
            moving[0] = 0;
            moving[1] = 0;
            moving[2] = 0;
            moving[3] = 1;
            enQueue(move, moving);
            xy.x += 1;
            labelPast(pcopy, xy.x, xy.y);
        }
        else
        {
            //若为已走过路线,则出栈
            if (move->tail->up == 1)
            {
                xy.y += 1;
            }
            if (move->tail->down == 1)
            {
                xy.y -= 1;
            }
            if (move->tail->left == 1)
            {
                xy.x += 1;
            }
            if (move->tail->right == 1)
            {
                xy.x -= 1;
            }
            deQueue2(move);
        }
        if (xy.x == endx && xy.y == endy)
        {
            flag = 1;
        }
    }
    return move;
}

//打印迷宫
void printMaze(PMaze p)
{
    int i;
    while (1)
    {
        for (i = 0; i < CAL; i++)
        {
            printf("%d ", p->x[i]);
        }
        printf("\n");
        if (p->next == NULL)
        {
            break;
        }
        p = p->next;
    }
}

//释放掉无用指针
void freePMove(PQueue p){
    PMove temp, temp2;
    temp = p->head;
    while (temp!=NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}

//测试用例
int main()
{
    PMaze maze, mazeNode;
    PQueue move;
    PMove moveNode;
    int i, counter = 0, flag = 0, a[4];
    maze = initMazeRow(CAL);
    move = creatPointer();
    for (i = 0; i < ROW; i++)
    {
        if (i == 0)
        {
            maze = mazeNode;
        }
        mazeNode->next = initMazeRow(CAL);
        mazeNode = mazeNode->next;
    }
    //创建并打印迷宫 以(0, 0)为起点,以(9, 9)为终点
    mazeNode = maze->next;
    for (i = 0; i < ROW; i++)
    {
        mazeNode->x[i] = mazeNode->x[i + 1] = 1;
        mazeNode = mazeNode->next;
    }
    mazeNode = maze->next;
    for (i = ROW; i > 0; i--)
    {
        mazeNode->x[i] = mazeNode->x[i - 1] = 1;
        mazeNode = mazeNode->next;
    }
    printf("The maze is:\n");
    printMaze(maze->next);
    printf("定义左上角为(0, 0)，右下角为(9, 9)，只可以从标为1的点走");
    printf("\n起点: (0, 0), 终点: (9, 9)");
    //探索迷宫
    move = mazeExplore(maze->next, move, 0, 0, CAL-1, ROW-1);
    if(move->head==NULL){
        printf("迷宫不正确，没有可以走出迷宫的路径\n");
        return 0;
    }
    //输出如何走出迷宫
    moveNode = move->head;
    printf("\n\nThe solve is: \n");
    while (1)
    {
        if (moveNode->up == 1)
        {
            printf("UP");
        }
        if (moveNode->down == 1)
        {
            printf("DOWN");
        }
        if (moveNode->left == 1)
        {
            printf("LEFT");
        }
        if (moveNode->right == 1)
        {
            printf("RIGHT");
        }
        if (moveNode->next == NULL)
        {
            break;
        }
        printf("->");
        moveNode = moveNode->next;
    }
    printf("\n打印出的路径并不一定是最短路径,不过顺着这个路径就可以走出迷宫\n");
    //释放空间
    freePMove(move);
    free(move);
    return 0;
}