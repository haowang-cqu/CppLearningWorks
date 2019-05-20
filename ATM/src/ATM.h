#ifndef ATM_H_
#define ATM_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Time.h"
#include "Account.h"
#include "CSV.h"

class ATM {
private:
	CSV *file;
	Account *account;  // 指向当前操作者账户的基类指针
public:
	ATM(CSV *file){
		this->file = file;
		this->account = NULL;
	}
	// 读入账户
	void setAccount(Account *account);
	// 存款  / 还款
	bool Deposit(double money);
	// 取款  / 借款
	bool Withdrow(int money);
	// 转账
	bool Tansfer(double money, std::string other);
	// 查询余额  / 欠款和信用额度
	void show();
	// 修改密码
	void changePassword(std::string password);
	// 保存操作记录
	void Record(int number, double money, std::string other="");
};

#endif /* ATM_H_ */
