#include "student.h"

Student::~Student()
{
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
	const struct tm *time_info = _localtime64(&(this->kBirthday));				// 解析得到 tm 结构体数据

	// 为了提高效率，这里直接采用最原始的方式进行格式化日期字符串
	// 实际后面的所有代码等同于：
	/* CPP 等效代码
	* return FormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 FormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string Student::birthday(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kBirthday));				// 解析得到 tm 结构体数据

	return FormatTime(time_info, ops);											// 返回由 ops 确定的时间字串组合
}

std::string Student::admission_date() const
{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// 解析得到 tm 结构体数据

	// 为了提高效率，这里直接采用最原始的方式进行格式化日期字符串
	// 实际后面的所有代码等同于：
	/* CPP 等效代码
	* return FormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 FormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string Student::admission_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// 解析得到 tm 结构体数据

	return FormatTime(time_info, ops);											// 返回由 ops 确定的时间字串组合
}

std::string Student::expected_graduation_date() const
{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// 解析得到 tm 结构体数据

	// 为了提高效率，这里直接采用最原始的方式进行格式化日期字符串
	// 实际后面的所有代码等同于：
	/* CPP 等效代码
	* return FormatTime(time_info, TimeOutputModel::All);
	*/
	// 在等效代码中因为经过 FormatTime 函数需要很多 if 判断，
	// 然后还要将每个字段进行组合（字符串拼接），
	// 我认为会花费不必要的时间！！！
	char buffer[128] = { 0 };													// 定义一个足够大的缓冲区
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// 格式化时间

	return std::string(buffer);													// 将字符数组转换为字符串并返回
}

std::string Student::expected_graduation_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// 解析得到 tm 结构体数据

	return FormatTime(time_info, ops);											// 返回由 ops 确定的时间字串组合
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
	if (college.length() > Student::COLLEGE_NAME_MAX_LENGTH) {
		throw std::invalid_argument("College name is too long.");
	}

	this->_college = college;
	return *this;
}

Student& Student::set_classroom(const std::string classroom)
{
	// 长度检查
	if (classroom.length() > Student::CLASSROOM_NAME_MAX_LENGTH) {
		throw std::invalid_argument("Classroom name is too long.");
	}

	this->_classroom = classroom;
	return *this;
}

/// <summary>
/// 格式化日期字符串
/// </summary>
/// <param name="time_info">包含日期信息的 tm 结构体</param>
/// <param name="ops">可选字段的可选参数组合</param>
/// <returns>包含特定可选字段的日期字符串</returns>
std::string Student::FormatTime(const tm* time_info, const std::int8_t ops) const
{
	std::string buffer = "";													// 返回值缓冲区
	char part_buffer[16];														// 可选时间字段缓冲区

	bool include_year = false;													// 是否包含“年”的字段
	bool include_month = false;													// 是否包含“月”的字段
	bool include_day = false;													// 是否包含“日”的字段
	bool include_hour = false;													// 是否包含“时”的字段
	bool include_minute = false;												// 是否包含“分”的字段
	bool include_second = false;												// 是否包含“秒”的字段
	bool include_weekday = false;												// 是否包含“周”的字段

	if (ops & TimeOutputModel::Year)											// 添加“年”字段
	{
		include_year = true;													// 修改标识符，表示该字段被包含在日期字串内

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			"%Y", 
			time_info
		);																		// 获取年
		buffer.append(part_buffer);												// 添加年字段
	}

	if (ops & TimeOutputModel::Month)											// 添加“月”字段
	{
		include_month = true;													// 修改标识符，表示该字段被包含在日期字串内

		bool include_date_separator = include_year;								// 计算是否需要添加“日期内分隔符”

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_date_separator ? "/%m" : "%m"), 
			time_info
		);																		// 获取月
		buffer.append(part_buffer);												// 添加月字段
	}

	if (ops & TimeOutputModel::Day)												// 添加“日”字段
	{
		include_day = true;														// 修改标识符，表示该字段被包含在日期字串内

		bool include_date_separator =
			include_year ||
			include_month;														// 计算是否需要添加“日期内分隔符”

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_date_separator ? "/%d" : "%d"), 
			time_info
		);																		// 获取日
		buffer.append(part_buffer);												// 添加日字段
	}

	if (ops & TimeOutputModel::Hour)											// 添加“时”字段
	{
		include_hour = true;													// 修改标识符，表示该字段被包含在日期字串内

		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;														// 计算是否需要添加“组间分隔符”
																				// 所谓“组间分隔符”即为Date、Time、Weekday三者间的分隔符

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_group_separator ? " %H" : "%H"), 
			time_info
		);																		// 获取时
		buffer.append(part_buffer);												// 添加时字段
	}

	if (ops & TimeOutputModel::Minute)											// 添加“分”字段
	{
		include_minute = true;													// 修改标识符，表示该字段被包含在日期字串内

		bool include_time_separator =
			include_hour;														// 计算是否需要添加“时间内分隔符”
		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;														// 计算是否需要添加“组间分隔符”

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_time_separator ? ":%M" : (include_group_separator ? " %M" : "%M")), 
			time_info
		);																		// 获取分
		buffer.append(part_buffer);												// 添加分字段
	}

	if (ops & TimeOutputModel::Second)											// 添加“秒”字段
	{
		include_second = true;													// 修改标识符，表示该字段被包含在日期字串内

		bool include_time_separator =
			include_hour ||
			include_minute;														// 计算是否需要添加“时间内分隔符”
		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;														// 计算是否需要添加“组间分隔符”

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_time_separator ? ":%S" : (include_group_separator ? " %S" : "%S")), 
			time_info
		);																		// 获取秒
		buffer.append(part_buffer);												// 添加秒字段
	}

	if (ops & TimeOutputModel::Weekday)											// 添加“周”字段
	{
		include_weekday = true;													// 修改标识符，表示该字段被包含在日期字串内

		bool include_group_separator =
			include_year ||
			include_month ||
			include_day ||
			include_hour ||
			include_minute ||
			include_second;														// 计算是否需要添加“组间分隔符”

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_group_separator ? " %A" : "%A"), 
			time_info
		);																		// 获取周
		buffer.append(part_buffer);												// 添加周字段
	}

	return buffer;																// 返回日期字符串
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
	if (college_buffer.length() > stu.COLLEGE_NAME_MAX_LENGTH)
	{
		throw std::invalid_argument("College name is too long.");
	} 
	else
	{
		stu._college = college_buffer;
	}

	std::cout << "班级: ";
	is >> classroom_buffer;
	if (classroom_buffer.length() > stu.CLASSROOM_NAME_MAX_LENGTH)
	{
		throw std::invalid_argument("College name is too long.");
	}
	else
	{
		stu._classroom = classroom_buffer;
	}

	return is;
}
