//============================================================================
// Name        : ATM.cpp
// Author      : Bully
// Version     : 1.0
// Copyright   :
// Description : 模拟ATM, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>
#include <vector>
#include "ATM.h"
#include "Account.h"
#include "CSV.h"
#include "cUI.h"
using namespace std;

int main() {
	while(true){
		CSV accountlist;
		accountlist.openFile("E:\\cppworkspace\\ATM\\files\\Account.csv");
		ATM atm(&accountlist);
		Account account;
		int number = accountlist.getRow();  // 账号的个数
		cUI::welcome();
		cin.get();
		cUI::load(number, accountlist.getFile(), &account);
		bool pass = cUI::password(account.getPassword());
		if(!pass)   // 密码验证没通过
		{
			Sleep(3000);
			cout << endl;
			cin.sync();
			continue;
		}
		atm.setAccount(&account);
		while(true){
			int input;
			if (account.isIslAccount()){
				input = cUI::menu2();
			}
			else{
				input = cUI::menu1();
			}
			if (input == 6){
				cout << "退卡成功，即将返回主界面..." << endl;
				cout << endl;
				cin.sync();
				Sleep(3000);
				break;
			}
			int money;
			bool success;
			string newpassword1;
			string newpassword2;
			string other1;
			string other2;
			switch(input){
				case 1:
					atm.show();
					cout << "press <enter> to quit" << endl;
					cin.sync();
					cin.get();
					break;
				case 2:
					money = cUI::getMoney(1, account);
					success = atm.Withdrow(money);
					cUI::isSuccess(success);
					break;
				case 3:
					money = cUI::getMoney(2, account);
					success = atm.Deposit(money);
					cUI::isSuccess(success);
					break;
				case 4:
					money = cUI::getMoney(3, account);
					cout << "请输入收款账户: ";
					cin >> other1;
					cout << "请再次输入确认: ";
					cin >> other2;
					if (other1 == other2){
						success = atm.Tansfer(money, other1);
						cUI::isSuccess(success);
					}
					else{
						cout << "输入账户不一致，转账失败" << endl;
						cout << "press <enter> to quit" << endl;
						cin.sync();
						cin.get();
					}
					break;
				case 5:
					cout << "请输入新密码: ";
					cin >> newpassword1;
					cout << "请再次输入确认: ";
					cin >> newpassword2;
					if (newpassword1 == newpassword2){
						atm.changePassword(newpassword2);
						cout << "成功修改密码" << endl << endl;
					}
					else
						cout << "输入密码不一致，修改密码失败" << endl << endl;
					break;
				default:
					cout << "输入错误" << endl;
			}
		}
	}
	return 0;
}
