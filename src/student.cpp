#include "student.h"

Student::~Student()
{
	delete _student_card;
}

std::string Student::name() const
{
	return std::string(this->kName);
}

std::string Student::sex() const
{
	return std::string(this->kSex);
}

std::string Student::birthday() const
{
	const struct tm* time_info = _localtime64(&(this->kBirthday));				// 解析得到 tm 结构体数据

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

std::string Student::birthday(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kBirthday));				// 解析得到 tm 结构体数据

	return TimeOutputModel::FormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
}

std::string Student::admission_date() const
{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// 解析得到 tm 结构体数据

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

std::string Student::admission_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// 解析得到 tm 结构体数据

	return TimeOutputModel::FormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
}

std::string Student::expected_graduation_date() const
{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// 解析得到 tm 结构体数据

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

std::string Student::expected_graduation_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// 解析得到 tm 结构体数据

	return TimeOutputModel::FormatTime(time_info, ops);							// 返回由 ops 确定的时间字串组合
}

std::int64_t Student::student_id() const
{
	return std::int64_t(this->kStudentID);
}

std::string Student::college() const
{
	return std::string(this->_college);
}

std::string Student::classroom() const
{
	return std::string(this->_classroom);
}

Student& Student::set_college(const std::string college)
{
	// 长度检查
	if (checkCollegeName(college)) {
		this->_college = college;
	}
	else {
		throw std::invalid_argument("College name is not valid.");
	}

	return *this;
}

Student& Student::set_classroom(const std::string classroom)
{
	// 长度检查
	if (checkClassroomName(classroom)) {
		this->_classroom = classroom;
	}
	else {
		throw std::invalid_argument("Classroom name is not valid.");
	}

	return *this;
}

bool Student::checkCollegeName(const std::string college) const
{
	if (college.length() > COLLEGE_NAME_MAX_LENGTH) {
		return false;
	}

	return true;
}

bool Student::checkClassroomName(const std::string classroom) const
{
	if (classroom.length() > CLASSROOM_NAME_MAX_LENGTH) {
		return false;
	}

	return true;
}

std::string Student::correctName(const std::string name) const
{
	// 当名字超出最大长度，
	// 仅显示部分内容，并用省略号显示
	if (name.length() > NAME_MAX_LENGTH) {
		std::string name_with_omitted_char = name.substr(0, (NAME_MAX_LENGTH - std::int8_t(3)));
		name_with_omitted_char.append("...");
		return name_with_omitted_char;
	}

	// 返回设置名字
	return name;
}

std::string Student::correctSex(const std::string sex) const
{
	// 当性别超出最大长度，
	// 仅显示部分内容，并用省略号显示
	if (sex.length() > SEX_MAX_LENGTH) {
		std::string sex_with_omitted_char = sex.substr(0, (SEX_MAX_LENGTH - std::int8_t(3)));
		sex_with_omitted_char.append("...");
		return sex_with_omitted_char;
	}

	// 返回设置性别
	return sex;
}

std::int64_t Student::correctStudentID(const std::int64_t student_id) const
{
	std::int64_t student_id_length = std::int64_t(std::log10(student_id)) + std::int64_t(1);

	// 设置学号位数过长
	if (student_id_length > STUDENT_ID_MAX_LENGTH) {
		// 因为学号是 Student 类的 const 常量，只能赋值一次。
		// 所以，如果设置的值错误，就应该直接抛弃错误对象的创建，
		// 否则，错误的 student id 将无法重新赋值
		throw std::invalid_argument("The 'student_id' exceeds maximum length.");
	}
	else if (student_id_length < STUDENT_ID_MIN_LENGTH) {
		throw std::invalid_argument("The 'student_id' exceeds minimum length.");
	}

	// 返回设置的学号
	return student_id;
}

std::string Student::correctCollegeName(const std::string college) const
{
	// 当学院名超出最大长度，
	// 仅显示部分内容，并用省略号显示
	if (college.length() > COLLEGE_NAME_MAX_LENGTH) {
		std::string college_with_omitted_char = college.substr(0, (COLLEGE_NAME_MAX_LENGTH - std::int8_t(3)));
		college_with_omitted_char.append("...");
		return college_with_omitted_char;
	}

	// 返回设置学院名
	return college;
}

std::string Student::correctClassroomName(const std::string classroom) const
{
	// 当班级名超出最大长度，
	// 仅显示部分内容，并用省略号显示
	if (classroom.length() > CLASSROOM_NAME_MAX_LENGTH) {
		std::string classroom_with_omitted_char = classroom.substr(0, (CLASSROOM_NAME_MAX_LENGTH - std::int8_t(3)));
		classroom_with_omitted_char.append("...");
		return classroom_with_omitted_char;
	}

	// 返回设置班级名
	return classroom;
}

// 支持默认打印信息
std::ostream& operator<<(std::ostream& os, const Student& stu)
{
	os << "姓名\t" << stu.name() << "\n"
		<< "性别\t" << stu.sex() << "\n"
		<< "生日\t" << stu.birthday(TimeOutputModel::Date) << "\n"
		<< "入学\t" << stu.admission_date(TimeOutputModel::Date) << "\n"
		<< "毕业\t" << stu.expected_graduation_date(TimeOutputModel::Date) << "\n"
		<< "学号\t" << stu.student_id() << "\n"
		<< "学院\t" << stu.college() << "\n"
		<< "班级\t" << stu.classroom();
	return os;
}

// 只支持修改“学院”、“班级”的信息
std::istream& operator>>(std::istream& is, Student& stu)
{
	// 定义对应的缓冲区
	std::string college_buffer;
	std::string classroom_buffer;

	std::cout << "学院: ";
	is >> college_buffer;
	if (stu.checkCollegeName(college_buffer))
	{
		throw std::invalid_argument("College name is not valid.");
	}
	else
	{
		stu._college = college_buffer;
	}

	std::cout << "班级: ";
	is >> classroom_buffer;
	if (stu.checkClassroomName(classroom_buffer))
	{
		throw std::invalid_argument("Classroom name is not valid.");
	}
	else
	{
		stu._classroom = classroom_buffer;
	}

	return is;
}
