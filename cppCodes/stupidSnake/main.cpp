#include <iostream>
#include <random>
#include <stdint.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <memory>
#include <map>

#pragma execution_character_set("utf-8")

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

std::map<char, Direction> keyToDirection = {
    {'w', Direction::UP},
    {'s', Direction::DOWN},
    {'a', Direction::LEFT},
    {'d', Direction::RIGHT},
    {'W', Direction::UP},
    {'S', Direction::DOWN},
    {'A', Direction::LEFT},
    {'D', Direction::RIGHT},
    {VK_UP, Direction::UP},
    {VK_DOWN, Direction::DOWN},
    {VK_LEFT, Direction::LEFT},
    {VK_RIGHT, Direction::RIGHT},
};

std::map<Direction, Direction> unAllowedKey = {
    {Direction::UP, Direction::DOWN},
    {Direction::DOWN, Direction::UP},
    {Direction::LEFT, Direction::RIGHT},
    {Direction::RIGHT, Direction::LEFT},
};

// 判断游戏是否结束
bool game_over = false;

// 游戏地图的宽度和高度
int32_t width = 50;
int32_t height = 25;

// 游戏地图蛇的位置
bool map[50][25];

// 玩家的名字
std::string name = "player";

// 游戏速度
int32_t speed = 5;

// 玩家的分数
int32_t score = 0;

// 排行榜的条目
struct scoreEntry
{
    std::string userName;
    int32_t score;
};

// 设置光标的位置
void gotoxy(int16_t x, int16_t y)
{
    COORD coord;
    coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 显示菜单
void showMenu()
{
    gotoxy(width / 2 - 4, height / 2);
    std::cout << "1. Start Game 开始游戏" << std::endl;
    gotoxy(width / 2 - 4, height / 2 + 1);
    std::cout << "2. Show Rank 显示排行榜" << std::endl;
    gotoxy(width / 2 - 4, height / 2 + 2);
    std::cout << "3. Exit 退出" << std::endl;
}

// 隐藏光标
void hideCursor()
{
    // 获取控制台的句柄
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};

    // 将光标设置为不可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 显示地图
void showMap()
{
    for (int32_t i = 0; i <= width + 30; ++i)
    {
        gotoxy(i, 0);
        putchar(L'#');
        gotoxy(i, height);
        putchar(L'#');
    }
    for (int32_t i = 0; i <= height; ++i)
    {
        gotoxy(0, i);
        putchar(L'#');
        gotoxy(width, i);
        putchar(L'#');
    }
    for (int32_t i = 0; i <= height; ++i)
    {
        gotoxy(0, i);
        putchar(L'#');
        gotoxy(width + 30, i);
        putchar(L'#');
    }
}

// 读取排行榜
std::vector<scoreEntry> readLeaderboard(const std::string &filename)
{
    // 创建一个向量来存储排行榜
    std::vector<scoreEntry> leaderboard;

    // 打开排行榜文件
    std::ifstream file(filename);

    // 如果文件不存在，就返回一个空的排行榜
    if (!file)
    {
        return leaderboard;
    }

    // 从文件中读取排行榜
    std::string userName;
    int score;
    while (file >> userName >> score)
    {
        // 将条目添加到排行榜
        leaderboard.push_back({userName, score});
    }

    // 关闭文件
    file.close();

    // 返回排行榜
    return leaderboard;
}

// Update the leaderboard
// 更新排行榜
void updateLeaderboard(const std::string &filename, scoreEntry &newEntry)
{
    // 从文件中读取排行榜
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);

    // 将新的条目添加到排行榜
    leaderboard.push_back(newEntry);

    // 对排行榜进行排序
    std::sort(leaderboard.begin(), leaderboard.end(), [](const scoreEntry &a, const scoreEntry &b)
              { return a.score > b.score; });

    // 如果排行榜的大小大于10，就删除最后的元素
    if (leaderboard.size() > 10)
    {
        leaderboard.pop_back();
    }

    // 删除文件中的数据
    std::ofstream file_writer(filename, std::ios_base::out);
    file_writer.close();

    // 将排行榜写入文件
    std::fstream file(filename);
    for (const auto &entry : leaderboard)
    {
        file << entry.userName << " " << entry.score << "\n";
    }
    file.close();
}

