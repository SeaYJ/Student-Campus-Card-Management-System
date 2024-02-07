#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>
#include <ctime>
#include "SPECIAL_DEFINITION_MACRO.h"
#include "time_output_model.h"

class Student
{
	// ���������������
	friend std::ostream& operator<<(std::ostream& os, const Student& stu);

	// ����������������
	friend std::istream& operator>>(std::istream& is, Student& stu);
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
		: kName(name.substr(0, NAME_MAX_LENGTH)),
		kSex(sex.substr(0, SEX_MAX_LENGTH)),
		kBirthday(birthday),
		kAdmissionDate(admission_date),
		kExpectedGraduationDate(egdate),
		kStudentID((std::log10(student_id) + 1 > STUDENT_ID_MAX_LENGTH ? -1 : student_id)),
		_college(college.substr(0, COLLEGE_NAME_MAX_LENGTH)),
		_classroom(classroom.substr(0, CLASSROOM_NAME_MAX_LENGTH))
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

	// һ�������ڶ�Ӧһ�ұ���֮ǰ
	// ��Ϊ�Ǿ�̬���Ա������˳���졣
	// ���� NAME_MAX_LENGTH ���� kName ֮�������ģ�
	// ��˵�������ʹ����ʱ�������ڣ���˴���δ�������Ϊ��
	//		����Դ�ڴ��� https://stackoverflow.com/users/7976805/yksisarvinen �İ���
	//		�������� https://stackoverflow.com/questions/77954668/c-list-initialization-is-not-working-as-expected
	const std::int8_t NAME_MAX_LENGTH = 15;				// kName ����󳤶�
	const std::int8_t SEX_MAX_LENGTH = 5;				// kSex ����󳤶�
	const std::int8_t STUDENT_ID_MAX_LENGTH = 15;		// kStudentID ����󳤶�
	const std::int8_t COLLEGE_NAME_MAX_LENGTH = 50;		// _college ����󳤶�
	const std::int8_t CLASSROOM_NAME_MAX_LENGTH = 50;	// _classroom ����󳤶�

	const std::string kName;					// ����
	const std::string kSex;						// �Ա�
	const std::time_t kBirthday;				// ��������
	const std::time_t kAdmissionDate;			// ��ѧ����
	const std::time_t kExpectedGraduationDate;	// Ԥ�Ʊ�ҵ����(������ҵ)
	const std::int64_t kStudentID;				// ѧ����
	std::string _college;						// ����ѧԺ
	std::string _classroom;						// �����༶

	// ��ʽ�������ַ���
	// ���ǰ��� ops ��Ҫ����Ҫ�Ŀ�ѡ�ֶν�����ϡ�ƴ��
	std::string FormatTime(const struct tm* time_info, const std::int8_t ops) const;
};

#endif // !STUDENT_H_
