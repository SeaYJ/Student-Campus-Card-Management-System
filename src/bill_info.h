#ifndef BILL_INFO_H_
#define BILL_INFO_H_

#include <iostream>
#include <string>
#include <ctime>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "SPECIAL_DEFINITION_MACRO.h"
#include "time_io_model.h"

#ifndef NAMESPACE_DEF_BOOSTMUL
#define NAMESPACE_DEF_BOOSTMUL
namespace boostMul = boost::multiprecision;
#endif // NAMESPACE_DEF_BOOSTMUL

#ifndef TYPE_DEF_COIN
#define TYPE_DEF_COIN
typedef boostMul::cpp_dec_float_50 coin;
#endif // !TYPED_EFL_COIN

typedef struct
{
	std::string bill_num;
	std::time_t date;
	coin amount;
} BillInfo;

// �������������
inline std::ostream& operator<<(std::ostream& os, const BillInfo& bill_info) {
	// ��� bill �ĸ����ֶε� os ����
	os << "�������\t" << bill_info.bill_num << "\n"
		<< "����ʱ��\t" << TimeOutputModel::OutputFormatTime(_localtime64(&(bill_info.date)), TimeOutputModel::All) << "\n"
		<< "���׽��\t" << bill_info.amount;

	return os;
}

#endif // !_BILL_INFO_H

