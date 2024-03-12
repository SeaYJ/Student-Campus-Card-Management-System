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
	// ���������������
	friend std::ostream& operator<<(std::ostream& os, const StudentCard& stu);

	// ����������������
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

	// ȡ����
	std::int64_t account() const;
	std::string card_creation_date() const;
	std::string card_creation_date(const std::int8_t ops) const;
	std::string card_expiration_date() const;
	std::string card_expiration_date(const std::int8_t ops) const;
	std::string password() const;
	coin account_balance() const;
	std::stack<BillInfo> all_expense_records() const;

	// �溯��
	StudentCard& set_password(const std::string pwd);
	StudentCard& set_balance(const coin balance);

	// ��麯��
	bool CheckPassword(const std::string pwd) const;
	bool CheckAccountBalance(const coin balance) const;
	bool CheckTransactionAmount(const coin amount) const;

	// ���ܺ���
	StudentCard& Pay(const coin amount);
	StudentCard& Earn(const coin amount);

private:
	DISALLOW_COPY_AND_ASSIGN(StudentCard);
	const std::int8_t ACCOUNT_MAX_LENGTH = 15;				// account ����󳤶ȣ�ע���� STUDENT_ID_MAX_LENGTH ����һ�� 
	const std::int8_t ACCOUNT_MIN_LENGTH = 6;				// account ����󳤶ȣ�ע���� STUDENT_ID_MIN_LENGTH ����һ�� 
	const std::int8_t PASSWORD_MAX_LENGTH = 16;				// _password ����󳤶�
	const std::int8_t PASSWORD_MIN_LENGTH = 8;				// _password ����С����
	const float50 BALANCE_MAX_LIMIT = float50("50000.0");	// _account_balance �ɴ洢������޶�
	const float50 BALANCE_MIN_LIMIT = float50("0.0");		// _account_balance �ɴ洢����С�޶�

	const float50 MAX_TRADING_VOLUME = float50("2000.0");	// ����׽��
	const float50 MIN_TRADING_LIMIT = float50("0.01");		// ��С���׶��
	const float50 MIN_TRADING_VOLUME = float50("0.01");		// ��С���׽��

	const std::int64_t kAccount;				// �˻���ֱ��ʹ��ѧ����Ϊ�˻���
	const std::time_t kCardCreationDate;		// ��������
	const std::time_t kCardExpirationDate;		// ������Ч�ڣ�ֱ��ʹ��Ԥ�Ʊ�ҵ��������Ƴ�һ���£�
	std::string _password;						// �˺����� | [8, 16]λ | Ӣ�Ĵ�Сд������
	coin _account_balance;						// �˻���� | [0, 50000]
	std::stack<BillInfo> _expense_records;		// ���Ѽ�¼

	// ������
	std::int64_t CorrectAccount(const std::int64_t account) const;
	std::string CorrectPassword(const std::string pwd) const;
	coin CorrectAccountBalance(const coin balance) const;

	// ˽�й��ܺ���
	std::string GetUniqueOrderNumber() const;
};

#endif // !STUDENT_CARD_H_
