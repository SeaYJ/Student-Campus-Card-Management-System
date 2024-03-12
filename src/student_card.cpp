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
	* return TimeOutputModel::OutputFormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� TimeOutputModel::OutputFormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string StudentCard::card_creation_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardCreationDate));		// �����õ� tm �ṹ������

	return TimeOutputModel::OutputFormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
}

std::string StudentCard::card_expiration_date() const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// �����õ� tm �ṹ������

	// Ϊ�����Ч�ʣ�����ֱ�Ӳ�����ԭʼ�ķ�ʽ���и�ʽ�������ַ���
	// ʵ�ʺ�������д����ͬ�ڣ�
	/* CPP ��Ч����
	* return TimeOutputModel::OutputFormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� TimeOutputModel::OutputFormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string StudentCard::card_expiration_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// �����õ� tm �ṹ������

	return TimeOutputModel::OutputFormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
}

std::string StudentCard::password() const
{
	return std::string(_password);
}

coin StudentCard::account_balance() const
{
	return coin(_account_balance);
}

std::stack<BillInfo> StudentCard::all_expense_records() const
{
	return std::stack<BillInfo>(_expense_records);
}

StudentCard& StudentCard::set_password(const std::string pwd)
{
	if (CheckPassword(pwd)) {
		_password = pwd;
	}
	else {
		throw std::invalid_argument("The password is incorrect. The password should consist of 8 to 16 characters, using only letters or numbers.");
	}

	return *this;
}

StudentCard& StudentCard::set_balance(const coin balance)
{
	if (CheckAccountBalance(balance)) {
		_account_balance = balance;
	}
	else {
		throw std::invalid_argument("Account balance is abnormal. The account balance must be at least 0 yuan and should not exceed 50,000 yuan.");
	}

	return *this;
}

bool StudentCard::CheckPassword(const std::string pwd) const
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

bool StudentCard::CheckAccountBalance(const coin balance) const
{
	// ������Χ
	if (balance < float50("0.0") || balance > BALANCE_MAX_LIMIT) {
		return false;
	}

	// �������
	return true;
}

bool StudentCard::CheckTransactionAmount(const coin amount) const
{
	if (// ���׽�������С����
		amount < MIN_TRADING_VOLUME ||
		// ���׽����������
		amount > MAX_TRADING_VOLUME ||
		// ���׽�������С���׶�ȹ淶
		boostMul::fmod(amount, MIN_TRADING_LIMIT) != float50("0.0")) {

		// ���׽����Ϲ淶
		return false;
	}

	// ���׽����Ϲ淶
	return true;
}

StudentCard& StudentCard::Pay(const coin amount)
{
	// �������Ľ��׽���Ƿ�淶
	if (!CheckTransactionAmount(amount)) {
		throw std::invalid_argument(
			"The transaction amount cannot be less than the minimum transaction amount (" +
			boost::lexical_cast<std::string>(MIN_TRADING_VOLUME) +
			" Chinese Yuan), nor greater than the maximum transaction amount (" +
			boost::lexical_cast<std::string>(MAX_TRADING_VOLUME) +
			" Chinese Yuan). Additionally, the transaction amount must be a multiple of the minimum transaction limit (" +
			boost::lexical_cast<std::string>(MIN_TRADING_LIMIT) +
			" Chinese Yuan)."
		);
	}

	// ����˻�����Ƿ��㹻֧��
	const coin _account_balance_buffer = _account_balance - amount;
	if (_account_balance_buffer < BALANCE_MIN_LIMIT) {
		throw std::invalid_argument(
			"Sorry, but the minimum account requirement is " +
			boost::lexical_cast<std::string>(BALANCE_MIN_LIMIT) +
			" Chinese yuan. Transferring " +
			boost::lexical_cast<std::string>(amount) +
			" RMB out of the account would result in insufficient funds. Therefore, this transaction is canceled, and the account balance will remain unchanged."
		);
	}

	// ��������
	std::time_t current_time = time(nullptr);

	BillInfo order{};
	order.date = current_time;
	order.bill_num = GetUniqueOrderNumber();
	order.amount = -amount;

	_expense_records.push(order);

	// ������
	_account_balance = _account_balance_buffer;

	return *this;
}

StudentCard& StudentCard::Earn(const coin amount)
{
	// �������Ľ��׽���Ƿ�淶
	if (!CheckTransactionAmount(amount)) {
		throw std::invalid_argument(
			"The transaction amount cannot be less than the minimum transaction amount (" +
			boost::lexical_cast<std::string>(MIN_TRADING_VOLUME) +
			" Chinese Yuan), nor greater than the maximum transaction amount (" +
			boost::lexical_cast<std::string>(MAX_TRADING_VOLUME) +
			" Chinese Yuan). Additionally, the transaction amount must be a multiple of the minimum transaction limit (" +
			boost::lexical_cast<std::string>(MIN_TRADING_LIMIT) +
			" Chinese Yuan)."
		);
	}

	// ����˻�����Ƿ�����
	const coin _account_balance_buffer = _account_balance + amount;
	if (_account_balance_buffer > BALANCE_MAX_LIMIT) {
		throw std::invalid_argument(
			"For security reasons, the maximum account balance is " +
			boost::lexical_cast<std::string>(BALANCE_MAX_LIMIT) +
			" RMB. Adding " +
			boost::lexical_cast<std::string>(amount) +
			" RMB in this transaction would cause an overflow in the account balance. Therefore, the transaction is canceled, and the account balance remains unchanged."
		);
	}

	std::time_t current_time = time(nullptr);

	// ��������
	BillInfo order{};
	order.date = current_time;
	order.bill_num = GetUniqueOrderNumber();
	order.amount = amount;

	_expense_records.push(order);

	// ������
	_account_balance = _account_balance_buffer;

	return *this;
}

std::int64_t StudentCard::CorrectAccount(const std::int64_t account) const
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

std::string StudentCard::CorrectPassword(const std::string pwd) const
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

coin StudentCard::CorrectAccountBalance(const coin balance) const
{

	// ������С�� 0���ͷ�����Сֵ 0
	if (balance < float50("0.0")) {
		return coin("0");
	}
	// ������������ֵ���ͷ������ֵ
	else if (balance > BALANCE_MAX_LIMIT) {
		return BALANCE_MAX_LIMIT;
	}

	// �������ý��
	return balance;
}

std::string StudentCard::GetUniqueOrderNumber() const
{
	// ����UUID
	boost::uuids::random_generator generator;
	boost::uuids::uuid uuid = generator();

	// ��UUIDת��Ϊ�ַ������滻���ۺ�Ϊ�ո񣬲�ת��Ϊ��д
	std::string uuid_str = boost::uuids::to_string(uuid);
	uuid_str.erase(std::remove(uuid_str.begin(), uuid_str.end(), '-'), uuid_str.end());
	std::transform(uuid_str.begin(), uuid_str.end(), uuid_str.begin(), ::toupper);

	return uuid_str;
}

// ֧��Ĭ�ϴ�ӡ��Ϣ
std::ostream& operator<<(std::ostream& os, const StudentCard& stu_card)
{
	// ����������ȣ�2λС����
	// û��������ûᵼ�����������������ڣ�����ľ��Ȼ�������
	os << std::setiosflags(std::ios::fixed) << std::setprecision(2);

	os << "�˻�\t" << stu_card.account() << "\n"
		<< "����\t" << "******" << "\n"
		<< "���\t" << stu_card.account_balance() << "\n"
		<< "����\t" << stu_card.card_creation_date(TimeOutputModel::Date) << "\n"
		<< "����\t" << stu_card.card_expiration_date(TimeOutputModel::Date);

	// �ָ�Ĭ�������������
	os << std::resetiosflags(std::ios::fixed) << std::setprecision(std::numeric_limits<double>::digits10);

	return os;
}

// ֻ֧�֡����롱�����˻������޸�
std::istream& operator>>(std::istream& is, StudentCard& stu_card)
{
	// ���建����
	std::string password_buffer;
	coin balance_buffer;

	std::cout << "����: ";
	is >> password_buffer;
	if (stu_card.CheckPassword(password_buffer)) {
		stu_card._password = password_buffer;
	}
	else {
		throw std::invalid_argument("The password is incorrect. The password should consist of 8 to 16 characters, using only letters or numbers.");
	}

	std::cout << "�˻����: ";
	is >> balance_buffer;
	if (stu_card.CheckAccountBalance(balance_buffer)) {
		stu_card._account_balance = balance_buffer;
	}
	else {
		throw std::invalid_argument("Account balance is abnormal. The account balance must be at least 0 yuan and should not exceed 50,000 yuan.");
	}

	return is;
}
