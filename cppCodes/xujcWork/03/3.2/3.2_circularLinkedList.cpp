#include <iostream>
#include <string>
#include <vector>
using namespace std;
string er;

class student
{
public:
    string num, name, sex;
    int score;

    bool operator==(student &stu);
    friend ostream &operator<<(ostream &os, student &stu);
};

bool student::operator==(student &stu)
{
    return (num == stu.num) && (name == stu.name) && (sex == stu.sex) && (score = stu.score);
}

ostream &operator<<(ostream &os, student &stu)
{
    os << stu.num << "\t" << stu.name << "\t" << stu.sex << "\t" << stu.score;
    return os;
}

template <class DataType>
struct Node
{
    DataType data;
    Node<DataType> *next;
};

template <class DataType>
class LinkList
{
protected:
    Node<DataType> *first;

public:
    LinkList() {}
    LinkList(vector<DataType> a, int n);
    ~LinkList();
    int Length();
    DataType Get(int i);
    int Locate(DataType x);
    void Insert(int i, DataType x);
    DataType Delete(int i);
    void PrintList();
    void Lt4();
    void Lt7();
    friend void play();
    Node<DataType> *head();
};

// 创建链表
template <class DataType>
LinkList<DataType>::LinkList(vector<DataType> a, int n)
{
    first = new Node<DataType>;
    Node<DataType> *r = first;
    for (int i = 0; i < n; i++)
    {
        Node<DataType> *s = new Node<DataType>;
        s->data = a[i];

        r->next = s;
        r = s;
    }
    r->next = first;
}

