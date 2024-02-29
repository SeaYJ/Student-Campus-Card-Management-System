#include "main.h"
#include "student.h"


int main(int argc, char* argv[]) 
{
	std::string 
		name = "杨一一测试测试测试测试测试测试测试测试",
		sex = "女测试测试测试测试",
		college = "计算机学院测试测试测试测试",
		classroom = "计算机2101";
	std::time_t
		birthday,
		admission_date,
		egdate;
	std::int64_t student_id = 312122011012;

	time(&birthday);
	time(&admission_date);
	time(&egdate);

	Student s(
		name,
		sex,
		birthday,
		admission_date,
		egdate,
		student_id,
		college,
		classroom);

	//try
	//{
	//	s.set_college("计算机科学与技术学院");
	//	s.set_classroom("计算机科学与技术2101班");
	//}
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << std::endl;
	//}

	//std::cout
	//	<< "姓名\t" << s.name() << "\n"
	//	<< "性别\t" << s.sex() << "\n"
	//	<< "生日\t" << s.birthday() << "\n"
	//	<< "入学\t" << s.admission_date(TimeOutputModel::Date | TimeOutputModel::Time) << "\n"
	//	<< "毕业\t" << s.expected_graduation_date(TimeOutputModel::Year | TimeOutputModel::Month | TimeOutputModel::Hour | TimeOutputModel::Minute | TimeOutputModel::Weekday) << "\n"
	//	<< "学号\t" << s.student_id() << "\n"
	//	<< "学院\t" << s.college() << "\n"
	//	<< "班级\t" << s.classroom() << std::endl;
	
	std::cout << s << "\n";
	//std::cin >> s;
	//std::cout << s << "\n";

	StudentCard sd(student_id, admission_date, egdate);

	std::cout << sd << "\n";

	return 0;
}