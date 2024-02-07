#ifndef STUDENT_CARD_H_
#define STUDENT_CARD_H_

#include <iostream>
#include <string>
#include <ctime>
#include <stack>
#include "SPECIAL_DEFINITION_MACRO.h"

class StudentCard
{
public:
	explicit StudentCard(
		std::int64_t account,
		std::time_t ccdate,
		std::time_t cedate,
		std::string pwd = "01234567",
		std::int16_t balance = 0
	)
		: kAccount(account),
		kCardCreationDate(ccdate),
		kCardExpirationDate(cedate),
		password(pwd),
		account_balance(balance) 
	{}

	~StudentCard();

	struct BillInfo
	{
		std::int64_t bill_num;
		std::time_t date;
		std::time_t amount;
	};

private:
	DISALLOW_COPY_AND_ASSIGN(StudentCard);

	const std::int64_t kAccount;				// 账户（直接使用学号作为账户）
	const std::time_t kCardCreationDate;		// 建卡日期
	const std::time_t kCardExpirationDate;		// 建卡有效期（直接使用预计毕业日期向后推迟一个月）
	std::string password;						// 账号密码 | [8, 16] | 英文大小写、数字
	std::int16_t account_balance;				// 账户余额 | [0, 50000]
	std::stack<BillInfo> expense_records;		// 消费记录
};


StudentCard::~StudentCard()
{
}


#endif // !STUDENT_CARD_H_
