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

bool game_over = false;

int32_t width = 50;
int32_t height = 25;
struct scoreEntry
{
    std::string userName;
    int32_t score;
};

void gotoxy(int16_t x, int16_t y)
{
    COORD coord;
    coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showMenu()
{
    gotoxy(width / 2 - 4, height / 2);
    std::cout << "1. Start Game" << std::endl;
    gotoxy(width / 2 - 4, height / 2 + 1);
    std::cout << "2. Show Rank" << std::endl;
    gotoxy(width / 2 - 4, height / 2 + 2);
    std::cout << "3. Exit" << std::endl;
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void showMap()
{
    for (int32_t i = 0; i <= width + 30; ++i)
    {
        gotoxy(i, 0);
        putchar('#');
        gotoxy(i, height);
        putchar('#');
    }
    for (int32_t i = 0; i <= height; ++i)
    {
        gotoxy(0, i);
        putchar('#');
        gotoxy(width, i);
        putchar('#');
    }
    for (int32_t i = 0; i <= height; ++i)
    {
        gotoxy(0, i);
        putchar('#');
        gotoxy(width + 30, i);
        putchar('#');
    }
}

// 读取排行榜
std::vector<scoreEntry> readLeaderboard(const std::string &filename)
{
    std::vector<scoreEntry> leaderboard;
    std::ifstream file(filename);

    if (!file)
    {
        return leaderboard;
    }

    std::string userName;
    int score;
    while (file >> userName >> score)
    {
        leaderboard.push_back({userName, score});
    }
    return leaderboard;
}

// 更新排行榜
void updateLeaderboard(const std::string &filename, scoreEntry newEntry)
{
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);
    leaderboard.push_back(newEntry);
    std::sort(leaderboard.begin(), leaderboard.end(), [](const scoreEntry &a, const scoreEntry &b)
              { return a.score > b.score; });

    // 如果排行榜的大小大于10，就删除最后的元素
    if (leaderboard.size() > 10)
    {
        leaderboard.pop_back();
    }

    std::ofstream file(filename);
    for (const auto &entry : leaderboard)
    {
        file << entry.userName << " " << entry.score << "\n";
    }
}

// 打印排行榜
void printLeaderboard(const std::string &filename)
{
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);
    int i = 1;
    for (const auto &entry : leaderboard)
    {
        gotoxy(width / 2 - 4, height / 2 + i);
        ++i;
        std::cout << entry.userName << ": " << entry.score << "\n";
    }
}

int getMaxScore(const std::string &filename)
{
    std::vector<scoreEntry> leaderboard = readLeaderboard(filename);
    if (leaderboard.empty())
    {
        return 0;
    }
    return leaderboard[0].score;
}

void displayTheScorePanel(int32_t score)
{
    gotoxy(width + 10, height / 2);
    std::cout << "Score: " << score;
    gotoxy(width + 10, height / 2 + 1);
    std::cout << "Max Score: " << getMaxScore("leaderboard.txt");
}

class food
{
public:
    int32_t x;
    int32_t y;

