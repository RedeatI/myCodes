#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdint.h>
#include <windows.h>
#include <wchar.h>
#include <conio.h>
#include <fstream>
#include <algorithm>
#include <mmsystem.h>
#include <limits>

// Judge whether the game is over
// 判断游戏是否结束
bool game_over = false;

// The width and height of the game map
// 游戏地图的宽度和高度
int32_t width = 50;
int32_t height = 25;

// The entry of the leaderboard
// 排行榜的条目
struct scoreEntry
{
    std::string userName;
    int32_t score;
};

// Set the position of the cursor
// 设置光标的位置
void gotoxy(int16_t x, int16_t y)
{
    COORD coord;
    coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Show the menu
// 显示菜单
void showMenu()
{
    gotoxy(width / 2 - 4, height / 2);
    std::cout << "1. Start Game" << std::endl;
    gotoxy(width / 2 - 4, height / 2 + 1);
    std::cout << "2. Show Rank" << std::endl;
    gotoxy(width / 2 - 4, height / 2 + 2);
    std::cout << "3. Exit" << std::endl;
}

// Hide the cursor
// 隐藏光标
void hideCursor()
{
    // Get the handle of the console
    // 获取控制台的句柄
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};

    // Set the cursor to be invisible
    // 将光标设置为不可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// Show the map
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

// Read the leaderboard
// 读取排行榜
std::vector<scoreEntry> readLeaderboard(const std::string &filename)
{
    // Create a vector to store the leaderboard
    // 创建一个向量来存储排行榜
    std::vector<scoreEntry> leaderboard;

    // Open the leaderboard file
    // 打开排行榜文件
    std::ifstream file(filename);

    // If the file does not exist, return an empty leaderboard
    // 如果文件不存在，就返回一个空的排行榜
    if (!file)
    {
        return leaderboard;
    }

    // Read the leaderboard from the file
    // 从文件中读取排行榜
    std::string userName;
    int score;
    while (file >> userName >> score)
    {
        // Add the entry to the leaderboard
        // 将条目添加到排行榜
        leaderboard.push_back({userName, score});
    }

    // Close the file
    // 关闭文件
    file.close();

    // Return the leaderboard
    // 返回排行榜
    return leaderboard;
}

// Update the leaderboard
// 更新排行榜
void updateLeaderboard(const std::string &filename, scoreEntry &newEntry)
{
    // Read the leaderboard from the file
    // 从文件中读取排行榜
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);

    // Add the new entry to the leaderboard
    // 将新的条目添加到排行榜
    leaderboard.push_back(newEntry);

    // Sort the leaderboard
    // 对排行榜进行排序
    std::sort(leaderboard.begin(), leaderboard.end(), [](const scoreEntry &a, const scoreEntry &b)
              { return a.score > b.score; });

    // If the size of the leaderboard is greater than 10, delete the last element
    // 如果排行榜的大小大于10，就删除最后的元素
    if (leaderboard.size() > 10)
    {
        leaderboard.pop_back();
    }

    // Delete the data in the file
    // 删除文件中的数据
    std::ofstream file_writer(filename, std::ios_base::out);
    file_writer.close();

    // Write the leaderboard to the file
    // 将排行榜写入文件
    std::fstream file(filename);
    for (const auto &entry : leaderboard)
    {
        file << entry.userName << " " << entry.score << "\n";
    }
    file.close();
}

// Print the leaderboard
// 打印排行榜
void printLeaderboard(const std::string &filename)
{
    // Read the leaderboard from the file
    // 从文件中读取排行榜
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);

    // Print the leaderboard
    // 打印排行榜
    int i = 1;
    for (const auto &entry : leaderboard)
    {
        gotoxy(width / 2 - 4, height / 2 + i);
        ++i;
        std::cout << entry.userName << ": " << entry.score << "\n";
    }
}

// Get the max score from the leaderboard
// 从排行榜中获取最高分
int getMaxScore(const std::string &filename)
{
    // Read the leaderboard from the file
    // 从文件中读取排行榜
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);

    // If the leaderboard is empty, return 0
    // 如果排行榜为空，就返回0
    if (leaderboard.empty())
    {
        return 0;
    }

    // Return the max score
    // 返回最高分
    return leaderboard[0].score;
}

// Display the score panel
// 显示分数面板
void displayTheScorePanel(int32_t score)
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

class food
{
public:
    int32_t x;
    int32_t y;

