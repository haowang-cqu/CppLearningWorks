//
// Created by bully on 19-5-9.
//

#include <iomanip>
#include <fstream>
#include "DocMan.h"
using namespace std;

DocMan::DocMan()
{
    strcpy(this->new_path, "0");
    char temp[1024] = {0};
    int cnt = readlink("/proc/self/exe", temp, 1024);
    for (int i = cnt-1; i >= 0; i--)
    {
        if (temp[i] != '/')
            temp[i] = 0;
        else {
            temp[i] = 0;
            break;
        }
    }
    strcpy(this->path, temp);
}

void DocMan::setPath(const char *path) {
    strcpy(this->path, path);
}

void DocMan::setNewpath(const char *new_path) {
    strcpy(this->new_path, new_path);
}

char* DocMan::getPath() {
    return path;
}

void DocMan::printPath() {
    cout << this->path << endl;
}

void DocMan::make_dir(const char *_path) {
    int test = mkdir(_path,0777);
    if(test != 0)
        perror(_path);
    return;
}

void DocMan::del_dir(const char* _path)
{
    DIR *dirp = opendir(_path);
    if (dirp == NULL)
    {
        perror(_path);
        return;
    }
    struct dirent *entry;
    int ret;
    while(1)
    {
        entry = readdir(dirp);
        if (entry == NULL)
            break;
        if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
            continue;
        char buf[1024];
        snprintf(buf, 1024, "%s%s%s", _path, "/" , entry->d_name);
        ret = remove(buf);
        if (ret == -1)
        {
            if (errno == ENOTEMPTY)
            {
                del_dir(buf);
                continue;
            }
            perror(buf);
            return;
        }

    }
    closedir(dirp);
    ret = rmdir(_path);
    if (ret == -1)
    {
        perror(_path);
    }
    return;
}

void DocMan::make_file(const char *_path) {
    int test = open(_path,O_WRONLY|O_CREAT|O_EXCL, 0777);
    if (test == -1)
        perror(_path);
    close(test);    // 关闭文件
    return;
}

void DocMan::del_file(const char *_path) {
    int test = unlink(_path);
    if (test == -1)
        perror(_path);
    return;
}

void DocMan::read_dir(const char *_path, bool JustName) {
    DIR *dirp = opendir(_path);
    if (dirp == NULL)
    {
        perror(_path);
        return;
    }
    dirent *direntp;
    char buf[1024];           // 储存路径+文件名
    while ((direntp = readdir(dirp)) != NULL)
    {
        if (strcmp(direntp->d_name, ".")==0||strcmp(direntp->d_name, "..")==0)
            continue;
        if (JustName)
        {
            cout << direntp->d_name << endl;
        }
        else
        {
            sprintf(buf, "%s%s%s", _path, "/",direntp->d_name);
            struct stat statbuf;
            if (stat(buf, &statbuf) == -1)
            {
                cerr << "Get stat on " << buf << " Error: " << endl;
                cerr << strerror(errno) << endl;
            }
            long long file_size = statbuf.st_size;
            stringstream ss;
            if (file_size > 1024)
                ss << "size:" << file_size/1024 << "KB";
            else
                ss << "size:" << file_size << "B";
            string file_size_s;
            ss >> file_size_s;
            char time[100];
            strcpy(time, ctime(&statbuf.st_size));
            time[strlen(time)- 1] = 0;  // 删除末尾自带的换行符
            cout.setf(ios::left);
            cout << setw(15) <<file_size_s;
            cout << time << "    " << direntp->d_name << endl;
        }
    }
    closedir(dirp);
}

void DocMan::copy_file_and_dir(const char *_path, const char *const _new_path) {
    struct stat cur_file;
    stat(_path, &cur_file);

    if (S_ISDIR(cur_file.st_mode))       // 如果当前路径是文件夹
    {
        DIR *cur_dir;
        dirent *cur_ent;

        if ((cur_dir = opendir(_path)) == NULL)     // 打开文件夹失败
        {
            perror(_path);
            return;
        }
        if (access(_new_path, F_OK))              // 文件夹不存在，创建目标文件夹
        {
            int test = mkdir(_new_path, S_IRWXU);
            if(test != 0) {
                perror(_new_path);
                return;
            }
        }
        while ((cur_ent = readdir(cur_dir)) != NULL)   // 递归复制子目录
        {
            if (strcmp(cur_ent->d_name, ".") && strcmp(cur_ent->d_name, ".."))  // 不为./..目录
            {
                copy_file_and_dir(((string) _path + "/" + cur_ent->d_name).c_str(),
                        ((string) _new_path + "/" + cur_ent->d_name).c_str());
            }
        }
        closedir(cur_dir);
        return;
    }
    else  // 拷贝文件
    {
        if (_path == _new_path)
            return;
        fstream fsin, fsout;
        fsin.open(_path, ios::in|ios::binary);
        fsout.open(_new_path, ios::out|ios::binary);
        fsout << fsin.rdbuf();
        return;
    }
}

