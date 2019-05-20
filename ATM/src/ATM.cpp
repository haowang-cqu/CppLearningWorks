#include "ATM.h"
using namespace std;

void ATM::setAccount(Account *account) {
	this->account = account;
}

// 存款  /  还款
bool ATM::Deposit(double money) {
	vector<vector<string>> &file = this->file->getFile();
	this->account->setBalance(this->account->getBalance() + money);
	for (int i = 1; i < this->file->getRow(); i++) {
		if (this->account->getAccount() == file[i][0]) {
			stringstream ss;
			ss << this->account->getBalance();
			ss >> file[i][5];
			this->file->saveCSV();   // 存入文件
			if (account->isIslAccount()) {
				Record(3, money);
				return true;
			}
			Record(1, money);  // 保存操作记录
			return true;
		}
	}
	return false;
}

// 取款  / 借款
bool ATM::Withdrow(int money) {
	vector<vector<string>> &file = this->file->getFile();
	this->account->setBalance(this->account->getBalance() - money);
	for (int i = 1; i < this->file->getRow(); i++) {
		if (this->account->getAccount() == file[i][0]) {
			stringstream ss;
			ss << this->account->getBalance();
			ss >> file[i][5];
			this->file->saveCSV();   // 存入文件
			Record(2, money);   	 // 保存操作记录
			return true;
		}
	}
	return false;
}

// 转账
bool ATM::Tansfer(double money, string other) {
	vector<vector<string>> &file = this->file->getFile();
	this->account->setBalance(this->account->getBalance() - money);
	for (int i = 1; i < this->file->getRow(); i++) {
		if (this->account->getAccount() == file[i][0]) {
			stringstream ss;
			ss << this->account->getBalance();
			ss >> file[i][5];
		}
		if (other == file[i][0]) {
			double otherMoney;
			stringstream s1;
			s1 << file[i][5];
			s1 >> otherMoney;
			otherMoney += money;
			stringstream s2;
			s2 << otherMoney;
			s2 >> file[i][5];
		}
	}
	this->file->saveCSV();   // 存入文件
	Record(4, money, other);  // 保存操作记录
	return true;
}

// 查询余额  / 欠款和信用额度
void ATM::show() {
	this->account->show();
}

// 修改密码
void ATM::changePassword(std::string password) {
	vector<vector<string>> &file = this->file->getFile();
	for (int i = 1; i < this->file->getRow(); i++) {
		if (this->account->getAccount() == file[i][0]) {
			file[i][4] = password;
			this->file->saveCSV();
		}
	}
}

void ATM::Record(int number, double money, string other) {
	ofstream out_file;
	out_file.open("E:\\cppworkspace\\ATM\\files\\Record.txt", ios::app); // 打开文件，追加操作记录
	out_file << endl;
	out_file << "时间：" << Time::getTime() << endl;
	out_file << "账户：" << this->account->getAccount() << endl;
	out_file << "操作类型：";
	switch (number) {
	case 1:
		out_file << "存款" << endl;
		out_file << "详情：" << "存入" << money << "元" << endl;
		break;
	case 2:
		out_file << "取款" << endl;
		out_file << "详情：" << "取出" << money << "元" << endl;
		break;
	case 3:
		out_file << "还款" << endl;
		out_file << "详情：" << "还款" << money << "元" << endl;
		break;
	case 4:
		out_file << "转账" << endl;
		out_file << "详情：" << "转出" << money << "元" << endl;
		out_file << "收款账户：" << other << endl;
		break;
	}
	if (account->isIslAccount()) {
		out_file << "欠款：" << -this->account->getBalance() << endl;
		out_file << "信誉度：" << this->account->getReputation() << endl;
	} else {
		out_file << "余额：" << this->account->getBalance() << endl;
	}
}
