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

	// ȡ����
	std::int64_t account() const;
	std::string card_creation_date() const;
	std::string card_creation_date(const std::int8_t ops) const;
	std::string card_expiration_date() const;
	std::string card_expiration_date(const std::int8_t ops) const;
	std::string password() const;
	std::uint16_t account_balance() const;

	// �溯��
	StudentCard& set_password(const std::string pwd);
	StudentCard& set_balance(const std::uint16_t balance);

	// ��麯��
	bool checkPassword(const std::string pwd) const;
	bool checkAccountBalance(const std::uint16_t balance) const;

private:
	DISALLOW_COPY_AND_ASSIGN(StudentCard);
	const std::int8_t ACCOUNT_MAX_LENGTH = 15;		// account ����󳤶ȣ�ע���� STUDENT_ID_MAX_LENGTH ����һ�� 
	const std::int8_t ACCOUNT_MIN_LENGTH = 6;		// account ����󳤶ȣ�ע���� STUDENT_ID_MIN_LENGTH ����һ�� 
	const std::int8_t PASSWORD_MAX_LENGTH = 16;		// _password ����󳤶�
	const std::int8_t PASSWORD_MIN_LENGTH = 8;		// _password ����С����
	const std::uint16_t BALANCE_MAX_LIMIT = 50000;	// _account_balance ����޶�

	const std::int64_t kAccount;				// �˻���ֱ��ʹ��ѧ����Ϊ�˻���
	const std::time_t kCardCreationDate;		// ��������
	const std::time_t kCardExpirationDate;		// ������Ч�ڣ�ֱ��ʹ��Ԥ�Ʊ�ҵ��������Ƴ�һ���£�
	std::string _password;						// �˺����� | [8, 16]λ | Ӣ�Ĵ�Сд������
	std::uint16_t _account_balance;				// �˻���� | [0, 50000]
	std::stack<BillInfo> _expense_records;		// ���Ѽ�¼

	// ������
	std::int64_t correctAccount(const std::int64_t account) const;
	std::string correctPassword(const std::string pwd) const;
	std::uint16_t correctAccountBalance(const std::uint16_t balance) const;
};

#endif // !STUDENT_CARD_H_
