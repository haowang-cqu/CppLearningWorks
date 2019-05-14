#include "csv.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    CSV csv("user.csv");
    vector<vector<string>> &file = csv.getFile();
    cout << "原表格~~~" << endl;
    for (int i = 0; i < csv.getRow(); i++)
    {
        for (int j = 0; j < csv.getCol(); j++)
        {
            cout << file[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "修改Bob的密码为765432~~~" << endl;
    for (int i = 0; i < csv.getRow(); i++)
    {
        if (file[i][0] == "Bob")
            file[i][2] = "765432";
    }
    for (int i = 0; i < csv.getRow(); i++)
    {
        for (int j = 0; j < csv.getCol(); j++)
        {
            cout << file[i][j] << "  ";
        }
        cout << endl;
    }
    csv.saveCSV();
    return 0;
}
