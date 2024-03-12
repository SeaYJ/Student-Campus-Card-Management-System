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
	* return TimeOutputModel::OutputFormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 TimeOutputModel::OutputFormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string StudentCard::card_creation_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardCreationDate));		// 解析得到 tm 结构体数据

	return TimeOutputModel::OutputFormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
}

std::string StudentCard::card_expiration_date() const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// 解析得到 tm 结构体数据

	// 为了提高效率，这里直接采用最原始的方式进行格式化日期字符串
	// 实际后面的所有代码等同于：
	/* CPP 等效代码
	* return TimeOutputModel::OutputFormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 TimeOutputModel::OutputFormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string StudentCard::card_expiration_date(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kCardExpirationDate));	// 解析得到 tm 结构体数据

	return TimeOutputModel::OutputFormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
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

bool StudentCard::CheckAccountBalance(const coin balance) const
{
	// 金额超出范围
	if (balance < float50("0.0") || balance > BALANCE_MAX_LIMIT) {
		return false;
	}

	// 金额正常
	return true;
}

bool StudentCard::CheckTransactionAmount(const coin amount) const
{
	if (// 交易金额低于最小限制
		amount < MIN_TRADING_VOLUME ||
		// 交易金额超过最大限制
		amount > MAX_TRADING_VOLUME ||
		// 交易金额不符合最小交易额度规范
		boostMul::fmod(amount, MIN_TRADING_LIMIT) != float50("0.0")) {

		// 交易金额不符合规范
		return false;
	}

	// 交易金额符合规范
	return true;
}

StudentCard& StudentCard::Pay(const coin amount)
{
	// 检查输入的交易金额是否规范
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

	// 检查账户金额是否足够支付
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

	// 创建订单
	std::time_t current_time = time(nullptr);

	BillInfo order{};
	order.date = current_time;
	order.bill_num = GetUniqueOrderNumber();
	order.amount = -amount;

	_expense_records.push(order);

	// 余额计算
	_account_balance = _account_balance_buffer;

	return *this;
}

StudentCard& StudentCard::Earn(const coin amount)
{
	// 检查输入的交易金额是否规范
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

	// 检查账户金额是否会溢出
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

	// 创建订单
	BillInfo order{};
	order.date = current_time;
	order.bill_num = GetUniqueOrderNumber();
	order.amount = amount;

	_expense_records.push(order);

	// 余额计算
	_account_balance = _account_balance_buffer;

	return *this;
}

std::int64_t StudentCard::CorrectAccount(const std::int64_t account) const
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

std::string StudentCard::CorrectPassword(const std::string pwd) const
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

coin StudentCard::CorrectAccountBalance(const coin balance) const
{

	// 如果金额小于 0，就返回最小值 0
	if (balance < float50("0.0")) {
		return coin("0");
	}
	// 如果金额大于最大值，就返回最大值
	else if (balance > BALANCE_MAX_LIMIT) {
		return BALANCE_MAX_LIMIT;
	}

	// 返回设置金额
	return balance;
}

std::string StudentCard::GetUniqueOrderNumber() const
{
	// 生成UUID
	boost::uuids::random_generator generator;
	boost::uuids::uuid uuid = generator();

	// 将UUID转换为字符串，替换破折号为空格，并转换为大写
	std::string uuid_str = boost::uuids::to_string(uuid);
	uuid_str.erase(std::remove(uuid_str.begin(), uuid_str.end(), '-'), uuid_str.end());
	std::transform(uuid_str.begin(), uuid_str.end(), uuid_str.begin(), ::toupper);

	return uuid_str;
}

// 支持默认打印信息
std::ostream& operator<<(std::ostream& os, const StudentCard& stu_card)
{
	// 设置输出精度（2位小数）
	// 没有这个设置会导致四舍五入的情况存在，输出的精度会有问题
	os << std::setiosflags(std::ios::fixed) << std::setprecision(2);

	os << "账户\t" << stu_card.account() << "\n"
		<< "密码\t" << "******" << "\n"
		<< "余额\t" << stu_card.account_balance() << "\n"
		<< "开卡\t" << stu_card.card_creation_date(TimeOutputModel::Date) << "\n"
		<< "到期\t" << stu_card.card_expiration_date(TimeOutputModel::Date);

	// 恢复默认输出精度设置
	os << std::resetiosflags(std::ios::fixed) << std::setprecision(std::numeric_limits<double>::digits10);

	return os;
}

// 只支持“密码”、“账户余额”的修改
std::istream& operator>>(std::istream& is, StudentCard& stu_card)
{
	// 定义缓冲区
	std::string password_buffer;
	coin balance_buffer;

	std::cout << "密码: ";
	is >> password_buffer;
	if (stu_card.CheckPassword(password_buffer)) {
		stu_card._password = password_buffer;
	}
	else {
		throw std::invalid_argument("The password is incorrect. The password should consist of 8 to 16 characters, using only letters or numbers.");
	}

	std::cout << "账户余额: ";
	is >> balance_buffer;
	if (stu_card.CheckAccountBalance(balance_buffer)) {
		stu_card._account_balance = balance_buffer;
	}
	else {
		throw std::invalid_argument("Account balance is abnormal. The account balance must be at least 0 yuan and should not exceed 50,000 yuan.");
	}

	return is;
}
