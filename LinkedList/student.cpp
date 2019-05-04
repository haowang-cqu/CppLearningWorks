#include <cstring>
#include <iostream>
using namespace std;

//定义学生结构体
struct student
{
    long num;
    char name[20];
    float score;
    /**
     * 为了方便输出，以及Link类中重载输出运算符号，
     * 先对student结构体做一次输出运算符重载
     */
    friend std::ostream &operator<<(std::ostream &os, student &stu)
    {
        os << "ID: " << stu.num << "  "
           << "NAME: " << stu.name << "  "
           << "SCORE: " << stu.score << endl;
        return os;
    }
    /**
     * 重载赋值运算符（用于拷贝节点）
     */
    student &operator=(const student &stu)
    {
        strcpy(name, stu.name);
        num = stu.num;
        score = stu.score;
        return *this;
    }
    /**
     * 重载!=（用于查找节点）
     */
    bool operator!=(const student &stu)
    {
        if (strcmp(name, stu.name) != 0 || num != stu.num || score != stu.score)
        {
            return true;
        }
        return false;
    }
};

/**
 * 节点类
 * 数据域：学生结构体
 * 指针域：指向下一个节点的指针
 */
class Node
{
public:
    Node *next;
    student data;
    Node(const student &data, Node *next = NULL)
    {
        this->data = data;
        this->next = next;
    }
    Node()
    {
        this->next = NULL;
    }
};

/**
 * 链表类
 * 数据成员：头指针、链表长度
 */
class Link
{
private:
    Node *head; // 头指针
    int size;   // 元素个数

public:
    Link();
    Link(Link &other);
    ~Link();
    Link &operator=(const Link &other);                                  // 重载赋值运算符
    friend std::ostream &operator<<(std::ostream &os, const Link &link); // 重载输出运算符
    int getSize() const;                                                 // 获取链表长度
    void copy(const Link &other);                                        // 复制链表（拷贝构造函数和赋值运算符调用）
    void release();                                                      // 删除链表（析构函数调用）
    void insertHead(const student &data);                                // 头插
    void insertTail(const student &data);                                // 尾插
    student &getNode(int position) const;                                // 获取节点data
    void delNode(int position);                                          // 删除节点
    void changeNode(int position, const student &data);                  // 修改节点
    int findNode(const student &data) const;                             // 查找节点，返回位置
};

Link::Link()
{
    head = NULL;
    size = 0;
}

Link::Link(Link &other)
{
    head = NULL;
    size = 0;
    copy(other);
}

std::ostream &operator<<(std::ostream &os, const Link &link)
{
    for (int i = 0; i < link.getSize(); i++)
    {
        os << link.getNode(i);
    }
    return os;
}

Link::~Link()
{
    release();
}

Link &Link::operator=(const Link &other)
{
    release();
    copy(other);
    return *this;
}

int Link::getSize() const
{
    return size;
}

void Link::copy(const Link &other)
{
    for (int i = 0; i < other.size; i++)
    {
        insertTail(other.getNode(i));
    }
}

void Link::release()
{
    int len = size;
    for (int i = 0; i < len; i++)
    {
        delNode(0);
    }
}

void Link::delNode(int position)
{
    Node *previous;
    Node *current;
    current = head;
    previous = NULL;
    for (int i = 0; i < position; i++)
    {
        previous = current;
        current = current->next;
    }
    if (previous == NULL)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    delete current;
    size--;
}

void Link::insertHead(const student &data)
{
    Node *new_node = new Node;
    Node *temp = NULL;
    new_node->data = data;
    if (head != NULL) //not an empty list
    {
        temp = head;
        head = new_node;
        new_node->next = temp;
        temp = NULL;
    }
    else
    {
        head = new_node;
        new_node->next = NULL;
    }
    size++;
}

void Link::insertTail(const student &data)
{
    Node *new_node = new Node;
    Node *temp = NULL;
    new_node->data = data;
    if (head != NULL) //not an empty list
    {
        temp = head;
        //Locate to the end
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = NULL;
    }
    else
    {
        head = new_node;
        new_node->next = NULL;
    }
    size++;
}

student &Link::getNode(int position) const
{
    Node *current;
    current = head;
    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }
    return current->data;
}

void Link::changeNode(int position, const student &data)
{
    Node *current;
    current = head;
    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }
    current->data = data;
}

int Link::findNode(const student &data) const
{
    Node *current;
    current = head;
    int count = 0;
    while (current != NULL && current->data != data)
    {
        current = current->next;
        count++;
    }
    if (current == NULL)
    {
        return -1; // -1代表没找到
    }
    else
    {
        return count;
    }
}

int main()
{
    student stu1 = {1, "Tom", 100};
    student stu2 = {2, "Bob", 90};
    student stu3 = {3, "Join", 88};
    student stu4 = {4, "Marry", 66};
    student stu5 = {5, "Jio", 100};
    Link a, b;
    // 测试头插法
    a.insertHead(stu1);
    a.insertHead(stu2);
    a.insertHead(stu3);
    a.insertHead(stu4);
    a.insertHead(stu5);
    cout << "头插法生成链表a：" << endl;
    cout << a;
    cout << "************************" << endl
         << endl;
    // 测试尾插法
    b.insertTail(stu1);
    b.insertTail(stu2);
    b.insertTail(stu3);
    b.insertTail(stu4);
    b.insertTail(stu5);
    cout << "尾插法生成链表b：" << endl;
    cout << b;
    cout << "************************" << endl
         << endl;
    // 测试拷贝构造函数
    Link c(a);
    cout << "拷贝a生成c：" << endl;
    cout << c;
    cout << "************************" << endl
         << endl;
    // 测试赋值运算
    c = b;
    cout << "b赋值给c后的c：" << endl;
    cout << c;
    cout << "************************" << endl
         << endl;
    // 测试查找
    cout << "c中查找stu3" << endl;
    cout << c.getNode(c.findNode(stu3));
    cout << endl;
    // 测试删除
    c.delNode(c.findNode(stu3));
    cout << "已删除c中stu3..." << endl;
    cout << c;
    cout << "************************" << endl
         << endl;
    // 测试修改
    stu5.score = 0;
    c.changeNode(c.findNode(stu1), stu5);
    cout << "已将c中stu1改为stu5..." << endl;
    cout << c;
    cout << "************************" << endl
         << endl;
    return 0;
}