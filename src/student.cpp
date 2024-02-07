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
	const struct tm *time_info = _localtime64(&(this->kBirthday));				// �����õ� tm �ṹ������

	// Ϊ�����Ч�ʣ�����ֱ�Ӳ�����ԭʼ�ķ�ʽ���и�ʽ�������ַ���
	// ʵ�ʺ�������д����ͬ�ڣ�
	/* CPP ��Ч����
	* return FormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� FormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string Student::birthday(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kBirthday));				// �����õ� tm �ṹ������

	return FormatTime(time_info, ops);											// ������ ops ȷ����ʱ���ִ����
}

std::string Student::admission_date() const
{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// �����õ� tm �ṹ������

	// Ϊ�����Ч�ʣ�����ֱ�Ӳ�����ԭʼ�ķ�ʽ���и�ʽ�������ַ���
	// ʵ�ʺ�������д����ͬ�ڣ�
	/* CPP ��Ч����
	* return FormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� FormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string Student::admission_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// �����õ� tm �ṹ������

	return FormatTime(time_info, ops);											// ������ ops ȷ����ʱ���ִ����
}

std::string Student::expected_graduation_date() const
{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// �����õ� tm �ṹ������

	// Ϊ�����Ч�ʣ�����ֱ�Ӳ�����ԭʼ�ķ�ʽ���и�ʽ�������ַ���
	// ʵ�ʺ�������д����ͬ�ڣ�
	/* CPP ��Ч����
	* return FormatTime(time_info, TimeOutputModel::All);
	*/
	// �ڵ�Ч��������Ϊ���� FormatTime ������Ҫ�ܶ� if �жϣ�
	// Ȼ��Ҫ��ÿ���ֶν�����ϣ��ַ���ƴ�ӣ���
	// ����Ϊ�Ứ�Ѳ���Ҫ��ʱ�䣡����
	char buffer[128] = { 0 };													// ����һ���㹻��Ļ�����
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S %A", time_info);		// ��ʽ��ʱ��

	return std::string(buffer);													// ���ַ�����ת��Ϊ�ַ���������
}

std::string Student::expected_graduation_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// �����õ� tm �ṹ������

	return FormatTime(time_info, ops);											// ������ ops ȷ����ʱ���ִ����
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
	// ���ȼ��
	if (college.length() > Student::COLLEGE_NAME_MAX_LENGTH) {
		throw std::invalid_argument("College name is too long.");
	}

	this->_college = college;
	return *this;
}

Student& Student::set_classroom(const std::string classroom)
{
	// ���ȼ��
	if (classroom.length() > Student::CLASSROOM_NAME_MAX_LENGTH) {
		throw std::invalid_argument("Classroom name is too long.");
	}

	this->_classroom = classroom;
	return *this;
}