// 链表长度
template <class DataType>
int LinkList<DataType>::Length()
{
    Node<DataType> *p = first->next;
    int count = 0;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

// 按位查找
template <class DataType>
DataType LinkList<DataType>::Get(int i)
{
    Node<DataType> *p = first->next;
    if (p == NULL)
    {
        er = "该链表为空";
        throw er;
    }
    int count = 1;
    while (p != first && count < i)
    {
        count++;
        p = p->next;
    }
    if (p == first || i == 0)
    {
        er = "位置异常";
        throw er;
    }
    else
    {
        return p->data;
    }
}

// 按值查找
template <class DataType>
int LinkList<DataType>::Locate(DataType x)
{
    Node<DataType> *p = first->next;
    int count = 1;
    while (p != first)
    {
        if (p->data == x)
            return count;
        else
        {
            p = p->next;
            count++;
        }
    }
    er = "链表中不存在该元素";
    throw er;
}

// 插入
template <class DataType>
void LinkList<DataType>::Insert(int i, DataType x)
{
    Node<DataType> *p = first;
    int count = 0;
    while (p != first && count < i - 1)
    {
        p = p->next;
        count++;
    }
    if (p->next == first && count < i - 1)
    {
        er = "位置异常";
        throw er;
    }
    else
    {
        Node<DataType> *s = new Node<DataType>;
        s->data = x;
        s->next = p->next;
        p->next = s;
    }
}

// 删除
template <class DataType>
DataType LinkList<DataType>::Delete(int i)
{
    Node<DataType> *p = first;
    int count = 0;
    while (p->next != first && count < i - 1)
    {
        p = p->next;
        count++;
    }
    if (p->next == first || p->next->next == first)
    {
        er = "位置异常";
        throw er;
    }
    else
    {
        Node<DataType> *q = p->next;
        DataType x = q->data;
        p->next = q->next;
        delete q;
        return x;
    }
}

// 遍历
template <class DataType>
void LinkList<DataType>::PrintList()
{
    Node<DataType> *p = first->next;
    while (p != first)
    {
        cout << p->data << '\n';
        p = p->next;
    }
}

// 虚构函数
template <class DataType>
LinkList<DataType>::~LinkList()
{
    Node<DataType> *p = first->next;
    while (p != first)
    {
        Node<DataType> *q = p;
        p = p->next;
        delete q;
    }
    delete first;
}

template <class DataType>
void LinkList<DataType>::Lt4()
{
    if (first->next == NULL)
    {
        er = "链表为空";
        throw er;
    }
    if (first->next->next == first)
    {
        return;
    }
    Node<DataType> *q = first->next;
    Node<DataType> *p = q->next;
    Node<DataType> *p_ = NULL;
    q->next = first;
    while (p != first)
    {
        p_ = p->next;
        p->next = q;
        q = p;
        p = p_;
    }
    first->next = q;
}

template <class DataType>
void LinkList<DataType>::Lt7()
{
    Node<DataType> *s;
    Node<DataType> *p = first->next;
    while (p != first && p->next != first)
    {
        s = p;
        Node<DataType> *q = p->next;
        while (q != first)
        {
            if (q->data == p->data)
            {
                s->next = q->next;
                q = s->next;
            }
            else
            {
                s = q;
                q = q->next;
            }
        }
        p = p->next;
    }
}

template <class DataType>
Node<DataType> *LinkList<DataType>::head()
{
    return this->first;
}

LinkList<student> *link;

void stuPrint()
{
    if (!link)
    {
        cout << "表为空。" << endl;
        return;
    }

    cout << "学号\t姓名\t性别\t成绩\n";
    link->PrintList();
}

void stuCreate()
{
    if (link)
    {
        cout << "是否删除已有的表？ y/n:";
        char t;
        cin >> t;
        if (t == 'y')
        {
            delete link;
            link = nullptr;
        }
        else
        {
            return;
        }
    }

    cout << "建立表" << endl;
    cout << "输入人数：";
    int count;
    cin >> count;
    while (count < 0)
    {
        cout << "人数不能为负数，重新输入：";
        cin >> count;
    }

    vector<student> stus(count);
    for (int i = 0; i < count; ++i)
    {
        cout << i + 1 << "位学生信息输入：" << endl;
        cout << "学号:";
        cin >> stus[i].num;
        cout << "姓名:";
        cin >> stus[i].name;
        cout << "性别:";
        cin >> stus[i].sex;
        cout << "成绩:";
        cin >> stus[i].score;
        cout << "======================" << endl;
    }

    link = new LinkList<student>(stus, count);

    cout << "建立成功。" << endl;
}

void stuInsert()
{
    if (!link)
    {
        cout << "表为空。" << endl;
        return;
    }

    cout << "请输入要插入学生的位置：";
    int i;
    cin >> i;
    while (i < 1 || i > link->Length() + 1)
    {
        cout << "位置错误，请重新输入:";
        cin >> i;
    }

    student stu;
    cout << "学生信息输入：" << endl;
    cout << "学号:";
    cin >> stu.num;
    cout << "姓名:";
    cin >> stu.name;
    cout << "性别:";
    cin >> stu.sex;
    cout << "成绩:";
    cin >> stu.score;

    link->Insert(i, stu);
}

void numSrc(vector<student> &searched)
{
    auto temp = link->head();
    string num;
    cout << "输入学号：";
    cin >> num;
    while (temp)
    {
        if (temp->data.num == num)
        {
            searched.emplace_back(temp->data);
        }
        temp = temp->next;
    }
}

void nameSrc(vector<student> &searched)
{
    auto temp = link->head();
    string name;
    cout << "输入姓名：";
    cin >> name;
    while (temp)
    {
        if (temp->data.name == name)
        {
            searched.emplace_back(temp->data);
        }
        temp = temp->next;
    }
}

vector<student> stuSearch()
{
    vector<student> searched;

    if (!link)
    {
        cout << "表为空。" << endl;
        return searched;
    }

    cout << "1.按学号\n2.按姓名\n请输入：";
    int sel;
    cin >> sel;
    if (sel == 1)
    {
        numSrc(searched);
    }
    else if (sel == 2)
    {
        nameSrc(searched);
    }
    else
    {
        cout << "输入无效。\n";
        return searched;
    }

    if (searched.empty())
    {
        cout << "查无此人。\n";
        return searched;
    }

    cout << "查找到：\n";
    cout << "学号\t姓名\t性别\t成绩\n";
    int i = 0;
    for (auto stu : searched)
    {
        cout << ++i << ": " << stu << endl;
    }
    cout << "====================================" << endl;

    return searched;
}

void stuDel()
{
    vector<student> searched = stuSearch();

    if (searched.empty())
    {
        return;
    }

    cout << "请选择要删除的人的序号：" << endl;
    int sel;
    cin >> sel;

    while (sel < 1 || sel > searched.size())
    {
        cout << "错误输入，重新输入：";
        cin >> sel;
    }

    int i = 0;
    auto temp = link->head();
    while (temp)
    {
        if (temp->data == searched[sel - 1])
        {
            break;
        }
        ++i;
        temp = temp->next;
    }

    link->Delete(i);
    cout << searched[sel - 1].name << "\t已被删除。\n";
}

void msg()
{
    cout << endl
         << endl;
    cout << "\t学生信息管理系统" << endl;
    cout << "====================================" << endl;
    cout << "\t1.学生信息线性表的建立" << endl;
    cout << "\t2.插入学生信息" << endl;
    cout << "\t3.查询学生信息" << endl;
    cout << "\t4.删除学生信息" << endl;
    cout << "\t5.输出所有学生信息" << endl;
    cout << "\t0.退出学生管理系统" << endl;
    cout << "====================================" << endl;
    cout << "请选择0-5" << endl;
}

void play()
{
    int flag = 1;
    while (flag)
    {
        try
        {
            msg();
            int select;
            cout << "请选择：";
            cin >> select;
            cout << endl
                 << endl;
            switch (select)
            {
            case 0:
                flag = 0;
                break;
            case 1:
                stuCreate();
                break;
            case 2:
                stuInsert();
                break;
            case 3:
                stuSearch();
                break;
            case 4:
                stuDel();
                break;
            case 5:
                stuPrint();
                break;
            }
        }
        catch (string &er)
        {
            cout << er << endl;
        }
    }
}

int main()
{
    play();
    return 0;
}