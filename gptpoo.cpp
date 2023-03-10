#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 11;
const int EMPTY = 0;
const int BLACK = 1;
const int WHITE = 2;

int board[BOARD_SIZE][BOARD_SIZE];
int player = BLACK; // 玩家执黑棋

// 初始化棋盘
bool dfs(int x, int y, vector<vector<bool>> &visited, int player);

void initBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = EMPTY;
        }
    }
}

// 输出棋盘
void printBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// 判断是否越界
bool inBoard(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

// 判断该位置是否为空
bool isEmpty(int x, int y)
{
    return board[x][y] == EMPTY;
}

// 判断是否胜利
bool isWin(int player)
{
    vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (player == BLACK && inBoard(0, i) && !visited[0][i] && board[0][i] == BLACK)
        {
            visited[0][i] = true;
            if (dfs(0, i, visited, BLACK))
                return true;
        }
        else if (player == WHITE && inBoard(i, 0) && !visited[i][0] && board[i][0] == WHITE)
        {
            visited[i][0] = true;
            if (dfs(i, 0, visited, WHITE))
                return true;
        }
    }
    return false;
}

bool dfs(int x, int y, vector<vector<bool>> &visited, int player)
{
    if (player == BLACK && x == BOARD_SIZE - 1)
        return true;
    if (player == WHITE && y == BOARD_SIZE - 1)
        return true;
    int dx[6] = {-1, 0, 1, 1, 0, -1};
    int dy[6] = {0, 1, 1, 0, -1, -1};
    for (int i = 0; i < 6; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (inBoard(nx, ny) && !visited[nx][ny] && board[nx][ny] == player)
        {
            visited[nx][ny] = true;
            if (dfs(nx, ny, visited, player))
                return true;
        }
    }
    return false;
}

// 判断是否结束游戏
bool isGameOver()
{
    return isWin(BLACK) || isWin(WHITE);
}

// 随机走法
void randomMove()
{
    int x, y;
    do
    {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    } while (!isEmpty(x, y));
    board[x][y] = player;
}

// AI下棋
void aiMove()
{
    randomMove(); // 这里只实现了随机走法
}

int main()
{
    srand(time(NULL)); // 设置随机种子
    initBoard();
    printBoard();
    while (!isGameOver())
    {
        if (player == BLACK)
        {
            cout << "BLACK's turn:" << endl;
            aiMove();
        }
        else
        {
            cout << "WHITE's turn:" << endl;
            aiMove();
        }
        printBoard();
        player = player == BLACK ? WHITE : BLACK;
    }
    return 0;
}
