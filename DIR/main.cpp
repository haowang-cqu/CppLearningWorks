#include <iostream>
#include "DocMan.h"
#include "GetInput.h"
using namespace std;

int main() {
    GetInput input;
    DocMan doc;
    /**
     * 循环获取执行用户命令，遇到exit命令终止循环
     */
     cout << "欢迎使用C++文件管理系统" << endl;
    while (true) {
        char *path = doc.getPath();
        cout << ">>>";
        input.get();
        if (input.getNumber() == 0)
            continue;
        if (input.isExit()) {
            cout << "感谢使用C++文件管理系统" << endl;
            break;
        }
        else
            doc.call(input);
    }
    return 0;
}