#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include "SPECIAL_DEFINITION_MACRO.h"
#include "time_output_model.h"
#include "student_card.h"

class Student
{
	// 重载输出流操作符
	friend std::ostream& operator<<(std::ostream& os, const Student& stu);

	// 重载输入流操作符
	friend std::istream& operator>>(std::istream& is, Student& stu);
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
		: kName(CorrectName(name)),
		kSex(CorrectSex(sex)),
		kBirthday(birthday),
		kAdmissionDate(admission_date),
		kExpectedGraduationDate(egdate),
		kStudentID(CorrectStudentID(student_id)),
		_college(CorrectCollegeName(college)),
		_classroom(CorrectClassroomName(classroom))
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

	// 检查函数
	bool CheckCollegeName(const std::string college) const;
	bool CheckClassroomName(const std::string classroom) const;

private:
	DISALLOW_COPY_AND_ASSIGN(Student);

	// 一定定义在对应一艘变量之前
	// 因为非静态类成员按声明顺序构造。
	// 由于 NAME_MAX_LENGTH 是在 kName 之后声明的，
	// 因此当您尝试使用它时它不存在，因此存在未定义的行为。
	//		——源于大佬 https://stackoverflow.com/users/7976805/yksisarvinen 的帮助
	//		——帖子 https://stackoverflow.com/questions/77954668/c-list-initialization-is-not-working-as-expected
	const std::int8_t NAME_MAX_LENGTH = 15;				// kName 的最大长度
	const std::int8_t SEX_MAX_LENGTH = 5;				// kSex 的最大长度
	const std::int8_t STUDENT_ID_MAX_LENGTH = 15;		// kStudentID 的最大长度
	const std::int8_t STUDENT_ID_MIN_LENGTH = 6;		// kStudentID 的最小长度
	const std::int8_t COLLEGE_NAME_MAX_LENGTH = 50;		// _college 的最大长度
	const std::int8_t CLASSROOM_NAME_MAX_LENGTH = 50;	// _classroom 的最大长度

	const std::string kName;					// 姓名
	const std::string kSex;						// 性别
	const std::time_t kBirthday;				// 出生日期
	const std::time_t kAdmissionDate;			// 入学日期
	const std::time_t kExpectedGraduationDate;	// 预计毕业日期(正常毕业)
	const std::int64_t kStudentID;				// 学生号
	std::string _college;						// 所属学院
	std::string _classroom;						// 所属班级

	StudentCard* _student_card;					// 校园卡

	// 纠错函数
	std::string CorrectName(const std::string name) const;
	std::string CorrectSex(const std::string sex) const;
	std::int64_t CorrectStudentID(const std::int64_t student_id) const;
	std::string CorrectCollegeName(const std::string college) const;
	std::string CorrectClassroomName(const std::string classroom) const;
};

#endif // !STUDENT_H_
