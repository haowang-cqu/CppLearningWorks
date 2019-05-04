#include <iostream>
using namespace std;

template <class T>
class Link; // 前向申明Link类

template <class T>
class Node
{
public:
    Node<T> *next;
    T data;
    friend Link<T>; // 把Link类作为友元
    Node(const T &data, Node<T> *next = NULL)
    {
        this->data = data;
        this->next = next;
    }
    Node()
    {
        this->next = NULL;
    }
};

template <class T>
class Link
{
private:
    Node<T> *head; // 头指针
    int size;      // 元素个数

public:
    Link();
    Link(Link<T> &other);
    ~Link();
    Link &operator=(const Link<T> &other);                                  // 重载赋值运算符
    template <class U>
    friend std::ostream &operator<<(std::ostream &os, const Link<U> &link); // 重载输出运算符
    int getSize() const;                                                    // 获取链表长度
    void copy(const Link<T> &other);                                        // 复制链表（拷贝构造函数和赋值运算符调用）
    void release();                                                   // 删除链表（析构函数调用）
    void insertHead(const T &data);                                   // 头插
    void insertTail(const T &data);                                   // 尾插
    T &getNode(int position) const;                                         // 获取节点data
    void delNode(int position);                                       // 删除节点
    void changeNode(int position, const T &data);                     // 修改节点
    int findNode(const T &data);                                      // 查找节点，返回位置
};

template <class T>
Link<T>::Link()
{
    head = NULL;
    size = 0;
}

template <class T>
Link<T>::Link(Link<T> &other)
{
    head = NULL;
    size = 0;
    copy(other);
}

template <class U>
std::ostream &operator<<(std::ostream &os, const Link<U> &link)
{
    os << "[";
    for (int i = 0; i < link.getSize(); i++)
    {
        os << link.getNode(i);
        if (i != link.getSize() - 1)
        {
            os << ", ";
        }
    }
    os << "]" << endl;
    return os;
}

template <class T>
Link<T>::~Link()
{
    release();
}

template <class T>
Link<T> &Link<T>::operator=(const Link<T> &other)
{
    release();
    copy(other);
    return *this;
}

template <class T>
int Link<T>::getSize() const
{
    return size;
}

template <class T>
void Link<T>::copy(const Link<T> &other)
{
    for (int i = 0; i < other.size; i++)
    {
        insertTail(other.getNode(i));
    }
}

template <class T>
void Link<T>::release()
{
    int len = size;
    for (int i = 0; i < len; i++)
    {
        delNode(0);
    }
}

template <class T>
void Link<T>::delNode(int position)
{
    Node<T> *previous;
    Node<T> *current;
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

template <class T>
void Link<T>::insertHead(const T &data)
{
    Node<T> *new_node = new Node<T>;
    Node<T> *temp = NULL;
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

template <class T>
void Link<T>::insertTail(const T &data)
{
    Node<T> *new_node = new Node<T>;
    Node<T> *temp = NULL;
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

template <class T>
T &Link<T>::getNode(int position) const
{
    Node<T> *current;
    current = head;
    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }
    return current->data;
}

template <class T>
void Link<T>::changeNode(int position, const T &data)
{
    Node<T> *current;
    current = head;
    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }
    current->data = data;
}

template <class T>
int Link<T>::findNode(const T &data)
{
    Node<T> *current;
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
    Link<int> a;
    // 测试头插法
    for (int i = 0; i < 10; i++)
    {
        a.insertHead(i);
    }
    cout << "size of a: " << a.getSize() << endl;
    cout << "a: ";
    cout << a;
    cout << "********************************" << endl;

    Link<int> b;
    // 测试尾插法
    for (int i = 0; i < 10; i++)
    {
        b.insertTail(i);
    }
    cout << "size of b: " << b.getSize() << endl;
    cout << "b: ";
    cout << b;
    cout << "******************************" << endl;

    // 测试拷贝构造函数
    Link<int> c(a);
    cout << "size of c: " << c.getSize() << endl;
    cout << "c: ";
    cout << c;
    cout << "******************************" << endl;

    // 测试赋值运算符
    Link<int> d;
    d = b;
    cout << "size of d: " << d.getSize() << endl;
    cout << "d: ";
    cout << d;
    cout << "******************************" << endl;

    // 测试删除节点
    a.delNode(0);
    cout << "删除了a的第一个节点~~" << endl;
    cout << "size of a: " << a.getSize() << endl;
    cout << "a: ";
    cout << a;
    cout << "********************************" << endl;

    // 测试查找节点
    int position = a.findNode(6);
    cout << "a中数值为6的节点所在位置：" << position << endl;
    cout << "********************************" << endl;

    // 测试修改节点数据
    a.changeNode(2, 1000);
    cout << "将a的的三个节点改为了1000~~" << endl;
    cout << "size of a: " << a.getSize() << endl;
    cout << "a: ";
    cout << a;
    cout << "********************************" << endl;

    // 测试储存不同数据类型
    Link<string> str_link;
    str_link.insertTail("I");
    str_link.insertTail("love");
    str_link.insertTail("coding");
    str_link.insertTail("!");
    cout << "创建了一个string链表~~~" << endl;
    cout << str_link;
    cout << "********************************" << endl;

    Link<double> dou_link;
    dou_link.insertTail(3.14);
    dou_link.insertTail(6.28);
    dou_link.insertTail(9.42);
    cout << "创建了一个double链表~~~" << endl;
    cout << dou_link;
    cout << "********************************" << endl;
    return 0;
}