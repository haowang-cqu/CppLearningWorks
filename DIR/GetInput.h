//
// Created by bully on 19-5-10.
//

#ifndef DIR_GETINPUT_H
#define DIR_GETINPUT_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

class GetInput {
private:
    std::vector<std::string> input;  // 储存用户输入
    int number;                      // 用户输入参数个数
public:
    // 获取用户输入
    void get();
    // 返回vector
    std::vector<std::string>& getInput();
    int getNumber();
    // 判断用户输入是否为退出
    bool isExit();
    // 相对路径转绝对路径
};


#endif //DIR_GETINPUT_H
