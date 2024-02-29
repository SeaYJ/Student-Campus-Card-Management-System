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
	const struct tm* time_info = _localtime64(&(this->kCardCreationDate));		// 解析得到 tm 结构体数据

	// 为了提高效率，这里直接采用最原始的方式进行格式化日期字符串
	// 实际后面的所有代码等同于：
	/* CPP 等效代码
	* return TimeOutputModel::FormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 TimeOutputModel::FormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string StudentCard::card_creation_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardCreationDate));		// 解析得到 tm 结构体数据

	return TimeOutputModel::FormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
}

std::string StudentCard::card_expiration_date() const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// 解析得到 tm 结构体数据

	// 为了提高效率，这里直接采用最原始的方式进行格式化日期字符串
	// 实际后面的所有代码等同于：
	/* CPP 等效代码
	* return TimeOutputModel::FormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 TimeOutputModel::FormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string StudentCard::card_expiration_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// 解析得到 tm 结构体数据

	return TimeOutputModel::FormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
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
	// 检查密码是否在 [8, 16] 位之间
	if (pwd.length() < 8 || pwd.length() > 16) {
		return false;
	}

	// 检查密码是否只包含字母和数字
	for (char c : pwd) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return false;
		}
	}

	// 密码符合要求
	return true;
}

bool StudentCard::checkAccountBalance(const std::uint16_t balance) const
{
	// 金额超出范围
	if (balance < 0 || balance > BALANCE_MAX_LIMIT) {
		return false;
	}

	// 金额正常
	return true;
}

std::int64_t StudentCard::correctAccount(const std::int64_t account) const
{
	std::int64_t account_length = std::int64_t(std::log10(account)) + std::int64_t(1);

	// 设置账户位数过长
	if (account_length > ACCOUNT_MAX_LENGTH) {
		// 因为学号是 StudentCard 类的 const 常量，只能赋值一次。
		// 所以，如果设置的值错误，就应该直接抛弃错误对象的创建，
		// 否则，错误的 account 将无法重新赋值
		throw std::invalid_argument("The 'account' exceeds maximum length.");
	}
	else if (account_length < ACCOUNT_MIN_LENGTH) {
		throw std::invalid_argument("The 'account' exceeds minimum length.");
	}

	// 返回设置的账户
	return account;
}

std::string StudentCard::correctPassword(const std::string pwd) const
{
	const std::string kDefaultPassword = "12345678";// 默认的账户密码

	// 检查密码是否只包含字母和数字
	// 如果密码包含非法字符就直接返回默认密码
	for (char c : pwd) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return kDefaultPassword;
		}
	}

	//////////////////////////////////
	// 检查密码长度是否在[8, 16]位之间//
	//////////////////////////////////
	// 如果密码长度大于 16，就截取密码前 16 位
	if (pwd.length() > 16) {
		return pwd.substr(0, PASSWORD_MAX_LENGTH);
	}
	// 如果密码长度小于 8，就返回默认密码
	else if (pwd.length() < 8) {
		return kDefaultPassword;
	}

	// 返回设置的密码
	return pwd;
}

std::uint16_t StudentCard::correctAccountBalance(const std::uint16_t balance) const
{

	// 如果金额小于 0，就返回最小值 0
	if (balance < 0) {
		return 0;
	}
	// 如果金额大于最大值，就返回最大值
	else if (balance > BALANCE_MAX_LIMIT) {
		return BALANCE_MAX_LIMIT;
	}

	// 返回设置金额
	return balance;
}

// 支持默认打印信息
std::ostream& operator<<(std::ostream& os, const StudentCard& stu_card)
{
	os	<< "账户\t" << stu_card.account() << "\n"
		<< "密码\t" << "******" << "\n" 
		<< "余额\t" << stu_card.account_balance() << "\n"
		<< "开卡\t" << stu_card.card_creation_date(TimeOutputModel::Date) << "\n"
		<< "到期\t" << stu_card.card_expiration_date(TimeOutputModel::Date);

	return os;
}

// 只支持“密码”、“账户余额”的修改
std::istream& operator>>(std::istream& is, StudentCard& stu_card)
{
	// 定义缓冲区
	std::string password_buffer;
	std::uint16_t balance_buffer;

	std::cout << "密码: ";
	is >> password_buffer;
	if (stu_card.checkPassword(password_buffer)) {
		stu_card._password = password_buffer;
	}
	else {
		throw std::invalid_argument("The password is incorrect. The password should consist of 8 to 16 characters, using only letters or numbers.");
	}

	std::cout << "账户余额: ";
	is >> balance_buffer;
	if (stu_card.checkAccountBalance(balance_buffer)) {
		stu_card._account_balance = balance_buffer;
	}
	else {
		throw std::invalid_argument("Account balance is abnormal. The account balance must be at least 0 yuan and should not exceed 50,000 yuan.");
	}

	return is;
}
