#include "cUI.h"
using namespace std;

void cUI::welcome(){
	cout << "*****************************" << endl;
	cout << "*                           *" << endl;
	cout << "*         WELCOME           *" << endl;
	cout << "* press <enter> to continue *" << endl;
	cout << "*         ... ...           *" << endl;
	cout << "*                           *" << endl;
	cout << "*****************************" << endl;
}

// 储蓄卡账户的操作界面
int cUI::menu1(){
	cout << "主菜单:" << endl;
	cout << "\t1 - 账户信息" << endl;
	cout << "\t2 - 取款" << endl;
	cout << "\t3 - 存款" << endl;
	cout << "\t4 - 转账" << endl;
	cout << "\t5 - 修改密码" << endl;
	cout << "\t6 - 退卡" << endl;
	cout << "请输入操作序号: ";
	int input;
	cin >> input;
	return input;
}

// 信用卡账户的操作界面
int cUI::menu2(){
	cout << "主菜单:" << endl;
	cout << "\t1 - 账户信息" << endl;
	cout << "\t2 - 取款" << endl;
	cout << "\t3 - 还款" << endl;
	cout << "\t4 - 转账" << endl;
	cout << "\t5 - 修改密码" << endl;
	cout << "\t6 - 退卡" << endl;
	cout << "请输入操作序号: ";
	int input;
	cin >> input;
	return input;
}

void cUI::load(int number, vector<vector<string>> &users, Account *ac){
	cout << "           登录中...        " << endl;
	string account;
	while (true){
		cout << "请输入账号: ";
		cin >> account;
		for (int i = 1; i < number; i++){
			if (users[i][0] == account){
				ac->setAccount(users[i][0]);
				ac->setIslAccount(users[i][1] == "lAccount");
				ac->setName(users[i][2]);
				ac->setId(users[i][3]);
				ac->setPassword(users[i][4]);
				stringstream ss1;
				ss1 << users[i][5];
				double balance;
				ss1 >> balance;
				ac->setBalance(balance);
				stringstream ss2;
				ss2 << users[i][6];
				double Reputation;
				ss2 >> Reputation;
				ac->setReputation(Reputation);
				return;
			}
		}
		cout << "账号输入错误，请重新输入" << endl;
	}
}

bool cUI::password(const string& password){
	cout << "           登录中...        " << endl;
	int count = 0;
	string input;
	cout << "请输入密码: ";
	for (int i = 0; i < 3; i++){
		cin >> input;
		if (input == password){
			return true;
		}
		else{
			cout << "密码错误！" << endl;
			count++;
			if (count < 3){
				cout << "还有" << 3-count << "次输入机会"<< endl;
				cout << "请输入密码: ";
			}

		}
	}
	if(count >= 3){
		cout << "账号已被冻结，即将返回主界面..." << endl;
		return false;
	}
	return false;
}

double cUI::getMoney(const int n, Account &account){
	double money;
	int temp;
	switch (n){
	case 1:  // 取款, 输入整百且不超过额度
		while (true){
			cout << "请输入取款金额：";
			cin >> money;
			temp = int(money);
			if (money - temp != 0 || temp % 100 != 0 || money > 3000 || money < 100)
			{
				cout << "取款金额只能为100-3000的整百，请重新输入" << endl;
				continue;
			}
			if (account.isIslAccount() && (money - account.getBalance()) > account.getReputation()){
				cout << "超过可透支额度，请重新输入" << endl;
				continue;
			}
			if (!account.isIslAccount() && money > account.getBalance()){
				cout << "余额不足，请重新输入" << endl;
				continue;
			}
			break;
		}
		break;
	case 2:  // 存款 还款
		while (true){
			cout << "请投币：";
			cin >> money;
			if (money <= 0){
				cout << "输入金额有误，请重新输入" << endl;
				continue;
			}
			if (account.isIslAccount() && -account.getBalance() < money){
				cout << "还款金额不能超过欠款，请重新输入" << endl;
				continue;
			}
			break;
		}
		break;
	case 3:  // 转账
		while (true){
			cout << "请输入转账金额:";
			cin >> money;
			if (money <= 0){
				cout << "输入金额有误，请重新输入" << endl;
				continue;
			}
			if (account.isIslAccount() && (money - account.getBalance()) > account.getReputation()){
				cout << "超过可透支额度，请重新输入" << endl;
				continue;
			}
			if (!account.isIslAccount() && money > account.getBalance()){
				cout << "余额不足，请重新输入" << endl;
				continue;
			}
			break;
		}
		break;
	}
	return money;
}

void cUI::isSuccess(bool success){
	if (success)
		cout << "操作成功" << endl;
	else
		cout << "操作异常，请与银行工作人员联系" << endl;
	cout << "press <enter> to quit" << endl;
	cin.sync();
	cin.get();
}
