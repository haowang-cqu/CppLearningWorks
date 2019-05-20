#include "Account.h"
using namespace std;

void Account::show(){
	if(this->islAccount){
		cout << "\n\t账户类型: " << "借款帐户" << endl;
		cout << "\t当前欠款: " << -(this->balance) << endl;
		cout << "\t您的信誉度: " << this->reputation << endl;
	}
	else{
		cout << "\n\t账户类型: " << "存款帐户" << endl;
		cout << "\t当前余额: " << this->balance << endl;
	}

}
