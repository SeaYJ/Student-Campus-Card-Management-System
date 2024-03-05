#include "main.h"
#include "student.h"


int main(int argc, char* argv[])
{
	std::string
		name = "��һһ���Բ��Բ��Բ��Բ��Բ��Բ��Բ���",
		sex = "Ů���Բ��Բ��Բ���",
		college = "�����ѧԺ���Բ��Բ��Բ���",
		classroom = "�����2101";
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
	//	s.set_college("�������ѧ�뼼��ѧԺ");
	//	s.set_classroom("�������ѧ�뼼��2101��");
	//}
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << std::endl;
	//}

	//std::cout
	//	<< "����\t" << s.name() << "\n"
	//	<< "�Ա�\t" << s.sex() << "\n"
	//	<< "����\t" << s.birthday() << "\n"
	//	<< "��ѧ\t" << s.admission_date(TimeOutputModel::Date | TimeOutputModel::Time) << "\n"
	//	<< "��ҵ\t" << s.expected_graduation_date(TimeOutputModel::Year | TimeOutputModel::Month | TimeOutputModel::Hour | TimeOutputModel::Minute | TimeOutputModel::Weekday) << "\n"
	//	<< "ѧ��\t" << s.student_id() << "\n"
	//	<< "ѧԺ\t" << s.college() << "\n"
	//	<< "�༶\t" << s.classroom() << std::endl;

	//std::cout << s << "\n";
	//std::cin >> s;
	//std::cout << s << "\n";

	StudentCard sd(student_id, admission_date, egdate);

	//boost::multiprecision::cpp_dec_float_50  A("10.211"),
	//	B("0.01");
	//std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(100) 
	//	<< "A\t" << A << "\n"
	//	<< "B\t" << B << "\n"
	//	<< "mod\t" << (boost::multiprecision::fmod(A, B)) << "\n";

	sd.set_balance(coin("50000"));
	std::cout << sd << "\n\n";
	try
	{
		sd.Pay(coin("10.02"));
		sd.Pay(coin("100.6"));
		sd.Pay(coin("500.74"));
		sd.Pay(coin("1000.11"));
		sd.Pay(coin("2000"));
		sd.Earn(coin("1900.12"));
		sd.Earn(coin("100.9"));
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << sd << "\n";

	std::stack<BillInfo> t = sd.all_expense_records();
	while (!t.empty()) {
		BillInfo a = t.top();
		std::cout << a << "\n\n";
		t.pop();
	}

	return 0;
}