// 打印排行榜
void printLeaderboard(const std::string &filename)
{
    // 清空控制台
    system("cls");

    // 显示排行榜
    gotoxy(width / 2 - 4, height / 2);
    std::cout << "Rank 排名: " << std::endl;

    // 从文件中读取排行榜
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);

    // 打印排行榜
    size_t i = 0;

    for (; i < leaderboard.size(); ++i)
    {
        gotoxy(width / 2 - 4, height / 2 + i + 1);
        std::cout << i + 1 << ". " << leaderboard[i].userName << " " << leaderboard[i].score << std::endl;
    }

    // 暂停游戏
    gotoxy(width / 2 - 4, height / 2 + i + 1);
    system("pause");
}

// 从排行榜中获取最高分
int getMaxScore(const std::string &filename)
{
    // 从文件中读取排行榜
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);

    // 如果排行榜为空，就返回0
    if (leaderboard.empty())
    {
        return 0;
    }

    // 返回最高分
    return leaderboard[0].score;
}

// 显示分数面板
void displayTheScorePanel()
{
    gotoxy(width + 10, height / 2);
    std::cout << "Score: " << score;
    gotoxy(width + 10, height / 2 + 1);
    std::cout << "Max Score: " << getMaxScore("leaderboard.txt");
    gotoxy(width + 10, height / 2 + 4);
    std::cout << "操作方法：";
    gotoxy(width + 10, height / 2 + 5);
    std::cout << "w or ↑ : 上";
    gotoxy(width + 10, height / 2 + 6);
    std::cout << "s or ↓ : 下";
    gotoxy(width + 10, height / 2 + 7);
    std::cout << "a or ← : 左";
    gotoxy(width + 10, height / 2 + 8);
    std::cout << "d or → : 右";
}

Direction getPlayerInput(Direction key)
{
    auto checkKeyState = [](Direction currentKey, int vkKey, char keyChar, bool &change) -> Direction
    {
        if (!change)
        {
            return currentKey;
        }

        if (GetAsyncKeyState(vkKey) || GetAsyncKeyState(keyChar))
        {
            auto key = keyToDirection[keyChar];
            if (unAllowedKey[currentKey] != key)
            {
                change = false;
                return key;
            }
        }
        return currentKey;
    };

    bool change = true;
    key = checkKeyState(key, VK_UP, 'W', change);
    key = checkKeyState(key, VK_DOWN, 'S', change);
    key = checkKeyState(key, VK_LEFT, 'A', change);
    key = checkKeyState(key, VK_RIGHT, 'D', change);
    return key;
}

void clearKeyStates()
{
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState('W');
    GetAsyncKeyState('S');
    GetAsyncKeyState('A');
    GetAsyncKeyState('D');
}

class food
{
public:
    int32_t x;
    int32_t y;

    // 创建食物
    void createFood()
    {
        // 生成随机数
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int32_t> dis_x(1, width - 1);
        std::uniform_int_distribution<int32_t> dis_y(1, height - 1);

        // 设置食物的位置
        x = dis_x(gen);
        y = dis_y(gen);
    }

    // 显示食物
    void showFood()
    {
        gotoxy(x, y);
        putchar(L'@');
    }
};

class snake
{
public:
    int32_t x, y;
    std::shared_ptr<snake> next;
    std::shared_ptr<snake> prev;

    snake(int32_t x, int32_t y)
    {
        this->x = x;
        this->y = y;
        map[x][y] = true;
        next = nullptr;
        prev = nullptr;
    }