void DocMan::call(GetInput &input) {
    vector<string> cmd(input.getInput());
    int number = input.getNumber();
    if (cmd[0] == "pwd")
    {
        if (number > 1)
        {
            cout << "pwd不需要参数" << endl;
            return;
        }
        this->printPath();
        return;
    }
    if (cmd[0] == "cd")
    {
        if (number == 1)
        {
            cout << "cd缺乏参数" << endl;
            return;
        }
        if (number > 2)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        DIR *dp = opendir(cmd[1].c_str());
        if (dp == NULL)
        {
            perror(cmd[1].c_str());
            return;
        }
        else
        {
            strcpy(this->path, cmd[1].c_str());
            closedir(dp);
            return;
        }
    }
    if (cmd[0] == "help")
    {
        if (number > 1)
        {
            cout << "help不需要参数" << endl;
            return;
        }
        this->help();
        return;
    }
    if (cmd[0] == "mkdir")
    {
        if (number == 1)
        {
            cout << "mkdir缺乏参数" << endl;
            return;
        }
        if (number > 2)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        string temp = cmd[1];
        this->make_dir(temp.c_str());
        return;
    }
    if (cmd[0] == "touch")
    {
        if (number == 1)
        {
            cout << "mkdir缺乏参数" << endl;
            return;
        }
        if (number > 2)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        string temp = cmd[1];
        this->make_file(temp.c_str());
        return;
    }
    if (cmd[0] == "rm")
    {
        if (number == 1)
        {
            cout << "rm缺乏参数" << endl;
            return;
        }
        if (number > 2)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        string temp = cmd[1];
        this->del_file(temp.c_str());
        return;
    }
    if (cmd[0] == "rmdir")
    {
        if (number == 1)
        {
            cout << "rmdir缺乏参数" << endl;
            return;
        }
        if (number > 2)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        string temp = cmd[1];
        this->del_dir(temp.c_str());
        return;
    }
    if (cmd[0] == "ls")
    {
        if (number == 1)
        {
            this->read_dir(this->path, true);
            return;
        }
        if (number == 2)
        {
            if (cmd[1] == "-l")
            {
                this->read_dir(this->path, false);
                return;
            }
            absPath(cmd[1]);
            string temp = cmd[1];
            this->read_dir(temp.c_str(), true);
            return;
        }
        if (number == 3)
        {
            if (cmd[1] == "-l")
            {
                absPath(cmd[2]);
                string temp = cmd[2];
                this->read_dir(temp.c_str(), false);
            }
            else
            {
                cout << "输入错误" << endl;
            }
            return;
        }
        else
        {
            cout << "参数过多" << endl;
            return;
        }
    }
    if (cmd[0] == "cp")
    {
        if (number < 3)
        {
            cout << "cp缺乏参数" << endl;
            return;
        }
        if (number > 3)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        absPath(cmd[2]);
        string temp1 = cmd[1];
        string temp2 = cmd[2];
        this->copy_file_and_dir(temp1.c_str(), temp2.c_str());
        return;
    }
    if (cmd[0] == "mv")
    {
        if (number < 3)
        {
            cout << "mv缺乏参数" << endl;
            return;
        }
        if (number > 3)
        {
            cout << "参数过多" << endl;
            return;
        }
        absPath(cmd[1]);
        absPath(cmd[2]);
        string temp1 = cmd[1];
        string temp2 = cmd[2];
        this->copy_file_and_dir(temp1.c_str(), temp2.c_str());
        struct stat cur_file;
        stat(temp1.c_str(), &cur_file);
        if (S_ISDIR(cur_file.st_mode))       // 如果当前路径是文件夹
            del_dir(temp1.c_str());
        else
            del_file(temp1.c_str());
        return;
    }
    else
    {
        cout << "未找到命令" << cmd[0] << endl;
        cout << "输入 help --<enter> 获取帮助" << endl;
        return;
    }
}


void DocMan::help() {
    cout << "pwd  "  << "查看当前路径" << endl;                                  // 已实现
    cout << "mkdir [path]  " << "新建文件夹" << endl;                            // 已实现
    cout << "rmdir [path]  " << "删除文件夹和文件夹内所有文件" << endl;
    cout << "touch [path]  " << "新建空文件" << endl;                            // 已实现
    cout << "cd [path]  " << "切换目录" << endl;                                 // 已实现
    cout << "rm [path]  " << "删除文件" << endl;                                 // 已实现
    cout << "mv [path] [new path]  " << "移动文件夹或者文件到指定路径" << endl;
    cout << "cp [path] [new path]  " << "复制文件或文件夹到指定路径" << endl;
    cout << "ls [-l] [path]  " << "罗列文件夹下的内容，-l参数可查看详细信息" << endl; // 已实现
    cout << "exit  " << "退出文件管理系统" << endl;                                // 已实现
}

void DocMan::absPath(std::string &path) {
    if (path[0] == '/')  // 第一个字符为'/'视为绝对路径直接返回
        return;
    string temp(this->path);
    path = temp + '/' + path;
    if (path[path.length() - 1] != '/')
        path += '/';
    vector<string> before, after;
    temp.clear();
    for (int j = 0; j < path.size(); j++)
    {
        if(path[j] != '/')
        {
            temp += path[j];
        }
        else
        {
            before.push_back(temp);
            temp.clear();
        }
    }
    while (!before.empty())
    {
        if (before.back() != "..")
        {
            temp = before.back();
            after.push_back(temp);
            before.pop_back();
        }
        else
        {
            before.pop_back();
            before.pop_back();
        }
    }
    while (!after.empty())
    {
        before.push_back(after.back());
        after.pop_back();
    }
    path.clear();
    for (int k = 0; k < before.size(); k++)
    {
        path += before[k];
        if (k != before.size() - 1)
            path += '/';
    }
}