/*
 * Hugeint.h
 *
 *  Created on: 2019年4月24日
 *      Author: bully
 */

#ifndef HUGEINT_H_
#define HUGEINT_H_

#include <iostream>
using namespace std;
const int MAX = 50;

class HugeInt
{
private:
      char number[MAX];  // 数值
      int len;  // 长度
      bool flag;  // 符号

public:
      // 工具函数
      static void reverse(char number[]);
      void setValue(const char *number);

      // 构造函数
      HugeInt();
      HugeInt(const int number);
      HugeInt(const char *number);

      HugeInt abs();    // 绝对值

      // 重载赋值运算符
      HugeInt operator=(const HugeInt &other);

      // 重载单目-
      HugeInt operator-();

      // 重载比较运算
      bool operator<(const HugeInt other);
      bool operator>(const HugeInt other);
      bool operator<=(const HugeInt other);
      bool operator>=(const HugeInt other);
      bool operator==(const HugeInt other);

      // 重载+
      HugeInt operator+(const HugeInt &other);
      HugeInt operator+(const int other);
      HugeInt operator+(const char *other);

      // 重载双目-
      HugeInt operator-(const HugeInt &other);
      HugeInt operator-(const int other);
      HugeInt operator-(const char *other);

      // 重载<< >>
      friend ostream &operator<<(ostream &os, const HugeInt &self);
      friend istream &operator>>(istream &is, HugeInt &self);
};

#endif /* HUGEINT_H_ */
