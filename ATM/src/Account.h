#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
#include <vector>

// 账户基类
class Account {
private:
	// 账户,账户类型,姓名,身份证号,密码,余额或欠款,信用额度
	std::string account;
	bool islAccount;  // 借款账户为true，存款账户为flase
	std::string name;
	std::string id;
	std::string password;
	double balance;   // 借款账户余额为负数
	double reputation;

public:
	const std::string& getAccount() const {
		return account;
	}
	void setAccount(const std::string& account) {
		this->account = account;
	}
	const std::string& getId() const {
		return id;
	}
	void setId(const std::string& id) {
		this->id = id;
	}
	const std::string& getName() const {
		return name;
	}
	void setName(const std::string& name) {
		this->name = name;
	}
	const std::string& getPassword() const {
		return password;
	}
	void setPassword(const std::string& password) {
		this->password = password;
	}
	double getBalance() const {
		return balance;
	}
	void setBalance(double balance) {
		this->balance = balance;
	}
	bool isIslAccount() const {
		return islAccount;
	}
	void setIslAccount(bool islAccount) {
		this->islAccount = islAccount;
	}
	double getReputation() const {
		return reputation;
	}
	void setReputation(double reputation) {
		this->reputation = reputation;
	}
	void show();
};
#endif /* ACCOUNT_H_ */