    void createFood()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int32_t> dis_x(1, width - 1);
        std::uniform_int_distribution<int32_t> dis_y(1, height - 1);
        x = dis_x(gen);
        y = dis_y(gen);
    }

    void showFood()
    {
        gotoxy(x, y);
        putchar('@');
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

    void initSnake()
    {
        snake *p = this->next;
        snake *q = this;
        for (int i = 1; i <= 10; ++i)
        {
            p = new snake(width / 2 - i, height / 2);
            p->prev = q;
            q->next = p;
            this->tail = p;
            q = p;
            p = p->next;
        }
    }

    bool isSnakeDeath(snake *pHead)
    {
        snake *temp = tail;
        if (pHead->x <= 0 || pHead->x >= width || pHead->y <= 0 || pHead->y >= height)
        {
            return true;
        }
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

    bool move(snake *pHead, char key)
    {
        pHead->clearSnake(tail);
        snake *temp = tail;
        while (temp != pHead)
        {
            temp->x = temp->prev->x;
            temp->y = temp->prev->y;
            temp = temp->prev;
        }

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

        if (isSnakeDeath(pHead))
        {
            game_over = true;
        }

        return game_over;
    }

    void showSnake()
    {
        snake *temp = this;
        while (temp != nullptr)
        {
            gotoxy(temp->x, temp->y);
            putchar('*');
            temp = temp->next;
        }
    }

    void checkAndCreateFood(snake *pHead, food *pFood)
    {
        pFood->createFood();
        snake *temp = pHead;
        while (temp != nullptr)
        {
            if (temp->x == pFood->x && temp->y == pFood->y)
            {
                pFood->createFood();
                temp = pHead;
            }
            else
            {
                temp = temp->next;
            }
        }
        pFood->showFood();
    }

    void eatFood(snake *pHead, food *pFood, int32_t &score, int32_t &speed)
    {
        if (pHead->x == pFood->x && pHead->y == pFood->y)
        {
            checkAndCreateFood(pHead, pFood);
            snake *p = new snake(99, 99);
            p->prev = pHead->tail;
            pHead->tail = p;
            if (speed < 20)
            {
                speed += 10;
                score += 10;
            }
            else if (speed >= 20 && speed <= 40)
            {
                speed += 3;
                score += 20;
            }
            else if (speed >= 40 && speed <= 50)
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
    PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    std::string name;
    std::ifstream file("player.txt");
    if (file.peek() == EOF)
    {
        std::ofstream file("player.txt");
        gotoxy(width / 2 - 4, height / 2 - 2);
        std::cout << "Please enter your name: ";
        std::cin >> name;

        file << name;
    }
    file.close();

    while (true)
    {
        system("cls");
        hideCursor();
        showMenu();
        char choice = _getch();
        if (choice == '3')
        {
            break;
        }
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
        else if (choice == '1')
        {
            game_over = false;
            while (!game_over)
            {
                int32_t speed = 0;
                int32_t score = 0;
                system("cls");
                hideCursor();
                showMap();
                snake *pHead = new snake(width / 2, height / 2);
                food *pFood = new food;
                pHead->initSnake();
                pHead->checkAndCreateFood(pHead, pFood);
                pHead->showSnake();
                char key = 'd';
                while (!game_over)
                {
                    if (GetAsyncKeyState(VK_UP) && key != 's')
                    {
                        key = 'w';
                    }
                    else if (GetAsyncKeyState(VK_DOWN) && key != 'w')
                    {
                        key = 's';
                    }
                    else if (GetAsyncKeyState(VK_LEFT) && key != 'd')
                    {
                        key = 'a';
                    }
                    else if (GetAsyncKeyState(VK_RIGHT) && key != 'a')
                    {
                        key = 'd';
                    }
                    if (pHead->move(pHead, key))
                    {
                        break;
                    }
                    pHead->eatFood(pHead, pFood, score, speed);
                    pFood->showFood();
                    pHead->showSnake();
                    displayTheScorePanel(score);
                    Sleep(80 - speed);
                }
                system("cls");
                gotoxy(width / 2 - 4, height / 2);
                std::cout << "Score: " << score;
                if (score > 0)
                {
                    updateLeaderboard("leaderboard.txt", {name, score});
                }
                gotoxy(width / 2 - 10, height / 2 + 1);
                std::cout << "Game Over! Again? (y/n)";
                char c;
                std::cin >> c;
                if (c == 'n')
                {
                    delete pFood;
                    delete pHead;
                    break;
                }
                game_over = false;
            }
        }
        else
        {
            gotoxy(width / 2 - 4, height / 2 + 3);
            std::cout << "Invalid input!" << std::endl;
            system("pause");
            gotoxy(width / 2 - 1, height / 2 + 3);
            std::cout << "              ";
        }
    }

    return 0;
}
