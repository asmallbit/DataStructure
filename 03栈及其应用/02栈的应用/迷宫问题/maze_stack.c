#include <stdio.h>
#include <stdlib.h>

#define ROW 10
#define CAL 10

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

//设置记录路线的栈
PMove creatStack(void)
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

//入栈,存储移动的方向的栈
int push(PMove p, int *x)
{
    PMove new, temp;
    new = creatStack();
    new->up = x[0];
    new->down = x[1];
    new->left = x[2];
    new->right = x[3];
    new->next = NULL;
    if (p->next == NULL)
    {
        p->next = new;
        return 1;
    }
    temp = p->next;
    p->next = new;
    new->next = temp;
    return 1;
}

//出栈  存储移动的方向的栈
int pop(PMove p)
{
    PMove temp;
    if (p->next == NULL)
    {
        //printf("This is an empty stack!\n");
        return 0;
    }
    temp = p->next;
    p->next = temp->next;
    free(temp);
    return 1;
}

//探索迷宫
PMove mazeExplore(PMaze p, PMove move, int beginx, int beginy, int endx, int endy)
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
            push(move, moving);
            xy.y -= 1;
            labelPast(pcopy, xy.x, xy.y);
        }
        else if (getKey(pcopy, xy.x, xy.y + 1) != 0 && getKey(pcopy, xy.x, xy.y + 1) != -1 && getKey(pcopy, xy.x, xy.y + 1) != 2)
        {
            moving[0] = 0;
            moving[1] = 1;
            moving[2] = 0;
            moving[3] = 0;
            push(move, moving);
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
            push(move, moving);
            xy.x -= 1;
            labelPast(pcopy, xy.x, xy.y);
        }
        else if (getKey(pcopy, xy.x + 1, xy.y) != 0 && getKey(pcopy, xy.x + 1, xy.y) != -1 && getKey(pcopy, xy.x + 1, xy.y) != 2)
        {
            moving[0] = 0;
            moving[1] = 0;
            moving[2] = 0;
            moving[3] = 1;
            push(move, moving);
            xy.x += 1;
            labelPast(pcopy, xy.x, xy.y);
        }
        else
        {
            //若为已走过路线,则出栈
            if (move->next->up == 1)
            {
                xy.y += 1;
            }
            if (move->next->down == 1)
            {
                xy.y -= 1;
            }
            if (move->next->left == 1)
            {
                xy.x += 1;
            }
            if (move->next->right == 1)
            {
                xy.x -= 1;
            }
            pop(move);
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

//最后处理,释放掉无用指针
void freePointersPMove(PMove p){
    PMove temp;
    PMaze node;
    while(p!=NULL){
        temp = p->next;
        free(p);
        p = temp;
    }
}

//测试用例
int main()
{
    PMaze maze, mazeNode;
    PMove move, moveNode, reverse, reverseNode;
    int i, counter = 0, flag = 0, a[4];
    maze = initMazeRow(CAL);
    move = creatStack();
    for (i = 0; i < ROW; i++)
    {
        if (i == 0)
        {
            mazeNode = maze;
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
    printf("定义左上角为(0, 0), 右下角为(9, 9),只可以从标为1的点走");
    printf("\n起点: (0, 0), 终点: (9, 9)");
    //探索迷宫
    move = mazeExplore(maze->next, move, 0, 0, CAL-1, ROW-1);
    if(move->next==NULL){
        printf("迷宫不正确,没有路线可以走出\n");
    }
    //输出如何走出迷宫
    moveNode = move->next;
    //顺序转换,用栈实现队列的效果
    reverse = creatStack();
    while (moveNode != NULL)
    {
        a[0] = moveNode->up;
        a[1] = moveNode->down;
        a[2] = moveNode->left;
        a[3] = moveNode->right;
        push(reverse, a);
        moveNode = moveNode->next;
    }
    reverseNode = reverse->next;
    printf("\n\nThe solve is: \n");
    while (1)
    {
        if (reverseNode->up == 1)
        {
            printf("UP");
        }
        if (reverseNode->down == 1)
        {
            printf("DOWN");
        }
        if (reverseNode->left == 1)
        {
            printf("LEFT");
        }
        if (reverseNode->right == 1)
        {
            printf("RIGHT");
        }
        if (reverseNode->next == NULL)
        {
            break;
        }
        printf("->");
        reverseNode = reverseNode->next;
    }
    printf("\n打印出的路径并不一定是最短路径,不过顺着这个路径就可以走出迷宫\n");
    //释放掉指针
    freePointersPMove(move);
    freePointersPMove(reverse);
    return 0;
}