#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>
#include <ctime>
#include "SPECIAL_DEFINITION_MACRO.h"
#include "time_output_model.h"

class Student
{
public:
	// ֻ�ṩһ���������캯����
	// ���ҽ�ֹ��ʽ����ת��
	explicit Student(
		std::string name,
		std::string sex,
		std::time_t birthday,
		std::time_t admission_date,
		std::time_t egdate,
		std::int64_t student_id,
		std::string college = "δ����",
		std::string classroom = "δ����"
	)
		: kName(name),
		kSex(sex),
		kBirthday(birthday),
		kAdmissionDate(admission_date),
		kExpectedGraduationDate(egdate),
		kStudentID(student_id),
		_college(college),
		_classroom(classroom)
	{}

	~Student();

	// ȡ����
	std::string name() const;
	std::string sex() const;
	std::string birthday() const;
	std::string birthday(const std::int8_t ops) const;
	std::string admission_date() const;
	std::string admission_date(const std::int8_t ops) const;
	std::string expected_graduation_date() const;
	std::string expected_graduation_date(const std::int8_t ops) const;
	std::int64_t student_id() const;
	std::string college() const;
	std::string classroom() const;

	// �溯��
	Student& set_college(const std::string college);
	Student& set_classroom(const std::string classroom);

private:
	DISALLOW_COPY_AND_ASSIGN(Student);

	const std::string kName;					// ����
	const std::string kSex;						// �Ա�
	const std::time_t kBirthday;				// ��������
	const std::time_t kAdmissionDate;			// ��ѧ����
	const std::time_t kExpectedGraduationDate;	// Ԥ�Ʊ�ҵ����(������ҵ)
	const std::int64_t kStudentID;				// ѧ����
	std::string _college;						// ����ѧԺ
	std::string _classroom;						// �����༶

	const std::int8_t COLLEGE_NAME_MAX_LENGTH = 50;
	const std::int8_t CLASSROOM_NAME_MAX_LENGTH = 50;

	// ��ʽ�������ַ���
	// ���ǰ��� ops ��Ҫ����Ҫ�Ŀ�ѡ�ֶν�����ϡ�ƴ��
	std::string FormatTime(const struct tm* time_info, const std::int8_t ops) const;
};

#endif // !STUDENT_H_
