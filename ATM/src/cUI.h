#ifndef CUI_H_
#define CUI_H_
#include <iostream>
#include <vector>
#include <sstream>
#include "Account.h"

class cUI {
public:
	static void welcome();
	static int menu1();
	static int menu2();
	static void load(int number, std::vector<std::vector<std::string>> &, Account *);
	static bool password(const std::string &);
	// 获取并验证用户输入钱数的有效性, 并在输入有效后返回钱数
	static double getMoney(const int n, Account &account);
	static void isSuccess(bool success);
};
#endif /* CUI_H_ */
