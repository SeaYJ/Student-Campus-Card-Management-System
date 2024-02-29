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
	const struct tm* time_info = _localtime64(&(this->kBirthday));				// �����õ� tm �ṹ������

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

std::string Student::birthday(const std::int8_t ops) const
{
	const struct tm* time_info = _localtime64(&(this->kBirthday));				// �����õ� tm �ṹ������

	return TimeOutputModel::FormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
}

std::string Student::admission_date() const
{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// �����õ� tm �ṹ������

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

std::string Student::admission_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kAdmissionDate));			// �����õ� tm �ṹ������

	return TimeOutputModel::FormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
}

std::string Student::expected_graduation_date() const
{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// �����õ� tm �ṹ������

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

std::string Student::expected_graduation_date(const std::int8_t ops) const

{
	const struct tm* time_info = _localtime64(&(this->kExpectedGraduationDate));// �����õ� tm �ṹ������

	return TimeOutputModel::FormatTime(time_info, ops);							// ������ ops ȷ����ʱ���ִ����
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
	// ���ȼ��
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
	// �����ֳ�����󳤶ȣ�
	// ����ʾ�������ݣ�����ʡ�Ժ���ʾ
	if (name.length() > NAME_MAX_LENGTH) {
		std::string name_with_omitted_char = name.substr(0, (NAME_MAX_LENGTH - std::int8_t(3)));
		name_with_omitted_char.append("...");
		return name_with_omitted_char;
	}

	// ������������
	return name;
}

std::string Student::correctSex(const std::string sex) const
{
	// ���Ա𳬳���󳤶ȣ�
	// ����ʾ�������ݣ�����ʡ�Ժ���ʾ
	if (sex.length() > SEX_MAX_LENGTH) {
		std::string sex_with_omitted_char = sex.substr(0, (SEX_MAX_LENGTH - std::int8_t(3)));
		sex_with_omitted_char.append("...");
		return sex_with_omitted_char;
	}

	// ���������Ա�
	return sex;
}

std::int64_t Student::correctStudentID(const std::int64_t student_id) const
{
	std::int64_t student_id_length = std::int64_t(std::log10(student_id)) + std::int64_t(1);

	// ����ѧ��λ������
	if (student_id_length > STUDENT_ID_MAX_LENGTH) {
		// ��Ϊѧ���� Student ��� const ������ֻ�ܸ�ֵһ�Ρ�
		// ���ԣ�������õ�ֵ���󣬾�Ӧ��ֱ�������������Ĵ�����
		// ���򣬴���� student id ���޷����¸�ֵ
		throw std::invalid_argument("The 'student_id' exceeds maximum length.");
	}
	else if (student_id_length < STUDENT_ID_MIN_LENGTH) {
		throw std::invalid_argument("The 'student_id' exceeds minimum length.");
	}

	// �������õ�ѧ��
	return student_id;
}

std::string Student::correctCollegeName(const std::string college) const
{
	// ��ѧԺ��������󳤶ȣ�
	// ����ʾ�������ݣ�����ʡ�Ժ���ʾ
	if (college.length() > COLLEGE_NAME_MAX_LENGTH) {
		std::string college_with_omitted_char = college.substr(0, (COLLEGE_NAME_MAX_LENGTH - std::int8_t(3)));
		college_with_omitted_char.append("...");
		return college_with_omitted_char;
	}

	// ��������ѧԺ��
	return college;
}

std::string Student::correctClassroomName(const std::string classroom) const
{
	// ���༶��������󳤶ȣ�
	// ����ʾ�������ݣ�����ʡ�Ժ���ʾ
	if (classroom.length() > CLASSROOM_NAME_MAX_LENGTH) {
		std::string classroom_with_omitted_char = classroom.substr(0, (CLASSROOM_NAME_MAX_LENGTH - std::int8_t(3)));
		classroom_with_omitted_char.append("...");
		return classroom_with_omitted_char;
	}

	// �������ð༶��
	return classroom;
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
	if (stu.checkCollegeName(college_buffer))
	{
		throw std::invalid_argument("College name is not valid.");
	}
	else
	{
		stu._college = college_buffer;
	}

	std::cout << "�༶: ";
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
