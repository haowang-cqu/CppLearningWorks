//
// Created by bully on 2019/5/14.
//

#include "CSV.h"
using namespace std;
CSV::CSV()
{
    this->row = 0;
    this->col = 0;
}
CSV::CSV(string filename)
{
    openFile(filename);
}

void CSV::openFile(string filename)
{
    this->filename = filename;
    this->row = 0;
    this->col = 0;
    this->file.clear(); // 清除当前内容
    ifstream in_file(filename, ios::in);
    string line;        // 储存当前读到的行
    while (getline(in_file, line))
    {
        stringstream ss(line);
        std::string temp;				   // 储存当前行内读取到的元素
        std::vector<std::string> curLine; // 储存当前行的数据
        while (getline(ss, temp, ','))
        {
            curLine.push_back(temp);
        }
        this->col = curLine.size();
        this->file.push_back(curLine); // 将读到的行存入二维vector
        row++;
    }
}

void CSV::saveCSV()
{
    ofstream out_file;
    out_file.open(this->filename, ios::out); // 打开文件
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            out_file << file[i][j];
            if (j != col - 1)
            { // 不是行末尾则写入逗号
                out_file << ',';
            }
        }
        out_file << endl; // 行结束写入换行符
    }
    out_file.close(); // 关闭文件
}

std::vector<std::vector<std::string>> &CSV::getFile()
{
    return this->file;
}

int CSV::getRow()
{
    return this->row;
}

int CSV::getCol()
{
    return this->col;
}
