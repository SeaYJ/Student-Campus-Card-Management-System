#include "student_card.h"

StudentCard::~StudentCard()
{
}

std::int64_t StudentCard::account() const
{
	return std::int64_t(kAccount);
}

std::string StudentCard::card_creation_date() const
{
	const struct tm* time_info = _localtime64(&(this->kCardCreationDate));		// �����õ� tm �ṹ������

	// Ϊ�����Ч�ʣ�����ֱ�Ӳ�����ԭʼ�ķ�ʽ���и�ʽ�������ַ���
	// ʵ�ʺ�������д����ͬ�ڣ�
	/* CPP ��Ч����
	* return TimeOutputModel::FormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� TimeOutputModel::FormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string StudentCard::card_creation_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardCreationDate));		// �����õ� tm �ṹ������

	return TimeOutputModel::FormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
}

std::string StudentCard::card_expiration_date() const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// �����õ� tm �ṹ������

	// Ϊ�����Ч�ʣ�����ֱ�Ӳ�����ԭʼ�ķ�ʽ���и�ʽ�������ַ���
	// ʵ�ʺ�������д����ͬ�ڣ�
	/* CPP ��Ч����
	* return TimeOutputModel::FormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� TimeOutputModel::FormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string StudentCard::card_expiration_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// �����õ� tm �ṹ������

	return TimeOutputModel::FormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
}

std::string StudentCard::password() const
{
	return std::string(_password);
}

std::uint16_t StudentCard::account_balance() const
{
	return std::uint16_t(_account_balance);
}

StudentCard& StudentCard::set_password(const std::string pwd)
{
	if (checkPassword(pwd)) {
		_password = pwd;
	}
	else {
		throw std::invalid_argument("The password is incorrect. The password should consist of 8 to 16 characters, using only letters or numbers.");
	}

	return *this;
}

StudentCard& StudentCard::set_balance(const std::uint16_t balance)
{
	if (checkAccountBalance(balance)) {
		_account_balance = balance;
	}
	else {
		throw std::invalid_argument("Account balance is abnormal. The account balance must be at least 0 yuan and should not exceed 50,000 yuan.");
	}

	return *this;
}

bool StudentCard::checkPassword(const std::string pwd) const
{
	// ��������Ƿ��� [8, 16] λ֮��
	if (pwd.length() < 8 || pwd.length() > 16) {
		return false;
	}

	// ��������Ƿ�ֻ������ĸ������
	for (char c : pwd) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return false;
		}
	}

	// �������Ҫ��
	return true;
}

bool StudentCard::checkAccountBalance(const std::uint16_t balance) const
{
	// ������Χ
	if (balance < 0 || balance > BALANCE_MAX_LIMIT) {
		return false;
	}

	// �������
	return true;
}

std::int64_t StudentCard::correctAccount(const std::int64_t account) const
{
	std::int64_t account_length = std::int64_t(std::log10(account)) + std::int64_t(1);

	// �����˻�λ������
	if (account_length > ACCOUNT_MAX_LENGTH) {
		// ��Ϊѧ���� StudentCard ��� const ������ֻ�ܸ�ֵһ�Ρ�
		// ���ԣ�������õ�ֵ���󣬾�Ӧ��ֱ�������������Ĵ�����
		// ���򣬴���� account ���޷����¸�ֵ
		throw std::invalid_argument("The 'account' exceeds maximum length.");
	}
	else if (account_length < ACCOUNT_MIN_LENGTH) {
		throw std::invalid_argument("The 'account' exceeds minimum length.");
	}

	// �������õ��˻�
	return account;
}

std::string StudentCard::correctPassword(const std::string pwd) const
{
	const std::string kDefaultPassword = "12345678";// Ĭ�ϵ��˻�����

	// ��������Ƿ�ֻ������ĸ������
	// �����������Ƿ��ַ���ֱ�ӷ���Ĭ������
	for (char c : pwd) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return kDefaultPassword;
		}
	}

	//////////////////////////////////
	// ������볤���Ƿ���[8, 16]λ֮��//
	//////////////////////////////////
	// ������볤�ȴ��� 16���ͽ�ȡ����ǰ 16 λ
	if (pwd.length() > 16) {
		return pwd.substr(0, PASSWORD_MAX_LENGTH);
	}
	// ������볤��С�� 8���ͷ���Ĭ������
	else if (pwd.length() < 8) {
		return kDefaultPassword;
	}

	// �������õ�����
	return pwd;
}

std::uint16_t StudentCard::correctAccountBalance(const std::uint16_t balance) const
{

	// ������С�� 0���ͷ�����Сֵ 0
	if (balance < 0) {
		return 0;
	}
	// ������������ֵ���ͷ������ֵ
	else if (balance > BALANCE_MAX_LIMIT) {
		return BALANCE_MAX_LIMIT;
	}

	// �������ý��
	return balance;
}

// ֧��Ĭ�ϴ�ӡ��Ϣ
std::ostream& operator<<(std::ostream& os, const StudentCard& stu_card)
{
	os	<< "�˻�\t" << stu_card.account() << "\n"
		<< "����\t" << "******" << "\n" 
		<< "���\t" << stu_card.account_balance() << "\n"
		<< "����\t" << stu_card.card_creation_date(TimeOutputModel::Date) << "\n"
		<< "����\t" << stu_card.card_expiration_date(TimeOutputModel::Date);

	return os;
}

// ֻ֧�֡����롱�����˻������޸�
std::istream& operator>>(std::istream& is, StudentCard& stu_card)
{
	// ���建����
	std::string password_buffer;
	std::uint16_t balance_buffer;

	std::cout << "����: ";
	is >> password_buffer;
	if (stu_card.checkPassword(password_buffer)) {
		stu_card._password = password_buffer;
	}
	else {
		throw std::invalid_argument("The password is incorrect. The password should consist of 8 to 16 characters, using only letters or numbers.");
	}

	std::cout << "�˻����: ";
	is >> balance_buffer;
	if (stu_card.checkAccountBalance(balance_buffer)) {
		stu_card._account_balance = balance_buffer;
	}
	else {
		throw std::invalid_argument("Account balance is abnormal. The account balance must be at least 0 yuan and should not exceed 50,000 yuan.");
	}

	return is;
}