/// <summary>
/// ��ʽ�������ַ���
/// </summary>
/// <param name="time_info">����������Ϣ�� tm �ṹ��</param>
/// <param name="ops">��ѡ�ֶεĿ�ѡ�������</param>
/// <returns>�����ض���ѡ�ֶε������ַ���</returns>
std::string Student::FormatTime(const tm* time_info, const std::int8_t ops) const
{
	std::string buffer = "";													// ����ֵ������
	char part_buffer[16];														// ��ѡʱ���ֶλ�����

	bool include_year = false;													// �Ƿ�������ꡱ���ֶ�
	bool include_month = false;													// �Ƿ�������¡����ֶ�
	bool include_day = false;													// �Ƿ�������ա����ֶ�
	bool include_hour = false;													// �Ƿ������ʱ�����ֶ�
	bool include_minute = false;												// �Ƿ�������֡����ֶ�
	bool include_second = false;												// �Ƿ�������롱���ֶ�
	bool include_weekday = false;												// �Ƿ�������ܡ����ֶ�

	if (ops & TimeOutputModel::Year)											// ��ӡ��ꡱ�ֶ�
	{
		include_year = true;													// �޸ı�ʶ������ʾ���ֶα������������ִ���

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			"%Y", 
			time_info
		);																		// ��ȡ��
		buffer.append(part_buffer);												// ������ֶ�
	}

	if (ops & TimeOutputModel::Month)											// ��ӡ��¡��ֶ�
	{
		include_month = true;													// �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_date_separator = include_year;								// �����Ƿ���Ҫ��ӡ������ڷָ�����

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_date_separator ? "/%m" : "%m"), 
			time_info
		);																		// ��ȡ��
		buffer.append(part_buffer);												// ������ֶ�
	}

	if (ops & TimeOutputModel::Day)												// ��ӡ��ա��ֶ�
	{
		include_day = true;														// �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_date_separator =
			include_year ||
			include_month;														// �����Ƿ���Ҫ��ӡ������ڷָ�����

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_date_separator ? "/%d" : "%d"), 
			time_info
		);																		// ��ȡ��
		buffer.append(part_buffer);												// ������ֶ�
	}

	if (ops & TimeOutputModel::Hour)											// ��ӡ�ʱ���ֶ�
	{
		include_hour = true;													// �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;														// �����Ƿ���Ҫ��ӡ����ָ�����
																				// ��ν�����ָ�������ΪDate��Time��Weekday���߼�ķָ���

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_group_separator ? " %H" : "%H"), 
			time_info
		);																		// ��ȡʱ
		buffer.append(part_buffer);												// ���ʱ�ֶ�
	}

	if (ops & TimeOutputModel::Minute)											// ��ӡ��֡��ֶ�
	{
		include_minute = true;													// �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_time_separator =
			include_hour;														// �����Ƿ���Ҫ��ӡ�ʱ���ڷָ�����
		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;														// �����Ƿ���Ҫ��ӡ����ָ�����

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_time_separator ? ":%M" : (include_group_separator ? " %M" : "%M")), 
			time_info
		);																		// ��ȡ��
		buffer.append(part_buffer);												// ��ӷ��ֶ�
	}

	if (ops & TimeOutputModel::Second)											// ��ӡ��롱�ֶ�
	{
		include_second = true;													// �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_time_separator =
			include_hour ||
			include_minute;														// �����Ƿ���Ҫ��ӡ�ʱ���ڷָ�����
		bool include_group_separator =
			include_year ||
			include_month ||
			include_day;														// �����Ƿ���Ҫ��ӡ����ָ�����

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_time_separator ? ":%S" : (include_group_separator ? " %S" : "%S")), 
			time_info
		);																		// ��ȡ��
		buffer.append(part_buffer);												// ������ֶ�
	}

	if (ops & TimeOutputModel::Weekday)											// ��ӡ��ܡ��ֶ�
	{
		include_weekday = true;													// �޸ı�ʶ������ʾ���ֶα������������ִ���

		bool include_group_separator =
			include_year ||
			include_month ||
			include_day ||
			include_hour ||
			include_minute ||
			include_second;														// �����Ƿ���Ҫ��ӡ����ָ�����

		strftime(
			part_buffer, 
			sizeof(part_buffer), 
			(include_group_separator ? " %A" : "%A"), 
			time_info
		);																		// ��ȡ��
		buffer.append(part_buffer);												// ������ֶ�
	}

	return buffer;																// ���������ַ���
}

// ֧��Ĭ�ϴ�ӡ��Ϣ
std::ostream& operator<<(std::ostream& os, const Student& stu)
{
	os << "����\t" << stu.name() << "\n"
		<< "�Ա�\t" << stu.sex() << "\n"
		<< "����\t" << stu.birthday(TimeOutputModel::Date) << "\n"
		<< "��ѧ\t" << stu.admission_date(TimeOutputModel::Date) << "\n"
		<< "��ҵ\t" << stu.expected_graduation_date(TimeOutputModel::Date) << "\n"
		<< "ѧ��\t" << stu.student_id() << "\n"
		<< "ѧԺ\t" << stu.college() << "\n"
		<< "�༶\t" << stu.classroom();
	return os;
}

// ֻ֧���޸ġ�ѧԺ�������༶������Ϣ
std::istream& operator>>(std::istream& is, Student& stu)
{
	// �����Ӧ�Ļ�����
	std::string college_buffer;
	std::string classroom_buffer;

	std::cout << "ѧԺ: ";
	is >> college_buffer;
	if (college_buffer.length() > stu.COLLEGE_NAME_MAX_LENGTH)
	{
		throw std::invalid_argument("College name is too long.");
	} 
	else
	{
		stu._college = college_buffer;
	}

	std::cout << "�༶: ";
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
