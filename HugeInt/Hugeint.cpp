/*
 * Hugeint.cpp
 *
 *  Created on: 2019年4月24日
 *      Author: bully
 */

#include "Hugeint.h"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

void HugeInt::reverse(char number[])
{
    int i = 0;
    int j = strlen(number) - 1;
    while (i < j)
    {
    	char temp = number[i];
    	number[i] = number[j];
        number[j] = temp;
        i++;
        j--;
    }
}

void HugeInt::setValue(const char *number)
{   // 单独处理"-0"的情况
    if (strcmp(number, "-0") == 0)
    {
        number++;
    }
    if (number[0] == '-')  // 获取符号
    {
        flag = 1;
        number++;
    }
    else if (number[0] == '+')
    {
        flag = 0;
        number++;
    }
    else {
        flag = 0;
    }
    int i = 0;
    while (number[i] != 0)
    {
        this->number[i] = number[i];
        ++i;
    }
    this->number[i] = 0;
    this->len = strlen(this->number);     // 获取位数
    for (int i = this->len; i < MAX; i++) // 多余位置刷新为0
    {
        this->number[i] = 0;
    }
    reverse(this->number); //倒置字符串
}

HugeInt::HugeInt(const int number)
{
    char temp[MAX];
    stringstream str;
    str << number;
    str >> temp;
    setValue(temp);
}

HugeInt::HugeInt(const char *number)
{
    setValue(number);
}

// 空构造函数初始化为0
HugeInt::HugeInt()
{
	setValue("0");
}

HugeInt HugeInt::operator-()
{
    HugeInt result(*this);  // 拷贝构造函数
    if (result.flag == 0)
        result.flag = 1;
    else
        result.flag = 0;
    // 单独处理0
    if (strcmp(result.number, "0") == 0)
    {
        result.flag = 0;
    }
    return result;
}

HugeInt HugeInt::abs()
{
    HugeInt result(*this);  // 拷贝构造函数
    result.flag = 0;
    return result;
}


bool HugeInt::operator==(const HugeInt other)
{
    if (this->flag == other.flag
    && this->len == other.len
    && strcmp(this->number, other.number) == 0)
        return true;
    else
        return false;
}

bool HugeInt::operator<(const HugeInt other)
{
    if (*this == other)
        return false;
    if (this->flag == 1 && other.flag == 0)
        return true;
    if (this->flag == 0 && other.flag == 1)
        return false;
    if (this->flag == 0 && other.flag == 0)
    {
        if (this->len < other.len)
            return true;
        else if (this->len > other.len)
            return false;
        else
        {
            for (int i = 0; i < this->len; i++)
            {
                if (this->number[i] - '0' > other.number[i] - '0')
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool HugeInt::operator>(const HugeInt other)
{
    if (*this == other)
        return false;
    else
    {
        if (*this < other)
            return false;
        else
            return true;
    }
}

bool HugeInt::operator<=(const HugeInt other)
{
    if (*this > other)
        return false;
    else
        return true;
}

bool HugeInt::operator>=(const HugeInt other)
{
    if (*this < other)
        return false;
    else
        return true;
}

HugeInt HugeInt::operator+(const HugeInt &other)
{
    HugeInt _other(other);
    HugeInt result(0);
    int len_other = _other.len;
    if (_other.number[0] == '0' && len_other == 1)   // 加0
    {
        return *this;
    }
    if (this->number[0] == '0' && this->len == 1)   // 0加
    {
        result = _other;
        return result;
    }
    if (this->flag == _other.flag)  // 同号相加
    {
        result.flag = this->flag;  // 直接拷贝符号
        int j = 0; // 保存进位
        for (int i = 0; i < this->len || i < len_other; i++) {
            int x = 0;
            char c1 = this->number[i], c2 = _other.number[i];
            if (this->number[i] == 0)
                c1 = '0';
            if (_other.number[i] == 0)
                c2 = '0';
            x = (c1 - '0') + (c2 - '0') + j;
            result.number[i] = (x % 10) + '0';
            j = x / 10;
        }
        result.len = this->len > len_other ? this->len : len_other;
        for (int i = result.len; i < MAX; i++) {
            result.number[i] = 0;
        }
        if (j != 0) {
            result.number[result.len] = j + '0';
            result.len++;
        }
    }
    else
    {
        if (this->abs() == _other.abs())
            return result;
        HugeInt one(0);
        HugeInt two(0);
        if(this->abs() > _other.abs()) {
            one = this->abs();
            two = _other.abs();
            result.flag = this->flag;  // 符号为绝对值大的加数符号
            for (int i = 0; i < one.len || i < two.len; i++) {
                int x = 0;
                char c1 = one.number[i], c2 = two.number[i];
                if (this->number[i] == 0)
                    c1 = '0';
                if (_other.number[i] == 0)
                    c2 = '0';
                if ((c1 - '0') < (c2 - '0')) {
                    c1 += 10;
                    one.number[i + 1] -= 1;
                }
                x = (c1 - '0') - (c2 - '0');
                result.number[i] = x + '0';
            }
            int count = one.len - 1;
            while (true) {
                if (result.number[count] == '0') {
                    result.number[count] = 0;
                    count--;
                } else
                    break;
            }
            result.len = count + 1;
        }
        else
        {
            result = _other + *this;
        }
    }
    return result;
}

HugeInt HugeInt::operator-(const HugeInt &other)
{
    HugeInt _other(other);
    return *this + (-_other);
}

HugeInt HugeInt::operator+(const int other)
{
    return *this + HugeInt(other);
}

HugeInt HugeInt::operator+(const char *other)
{
    return *this + HugeInt(other);
}

HugeInt HugeInt::operator-(const int other)
{
    return *this - HugeInt(other);
}

HugeInt HugeInt::operator-(const char *other)
{
    return *this - HugeInt(other);
}

HugeInt HugeInt::operator=(const HugeInt &other)
{
    strcpy(this->number, other.number);
    this->len = other.len;
    this->flag = other.flag;
    return *this;
}

ostream &operator<<(ostream &os, const HugeInt &self)
{
    int len = self.len;
    if (self.flag == 1)
        os << '-';
    for (int i = len - 1; i >= 0; --i)
    {
        os << self.number[i];
    }
    return os;
}

istream &operator>>(istream &is, HugeInt &self)
{
	char number[MAX];
	is >> number;
	self.setValue(number);
	return is;
}