    // Create the food
    // 创建食物
    void createFood()
    {
        // Generate random number
        // 生成随机数
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int32_t> dis_x(1, width - 1);
        std::uniform_int_distribution<int32_t> dis_y(1, height - 1);
        // Set the position of the food
        // 设置食物的位置
        x = dis_x(gen);
        y = dis_y(gen);
    }

    // Show the food
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
    int32_t x;
    int32_t y;
    snake *next;
    snake *prev;
    snake *tail;

    snake(int32_t x, int32_t y)
    {
        this->x = x;
        this->y = y;
        next = nullptr;
        prev = nullptr;
        tail = nullptr;
    }

    // Initialize the snake
    // 初始化蛇
    void initSnake()
    {
        snake *p = this->next;
        snake *q = this;

        // Create the snake
        // 创建蛇
        for (int i = 1; i <= 10; ++i)
        {
            p = new snake(width / 2 - i, height / 2);

            // Set the next and prev pointer
            // 设置next和prev指针
            p->prev = q;
            q->next = p;

            // Set the tail pointer
            // 设置tail指针
            this->tail = p;

            // Move the pointer
            // 移动指针
            q = p;
            p = p->next;
        }
    }

    // Judge whether the snake is dead
    // 判断蛇是否死亡
    bool isSnakeDeath(snake *pHead)
    {
        // Judge whether the snake is out of the map
        // 判断蛇是否超出地图
        if (pHead->x <= 0 || pHead->x >= width || pHead->y <= 0 || pHead->y >= height)
        {
            return true;
        }

        // Judge whether the snake bites itself
        // 判断蛇是否咬到自己
        snake *temp = tail;
        // Traverse the snake
        // 遍历蛇
        while (temp->prev != pHead)
        {
            if (pHead->x == temp->x && pHead->y == temp->y)
            {
                return true;
            }
            temp = temp->prev;
        }
        return false;
    }

    // Move the snake
    // 移动蛇
    bool move(snake *pHead, char key)
    {
        // Clear the tail of the snake
        // 清除蛇的尾巴
        pHead->clearSnake(tail);

        // Move the snake from the tail to the head
        // 从尾巴到头部移动蛇
        snake *temp = tail;
        while (temp != pHead)
        {
            temp->x = temp->prev->x;
            temp->y = temp->prev->y;
            temp = temp->prev;
        }

        // Check the key
        // 检查按键
        if (key == 'w')
        {
            pHead->y--;
        }
        else if (key == 's')
        {
            pHead->y++;
        }
        else if (key == 'a')
        {
            pHead->x--;
        }
        else if (key == 'd')
        {
            pHead->x++;
        }

        // Judge whether the snake is dead
        // 判断蛇是否死亡
        if (isSnakeDeath(pHead))
        {
            game_over = true;
        }

        // Return whether the game is over
        // 返回游戏是否结束
        return game_over;
    }

    // Show the snake
    // 显示蛇
    void showSnake()
    {
        // Traverse the snake
        // 遍历蛇
        snake *temp = this;
        while (temp != nullptr)
        {
            gotoxy(temp->x, temp->y);
            putchar(L'*');
            temp = temp->next;
        }
    }

    // Check and create the food
    // 检查并创建食物
    void checkAndCreateFood(snake *pHead, food *pFood)
    {
        // Create the food
        // 创建食物
        pFood->createFood();

        // Traverse the snake
        // 遍历蛇
        snake *temp = pHead;
        while (temp != nullptr)
        {
            // Judge whether the food is in the snake
            // 判断食物是否在蛇身上
            if (temp->x == pFood->x && temp->y == pFood->y)
            {
                // Create the food again
                // 重新创建食物
                pFood->createFood();
                temp = pHead;
            }
            else
            {
                temp = temp->next;
            }
        }

        // Show the food
        // 显示食物
        pFood->showFood();
    }

