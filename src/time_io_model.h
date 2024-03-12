#ifndef TIME_IO_MODEL_H_
#define TIME_IO_MODEL_H_

#include <iostream>
#include <stdexcept>
#include <ctime>

class TimeInputModel {
public:
	/// <summary>
	/// ��ȡ�ض�ʱ��� std::time_t ֵ��
	/// </summary>
	/// <param name="year">�� [1900, 9999]</param>
	/// <param name="month">�� [1, 12]</param>
	/// <param name="day">�� [1, 31]</param>
	/// <param name="hour">ʱ [0, 23]</param>
	/// <param name="minute">�� [0, 59]</param>
	/// <param name="second">�� [0, 59]</param>
	/// <returns>��Ӧʱ��� time_t ֵ</returns>
	static std::time_t InputFormatTime(
		const std::int32_t year = 1900,
		const std::int32_t month = 1,
		const std::int32_t day = 1,
		const std::int32_t hour = 0,
		const std::int32_t minute = 0,
		const std::int32_t second = 0
	);
private:
	static int GetMaxDaysInMonth(int year, int month);
};

class TimeOutputModel
{
public:
	static const std::int8_t
		Year = 0b00000001,				// 0x01
		Month = 0b00000010,				// 0x02
		Day = 0b00000100,				// 0x04
		Hour = 0b00001000,				// 0x08
		Minute = 0b00010000,			// 0x10
		Second = 0b00100000,			// 0x20
		Weekday = 0b01000000,			// 0x40
		Date = Year | Month | Day,		// 0x07
		Time = Hour | Minute | Second,	// 0x38
		All = Date | Time | Weekday;	// 0x7F

	/// <summary>
	/// ��ʽ�������ַ���
	/// </summary>
	/// <param name="time_info">����������Ϣ�� tm �ṹ��</param>
	/// <param name="ops">��ѡ�ֶεĿ�ѡ�������</param>
	/// <returns>�����ض���ѡ�ֶε������ַ���</returns>
	static std::string OutputFormatTime(const tm* time_info, const std::int8_t ops);
};

#endif // !TIME_IO_MODEL_H_
