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

	const std::int64_t kAccount;				// �˻���ֱ��ʹ��ѧ����Ϊ�˻���
	const std::time_t kCardCreationDate;		// ��������
	const std::time_t kCardExpirationDate;		// ������Ч�ڣ�ֱ��ʹ��Ԥ�Ʊ�ҵ��������Ƴ�һ���£�
	std::string password;						// �˺����� | [8, 16] | Ӣ�Ĵ�Сд������
	std::int16_t account_balance;				// �˻���� | [0, 50000]
	std::stack<BillInfo> expense_records;		// ���Ѽ�¼
};


StudentCard::~StudentCard()
{
}


#endif // !STUDENT_CARD_H_
