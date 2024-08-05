#include <iostream>
#include <stdint.h>
#include <windows.h>
#include <vector>
#include <fstream>
using namespace std;

void gotoxy(int16_t x, int16_t y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

fstream openFile(string fileName)
{
    fstream file;
    file.open(fileName, ios::in | ios::out);
    if (file.is_open())
    {
        return file;
    }
    else
    {
        cout << "File not found" << endl;
        return file;
    }
}

class vim
{
private:
    int32_t x, y;

    pair<int, string> nodes;

    int32_t pageNow;

public:
    vim()
    {
        x = 0;
        y = 0;
        pageNow = 1;
    }

    
};

int32_t main()
{
    while (true)
    {
        string textName;
        cin >> textName;

        fstream file = openFile(textName);

        if (file.is_open())
        {
            cout << "File opened" << endl;
        }
        else
        {
            cout << "File not found" << endl;
        }

        string line;

        int32_t page = 1;
        cout << "Page " << page << " :" << endl;

        while (getline(file, line))
        {
            if (line.find("page") != string::npos)
            {
                cout << endl;
                cout << "Page " << ++page << " :" << endl;
            }
            else
            {
                cout << line << endl;
            }
        }

        file.close();
    }

    return 0;
}