    // Eat the food
    // 吃食物
    void eatFood(snake *pHead, food *pFood, int32_t &score, int32_t &speed)
    {
        // Judge whether the snake eats the food
        // 判断蛇是否吃到食物
        if (pHead->x == pFood->x && pHead->y == pFood->y)
        {
            // Create the food again
            // 重新创建食物
            checkAndCreateFood(pHead, pFood);

            // Create a new snake body
            // 创建一个新的蛇身
            snake *p = new snake(99, 99);
            p->prev = pHead->tail;
            pHead->tail = p;

            // Increase the speed and score
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

    // Clear the snake
    // 清除蛇
    inline void clearSnake(snake *tail)
    {
        gotoxy(tail->x, tail->y);
        putchar(' ');
    }
};

int main()
{
    // set the console to utf-8
    // 将控制台设置为utf-8
    system("chcp 65001");

    // play the background music
    // 播放背景音乐
    PlaySound(TEXT("TimeWar.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // get the player's name
    // 获取玩家的名字
    std::string name;
    std::ifstream file("player.txt");

    // if the file is empty, let the player enter his name
    // 如果文件为空，就让玩家输入他的名字
    if (file.peek() == EOF)
    {
        std::ofstream file("player.txt");
        gotoxy(width / 2 - 4, height / 2 - 2);
        std::cout << "Please enter your name: ";
        std::cin >> name;

        file << name;
    }
    else
    {
        // read the player's name from the file
        // 从文件中读取玩家的名字
        file >> name;
    }

    // close the file
    // 关闭文件
    file.close();

    // the main loop of the game
    // 游戏的主循环
    while (true)
    {
        // clear the console
        // 清空控制台
        system("cls");

        // hide the cursor
        // 隐藏光标
        hideCursor();

        // show the menu
        // 显示菜单
        showMenu();

        // get the player's choice
        // 获取玩家的选择
        char choice = _getch();

        // break the loop
        // 退出循环
        if (choice == '3')
        {
            break;
        }
        // print the leaderboard
        // 打印排行榜
        else if (choice == '2')
        {
            system("cls");
            gotoxy(width / 2 - 4, height / 2);
            std::cout << "Rank: " << std::endl;
            printLeaderboard("leaderboard.txt");
            gotoxy(width / 2 - 4, height / 2 + 11);
            system("pause");
            continue;
        }
        // start the game
        // 开始游戏
        else if (choice == '1')
        {
            // start the game
            // 开始游戏
            game_over = false;

            PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            PlaySound(TEXT("battle1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            while (!game_over)
            {
                // the default direction of the snake is right
                // 蛇的默认方向是向右
                char key = 'd';

                int32_t speed = 0;
                int32_t score = 0;
                system("cls");
                showMap();
                snake *pHead = new snake(width / 2, height / 2);
                food *pFood = new food;
                pHead->initSnake();
                pHead->checkAndCreateFood(pHead, pFood);
                pHead->showSnake();

                while (!game_over)
                {
                    // get the player's input
                    // 获取玩家的输入
                    if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && key != 's')
                    {
                        key = 'w';
                    }
                    else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && key != 'w')
                    {
                        key = 's';
                    }
                    else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && key != 'd')
                    {
                        key = 'a';
                    }
                    else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && key != 'a')
                    {
                        key = 'd';
                    }
                    if (pHead->move(pHead, key))
                    {
                        break;
                    }
                    // check and eat the food
                    // 检查食物
                    pHead->eatFood(pHead, pFood, score, speed);

                    // show the snake and the food
                    // 显示蛇和食物
                    pFood->showFood();
                    pHead->showSnake();

                    // display the score panel
                    // 显示分数面板
                    displayTheScorePanel(score);

                    // control the speed of the game
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
                system("cls");

                // show the game over message
                // 显示游戏结束信息
                gotoxy(width / 2 - 4, height / 2);
                std::cout << "Score: " << score;
                if (score > 0)
                {
                    scoreEntry entry{name, score};
                    updateLeaderboard("leaderboard.txt", entry);
                }
                gotoxy(width / 2 - 10, height / 2 + 1);
                std::cout << "Game Over! Again? (y/n)";

                // clear the input buffer of the console
                // 清空控制台的输入缓冲区
                while (_kbhit())
                {
                    _getch();
                }

                // get the player's choice
                // 获取玩家的选择
                char c = _getch();
                while (c != 'y' && c != 'n' && c != 'Y' && c != 'N')
                {
                    // 清空控制台的输入缓冲区
                    while (_kbhit())
                    {
                        _getch();
                    }
                    c = _getch();
                }

                // if the player chooses to exit the game, delete the snake and the food
                // 如果玩家选择退出游戏，就删除蛇和食物
                if (c == 'n' || c == 'N')
                {
                    delete pFood;
                    delete pHead;

                    // break the loop
                    // 退出循环
                    break;
                }

                game_over = false;
            }
        }
        // if the player enters an invalid input
        // 如果玩家输入了无效的输入
        else
        {
            system("cls");
            gotoxy(width / 2, height / 2);
            std::cout << "Invalid input!" << std::endl;
            gotoxy(width / 2 - 4, height / 2 + 1);
            system("pause");
        }
    }

    return 0;
}