    // 初始化蛇
    void initSnake(std::shared_ptr<snake> &tail)
    {
        std::shared_ptr<snake> p = this->next;
        std::shared_ptr<snake> q = std::shared_ptr<snake>(this);

        // 创建蛇
        for (int i = 1; i <= 10; ++i)
        {
            int32_t tx = width / 2 - i;
            int32_t ty = height / 2;

            p = std::shared_ptr<snake>(new snake(tx, ty));

            map[tx][ty] = true;

            // 设置next和prev指针
            p->prev = q;
            q->next = p;

            // 设置tail指针
            tail = p;

            // 移动指针
            q = p;
            p = p->next;
        }
    }

    // 显示蛇
    void showSnake()
    {
        // 遍历蛇
        snake *temp = this;
        while (temp != nullptr)
        {
            gotoxy(temp->x, temp->y);
            putchar('*');
            temp = temp->next.get(); // 使用 get() 获取原始指针
        }
    }
};

// 判断蛇是否死亡
bool isSnakeDeath(std::shared_ptr<snake> &pHead, std::shared_ptr<snake> &tail)
{
    return pHead->x <= 0 || pHead->x >= width || pHead->y <= 0 || pHead->y >= height || map[pHead->x][pHead->y];
}

// 清除蛇
inline void clearSnake(std::shared_ptr<snake> &tail)
{
    gotoxy(tail->x, tail->y);
    putchar(' ');
    map[tail->x][tail->y] = false;
}

// 移动蛇
bool move(std::shared_ptr<snake> &pHead, Direction &key, std::shared_ptr<snake> &tail)
{
    // 清除蛇的尾巴
    clearSnake(tail);

    // 从尾巴到头部移动蛇
    std::shared_ptr<snake> temp = tail;
    while (temp != pHead)
    {
        temp->x = temp->prev->x;
        temp->y = temp->prev->y;
        temp = temp->prev;
    }

    // 检查按键
    if (key == Direction::UP)
    {
        pHead->y--;
    }
    else if (key == Direction::DOWN)
    {
        pHead->y++;
    }
    else if (key == Direction::LEFT)
    {
        pHead->x--;
    }
    else if (key == Direction::RIGHT)
    {
        pHead->x++;
    }

    // 判断蛇是否死亡
    if (isSnakeDeath(pHead, tail))
    {
        game_over = true;
    }

    // 设置蛇的位置
    map[pHead->x][pHead->y] = true;

    // 返回游戏是否结束
    return game_over;
}

// 检查并创建食物
void checkAndCreateFood(std::shared_ptr<snake> &pHead, std::unique_ptr<food> &pFood)
{
    // 创建食物
    pFood->createFood();

    // 判断食物是否在蛇的身体上
    while (map[pFood->x][pFood->y])
    {
        pFood->createFood();
    }

    // 显示食物
    pFood->showFood();
}

// 吃食物
void eatFood(std::shared_ptr<snake> &pHead, std::unique_ptr<food> &pFood, std::shared_ptr<snake> &tail)
{
    // 判断蛇是否吃到食物
    if (pHead->x == pFood->x && pHead->y == pFood->y)
    {
        // 重新创建食物
        checkAndCreateFood(pHead, pFood);

        // 创建一个新的蛇身
        std::shared_ptr<snake> p(new snake(99, 99));
        p->prev = tail;
        tail = p;

        // 增加速度和分数
        if (speed < 15)
        {
            speed += 5;
            score += 10;
        }
        else if (speed >= 15 && speed <= 25)
        {
            speed += 3;
            score += 20;
        }
        else if (speed >= 25 && speed <= 34)
        {
            speed += 2;
            score += 30;
        }
        else
        {
            speed++;
            score += 50;
        }
    }
}

// 检查玩家的名字
void nameCheck()
{
    // 获取玩家的名字
    std::ifstream file("player.txt");

    // 如果文件为空，就让玩家输入他的名字
    if (file.peek() == EOF)
    {
        std::ofstream file("player.txt");
        gotoxy(width / 2 - 4, height / 2 - 2);
        std::cout << "Please enter your name 请输入您的名字: ";
        std::cin >> name;

        file << name;
    }
    else
    {
        // 从文件中读取玩家的名字
        file >> name;
    }

    // 关闭文件
    file.close();
}

