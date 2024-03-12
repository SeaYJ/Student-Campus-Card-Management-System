#ifndef STUDENT_CARD_H_
#define STUDENT_CARD_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "SPECIAL_DEFINITION_MACRO.h"
#include "time_io_model.h"
#include "bill_info.h"

#ifndef NAMESPACE_DEF_BOOSTMUL
#define NAMESPACE_DEF_BOOSTMUL
namespace boostMul = boost::multiprecision;
#endif // NAMESPACE_DEF_BOOSTMUL

#ifndef TYPE_DEF_COIN
#define TYPE_DEF_COIN
typedef boostMul::cpp_dec_float_50 coin;
#endif // !TYPED_EFL_COIN

#ifndef TYPE_DEF_FLOAT50
#define TYPE_DEF_FLOAT50
typedef boostMul::cpp_dec_float_50 float50;
#endif // !TYPE_DEF_FLOAT50

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
		coin balance = coin("0.0")
	)
		: kAccount(CorrectAccount(account)),
		kCardCreationDate(ccdate),
		kCardExpirationDate(cedate),
		_password(CorrectPassword(pwd)),
		_account_balance(CorrectAccountBalance(balance))
	{}

	~StudentCard();

	// 取函数
	std::int64_t account() const;
	std::string card_creation_date() const;
	std::string card_creation_date(const std::int8_t ops) const;
	std::string card_expiration_date() const;
	std::string card_expiration_date(const std::int8_t ops) const;
	std::string password() const;
	coin account_balance() const;
	std::stack<BillInfo> all_expense_records() const;

	// 存函数
	StudentCard& set_password(const std::string pwd);
	StudentCard& set_balance(const coin balance);

	// 检查函数
	bool CheckPassword(const std::string pwd) const;
	bool CheckAccountBalance(const coin balance) const;
	bool CheckTransactionAmount(const coin amount) const;

	// 功能函数
	StudentCard& Pay(const coin amount);
	StudentCard& Earn(const coin amount);

private:
	DISALLOW_COPY_AND_ASSIGN(StudentCard);
	const std::int8_t ACCOUNT_MAX_LENGTH = 15;				// account 的最大长度，注意与 STUDENT_ID_MAX_LENGTH 保持一致 
	const std::int8_t ACCOUNT_MIN_LENGTH = 6;				// account 的最大长度，注意与 STUDENT_ID_MIN_LENGTH 保持一致 
	const std::int8_t PASSWORD_MAX_LENGTH = 16;				// _password 的最大长度
	const std::int8_t PASSWORD_MIN_LENGTH = 8;				// _password 的最小长度
	const float50 BALANCE_MAX_LIMIT = float50("50000.0");	// _account_balance 可存储的最大限额
	const float50 BALANCE_MIN_LIMIT = float50("0.0");		// _account_balance 可存储的最小限额

	const float50 MAX_TRADING_VOLUME = float50("2000.0");	// 最大交易金额
	const float50 MIN_TRADING_LIMIT = float50("0.01");		// 最小交易额度
	const float50 MIN_TRADING_VOLUME = float50("0.01");		// 最小交易金额

	const std::int64_t kAccount;				// 账户（直接使用学号作为账户）
	const std::time_t kCardCreationDate;		// 建卡日期
	const std::time_t kCardExpirationDate;		// 建卡有效期（直接使用预计毕业日期向后推迟一个月）
	std::string _password;						// 账号密码 | [8, 16]位 | 英文大小写、数字
	coin _account_balance;						// 账户余额 | [0, 50000]
	std::stack<BillInfo> _expense_records;		// 消费记录

	// 纠错函数
	std::int64_t CorrectAccount(const std::int64_t account) const;
	std::string CorrectPassword(const std::string pwd) const;
	coin CorrectAccountBalance(const coin balance) const;

	// 私有功能函数
	std::string GetUniqueOrderNumber() const;
};

#endif // !STUDENT_CARD_H_
