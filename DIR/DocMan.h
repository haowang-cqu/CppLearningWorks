//
// Created by bully on 19-5-9.
//

#ifndef DIR_DOCMAN_H
#define DIR_DOCMAN_H
#include "GetInput.h"
#include <iostream>
#include <cstring>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>

class DocMan {
private:
    char path[1024];
    char new_path[1024];
public:
    DocMan();
    void setPath(const char *path);
    void setNewpath(const char *new_path);

    // 新建文件夹
    void make_dir(const char *_path);
    // 获取当前路径
    char *getPath();
    // 打印当前路径
    void printPath();
    // 删除文件夹
    void del_dir(const char *_path);
    // 创建空文件
    void make_file(const char *_path);
    // 删除文件
    void del_file(const char *_path);
    // 罗列目录内容
    void read_dir(const char *_path, bool JustName);
    // 复制文件、文件夹
    void copy_file_and_dir(const char *_path, const char *const _new_path);
    // 执行用户输入命令
    void call(GetInput &input);
    // 获取帮助文档
    void help();
    // 相对路径转化为绝对路径
    void absPath(std::string&);
};


#endif //DIR_DOCMAN_H