// 播放背景音乐
void playSound()
{
    // 检查背景音乐是否存在
    if (GetFileAttributes(TEXT("bgm.wav")) == INVALID_FILE_ATTRIBUTES)
    {
        system("cls");
        gotoxy(width / 2, height / 2);
        std::cout << "BGM file not found! BGM文件未找到!" << std::endl;
        gotoxy(width / 2 - 4, height / 2 + 1);
        system("pause");
    }
    else
    {
        PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

void mapClear()
{
    for (int32_t i = 0; i < width; ++i)
    {
        for (int32_t j = 0; j < height; ++j)
        {
            map[i][j] = false;
        }
    }
}

// 显示游戏结束信息
void gameOver()
{
    gotoxy(width / 2, height / 2);
    std::cout << "Score 分数: " << score;
    if (score > 0)
    {
        scoreEntry entry{name, score};
        updateLeaderboard("leaderboard.txt", entry);
    }
    gotoxy(width / 2 - 10, height / 2 + 1);
    std::cout << "Game Over! Again? 游戏结束!是否重新开始? (y/n)";

    // 清空地图
    mapClear();

    // 重置分数和速度
    score = 0;
    speed = 5;

    // 获取玩家的选择
    char c = _getch();
    while (c != 'y' && c != 'n')
    {
        // 清空控制台的输入缓冲区
        while (_kbhit())
        {
            _getch();
        }
        c = _getch();
    }

    if (c == 'y')
    {
        game_over = false;
    }
}

void tick()
{
    std::shared_ptr<snake> pHead(new snake(width / 2, height / 2));
    std::shared_ptr<snake> tail = pHead;

    std::unique_ptr<food> pFood(new food);

    system("cls");
    showMap();
    pHead->initSnake(tail);
    checkAndCreateFood(pHead, pFood);
    pHead->showSnake();

    // 蛇的默认方向是向右
    Direction key = Direction::RIGHT;

    // 清除按键状态
    clearKeyStates();

    while (!game_over)
    {
        // 获取玩家的输入
        key = getPlayerInput(key);

        if (move(pHead, key, tail))
        {
            break;
        }

        // 检查食物
        eatFood(pHead, pFood, tail);

        // 显示蛇和食物
        pFood->showFood();
        pHead->showSnake();

        // 显示分数面板
        displayTheScorePanel();

        // 控制游戏的速度
        if (key == 'a' || key == 'd')
        {
            Sleep(60 - speed * 0.7);
        }
        else
        {
            Sleep(80 - speed);
        }
    }

    // 停止背景音乐
    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    system("cls");

    gameOver();
}

// 开始游戏
void gameStart()
{
    game_over = false;

    while (!game_over)
    {
        // 播放背景音乐
        playSound();

        tick();
    }
}

// 游戏的主循环
void work()
{
    while (true)
    {
        // 清空控制台
        system("cls");

        // 隐藏光标
        hideCursor();

        // 显示菜单
        showMenu();

        // 获取玩家的选择
        char choice = _getch();

        // 退出循环
        if (choice == '3')
        {
            break;
        }
        // 打印排行榜
        else if (choice == '2')
        {
            printLeaderboard("leaderboard.txt");
            continue;
        }
        // 开始游戏
        else if (choice == '1')
        {
            gameStart();
        }
        // 如果玩家输入了无效的输入
        else
        {
            system("cls");
            gotoxy(width / 2, height / 2);
            std::cout << "Invalid input! 非法输入!" << std::endl;
            gotoxy(width / 2 - 4, height / 2 + 1);
            system("pause");
        }
    }
}

int main()
{
    // 将控制台设置为utf-8
    system("chcp 65001");

    nameCheck();

    work();

    return 0;
}
