//
// Created by bully on 19-5-10.
//
#include "GetInput.h"
using namespace std;

void GetInput::get() {
    this->input.clear();        // 清空input中的内容
    char _cin[1024] = {0};
    cin.getline(_cin, 1024);    // 获取一行输入
    stringstream ss;            // 使用字符串流处理用户输入，将各个参数分开存储在vector中
    ss << _cin;
    string temp;
    while (ss >> temp)
        this->input.push_back(temp);
    this->number = input.size(); // 存入用户输入参数个数
}

vector<string>& GetInput::getInput() {
    return this->input;
}

int GetInput::getNumber() {
    return this->number;
}

bool GetInput::isExit(){
    if (this->number == 1 && this->input[0] == "exit")
    {
        return true;
    }
    return false;
}