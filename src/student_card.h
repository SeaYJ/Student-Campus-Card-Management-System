#ifndef STUDENT_CARD_H_
#define STUDENT_CARD_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <stack>
#include "SPECIAL_DEFINITION_MACRO.h"
#include "time_output_model.h"

class StudentCard
{
	// 重载输出流操作符
	friend std::ostream& operator<<(std::ostream& os, const StudentCard& stu);

	// 重载输入流操作符
	friend std::istream& operator>>(std::istream& is, StudentCard& stu);
public:
	explicit StudentCard(
		std::int64_t account,
		std::time_t ccdate,
		std::time_t cedate,
		std::string pwd = "12345678",
		std::uint16_t balance = 0
	)
		: kAccount(correctAccount(account)),
		kCardCreationDate(ccdate),
		kCardExpirationDate(cedate),
		_password(correctPassword(pwd)),
		_account_balance(correctAccountBalance(balance))
	{}

	~StudentCard();

	struct BillInfo
	{
		std::int64_t bill_num;
		std::time_t date;
		std::time_t amount;
	};

	// 取函数
	std::int64_t account() const;
	std::string card_creation_date() const;
	std::string card_creation_date(const std::int8_t ops) const;
	std::string card_expiration_date() const;
	std::string card_expiration_date(const std::int8_t ops) const;
	std::string password() const;
	std::uint16_t account_balance() const;

	// 存函数
	StudentCard& set_password(const std::string pwd);
	StudentCard& set_balance(const std::uint16_t balance);

	// 检查函数
	bool checkPassword(const std::string pwd) const;
	bool checkAccountBalance(const std::uint16_t balance) const;

private:
	DISALLOW_COPY_AND_ASSIGN(StudentCard);
	const std::int8_t ACCOUNT_MAX_LENGTH = 15;		// account 的最大长度，注意与 STUDENT_ID_MAX_LENGTH 保持一致 
	const std::int8_t ACCOUNT_MIN_LENGTH = 6;		// account 的最大长度，注意与 STUDENT_ID_MIN_LENGTH 保持一致 
	const std::int8_t PASSWORD_MAX_LENGTH = 16;		// _password 的最大长度
	const std::int8_t PASSWORD_MIN_LENGTH = 8;		// _password 的最小长度
	const std::uint16_t BALANCE_MAX_LIMIT = 50000;	// _account_balance 最大限额

	const std::int64_t kAccount;				// 账户（直接使用学号作为账户）
	const std::time_t kCardCreationDate;		// 建卡日期
	const std::time_t kCardExpirationDate;		// 建卡有效期（直接使用预计毕业日期向后推迟一个月）
	std::string _password;						// 账号密码 | [8, 16]位 | 英文大小写、数字
	std::uint16_t _account_balance;				// 账户余额 | [0, 50000]
	std::stack<BillInfo> _expense_records;		// 消费记录

	// 纠错函数
	std::int64_t correctAccount(const std::int64_t account) const;
	std::string correctPassword(const std::string pwd) const;
	std::uint16_t correctAccountBalance(const std::uint16_t balance) const;
};

#endif // !STUDENT_CARD_H_
