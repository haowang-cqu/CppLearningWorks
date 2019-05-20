/*
 * CSV.h
 *
 *  Created on: 2019年5月15日
 *      Author: bully
 */

#ifndef CSV_H_
#define CSV_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


class CSV {
private:
    std::vector<std::vector<std::string>> file; // 储存文件所有内数据
    std::string filename;						// 储存文件名
    int row;									// 储存文件行数
    int col;									// 储存文件列数
public:
    CSV();
    CSV(std::string filename);
    std::vector<std::vector<std::string>> &getFile(); // 获得存储文件内容的vector（返回的是引用，便于直接修改）
    int getRow();
    int getCol();
    void openFile(std::string filename); // 读取文件，与构造函数相同
    void saveCSV();						 // 保存文件
};
#endif /* CSV_H_ */
