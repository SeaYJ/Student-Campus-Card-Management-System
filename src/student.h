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
	// 只提供一个参数构造函数，
	// 并且禁止隐式类型转换
	explicit Student(
		std::string name,
		std::string sex,
		std::time_t birthday,
		std::time_t admission_date,
		std::time_t egdate,
		std::int64_t student_id,
		std::string college = "未分配",
		std::string classroom = "未分配"
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

	// 取函数
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

	// 存函数
	Student& set_college(const std::string college);
	Student& set_classroom(const std::string classroom);

private:
	DISALLOW_COPY_AND_ASSIGN(Student);

	const std::string kName;					// 姓名
	const std::string kSex;						// 性别
	const std::time_t kBirthday;				// 出生日期
	const std::time_t kAdmissionDate;			// 入学日期
	const std::time_t kExpectedGraduationDate;	// 预计毕业日期(正常毕业)
	const std::int64_t kStudentID;				// 学生号
	std::string _college;						// 所属学院
	std::string _classroom;						// 所属班级

	const std::int8_t COLLEGE_NAME_MAX_LENGTH = 50;
	const std::int8_t CLASSROOM_NAME_MAX_LENGTH = 50;

	// 格式化日期字符串
	// 就是按照 ops 的要求将需要的可选字段进行组合、拼接
	std::string FormatTime(const struct tm* time_info, const std::int8_t ops) const;
};

#endif // !STUDENT_H_
